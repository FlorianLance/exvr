
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