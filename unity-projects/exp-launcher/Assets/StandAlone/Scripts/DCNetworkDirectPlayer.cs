
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
//using Ex;
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
//using UnityEngine.UIElements;

//public class DLLDCNetworkDirectPlayer : Ex.DLLCppImport {

//    public bool initialize(string networkSettingsFilePath) {
//        return initialize__dc_network_direct_player(_handle, networkSettingsFilePath) == 1;
//    }

//    public void update() {
//        update__dc_network_direct_player(_handle);
//    }

//    // actions
//    public void connect_to_devices() {
//        connect_to_devices__dc_network_direct_player(_handle);
//    }

//    public void disconnect_from_devices() {
//        disconnect_from_devices__dc_network_direct_player(_handle);
//    }

//    public void start_reading() {
//        start_reading__dc_network_direct_player(_handle);
//    }

//    public void stop_reading() {
//        stop_reading__dc_network_direct_player(_handle);
//    }

//    // states
//    public int devices_nb() {
//        return devices_nb__dc_network_direct_player(_handle);
//    }
//    public bool is_device_connected(int idD) {
//        return is_device_connected__dc_network_direct_player(_handle, idD) == 1;
//    }
//    public int current_frame_id(int idD) {
//        return current_frame_id__dc_network_direct_player(_handle, idD);
//    }
//    public int current_frame_cloud_size(int idD) {
//        return current_frame_cloud_size__dc_network_direct_player(_handle, idD);
//    }

//    // settings
//    public bool update_device_settings(string deviceSettingsFilePath) {
//        return update_device_settings__dc_network_direct_player(_handle, deviceSettingsFilePath) == 1;
//    }
//    public bool update_color_settings(string colorSettingsFilePath) {
//        return update_color_settings__dc_network_direct_player(_handle, colorSettingsFilePath) == 1;
//    }
//    public bool update_filters_settings(string filtersSettingsFilePath) {
//        return update_filters_settings__dc_network_direct_player(_handle, filtersSettingsFilePath) == 1;
//    }
//    public bool update_model_settings(string modelSettingsFilePath) {
//        return update_model_settings__dc_network_direct_player(_handle, modelSettingsFilePath) == 1;
//    }

//    // data
//    public void copy_transform(int idD, float[] transformData) {
//        copy_transform__dc_network_direct_player(_handle, idD, transformData);
//    }
//    public int copy_current_frame_vertices(int idD, NativeDLLVerticesSA vertices, int verticesCount) {
//        int nbVerticesCopied = 0;
//        unsafe {
//            nbVerticesCopied = copy_current_frame_vertices__dc_network_direct_player(
//                _handle, 
//                idD, 
//                Unity.Collections.LowLevel.Unsafe.NativeArrayUnsafeUtility.GetUnsafePtr(vertices.native), 
//                verticesCount
//            );
//        }
//        return nbVerticesCopied;
//    }


//    #region memory_management
//    protected override void create_DLL_class() {
//        _handle = new HandleRef(this, create__dc_network_direct_player());
//    }

//    protected override void delete_DLL_class() {
//        delete__dc_network_direct_player(_handle);
//    }
//    #endregion

//    #region dll_import

//    [DllImport("base-export", EntryPoint = "create__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern IntPtr create__dc_network_direct_player();
//    [DllImport("base-export", EntryPoint = "delete__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern void delete__dc_network_direct_player(HandleRef dcNetworkDirectPlayer);

//    [DllImport("base-export", EntryPoint = "initialize__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern int initialize__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, string networkSettingsFilePath);

//    [DllImport("base-export", EntryPoint = "update__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern void update__dc_network_direct_player(HandleRef dcNetworkDirectPlayer);

//    // actions
//    [DllImport("base-export", EntryPoint = "connect_to_devices__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern void connect_to_devices__dc_network_direct_player(HandleRef dcNetworkDirectPlayer);
//    [DllImport("base-export", EntryPoint = "disconnect_from_devices__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern void disconnect_from_devices__dc_network_direct_player(HandleRef dcNetworkDirectPlayer);
//    [DllImport("base-export", EntryPoint = "start_reading__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern void start_reading__dc_network_direct_player(HandleRef dcNetworkDirectPlayer);
//    [DllImport("base-export", EntryPoint = "stop_reading__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern void stop_reading__dc_network_direct_player(HandleRef dcNetworkDirectPlayer);

//    // states
//    [DllImport("base-export", EntryPoint = "devices_nb__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern int devices_nb__dc_network_direct_player(HandleRef dcNetworkDirectPlayer);
//    [DllImport("base-export", EntryPoint = "is_device_connected__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern int is_device_connected__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, int idD);
//    [DllImport("base-export", EntryPoint = "current_frame_id__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern int current_frame_id__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, int idD);
//    [DllImport("base-export", EntryPoint = "current_frame_cloud_size__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern int current_frame_cloud_size__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, int idD);

//    // settings
//    [DllImport("base-export", EntryPoint = "update_device_settings__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern int update_device_settings__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, string deviceSettingsFilePath);
//    [DllImport("base-export", EntryPoint = "update_color_settings__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern int update_color_settings__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, string colorSettingsFilePath);
//    [DllImport("base-export", EntryPoint = "update_filters_settings__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern int update_filters_settings__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, string filtersSettingsFilePath);
//    [DllImport("base-export", EntryPoint = "update_model_settings__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern int update_model_settings__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, string modelSettingsFilePath);

//    // data
//    [DllImport("base-export", EntryPoint = "copy_transform__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    static private extern void copy_transform__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, int idD, float[] transformData);
//    [DllImport("base-export", EntryPoint = "copy_current_frame_vertices__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
//    unsafe static private extern int copy_current_frame_vertices__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, int idD, void* vertices, int verticesCount);

//    #endregion
//}



//#if UNITY_EDITOR

//[CustomEditor(typeof(DCNetworkDirectPlayer))]
//public class DCNetworkDirectPlayerEditor : Editor{

//    private DCNetworkDirectPlayer dcNetworkDIrectPlayer { get { return target as DCNetworkDirectPlayer; } }

//    public override bool RequiresConstantRepaint() {
//        return true;
//    }

//    public override void OnInspectorGUI() {

//        var dcNDP = dcNetworkDIrectPlayer;
//        var origFontStyle = EditorStyles.label.fontStyle;

//        EditorStyles.label.fontStyle = FontStyle.Bold;
//        EditorGUILayout.LabelField("######### PARAMETERS #########");
//        EditorStyles.label.fontStyle = origFontStyle;
//        EditorGUI.indentLevel++;
        

//        EditorGUILayout.LabelField("Settings files path:");
//        EditorGUI.indentLevel++;
//        {
//            EditorGUILayout.BeginVertical();
//            {                    
//                EditorGUILayout.BeginHorizontal();
//                {
//                    EditorGUI.BeginDisabledGroup(Application.isPlaying);
//                    EditorGUILayout.LabelField("Network: ");
//                    dcNetworkDIrectPlayer.networkSettingsFilePath = EditorGUILayout.TextField(dcNetworkDIrectPlayer.networkSettingsFilePath);
//                    EditorGUI.EndDisabledGroup();
//                }
//                EditorGUILayout.EndHorizontal();
//            }
//            {
//                EditorGUILayout.BeginHorizontal();
//                {
//                    EditorGUILayout.LabelField("Device: ");
//                    EditorGUI.BeginDisabledGroup(!Application.isPlaying);
//                    if (GUILayout.Button("Update")) {
//                        dcNetworkDIrectPlayer.update_device_settings(dcNetworkDIrectPlayer.deviceSettingsFilePath);
//                    }
//                    EditorGUI.EndDisabledGroup();
//                    dcNetworkDIrectPlayer.deviceSettingsFilePath = EditorGUILayout.TextField(dcNetworkDIrectPlayer.deviceSettingsFilePath);
//                }
//                EditorGUILayout.EndHorizontal();

//                EditorGUILayout.BeginHorizontal();
//                {
//                    EditorGUILayout.LabelField("Color: ");
//                    EditorGUI.BeginDisabledGroup(!Application.isPlaying);
//                    if (GUILayout.Button("Update")) {
//                        dcNetworkDIrectPlayer.update_color_settings(dcNetworkDIrectPlayer.colorSettingsFilePath);
//                    }
//                    EditorGUI.EndDisabledGroup();
//                    dcNetworkDIrectPlayer.colorSettingsFilePath = EditorGUILayout.TextField(dcNetworkDIrectPlayer.colorSettingsFilePath);    
//                }
//                EditorGUILayout.EndHorizontal();

//                EditorGUILayout.BeginHorizontal();
//                {
//                    EditorGUILayout.LabelField("Filters: ");
//                    EditorGUI.BeginDisabledGroup(!Application.isPlaying);
//                    if (GUILayout.Button("Update")) {
//                        dcNetworkDIrectPlayer.update_filters_settings(dcNetworkDIrectPlayer.filtersSettingsFilePath);
//                    }
//                    EditorGUI.EndDisabledGroup();
//                    dcNetworkDIrectPlayer.filtersSettingsFilePath = EditorGUILayout.TextField(dcNetworkDIrectPlayer.filtersSettingsFilePath);
//                }
//                EditorGUILayout.EndHorizontal();

//                EditorGUILayout.BeginHorizontal();
//                {
//                    EditorGUILayout.LabelField("Model: ");
//                    EditorGUI.BeginDisabledGroup(!Application.isPlaying);
//                    if (GUILayout.Button("Update")) {
//                        dcNetworkDIrectPlayer.update_model_settings(dcNetworkDIrectPlayer.modelSettingsFilePath);
//                    }
//                    EditorGUI.EndDisabledGroup();
//                    dcNetworkDIrectPlayer.modelSettingsFilePath = EditorGUILayout.TextField(dcNetworkDIrectPlayer.modelSettingsFilePath);
//                }
//                EditorGUILayout.EndHorizontal();
//            }
//            EditorGUILayout.EndVertical();
//        }
//        EditorGUI.indentLevel--;

//        EditorGUI.BeginDisabledGroup(Application.isPlaying);
//        EditorGUILayout.LabelField("Actions to do at start:");
//        EditorGUILayout.BeginHorizontal();
//        {
//            dcNDP.initAtStart = GUILayout.Toggle(dcNDP.initAtStart, "initialize");
//            dcNDP.readDataAtStart = GUILayout.Toggle(dcNDP.readDataAtStart, "read data");
//        }
//        EditorGUILayout.EndHorizontal();

//        EditorGUILayout.LabelField("Settings to send at start:");
//        EditorGUILayout.BeginHorizontal();
//        {
//            dcNDP.sendDeviceSettingsAtStart = GUILayout.Toggle(dcNDP.sendDeviceSettingsAtStart, "device");
//            dcNDP.sendFiltersSettingsAtStart = GUILayout.Toggle(dcNDP.sendFiltersSettingsAtStart, "filters");
//            dcNDP.sendColorSettingsAtStart = GUILayout.Toggle(dcNDP.sendColorSettingsAtStart, "color");
//            dcNDP.sendModelSettingsAtStart = GUILayout.Toggle(dcNDP.sendModelSettingsAtStart, "model");
//        }
//        EditorGUILayout.EndHorizontal();


//        EditorGUI.EndDisabledGroup();

//        EditorGUILayout.Separator();
//        EditorGUI.indentLevel--;

//        EditorStyles.label.fontStyle = FontStyle.Bold;
//        EditorGUILayout.LabelField("######### INFORMATIONS #########");
//        EditorStyles.label.fontStyle = origFontStyle;
//        EditorGUI.indentLevel++;

        

//        if (!Application.isPlaying) {
//            EditorGUILayout.LabelField("Press play to display runtime informations.");
//        } else {
//            EditorGUILayout.LabelField("Number of devices: " + dcNDP.devices_nb());
//            EditorGUILayout.LabelField("Number of devices connected: " + dcNDP.connected_devices_nb());

//            EditorGUILayout.LabelField("Informations per device:");
//            EditorGUI.indentLevel++;
//            EditorGUILayout.BeginVertical();
//            for (int idD = 0; idD < dcNDP.devices_nb(); ++idD) {
//                EditorGUILayout.LabelField(string.Format("Device n°{0}, frame id [{1}], cloud size [{2}]", idD, dcNDP.current_frame_id(idD), dcNDP.current_frame_cloud_size(idD)));
//            }
//            EditorGUILayout.EndVertical();
//            EditorGUI.indentLevel--;
//        }

        
//        EditorGUILayout.Separator();
//        EditorGUI.indentLevel--;

//        EditorStyles.label.fontStyle = FontStyle.Bold;
//        EditorGUILayout.LabelField("######### COMMANDS #########");
//        EditorStyles.label.fontStyle = origFontStyle;
//        EditorGUI.indentLevel++;


//        EditorGUI.BeginDisabledGroup(!Application.isPlaying);
//        EditorGUILayout.BeginHorizontal();
//        {
//            if (GUILayout.Button("Connect all")) {
//                dcNDP.connect_to_devices();
//            }
//            if (GUILayout.Button("Disconnect all")) {
//                dcNDP.disconnect_from_devices();
//            }
//            if (GUILayout.Button("Start reading")) {
//                dcNDP.start_reading();
//            }
//            if (GUILayout.Button("Stop reading")) {
//                dcNDP.stop_reading();
//            }
//        }
//        EditorGUILayout.EndHorizontal();
//        EditorGUI.EndDisabledGroup();
//        EditorGUI.indentLevel--;
//    }
//}
//#endif



//public class DCNetworkDirectPlayer : MonoBehaviour{

//    public bool initAtStart                 = true;
//    public bool readDataAtStart             = true;
//    public bool sendDeviceSettingsAtStart   = true;
//    public bool sendColorSettingsAtStart    = true;
//    public bool sendFiltersSettingsAtStart  = true;
//    public bool sendModelSettingsAtStart    = true;

//    public string networkSettingsFilePath = "";
//    public string deviceSettingsFilePath = "";
//    public string colorSettingsFilePath = "";
//    public string filtersSettingsFilePath = "";
//    public string modelSettingsFilePath = "";

//    public List<int> currentCamerasFrameId = new List<int>();
//    public Material coloredCloudMaterial = null;
//    public List<GameObject> coloredClouds = new List<GameObject>();

//    private DLLDCNetworkDirectPlayer m_player = null;
//    private NativeIndicesSA indices = null;
//    private List<NativeDLLVerticesSA> cloudsVertices = new List<NativeDLLVerticesSA>();
//    private bool m_initialized = false;
//    private bool m_isReading = false;
//    private bool m_setingsSended = false;

//    #region public_functions

//    public bool initialize() {
//        if (m_initialized = m_player.initialize(networkSettingsFilePath)) {

//            int nbDevices = devices_nb();
//            coloredClouds = new List<GameObject>(nbDevices);
//            currentCamerasFrameId = new List<int>(nbDevices);

//            if (cloudsVertices.Count != nbDevices) {

//                foreach (var cloudVertices in cloudsVertices) {
//                    cloudVertices.clean();
//                }

//                cloudsVertices = new List<NativeDLLVerticesSA>(nbDevices);
//            }

//            for (int idC = 0; idC < nbDevices; ++idC) {
//                var coloredCloudGO = new GameObject();
//                coloredCloudGO.transform.SetParent(transform);
//                coloredCloudGO.name = "Colored cloud " + idC;
//                coloredCloudGO.transform.localPosition = Vector3.zero;
//                coloredCloudGO.transform.localRotation = Quaternion.identity;
//                coloredCloudGO.transform.localScale = Vector3.one;

//                var pc = coloredCloudGO.AddComponent<PointCloud>();
//                pc.set_as_dynamic();
//                pc.set_rendering(PointCloud.RenderingType.ParabloidGeo);

//                float[] m = new float[16];
//                m_player.copy_transform(idC, m);

//                var mat4 = new Matrix4x4(
//                    new Vector4(m[0], m[1], m[2], 0), // c0
//                    new Vector4(m[4], m[5], m[6], 0), // c1
//                    new Vector4(m[8], m[9], m[10], 0), // c2
//                    new Vector4(m[12], m[13], m[14], 1)  // c3
//                );

//                coloredCloudGO.transform.localRotation = mat4.rotation;
//                coloredCloudGO.transform.localPosition = mat4.GetPosition();

//                coloredClouds.Add(coloredCloudGO);
//                cloudsVertices.Add(new NativeDLLVerticesSA(400000));
//                currentCamerasFrameId.Add(-1);
//            }
//        }
//        return m_initialized;
//    }

//    public void connect_to_devices() {m_player.connect_to_devices();}
//    public void disconnect_from_devices() {m_player.disconnect_from_devices();}

//    public void start_reading() {
//        m_player.start_reading();
//        m_isReading = true;
//    }

//    public void stop_reading() {
//        m_isReading = false;
//        m_player.stop_reading();
//    }

//    public int devices_nb() {return m_player.devices_nb();}

//    public int connected_devices_nb() {
//        int countConnected = 0;
//        for (int idD = 0; idD < devices_nb(); ++idD) {
//            if (is_device_connected(idD)) {
//                ++countConnected;
//            }
//        }
//        return countConnected;
//    }
//    public bool is_device_connected(int idD) {return m_player.is_device_connected(idD);}
//    public int current_frame_id(int idD) {return m_player.current_frame_id(idD);}
//    public int current_frame_cloud_size(int idD) {return m_player.current_frame_cloud_size(idD);}

//    public bool update_device_settings(string deviceSettingsFilePath = "") {
//        if(deviceSettingsFilePath.Length > 0) {
//            this.deviceSettingsFilePath = deviceSettingsFilePath;
//        }
//        return m_player.update_device_settings(this.deviceSettingsFilePath);
//    }
//    public bool update_color_settings(string colorSettingsFilePath = "") {
//        if (colorSettingsFilePath.Length > 0) {
//            this.colorSettingsFilePath = colorSettingsFilePath;
//        }
//        return m_player.update_color_settings(this.colorSettingsFilePath);
//    }
//    public bool update_filters_settings(string filtersSettingsFilePath = "") {
//        if (filtersSettingsFilePath.Length > 0) {
//            this.filtersSettingsFilePath = filtersSettingsFilePath;
//        }
//        return m_player.update_filters_settings(this.filtersSettingsFilePath);
//    }
//    public bool update_model_settings(string modelSettingsFilePath = "") {
//        if (modelSettingsFilePath.Length > 0) {
//            this.modelSettingsFilePath = modelSettingsFilePath;
//        }
//        return m_player.update_model_settings(this.modelSettingsFilePath);
//    }

//    public void update() {

//        // store current frames id before updating
//        for (int idC = 0; idC < m_player.devices_nb(); idC++) {
//            currentCamerasFrameId[idC] = m_player.current_frame_id(idC);
//        }

//        Profiler.BeginSample("[DCNetworkDirectPlayer::update] Player update");
//        m_player.update();
//        Profiler.EndSample();

//        for (int idC = 0; idC < m_player.devices_nb(); idC++) {
//            if (currentCamerasFrameId[idC] != m_player.current_frame_id(idC)) {
                
//                int nbVerticesCopied = m_player.copy_current_frame_vertices(idC, cloudsVertices[idC], current_frame_cloud_size(idC));
//                var pc = coloredClouds[idC].GetComponent<PointCloudSA>();
//                Profiler.BeginSample("[DCNetworkDirectPlayer::update] Set points cloud");
//                pc.set_points(cloudsVertices[idC], indices, nbVerticesCopied);
//                Profiler.EndSample();
//            }
//        }
//    }

//    #endregion

//    private void Awake() {
//        m_player = new DLLDCNetworkDirectPlayer();
//        indices = new NativeIndicesSA(400000);
//    }

//    void Start(){

//        if (initAtStart) {
//            initialize();
//        }

//        if (m_initialized) {
//            connect_to_devices();
//        }
//    }

//    void Update(){

//        if (!m_setingsSended) {
//            int countConnected = connected_devices_nb();
//            Debug.Log("devices connected: " + countConnected);
//            if(countConnected == devices_nb()) {

//                if (sendDeviceSettingsAtStart) {
//                    Debug.Log("update_device_settings: " + update_device_settings());
//                }
//                if (sendColorSettingsAtStart) {
//                    Debug.Log("update_color_settings: " + update_color_settings());
//                }
//                if (sendFiltersSettingsAtStart) {
//                    Debug.Log("update_filters_settings: " + update_filters_settings());
//                }
//                if (sendModelSettingsAtStart) {
//                    Debug.Log("update_model_settings: " + update_model_settings());
//                }

//                if (readDataAtStart) {
//                    Debug.Log("start_reading");
//                    start_reading();
//                }

//                m_setingsSended = true;
//            }
//        }

//        if (!m_isReading) {
//            return;
//        }

//        update();
//    }

//    private void OnDestroy() {

//        stop_reading();
//        disconnect_from_devices();

//        indices.clean();
//        foreach (var cloudVertices in cloudsVertices) {
//            cloudVertices.clean();
//        }
//    }
//}
