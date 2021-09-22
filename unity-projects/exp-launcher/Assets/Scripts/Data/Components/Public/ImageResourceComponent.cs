/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{

    public class ImageResourceComponent : ExComponent {

        public Texture2D m_texture = null;

        protected override bool initialize() {
            add_signal("image loaded");
            return true;
        }


        public override void update_from_current_config() {
            load_image();
        }

        protected override void update_parameter_from_gui(string updatedArgName) {
            update_from_current_config();
        }

        private void load_image() {

            var imageData = currentC.get_resource_image_data("image");
            if(imageData != null) {
                m_texture = imageData.texture;
            } else {
                m_texture = ExVR.Resources().get_image_file_data("default_texture").texture;
            }
            invoke_signal("image loaded", new ImageContainer(m_texture, false));
        }
    }
}