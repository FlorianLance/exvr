/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{

    public class VideoResourceComponent : ExComponent{

        //public Texture2D m_texture = null;

        protected override bool initialize() {
            //events().add_signal("image_loaded", 1);
            return true;
        }

        protected override void start_routine() {
            //load_image();
            //events().invoke_signal("image_loaded", new ImageContainer(m_texture, false));
        }

        protected override void update_parameter_from_gui(XML.Arg arg) {
            //if (arg.Name == "image") {
            //    load_image();
            //}
        }

        //private void load_image() {

        //    var imageData = currentC.get_resource_image_data("image");
        //    if (imageData != null) {
        //        m_texture = imageData.texture;
        //    } else {
        //        m_texture = ExVR.Resources().get_image_file_data("default_texture").texture;
        //    }
        //}
    }
}