
/***********************************************************************************
** MIT License                                                                    **
** Copyright (c) [2024] [Florian Lance]                                           **
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
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Threading;
using System.Diagnostics;

// unity
using UnityEngine;
using UnityEngine.Profiling;
#if UNITY_EDITOR
using UnityEditor;
#endif

namespace Ex {

    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void NewFeedbackCB(int idC, int messageType, int feedbackType);

    public class DLLDCNetworkDirectPlayer : DLLCppImport {

        public void init_callbacks(NewFeedbackCB newFeedbackCB) {
            init_callbacks__dc_network_direct_player(_handle, newFeedbackCB);
        }

        public bool initialize(string networkSettingsFilePath) {
            return initialize__dc_network_direct_player(_handle, networkSettingsFilePath) == 1;
        }

        public int read_network_data(int idD) {
            return read_network_data__dc_network_direct_player(_handle, idD);
        }

        public bool uncompress_frame(int idD) {
            return uncompress_frame__dc_network_direct_player(_handle, idD) == 1;
        }

        // actions
        public void connect_to_devices() {
            connect_to_devices__dc_network_direct_player(_handle);
        }

        public void disconnect_from_devices() {
            disconnect_from_devices__dc_network_direct_player(_handle);
        }

        // states
        public int devices_nb() {
            return devices_nb__dc_network_direct_player(_handle);
        }
        public bool is_device_connected(int idD) {
            return is_device_connected__dc_network_direct_player(_handle, idD) == 1;
        }
        public int current_frame_id(int idD) {
            return current_frame_id__dc_network_direct_player(_handle, idD);
        }
        public int current_frame_cloud_size(int idD) {
            return current_frame_cloud_size__dc_network_direct_player(_handle, idD);
        }

        // settings
        public bool update_device_settings(string deviceSettingsFilePath) {
            return update_device_settings__dc_network_direct_player(_handle, deviceSettingsFilePath) == 1;
        }
        public bool update_color_settings(string colorSettingsFilePath) {
            return update_color_settings__dc_network_direct_player(_handle, colorSettingsFilePath) == 1;
        }
        public bool update_filters_settings(string filtersSettingsFilePath) {
            return update_filters_settings__dc_network_direct_player(_handle, filtersSettingsFilePath) == 1;
        }
        public bool update_model_settings(string modelSettingsFilePath) {
            return update_model_settings__dc_network_direct_player(_handle, modelSettingsFilePath) == 1;
        }

        // data
        public void copy_transform(int idD, float[] transformData) {
            copy_transform__dc_network_direct_player(_handle, idD, transformData);
        }
        public int copy_current_frame_vertices(int idD, NativeDLLVertices vertices, int verticesCount, bool applyModelTransform) {
            int nbVerticesCopied = 0;
            unsafe {
                nbVerticesCopied = copy_current_frame_vertices__dc_network_direct_player(
                    _handle,
                    idD,
                    Unity.Collections.LowLevel.Unsafe.NativeArrayUnsafeUtility.GetUnsafePtr(vertices.native),
                    verticesCount,
                    applyModelTransform ? 1 : 0
                );
            }
            return nbVerticesCopied;
        }


        #region memory_management
        protected override void create_DLL_class() {
            _handle = new HandleRef(this, create__dc_network_direct_player());
        }

        protected override void delete_DLL_class() {
            delete__dc_network_direct_player(_handle);
        }
        #endregion

        #region dll_import

        [DllImport("base-export", EntryPoint = "create__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern IntPtr create__dc_network_direct_player();
        [DllImport("base-export", EntryPoint = "delete__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern void delete__dc_network_direct_player(HandleRef dcNetworkDirectPlayer);

        [DllImport("base-export", EntryPoint = "init_callbacks__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern void init_callbacks__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, [MarshalAs(UnmanagedType.FunctionPtr)] NewFeedbackCB newFeedbackCB);

        [DllImport("base-export", EntryPoint = "initialize__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern int initialize__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, string networkSettingsFilePath);

        [DllImport("base-export", EntryPoint = "read_network_data__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern int read_network_data__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, int idD);

        [DllImport("base-export", EntryPoint = "uncompress_frame__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern int uncompress_frame__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, int idD);

        // actions
        [DllImport("base-export", EntryPoint = "connect_to_devices__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern void connect_to_devices__dc_network_direct_player(HandleRef dcNetworkDirectPlayer);
        [DllImport("base-export", EntryPoint = "disconnect_from_devices__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern void disconnect_from_devices__dc_network_direct_player(HandleRef dcNetworkDirectPlayer);

        // states
        [DllImport("base-export", EntryPoint = "devices_nb__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern int devices_nb__dc_network_direct_player(HandleRef dcNetworkDirectPlayer);
        [DllImport("base-export", EntryPoint = "is_device_connected__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern int is_device_connected__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, int idD);
        [DllImport("base-export", EntryPoint = "current_frame_id__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern int current_frame_id__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, int idD);
        [DllImport("base-export", EntryPoint = "current_frame_cloud_size__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern int current_frame_cloud_size__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, int idD);

        // settings
        [DllImport("base-export", EntryPoint = "update_device_settings__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern int update_device_settings__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, string deviceSettingsFilePath);
        [DllImport("base-export", EntryPoint = "update_color_settings__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern int update_color_settings__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, string colorSettingsFilePath);
        [DllImport("base-export", EntryPoint = "update_filters_settings__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern int update_filters_settings__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, string filtersSettingsFilePath);
        [DllImport("base-export", EntryPoint = "update_model_settings__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern int update_model_settings__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, string modelSettingsFilePath);

        // data
        [DllImport("base-export", EntryPoint = "copy_transform__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern void copy_transform__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, int idD, float[] transformData);
        [DllImport("base-export", EntryPoint = "copy_current_frame_vertices__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        unsafe static private extern int copy_current_frame_vertices__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, int idD, void* vertices, int verticesCount, int applyModelTransform);

        #endregion
    }

#if UNITY_EDITOR

    [CustomEditor(typeof(DCNetworkDirectPlayer))]
    public class DCNetworkDirectPlayerEditor : Editor {

        private DCNetworkDirectPlayer dcNetworkDIrectPlayer { get { return target as DCNetworkDirectPlayer; } }

        public override bool RequiresConstantRepaint() {
            return true;
        }

        public override void OnInspectorGUI() {

            base.OnInspectorGUI();

            var dcNDP = dcNetworkDIrectPlayer;
            var origFontStyle = EditorStyles.label.fontStyle;

            EditorGUILayout.Separator();

            EditorStyles.label.fontStyle = FontStyle.Bold;
            EditorGUILayout.LabelField("#### ACTIONS ####");
            EditorStyles.label.fontStyle = origFontStyle;

            EditorGUI.BeginDisabledGroup(!Application.isPlaying);

            EditorGUILayout.BeginHorizontal();
            if (GUILayout.Button("Connect all")) {
                dcNDP.connect_to_devices();
            }
            if (GUILayout.Button("Disconnect all")) {
                dcNDP.disconnect_from_devices();
            }
            EditorGUILayout.EndHorizontal();

            if (GUILayout.Button("Update device settings file")) {
                dcNDP.update_device_settings();
            }
            if (GUILayout.Button("Update filters settings file")) {
                dcNDP.update_filters_settings();
            }
            if (GUILayout.Button("Update color settings file")) {
                dcNDP.update_color_settings();
            }
            if (GUILayout.Button("Update model settings file")) {
                dcNDP.update_model_settings();
            }

            EditorGUI.EndDisabledGroup();
        }
    }
#endif

    public class ReadNetworkDataJob : ThreadedJob {

        public DLLDCNetworkDirectPlayer dllPlayer = null;
        public int idD = 0;
        public volatile bool doLoop = false;

        public void start_reading() {
            doLoop = true;
            start();
        }

        public void stop_reading() {
            doLoop = false;
            stop();
        }

        protected override void thread_function() {

            int totalPackedRead = 0;
            Thread.CurrentThread.Name = string.Concat("ReadNetworkData ", idD);
            Profiler.BeginThreadProfiling("ReadNetworkData", Thread.CurrentThread.Name);
            while (doLoop) {
                Profiler.BeginSample("[DCNetworkDirectPlayer::read_network_data]");
                int nbPackedRead = dllPlayer.read_network_data(idD);
                Profiler.EndSample();
                totalPackedRead += nbPackedRead;
            }
            Profiler.EndThreadProfiling();
        }
    }


    [Serializable]
    public class DeviceSettings {
        public bool display = true;
        public bool update = true;
        public Color tint = new Color(1f, 1f, 1f, 1f);
        public float pointSize = 0.005f;
        // states
        public bool connected = false;
        public int currentSize = 0;
        public int currentId = 0;
        public int cloudUpdated = 0;
        public int averageCloudUpdatedPerSecond = 0;
        public Stopwatch sw = new Stopwatch();
    }

    public class DCNetworkDirectPlayer : MonoBehaviour {

        [Header("#### INIT SETTINGS ####")]
        public bool initAtAwake = false;
        public bool loadDeviceSettingsAtAwake = false;
        public bool loadModelSettingsAwake = false;
        public bool loadFiltersSettingsAwake = false;
        public bool loadColorSettingsAtAwake = false;
        public bool connectAtStart = false;
        public bool readAtStart = false;

        [Header("#### SETTINGS FILES PATHS ####")]
        public string networkSettingsFilePath = "";
        public string deviceSettingsFilePath = "";
        public string colorSettingsFilePath = "";
        public string filtersSettingsFilePath = "";
        public string modelSettingsFilePath = "";

        [Header("#### CLOUDS SETTINGS #### ")]
        public Material cloudMaterial = null;
        public const int maximumNbOfDevices = 24;
        public const int maximumNbOfOBB = 4;
        public List<DeviceSettings> devicesSettings = new List<DeviceSettings>(maximumNbOfDevices);

        // data
        private bool m_initialized = false;
        private bool m_isReading = false;
        private List<int> m_idCameras = new List<int>();
        private List<int> m_nbVerticesToCopy = new List<int>();
        private List<GameObject> m_coloredClouds = new List<GameObject>();
        private DLLDCNetworkDirectPlayer m_dllPlayer = null;

        // jobs
        private List<ReadNetworkDataJob> m_readNetworkDataJobs = new List<ReadNetworkDataJob>();

        // native
        private NativeIndices m_indices = null;
        private List<NativeDLLVertices> m_cloudsVertices = new List<NativeDLLVertices>();

        // callbacks
        private static NewFeedbackCB newFeedbackCB = null;


        #region public_functions

        public bool initialize() {

            if (m_dllPlayer != null) {
                clean();
            }

            // init dll
            m_dllPlayer = new DLLDCNetworkDirectPlayer();
            m_dllPlayer.init_callbacks(newFeedbackCB);

            // send network config to dll    
            if (m_initialized = m_dllPlayer.initialize(networkSettingsFilePath)) {

                int nbDevices = devices_nb();

                // reset native vertices if necessary
                if (m_cloudsVertices.Count != nbDevices) {

                    foreach (var cloudVertices in m_cloudsVertices) {
                        cloudVertices.clean();
                    }

                    m_cloudsVertices = new List<NativeDLLVertices>(nbDevices);
                    for (int idC = 0; idC < nbDevices; ++idC) {
                        m_cloudsVertices.Add(new NativeDLLVertices(400000));
                    }
                }

                create_jobs(nbDevices);

                // init gameobjects / infos
                m_coloredClouds = new List<GameObject>(nbDevices);
                m_idCameras = new List<int>(nbDevices);
                m_nbVerticesToCopy = new List<int>(nbDevices);
                for (int idC = 0; idC < nbDevices; ++idC) {
                    m_idCameras.Add(idC);
                    m_nbVerticesToCopy.Add(0);
                    var coloredCloudGO = new GameObject();
                    coloredCloudGO.transform.SetParent(transform);
                    coloredCloudGO.name = "Colored cloud " + idC;
                    coloredCloudGO.transform.localPosition = Vector3.zero;
                    coloredCloudGO.transform.localRotation = Quaternion.identity;
                    coloredCloudGO.transform.localScale = Vector3.one;
                    coloredCloudGO.AddComponent<PointCloud>().set_as_dynamic();
                    m_coloredClouds.Add(coloredCloudGO);
                }
            }
            return m_initialized;
        }

        private void create_jobs(int nbDevices) {

            // read network data
            m_readNetworkDataJobs = new List<ReadNetworkDataJob>();
            for (int idC = 0; idC < nbDevices; ++idC) {
                var rndJob = new ReadNetworkDataJob();
                rndJob.dllPlayer = m_dllPlayer;
                rndJob.idD = idC;
                m_readNetworkDataJobs.Add(rndJob);
            }

        }

        public void clean() {

            if (m_dllPlayer != null) {

                // stop reading
                if (m_isReading) {
                    stop_reading();
                }

                // clean jobs
                m_readNetworkDataJobs = null;

                // disconnect devices
                disconnect_from_devices();

                // clean DLL
                m_dllPlayer.Dispose();
                m_dllPlayer = null;
            }
        }

        public void connect_to_devices() {
            if (m_dllPlayer != null) {
                m_dllPlayer.connect_to_devices();
            }
        }
        public void disconnect_from_devices() {
            if (m_dllPlayer != null) {
                m_dllPlayer.disconnect_from_devices();
            }
        }

        public void start_reading() {

            if (m_dllPlayer != null) {

                foreach (var deviceS in devicesSettings) {
                    deviceS.cloudUpdated = 0;
                    deviceS.averageCloudUpdatedPerSecond = 0;
                    deviceS.sw.Start();
                }

                foreach (var rndJob in m_readNetworkDataJobs) {
                    rndJob.start_reading();
                }

                m_isReading = true;
            }
        }

        public void stop_reading() {

            if (m_dllPlayer != null) {
                m_isReading = false;
                foreach (var rndJob in m_readNetworkDataJobs) {
                    rndJob.stop_reading();
                }

                foreach (var deviceS in devicesSettings) {
                    deviceS.sw.Stop();
                }
            }
        }

        public int devices_nb() {

            if (m_dllPlayer != null) {
                return m_dllPlayer.devices_nb();
            }
            return 0;
        }

        public int connected_devices_nb() {
            int countConnected = 0;
            for (int idD = 0; idD < devices_nb(); ++idD) {
                if (is_device_connected(idD)) {
                    ++countConnected;
                }
            }
            return countConnected;
        }
        public bool is_device_connected(int idD) {
            if (m_dllPlayer != null) {
                return m_dllPlayer.is_device_connected(idD);
            }
            return false;
        }
        public int current_frame_id(int idD) {
            if (m_dllPlayer != null) {
                return m_dllPlayer.current_frame_id(idD);
            }
            return 0;
        }
        public int current_frame_cloud_size(int idD) {
            if (m_dllPlayer != null) {
                return m_dllPlayer.current_frame_cloud_size(idD);
            }
            return 0;
        }

        public bool update_device_settings(string deviceSettingsFilePath = "") {

            if (deviceSettingsFilePath.Length > 0) {
                this.deviceSettingsFilePath = deviceSettingsFilePath.Replace('\\', '/');
            }

            if (m_dllPlayer != null) {
                return m_dllPlayer.update_device_settings(this.deviceSettingsFilePath);
            }
            return false;
        }
        public bool update_color_settings(string colorSettingsFilePath = "") {

            if (colorSettingsFilePath.Length > 0) {
                this.colorSettingsFilePath = colorSettingsFilePath.Replace('\\', '/');
            }

            if (m_dllPlayer != null) {
                return m_dllPlayer.update_color_settings(this.colorSettingsFilePath);
            }
            return false;
        }
        public bool update_filters_settings(string filtersSettingsFilePath = "") {

            if (filtersSettingsFilePath.Length > 0) {
                this.filtersSettingsFilePath = filtersSettingsFilePath.Replace('\\', '/');
            }

            if (m_dllPlayer != null) {
                return m_dllPlayer.update_filters_settings(this.filtersSettingsFilePath);
            }
            return false;
        }
        public bool update_model_settings(string modelSettingsFilePath = "") {

            if (modelSettingsFilePath.Length > 0) {
                this.modelSettingsFilePath = modelSettingsFilePath.Replace('\\', '/');
            }

            if (m_dllPlayer != null) {
                return m_dllPlayer.update_model_settings(this.modelSettingsFilePath);
            }
            return false;
        }

        public void update() {

            if (!m_isReading || (m_dllPlayer == null)) {
                return;
            }

            Profiler.BeginSample("[DCNetworkDirectPlayer::update] copy_camera_cloud");
            Parallel.ForEach(m_idCameras, idC => {
                if (m_dllPlayer.uncompress_frame(idC)) {

                    devicesSettings[idC].currentSize = m_dllPlayer.current_frame_cloud_size(idC);
                    devicesSettings[idC].currentId = m_dllPlayer.current_frame_id(idC);

                    m_dllPlayer.copy_current_frame_vertices(
                        idC,
                        m_cloudsVertices[idC],
                        devicesSettings[idC].currentSize,
                        true
                    );
                }
            });
            Profiler.EndSample();

            Profiler.BeginSample("[DCNetworkDirectPlayer::update] set_points");
            for (int idC = 0; idC < m_dllPlayer.devices_nb(); idC++) {
                if (devicesSettings[idC].update) {

                    var pc = m_coloredClouds[idC].GetComponent<PointCloud>();
                    pc.set_tint(devicesSettings[idC].tint);
                    pc.set_pt_size(devicesSettings[idC].pointSize);
                    pc.set_points(
                        m_cloudsVertices[idC],
                        m_indices,
                        devicesSettings[idC].currentSize
                    );

                    devicesSettings[idC].cloudUpdated++;
                    var timeS = devicesSettings[idC].sw.ElapsedMilliseconds / 1000f;
                    devicesSettings[idC].averageCloudUpdatedPerSecond = (int)(devicesSettings[idC].cloudUpdated / timeS);
                }

                m_coloredClouds[idC].GetComponent<MeshRenderer>().enabled = devicesSettings[idC].display;
            }
            Profiler.EndSample();
        }

        public void set_tint(int idC, Color color) {
            if (idC < m_coloredClouds.Count) {
                var pc = m_coloredClouds[idC].GetComponent<PointCloud>();
                pc.set_tint(devicesSettings[idC].tint = color);
            }
        }
        public void set_cloud_display_state(int idC, bool state) {
            if (idC < m_coloredClouds.Count) {
                m_coloredClouds[idC].GetComponent<MeshRenderer>().enabled = (devicesSettings[idC].display = state);
            }
        }
        public void set_cloud_update_state(int idC, bool state) {
            if (idC < m_coloredClouds.Count) {
                devicesSettings[idC].update = state;
            }
        }

        #endregion

        #region private_functions

        private void new_feedback(int idC, int messageType, int feedbackType) {


            string messageTypeStr;
            switch (messageType) {
                case 0:
                    messageTypeStr = "init_network_infos";
                    break;
                case 1:
                    messageTypeStr = "update_device_settings";
                    break;
                case 2:
                    messageTypeStr = "update_color_settings";
                    break;
                case 3:
                    messageTypeStr = "update_filters";
                    break;
                case 4:
                    messageTypeStr = "compressed_frame_data";
                    break;
                case 5:
                    messageTypeStr = "command";
                    break;
                case 6:
                    messageTypeStr = "feedback";
                    break;
                case 7:
                    messageTypeStr = "delay";
                    break;
                case 8:
                    messageTypeStr = "synchro";
                    break;
                case 9:
                    messageTypeStr = "ping";
                    break;
                default:
                    messageTypeStr = "invalid";
                    break;
            }

            string feedbackTypeStr;
            switch (feedbackType) {
                case 0:
                    feedbackTypeStr = "message_received";
                    break;
                case 1:
                    feedbackTypeStr = "timeout";
                    break;
                case 2:
                    feedbackTypeStr = "disconnect";
                    break;
                case 3:
                    feedbackTypeStr = "quit";
                    break;
                case 4:
                    feedbackTypeStr = "shutdown";
                    break;
                case 5:
                    feedbackTypeStr = "restart";
                    break;
                default:
                    feedbackTypeStr = "invalid";
                    break;
            }

            if (messageType == 0 && feedbackType == 0) {
                devicesSettings[idC].connected = true;
            }

            if (messageType == 6 && feedbackType == 2) {
                devicesSettings[idC].connected = false;
            }

            UnityEngine.Debug.Log(string.Format("Receive message of type [{0}] from device [{1}] with feeback [{2}] from Thread [{3}]", messageTypeStr, idC, feedbackTypeStr, Thread.CurrentThread.Name));
        }

        #endregion

        private void Awake() {

            // init callbacks
            newFeedbackCB = (int idC, int messageType, int feedbackType) => {
                new_feedback(idC, messageType, feedbackType);
            };

            //if (cloudMaterial != null) {
            //    PointCloud.pointCloudMat = cloudMaterial;
            //}

            // init natives indices
            m_indices = new NativeIndices(400000);

            for (int ii = 0; ii < maximumNbOfDevices; ++ii) {
                devicesSettings.Add(new DeviceSettings());
            }

            if (initAtAwake) {
                initialize();

                if (loadDeviceSettingsAtAwake) {
                    update_device_settings();
                }
                if (loadModelSettingsAwake) {
                    update_model_settings();
                }
                if (loadFiltersSettingsAwake) {
                    update_filters_settings();
                }
                if (loadColorSettingsAtAwake) {
                    update_color_settings();
                }
            }
        }


        private void Start() {
            if (connectAtStart) {
                connect_to_devices();
            }

            if (readAtStart) {
                start_reading();
            }
        }

        private void OnDestroy() {

            clean();

            // clean natives indices
            if (m_indices != null) {
                m_indices.clean();
            }

            // clean native vertices
            if (m_cloudsVertices != null) {
                foreach (var cloudVertices in m_cloudsVertices) {
                    cloudVertices.clean();
                }
            }
        }

        private void Update() {
            update();
        }
    }
}
