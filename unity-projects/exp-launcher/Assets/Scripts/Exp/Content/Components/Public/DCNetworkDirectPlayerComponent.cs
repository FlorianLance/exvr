/***********************************************************************************
** exvr-exp                                                                       **
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

namespace Ex {

    public class DCNetworkDirectPlayerComponent : ExComponent {

        DCNetworkDirectPlayer m_player = null;

        #region ex_functions
        protected override bool initialize() {

            var networkFile = ExVR.Resources().get_text_file_data(initC.get_resource_alias("network_settings"), false);
            if (networkFile == null) {
                log_error("No network config file defined.");
                return false;
            }
            var deviceFile  = ExVR.Resources().get_text_file_data(initC.get_resource_alias("device_settings"), false);
            var filtersFile = ExVR.Resources().get_text_file_data(initC.get_resource_alias("filters_settings"), false);   
            var colorFile   = ExVR.Resources().get_text_file_data(initC.get_resource_alias("color_settings"), false);
            var modelsFile  = ExVR.Resources().get_text_file_data(initC.get_resource_alias("models_settings"), false);

            m_player = gameObject.AddComponent<DCNetworkDirectPlayer>();
            m_player.networkSettingsFilePath = networkFile.path;
            bool playerInitialized = m_player.initialize();
            if (!playerInitialized){
                return false;
            }

            if (deviceFile != null) {
                log_message("LOAD DEVICE: " + deviceFile.path);
                if (!m_player.update_device_settings(deviceFile.path)) {
                    log_error("Failed to load device settings");
                }
            }
            if (filtersFile != null) {
                log_message("LOAD FILTERS: " + filtersFile.path);
                if (!m_player.update_filters_settings(filtersFile.path)) {
                    log_error("Failed to load filters settings");
                }
            }
            if (colorFile != null) {
                log_message("LOAD COLOR: " + colorFile.path);
                if (!m_player.update_color_settings(colorFile.path)) {
                    log_error("Failed to load color settings");
                }
            }
            if (modelsFile != null) {
                log_message("LOAD MODEL: " + modelsFile.path);
                if (!m_player.update_model_settings(modelsFile.path)) {
                    log_error("Failed to load model settings");
                }
            }

            m_player.connect_to_devices();

            return true;
        }

        protected override void start_experiment() {
            m_player.start_reading();
        }

        protected override void stop_experiment() {
            m_player.stop_reading();           
        }

        protected override void clean() {
            m_player.clean();
        }

        protected override void update_parameter_from_gui(string updatedArgName) {
            update_from_current_config();
        }

        public override void update_from_current_config() {
            //cppDll.set(Parameters.Container.Dynamic, "delay", currentC.get<int>("delay"));
            //cppDll.update_from_current_config();
        }

        protected override void update() {
            m_player.update();

            //for (int ii = 0; ii < m_grabbersData.Count; ++ii) {
            //    var gData = m_grabbersData[ii];
            //    if (gData.update) {
            //        //Debug.Log("-> " + ii + " " + gData.nbVertices + " " + gData.currentFrameId);
            //        send_infos_to_gui_current_config(
            //            string.Format("frame_infos_{0}_{1}", ii, m_grabbersData.Count),
            //            string.Format("Size: {0} Frame id: {1}", gData.nbVertices, gData.currentFrameId)
            //        );
            //    }
            //}

        }


        protected override void set_update_state(bool doUpdate) {
            for (int idC = 0; idC < m_player.connected_devices_nb(); ++idC) {
                m_player.set_cloud_update_state(idC, doUpdate);
            }
        }
        protected override void set_visibility(bool visible) {
            for(int idC = 0; idC < m_player.connected_devices_nb(); ++idC) {
                m_player.set_cloud_display_state(idC, visible);
            }            
        }

        #endregion

        #region private_functions


        #endregion

        #region public_functions


        #endregion  
    }
}

