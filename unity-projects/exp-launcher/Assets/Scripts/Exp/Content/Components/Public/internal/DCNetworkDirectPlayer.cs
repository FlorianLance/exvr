
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

// unity
using UnityEngine;
using UnityEngine.Profiling;
using System.Threading.Tasks;
using System.Diagnostics;

namespace Ex {

    public class DLLDCNetworkDirectPlayer : DLLCppImport {

        public bool initialize(string networkSettingsFilePath) {
            return initialize__dc_network_direct_player(_handle, networkSettingsFilePath) == 1;
        }

        public void update() {
            update__dc_network_direct_player(_handle);
        }

        // actions
        public void connect_to_devices() {
            connect_to_devices__dc_network_direct_player(_handle);
        }

        public void disconnect_from_devices() {
            disconnect_from_devices__dc_network_direct_player(_handle);
        }

        public void start_reading() {
            start_reading__dc_network_direct_player(_handle);
        }

        public void stop_reading() {
            stop_reading__dc_network_direct_player(_handle);
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

        [DllImport("base-export", EntryPoint = "initialize__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern int initialize__dc_network_direct_player(HandleRef dcNetworkDirectPlayer, string networkSettingsFilePath);

        [DllImport("base-export", EntryPoint = "update__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern void update__dc_network_direct_player(HandleRef dcNetworkDirectPlayer);

        // actions
        [DllImport("base-export", EntryPoint = "connect_to_devices__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern void connect_to_devices__dc_network_direct_player(HandleRef dcNetworkDirectPlayer);
        [DllImport("base-export", EntryPoint = "disconnect_from_devices__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern void disconnect_from_devices__dc_network_direct_player(HandleRef dcNetworkDirectPlayer);
        [DllImport("base-export", EntryPoint = "start_reading__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern void start_reading__dc_network_direct_player(HandleRef dcNetworkDirectPlayer);
        [DllImport("base-export", EntryPoint = "stop_reading__dc_network_direct_player", CallingConvention = CallingConvention.Cdecl)]
        static private extern void stop_reading__dc_network_direct_player(HandleRef dcNetworkDirectPlayer);

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


    public class DeviceSettings {
        public bool display = true;
        public bool update = true;
        public Color tint = new Color(1f, 1f, 1f, 1f);
    }

    public class DCNetworkDirectPlayer : MonoBehaviour {

        public int currentNbOfDevices = 4;
        public const int maximumNbOfDevices = 24;
        public List<DeviceSettings> devicesSettings = new List<DeviceSettings>(maximumNbOfDevices);

        public string networkSettingsFilePath = "";
        public string deviceSettingsFilePath = "";
        public string colorSettingsFilePath = "";
        public string filtersSettingsFilePath = "";
        public string modelSettingsFilePath = "";

        public List<int> currentCamerasFrameId = new List<int>();
        public Material coloredCloudMaterial = null;
        public List<GameObject> coloredClouds = new List<GameObject>();

        private DLLDCNetworkDirectPlayer m_dllPlayer = null;
        private NativeIndices indices = null;
        private List<NativeDLLVertices> cloudsVertices = new List<NativeDLLVertices>();
        private List<int> idCameras = new List<int>();
        private List<int> nbVerticesToCopy = new List<int>();
        private bool m_initialized = false;
        private bool m_isReading = false;

        #region public_functions

        public bool initialize() {

            if (m_initialized = m_dllPlayer.initialize(networkSettingsFilePath)) {
                int nbDevices           = devices_nb();
                coloredClouds           = new List<GameObject>(nbDevices);
                currentCamerasFrameId   = new List<int>(nbDevices);
                idCameras               = new List<int>(nbDevices);
                nbVerticesToCopy        = new List<int>(nbDevices);

                if (cloudsVertices.Count != nbDevices) {
                    foreach (var cloudVertices in cloudsVertices) {
                        cloudVertices.clean();
                    }
                    cloudsVertices = new List<NativeDLLVertices>(nbDevices);
                }

                for (int idC = 0; idC < nbDevices; ++idC) {
                    idCameras.Add(idC);
                    nbVerticesToCopy.Add(0);
                    var coloredCloudGO = new GameObject();
                    coloredCloudGO.transform.SetParent(transform);
                    coloredCloudGO.name = "Colored cloud " + idC;
                    coloredCloudGO.transform.localPosition = Vector3.zero;
                    coloredCloudGO.transform.localRotation = Quaternion.identity;
                    coloredCloudGO.transform.localScale = Vector3.one;
                    coloredCloudGO.AddComponent<PointCloud>().set_as_dynamic();

                    coloredClouds.Add(coloredCloudGO);
                    cloudsVertices.Add(new NativeDLLVertices(400000));
                    currentCamerasFrameId.Add(-1);
                }
            }
            return m_initialized;
        }

        public void connect_to_devices() {
            if (!m_initialized) {
                return;
            }
            m_dllPlayer.connect_to_devices(); 
        }
        public void disconnect_from_devices() {
            if (!m_initialized) {
                return;
            }
            m_dllPlayer.disconnect_from_devices();
            UnityEngine.Debug.Log("-> disconnect");
        }

        public void start_reading() {
            if (!m_initialized) {
                return;
            }
            m_dllPlayer.start_reading();
            m_isReading = true;
        }

        public void stop_reading() {
            if (!m_initialized) {
                return;
            }
            m_isReading = false;
            m_dllPlayer.stop_reading();
        }

        public int devices_nb() {
            if (!m_initialized) {
                return 0;
            }
            return m_dllPlayer.devices_nb(); 
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
            if (!m_initialized) {
                return false;
            }
            return m_dllPlayer.is_device_connected(idD); 
        }
        public int current_frame_id(int idD) {
            if (!m_initialized) {
                return 0;
            }
            return m_dllPlayer.current_frame_id(idD); 
        }
        public int current_frame_cloud_size(int idD) {
            if (!m_initialized) {
                return 0;
            }
            return m_dllPlayer.current_frame_cloud_size(idD); 
        }

        public bool update_device_settings(string deviceSettingsFilePath = "") {

            if (!m_initialized) {
                return false;
            }

            if (deviceSettingsFilePath.Length > 0) {
                this.deviceSettingsFilePath = deviceSettingsFilePath;
            }
            return m_dllPlayer.update_device_settings(this.deviceSettingsFilePath);
        }
        public bool update_color_settings(string colorSettingsFilePath = "") {

            if (!m_initialized) {
                return false;
            }

            if (colorSettingsFilePath.Length > 0) {
                this.colorSettingsFilePath = colorSettingsFilePath;
            }
            return m_dllPlayer.update_color_settings(this.colorSettingsFilePath);
        }
        public bool update_filters_settings(string filtersSettingsFilePath = "") {

            if (!m_initialized) {
                return false;
            }

            if (filtersSettingsFilePath.Length > 0) {
                this.filtersSettingsFilePath = filtersSettingsFilePath;
            }
            return m_dllPlayer.update_filters_settings(this.filtersSettingsFilePath);
        }
        public bool update_model_settings(string modelSettingsFilePath = "") {

            if (!m_initialized) {
                return false;
            }

            if (modelSettingsFilePath.Length > 0) {
                this.modelSettingsFilePath = modelSettingsFilePath;
            }
            return m_dllPlayer.update_model_settings(this.modelSettingsFilePath);
        }

        public void update() {

            if (!m_isReading) {
                return;
            }

            // store current frames id before updating
            for (int idC = 0; idC < m_dllPlayer.devices_nb(); idC++) {
                currentCamerasFrameId[idC] = m_dllPlayer.current_frame_id(idC);
            }

            Profiler.BeginSample("[DCNetworkDirectPlayer::update] Player update");
            m_dllPlayer.update();
            Profiler.EndSample();

            Profiler.BeginSample("[DCNetworkDirectPlayer::update] copy_camera_cloud");
            Parallel.ForEach(idCameras, idC => {

                if (currentCamerasFrameId[idC] != m_dllPlayer.current_frame_id(idC)) {
                    m_dllPlayer.copy_current_frame_vertices(idC, cloudsVertices[idC], m_dllPlayer.current_frame_cloud_size(idC), true);
                }
            });
            Profiler.EndSample();


            Profiler.BeginSample("[DCNetworkDirectPlayer::update] set_points");
            for (int idC = 0; idC < m_dllPlayer.devices_nb(); idC++) {
                var pc = coloredClouds[idC].GetComponent<PointCloud>();
                pc.set_tint(devicesSettings[idC].tint);
                coloredClouds[idC].SetActive(devicesSettings[idC].display);

                //if (currentCamerasFrameId[idC] != m_dllPlayer.current_frame_id(idC)) {
                    if (devicesSettings[idC].update) {
                        pc.set_points(cloudsVertices[idC], indices, m_dllPlayer.current_frame_cloud_size(idC));
                    }
                //}
            }
            Profiler.EndSample();
        }

        #endregion

        private void Awake() {
            m_dllPlayer = new DLLDCNetworkDirectPlayer();
            indices = new NativeIndices(400000);

            for (int ii = 0; ii < maximumNbOfDevices;  ++ii) {
                devicesSettings.Add(new DeviceSettings());
            }
        }

        private void OnDestroy() {

            stop_reading();
            disconnect_from_devices();

            indices.clean();
            foreach (var cloudVertices in cloudsVertices) {
                cloudVertices.clean();                    
            }
        }
    }
}