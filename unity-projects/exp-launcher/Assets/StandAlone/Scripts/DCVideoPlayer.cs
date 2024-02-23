

///***********************************************************************************
//** MIT License                                                                    **
//** Copyright (c) [2024] [Florian Lance]                                           **
//** Permission is hereby granted, free of charge, to any person obtaining a copy   **
//** of this software and associated documentation files (the "Software"), to deal  **
//** in the Software without restriction, including without limitation the rights   **
//** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
//** copies of the Software, and to permit persons to whom the Software is          **
//** furnished to do so, subject to the following conditions:                       **
//**                                                                                **
//** The above copyright notice and this permission notice shall be included in all **
//** copies or substantial portions of the Software.                                **
//**                                                                                **
//** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
//** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
//** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
//** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
//** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
//** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
//** SOFTWARE.                                                                      **
//************************************************************************************/

//// system
//using SA;
//using System;
//using System.Collections.Generic;
//using System.Runtime.InteropServices;

//// unity
//using UnityEngine;
//#if UNITY_EDITOR
//using UnityEditor;
//#endif
//using UnityEngine.Profiling;

//public class DLLDCVideoPlayer : SA.DLLCppImportSA {

//    // I/O
//    public bool load_from_file(string videoFilePath) {return load_from_file__dc_video_player(_handle, videoFilePath) == 1;}

//    // settings
//    public void set_looping_state(bool doLoops) {set_current_time__dc_video_player(_handle, doLoops ? 1 : 0);}

//    // getters
//    public float current_time_ms() { return current_time_ms__dc_video_player(_handle); }
//    public float duration_ms() {return duration_ms__dc_video_player(_handle);}
//    public int cameras_count() {return cameras_count__dc_video_player(_handle);}
//    public int frames_count(int idCamera) {return frames_count__dc_video_player(_handle, idCamera);}
//    public int current_frame_id(int idCamera) {return current_frame_id__dc_video_player(_handle, idCamera);}    

//    // navigation
//    public void start_playing() { start_playing__dc_video_player(_handle);}
//    public void stop_playing() { stop_playing__dc_video_player(_handle); }
//    public void restart() {  restart__dc_video_player(_handle);}
//    public bool is_playing() { return is_playing__dc_video_player(_handle) == 1;}
//    public void set_current_time(float timeMs) { set_current_time__dc_video_player(_handle, timeMs); }
//    public void update() { update__dc_video_player(_handle); }

//    // data
//    public int get_current_frame_valid_vertices_count(int idCamera) { return get_current_frame_valid_vertices_count__dc_video_player(_handle, idCamera); }
//    public void get_transform(int idCamera, float[] transformData) {get_transform__dc_video_player(_handle, idCamera, transformData);}
//    public int copy_camera_cloud(int idCamera, SA.NativeDLLVerticesSA vertices, int verticesCount) {
//        int nbVerticesCopied = 0;
//        unsafe {
//            nbVerticesCopied = copy_camera_cloud__dc_video_player(_handle, idCamera, Unity.Collections.LowLevel.Unsafe.NativeArrayUnsafeUtility.GetUnsafePtr(vertices.native), verticesCount);
//        }
//        return nbVerticesCopied;
//    }

//    #region memory_management
//    protected override void create_DLL_class() {
//        _handle = new HandleRef(this, create__dc_video_player());
//    }

//    protected override void delete_DLL_class() {
//        delete__dc_video_player(_handle); 
//    }
//    #endregion

//    #region dll_import

//    [DllImport("base-export", EntryPoint = "create__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern IntPtr create__dc_video_player();
//    [DllImport("base-export", EntryPoint = "delete__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern void delete__dc_video_player(HandleRef dcPlayer);
//    [DllImport("base-export", EntryPoint = "load_from_file__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern int load_from_file__dc_video_player(HandleRef dcPlayer, string pathDcVideoFile);
//    [DllImport("base-export", EntryPoint = "set_looping_state__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern void set_looping_state__dc_video_player(HandleRef dcPlayer, int doLoops);
//    [DllImport("base-export", EntryPoint = "duration_ms__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern float duration_ms__dc_video_player(HandleRef dcPlayer);
//    [DllImport("base-export", EntryPoint = "cameras_count__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern int cameras_count__dc_video_player(HandleRef dcPlayer);
//    [DllImport("base-export", EntryPoint = "frames_count__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern int frames_count__dc_video_player(HandleRef dcPlayer, int idCamera);
//    [DllImport("base-export", EntryPoint = "current_frame_id__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern int current_frame_id__dc_video_player(HandleRef dcPlayer, int idCamera);
//    [DllImport("base-export", EntryPoint = "get_transform__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern void get_transform__dc_video_player(HandleRef dcPlayer, int idCamera, float[] transformData);

//    [DllImport("base-export", EntryPoint = "start_playing__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static public extern void start_playing__dc_video_player(HandleRef dcPlayer);
//    [DllImport("base-export", EntryPoint = "stop_playing__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static public extern void stop_playing__dc_video_player(HandleRef dcPlayer);
//    [DllImport("base-export", EntryPoint = "restart__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static public extern void restart__dc_video_player(HandleRef dcPlayer);
//    [DllImport("base-export", EntryPoint = "is_playing__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static public extern int is_playing__dc_video_player(HandleRef dcPlayer);
//    [DllImport("base-export", EntryPoint = "set_current_time__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static public extern void set_current_time__dc_video_player(HandleRef dcPlayer, float timeMs);
//    [DllImport("base-export", EntryPoint = "current_time_ms__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static public extern float current_time_ms__dc_video_player(HandleRef dcPlayer);
//    [DllImport("base-export", EntryPoint = "update__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static public extern void update__dc_video_player(HandleRef dcPlayer);
//    [DllImport("base-export", EntryPoint = "get_current_frame_valid_vertices_count__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    static public extern int get_current_frame_valid_vertices_count__dc_video_player(HandleRef dcPlayer, int idCamera);
//    [DllImport("base-export", EntryPoint = "copy_camera_cloud__dc_video_player", CallingConvention = CallingConvention.Cdecl)]
//    unsafe static public extern int copy_camera_cloud__dc_video_player(HandleRef dcPlayer, int idCamera, void* vertices, int verticesCount);

//    #endregion
//}


//#if UNITY_EDITOR

//[CustomEditor(typeof(DCVideoPlayer))]
//public class DCVideoPlayerEditor : Editor{

//    private DCVideoPlayer dcVideoPlayer { get { return target as DCVideoPlayer; } }

//    public override bool RequiresConstantRepaint() {
//        return true;
//    }

//    public override void OnInspectorGUI() {

//        base.OnInspectorGUI();

//        if (!Application.isPlaying) {
//            return;
//        }

//        EditorGUILayout.Separator();
        

//        EditorGUILayout.BeginHorizontal();
//        EditorGUILayout.LabelField("Video file path: ");
//        dcVideoPlayer.videoFilePath = EditorGUILayout.TextField(dcVideoPlayer.videoFilePath);
//        if (GUILayout.Button("Load video")) {
//            dcVideoPlayer.load_video_from_file(dcVideoPlayer.videoFilePath);
//        }
//        EditorGUILayout.EndHorizontal();

//        EditorGUILayout.BeginHorizontal();
//        if (!dcVideoPlayer.is_playing()) {
//            if (GUILayout.Button("Play")) {
//                dcVideoPlayer.start_playing();
//            }
//        } else {
//            if (GUILayout.Button("Stop")) {
//                dcVideoPlayer.stop_playing();
//            }
//        }
//        if (GUILayout.Button("Restart")) {
//            dcVideoPlayer.restart();
//        }

//        EditorGUILayout.EndHorizontal();

//        float durationMs = dcVideoPlayer.duration_ms();
//        float currentTimeMs = dcVideoPlayer.current_time_ms();
//        EditorGUILayout.LabelField("Video duration: " + durationMs + "ms");

//        EditorGUILayout.BeginHorizontal();
//        EditorGUILayout.LabelField("Current time: " + currentTimeMs + "ms");

//        float currentFactor = currentTimeMs / durationMs;
//        float newFactor = EditorGUILayout.Slider(currentFactor, 0f, 1f);
//        if(newFactor != currentFactor) {
//            dcVideoPlayer.set_current_time(newFactor * durationMs);
//            if (!dcVideoPlayer.is_playing()) {
//                dcVideoPlayer.update();
//            }
//        }
//        EditorGUILayout.EndHorizontal();
//    }
//}
//#endif


//public class DCVideoPlayer : MonoBehaviour{

//    public string videoFilePath = "";
//    public bool loadAtStart = true;    
//    public bool playAtStart = true;

//    public List<int> currentCamerasFrameId = new List<int>();
//    public Material coloredCloudMaterial = null;
//    public List<GameObject> coloredClouds = new List<GameObject>();

//    private DLLDCVideoPlayer m_player;
//    private SA.NativeIndicesSA indices = null;
//    private List<SA.NativeDLLVerticesSA> cloudsVertices = new List<SA.NativeDLLVerticesSA>();
//    private bool m_videoLoaded = false;

//    #region public_functions
//    public bool load_video_from_file(string videoFilePath) {
//        if (m_player.load_from_file(videoFilePath)) {

//            int nbCameras = m_player.cameras_count();

//            coloredClouds = new List<GameObject>(nbCameras);
//            currentCamerasFrameId = new List<int>(nbCameras);

//            if (cloudsVertices.Count != nbCameras) {

//                foreach (var cloudVertices in cloudsVertices) {
//                    cloudVertices.clean();
//                }

//                cloudsVertices = new List<SA.NativeDLLVerticesSA>(nbCameras);
//            }

//            for (int idC = 0; idC < nbCameras; ++idC) {
//                var coloredCloudGO = new GameObject();
//                coloredCloudGO.transform.SetParent(transform);
//                coloredCloudGO.name = "Colored cloud " + idC;
//                coloredCloudGO.transform.localPosition = Vector3.zero;
//                coloredCloudGO.transform.localRotation = Quaternion.identity;
//                coloredCloudGO.transform.localScale = Vector3.one;

//                var pc = coloredCloudGO.AddComponent<SA.PointCloudSA>();
//                pc.set_as_dynamic();
//                pc.set_rendering(SA.PointCloudSA.RenderingType.ParabloidGeo);                

//                float[] m = new float[16];
//                m_player.get_transform(idC, m);

//                var mat4= new Matrix4x4(
//                    new Vector4(m[0],  m[1],  m[2],  0), // c0
//                    new Vector4(m[4],  m[5],  m[6],  0), // c1
//                    new Vector4(m[8],  m[9],  m[10], 0), // c2
//                    new Vector4(m[12], m[13], m[14], 1)  // c3
//                );

//                coloredCloudGO.transform.localRotation = mat4.rotation;
//                coloredCloudGO.transform.localPosition = mat4.GetPosition();

//                coloredClouds.Add(coloredCloudGO);
//                cloudsVertices.Add(new SA.NativeDLLVerticesSA(400000));
//                currentCamerasFrameId.Add(-1);
//            }

//            return m_videoLoaded = true;
//        }
//        return m_videoLoaded = false;
//    }

//    public bool is_loaded() { return m_videoLoaded; }
//    public void start_playing() {m_player.start_playing();}
//    public void stop_playing() {m_player.stop_playing();}
//    public void restart() { m_player.restart();}
//    public bool is_playing() { return m_player.is_playing();}
//    public void set_current_time(float timeMs) { m_player.set_current_time(timeMs); }
//    public float duration_ms() {return m_player.duration_ms();}
//    public float current_time_ms() { return m_player.current_time_ms(); }

//    public void update() {

//        // store current frames id before updating
//        for (int idC = 0; idC < m_player.cameras_count(); idC++) {
//            currentCamerasFrameId[idC] = m_player.current_frame_id(idC);
//        }

//        Profiler.BeginSample("[DCVideoPlayer::update] Player update");        
//        m_player.update();
//        Profiler.EndSample();

//        for (int idC = 0; idC < m_player.cameras_count(); idC++) {
//            if (currentCamerasFrameId[idC] != m_player.current_frame_id(idC)) {
//                int nbVerticesCopied = m_player.copy_camera_cloud(idC, cloudsVertices[idC], m_player.get_current_frame_valid_vertices_count(idC));
//                Debug.Log("-> " + nbVerticesCopied);
//                var pc = coloredClouds[idC].GetComponent<SA.PointCloudSA>();
//                Profiler.BeginSample("[DCVideoPlayer::update] Set points cloud");
//                pc.set_points(cloudsVertices[idC], indices, nbVerticesCopied);
//                Profiler.EndSample();
//            }
//        }
//    }

//    #endregion

//    private void Awake() {
//        m_player = new DLLDCVideoPlayer();
//        SA.PointCloudSA.pointCloudMat = coloredCloudMaterial;
//        indices = new NativeIndicesSA(400000);
//    }

//    void Start(){
//        if (loadAtStart) {
//            load_video_from_file(videoFilePath);
//        }
//        if (is_loaded() && playAtStart) {
//            start_playing();
//        }
//    }

//    void Update(){
       
//        if (!is_playing()) {
//            return;
//        }
//        update();        
//    }

//    private void OnDestroy() {
//        indices.clean();
//        foreach(var cloudVertices in  cloudsVertices) {
//            cloudVertices.clean();
//        }
//    }
//}

