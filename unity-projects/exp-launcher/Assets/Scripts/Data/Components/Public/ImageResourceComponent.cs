
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
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex{

    public class ImageResourceComponent : ExComponent {

        public ImageResource currentImage = null;
        public Dictionary<string, ImageResource> images = null;
        //(resources.Count);

        protected override bool initialize() {
            add_signal("image");
            add_signal("alias");
            add_signal("path");
            add_slot("update alias", (value) => {
                var alias = (string)value;
                update_current_image(alias);
                send_current_image();
            });

            var resources = initC.get_images_resources_list("images_list");
            images = new Dictionary<string, ImageResource>(resources.Count);
            foreach (var resource in resources) {

                var imageResource = ExVR.Resources().get_image_file_data(resource.alias);
                if(imageResource != null) {
                    images[resource.alias] = imageResource;
                } else {
                    return false;
                }                
            }

            return true;
        }

        public override void update_from_current_config() {
            update_current_image(currentC.get<string>("alias"));
        }

        protected override void update_parameter_from_gui(string updatedArgName) {
            update_from_current_config();
            send_current_image();
        }

        protected override void pre_start_routine() {
            if(currentC.get<string>("alias").Length > 0) {
                send_current_image();
            }
        }

        private void update_current_image(string alias) {

            if (alias.Length != 0) {
                if (images.ContainsKey(alias)) {
                    currentImage = images[alias];

                } else {
                    log_error(string.Format("No alias {0} available in init config images resources list. ", alias));
                }
            }
        }

        private void send_current_image() {
            if (currentImage != null) {
                invoke_signal("image", new ImageContainer(currentImage.texture, false));
                invoke_signal("alias", currentImage.alias);
                invoke_signal("path", currentImage.path);                
            }
        }
    }
}