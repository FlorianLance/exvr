
/***********************************************************************************
** exvr-exp                                                                       **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

// system
using System.Threading.Tasks;
using System.Collections.Generic;

// unity
using UnityEngine;
using Unity.Collections;
using UnityEngine.Profiling;
using UnityEngine.Rendering;
using Ex;
using System.Threading;
using System.Diagnostics;

namespace SA {


    public class VolumetricVideoCameraDataSA {

        public int lastFrameId = -1;
        public VolumetricVideoCameraDataInfoSA info = null;
        public float[] audio = null;
        public AudioClip audioClip = null;
        public NativeDLLVerticesSA vertices = null;
    }

    public class ProcessVolumetricVideoComponentSA {


        class VolumetricVideoFrameInfosSA {
            public VolumetricVideoFrameInfosSA(
                DLLK4VolumetricVideoComponentSA cppDll, VolumetricVideoCameraDataSA data,
                int cameraId, int frameId, int nbValidVertices, PointCloudSA pc, NativeIndicesSA commonIndices) {
                this.cppDll = cppDll;
                this.data = data;
                this.cameraId = cameraId;
                this.frameId = frameId;
                this.nbVertices = nbValidVertices;
                this.pc = pc;
                this.commonIndices = commonIndices;
            }

            public DLLK4VolumetricVideoComponentSA cppDll = null;
            public VolumetricVideoCameraDataSA data = null;
            public int cameraId = 0;
            public int frameId = 0;
            public PointCloudSA pc = null;
            public NativeIndicesSA commonIndices = null;
            public int nbVertices = 0;
        }

        static bool processDone = false;
        static List<VolumetricVideoFrameInfosSA> framesToProcess = new List<VolumetricVideoFrameInfosSA>();

        public static void reset() {
            if (processDone) {
                processDone = false;
            }
        }

        public static void add_frame(
            DLLK4VolumetricVideoComponentSA cppDll, VolumetricVideoCameraDataSA data,
            int cameraId, int frameId, int nbValidVertices, PointCloudSA pc, NativeIndicesSA commonIndices) {
            framesToProcess.Add(new VolumetricVideoFrameInfosSA(cppDll, data, cameraId, frameId, nbValidVertices, pc, commonIndices));
        }

        public static void process_all() {

            if (processDone) {
                return;
            }

            Parallel.For(0, framesToProcess.Count, ii => {

                var dtp = framesToProcess[ii];
                Profiler.BeginSample("[ExVR][ProcessVolumetricVideoComponent] uncompress_frame");
                if (!dtp.cppDll.uncompress_frame(
                    dtp.cameraId,
                    dtp.frameId,
                    ref dtp.data.vertices.native
                )) {
                    UnityEngine.Debug.LogError("uncompress error");
                    return;
                }
                Profiler.EndSample();
                dtp.data.lastFrameId = dtp.frameId;
            });

            var layout = new[]{
                new VertexAttributeDescriptor(VertexAttribute.Position, VertexAttributeFormat.Float32, 3),
                new VertexAttributeDescriptor(VertexAttribute.Color, VertexAttributeFormat.UNorm8, 4)
            };

            for (int ii = 0; ii < framesToProcess.Count; ++ii) {
                var ftp = framesToProcess[ii];
                if (ftp.nbVertices >= 0) {
                    ftp.pc.set_points(ftp.data.vertices, ftp.commonIndices, ftp.nbVertices);
                }
            }

            processDone = true;
            framesToProcess.Clear();
        }
    }

    public class VolumetricVideoComponentSA : MonoBehaviour {

        private GameObject resourceGO = null;
        private VolumetricVideoResourceSA volumetricVideo = null;
        private List<VolumetricVideoCameraDataSA> dataPerCamera = null;
        private NativeIndicesSA indices = null;

        [Header("Path")]
        public string videoFilePath = "";

        [Header("Video settings")]
        public bool doVideoLoop = true;
        public float startTime = 0.0f;
        public float endTime = 10.0f;

        [Header("Audio settings")]
        public int audioIdChannel = 0;
        bool doAudioLoop = true;
        bool enableAudio = true;
        float audioVolume = 1f;

        [Header("Clouds rendering settings")]
        public bool displayClouds = true;
        public float sizePoints = 0.0030f;
        public bool removeOutside = false;
        public bool cones = true;
        public bool circles = true;
        public Color tintColor = new Color(1f, 1f, 1f, 0.0f);
        public PointCloudSA.ParabloidGeoDetails details = PointCloudSA.ParabloidGeoDetails.Hight;
        public PointCloudSA.RenderingType rendering = PointCloudSA.RenderingType.ParabloidGeo;

        [Header("Materials")]
        public Material m_oobbMaterial = null;
        public Material m_pointCloudMaterial = null;


        // OOBB rendering
        [Header("OOBB settings")]
        public bool displayFilteringObb = false;
        public List<OBBFInfoSA> m_OBBsInfo = null;

        [Header("States")]
        public GameObject m_parentCloudsGO = null;
        public List<GameObject> m_OBBsGO = null;
        public AudioSource audioSource = null;
        public List<PointCloudSA> clouds = null;
        public DLLK4VolumetricVideoComponentSA vvcDll = null;
        public GameObject m_OBBsParent = null;

        Stopwatch videoTimer = new Stopwatch();

        #region mono_behaviour

        private void Awake() {

            // init experiment DLL
            if (DLLExperimentSA.global == null) {
                DLLExperimentSA.global = new DLLExperimentSA();
            }
        }

        private void Start() {

            resourceGO = GOSA.generate_empty_object("video", null, true);
            volumetricVideo = resourceGO.AddComponent<VolumetricVideoResourceSA>();
            volumetricVideo.path = videoFilePath;
            volumetricVideo.alias = "video";

            if (!volumetricVideo.initialize()) {
                return;
            }

            // init manager DLL
            try {
                vvcDll = new DLLK4VolumetricVideoComponentSA(volumetricVideo.get_dll_handle());
            } catch (System.Exception exception) {
                UnityEngine.Debug.LogError(string.Format("Cannot create K4VolumetricVideo DLL, error: {0}", exception.Message));
                vvcDll = null;
                return;
            }
            vvcDll.expDll = DLLExperimentSA.global;
            bool success = vvcDll.initialize();
            if (!success) {
                UnityEngine.Debug.LogError("Cannot initialize K4VolumetricVideo DLL.");
                return;
            }

            // init parents GO
            m_parentCloudsGO = GOSA.generate_empty_scene_object("video_clouds", transform, true);
            

            // obb
            m_OBBsGO = new List<GameObject>(10);
            m_OBBsInfo = new List<OBBFInfoSA>(10);
            m_OBBsParent = GO.generate_empty_scene_object("OBBs", m_parentCloudsGO.transform, true);
            m_OBBsParent.transform.localPosition = Vector3.zero;
            m_OBBsParent.transform.localEulerAngles = Vector3.zero;
            m_OBBsParent.transform.localScale = Vector3.one;

            for (int ii = 0; ii < 10; ++ii) {   
                var obbGO = GOSA.generate_cube(Instantiate(m_oobbMaterial), "filtering obb", m_OBBsParent.transform, 1f, null, -1);
                obbGO.SetActive(false);
                m_OBBsGO.Add(obbGO);
                m_OBBsInfo.Add(new OBBFInfoSA());
            }

            // audio
            audioSource = gameObject.AddComponent<AudioSource>();
            audioSource.clip = null;
            audioSource.playOnAwake = false;
            audioSource.loop = false;
            audioSource.enabled = false;
            audioSource.spatialize = false;
            audioSource.minDistance = 0f;
            audioSource.maxDistance = 100000f;
            audioSource.panStereo = 0.5f;
            audioSource.volume = 1f;
            audioSource.spatialBlend = 0.5f;

            clouds = new List<PointCloudSA>(volumetricVideo.nbCameras);
            dataPerCamera = new List<VolumetricVideoCameraDataSA>(volumetricVideo.nbCameras);

            PointCloudSA.pointCloudMat = m_pointCloudMaterial;

            for (int ii = 0; ii < volumetricVideo.nbCameras; ++ii) {

                GameObject cloudGO = GO.generate_empty_scene_object("camera_" + ii, m_parentCloudsGO.transform, true);
                //GO.init_local_scaling(cloudGO, new Vector3(0.1f, 0.1f, 0.1f));

                // set point cloud
                var pc = cloudGO.AddComponent<PointCloudSA>();
                pc.set_as_dynamic();
                clouds.Add(pc);

                VolumetricVideoCameraDataSA data = new VolumetricVideoCameraDataSA();
                data.info = volumetricVideo.cameraDataInfo[ii];

                // set audio
                int sizeSamples = vvcDll.process_audio(ii);
                if (sizeSamples > 0) {
                    data.audio = new float[sizeSamples];
                    vvcDll.copy_audio_samples(ii, data.audio);
                    data.audioClip = AudioClip.Create("camera_" + ii, sizeSamples / 7, 7, 48000, false);
                    data.audioClip.SetData(data.audio, 0);
                } else {
                    UnityEngine.Debug.LogError(string.Format("No audio frames detected for camera [{0}].", ii));
                    data.audioClip = null;
                }

                // set vertices
                data.vertices = new NativeDLLVerticesSA(data.info.maxNbVertices);

                dataPerCamera.Add(data);
            }

            // apply calibration matrices
            for (int ii = 0; ii < volumetricVideo.nbCameras; ++ii) {
                clouds[ii].transform.localRotation = volumetricVideo.cameraDataInfo[ii].model.GetRotation();
                clouds[ii].transform.localPosition = volumetricVideo.cameraDataInfo[ii].model.GetPosition();
            }

            // generate indices
            indices = new NativeIndicesSA(volumetricVideo.maxNbVerticesAllCameras);

            if (audioIdChannel < dataPerCamera.Count) {
                audioSource.clip = dataPerCamera[audioIdChannel].audioClip;
            } else {
                audioSource.clip = dataPerCamera[0].audioClip;
            }

            GOSA.init_local_scaling(m_parentCloudsGO, new Vector3(-1, 1, 1)); // invert x scale 

            videoTimer.Start();
            if (audioSource.clip != null) {
                audioSource.Play();
            }

            update_from_settings();
            set_visibility(true);
            
        }


        public void set_visibility(bool visibility) {

            foreach (var cloudGO in clouds) {
                cloudGO.gameObject.SetActive(visibility && displayClouds);
            }

            for (int ii = 0; ii < m_OBBsGO.Count; ++ii) {
                m_OBBsGO[ii].SetActive(visibility && displayFilteringObb && m_OBBsInfo[ii].display);
            }
        }

        public void update_from_settings() {

            // obb
            for (int ii = 0; ii < m_OBBsGO.Count; ++ii) {
                ApplySA.to_transform(m_OBBsInfo[ii].transform, m_OBBsGO[ii].transform, false);

                m_OBBsGO[ii].transform.localScale *= -1f;
                var p = m_OBBsGO[ii].transform.position;
                var r = m_OBBsGO[ii].transform.rotation;
                m_OBBsGO[ii].transform.localScale *= -1f;

                m_OBBsInfo[ii].transform.position = p;
                m_OBBsInfo[ii].transform.rotation = r;

                m_OBBsGO[ii].GetComponent<MeshRenderer>().material.SetColor("_Color", m_OBBsInfo[ii].color);
            }

            // audio
            audioSource.loop    = doAudioLoop;
            audioSource.enabled = enableAudio;
            audioSource.volume  = audioVolume;

            // point cloud shading
            for (int ii = 0; ii < volumetricVideo.nbCameras; ++ii) {
                var pc = clouds[ii];
                pc.set_pt_size(sizePoints);
                pc.set_rendering(rendering);
                pc.set_circles_state(circles);
                pc.set_paraboloid_frag_cones_state(cones);
                pc.set_paraboloid_geo_details(details);
                pc.set_tint(tintColor);
                pc.set_obb_filtering_state(removeOutside);
                pc.set_filtering_obb_infos(m_OBBsInfo);
            }
        }


        public void Update() {

            ProcessVolumetricVideoComponentSA.reset();

            update_from_settings();

            var videoD = volumetricVideo.duration;
            float start = startTime * 1000f;
            float end   = endTime * 1000f;
            if (start > end) {
                start = end;
            }
            if (start > videoD) {
                start = videoD;
            }
            if (end > videoD) {
                end = videoD;
            }

            var duration = end - start;
            var currTime = videoTimer.Elapsed.TotalMilliseconds + start;
            if (currTime > duration) {
                if (!doVideoLoop) {
                    return;
                }
                float percentage = (float)(currTime - start) / duration;
                currTime = start + (percentage - System.Math.Truncate(percentage)) * duration;
            }

            for (int ii = 0; ii < volumetricVideo.nbCameras; ++ii) {
                update_time(ii, (float)currTime);
            }
        }

        public void LateUpdate() {
            ProcessVolumetricVideoComponentSA.process_all();
        }


        public void stop() {
            audioSource.Stop();
            videoTimer.Stop();
        }

        public void play() {
            audioSource.UnPause();
            videoTimer.Start();
        }

        public void pause() {
            audioSource.Pause();
            videoTimer.Stop();
        }

        public void OnDestroy() {
            clean();
        }

        #endregion
        #region private_functions

        private void clean() {

            if (indices != null) {
                indices.clean();
            }
            if (dataPerCamera != null) {
                foreach (var camData in dataPerCamera) {
                    camData.vertices.clean();
                }
            }
        }

        private void update_time(int cameraId, float timeMs) {
            
            var data = dataPerCamera[cameraId];

            int currentFrameId = volumetricVideo.id_frame_from_time(cameraId, timeMs);
            int nbValidVertices = volumetricVideo.nb_valid_vertices(cameraId, currentFrameId);
            if (currentFrameId != data.lastFrameId) {

                ProcessVolumetricVideoComponentSA.add_frame(
                    vvcDll,
                    data,
                    cameraId, currentFrameId, nbValidVertices,
                    clouds[cameraId],
                    indices
                );
            }
        }


        #endregion
    }
}

