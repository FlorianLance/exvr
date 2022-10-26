
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
using System.IO;

// unity
using UnityEngine;

namespace Ex{

    public class CloudComponent : ExComponent{

        private PointCloud pc = null;

        protected override bool initialize() {

            // slots
            add_slot("visibility", (visibility) => { set_visibility((bool)visibility); });
            add_slot("position", (position) => { transform.localPosition = (Vector3)position; });
            add_slot("rotation", (rotation) => { transform.localEulerAngles = (Vector3)rotation; });
            add_slot("scale", (scale) => { transform.localScale = (Vector3)scale; });
            add_slot("transform", (value) => {
                var transformV = (TransformValue)value;
                transform.localPosition = transformV.position;
                transform.localRotation = transformV.rotation;
            });

            string alias = initC.get_resource_alias("cloud");
            if(alias.Length == 0) {
                log_error("No cloud alias defined.");
                return false;
            }

            var cloudData = ExVR.Resources().get_cloud_file_data(alias);
            string path = cloudData.path;
            string extension = System.IO.Path.GetExtension(path);

            List<Vector3> vertices = new List<Vector3>();
            List<Color> colors     = new List<Color>();
 
            if (extension == ".asc") {
                var lines = File.ReadLines(path);
                foreach (var line in lines) {
                    var split = line.Split(' ');
                    if(split.Length > 5) {
                        vertices.Add(new Vector3(Converter.to_float(split[0]), Converter.to_float(split[1]), Converter.to_float(split[2])));
                        colors.Add(new Color(Converter.to_int(split[3])/255f, Converter.to_int(split[4]) / 255f, Converter.to_int(split[5]) / 255f));
                    }
                }
            } else {
                log_error(string.Format("Cloud extension not managed: [{0}]", extension));
                return false;
            }
            //if (extension == ".ply") {
            // ...

            if (vertices.Count == 0) {
                log_error("Empty cloud.");
                return false;
            }

            pc = gameObject.AddComponent<PointCloud>();
            return pc.set_points(vertices, colors, vertices.Count);
        }

        protected override void start_experiment() {
            if (!initC.get<bool>("init_transform_do_not_apply")) {
                initC.update_transform("init_transform", transform, true);
            }
        }

        public override void update_from_current_config() {
            if (!currentC.get<bool>("transform_do_not_apply")) {
                currentC.update_transform("transform", transform, true);
            }

            float sizePoints = currentC.get<float>("size_points");
            bool cones = currentC.get<bool>("cones");
            bool circles = currentC.get<bool>("circles");
            Color tintColor = currentC.get_color("tint");
            var details = (PointCloud.ParabloidGeoDetails)currentC.get<int>("details");
            var rendering = (PointCloud.RenderingType)currentC.get<int>("rendering");

            pc.set_pt_size(sizePoints);
            pc.set_rendering(rendering);
            pc.set_obb_filtering_state(false);
            pc.set_circles_state(circles);
            pc.set_paraboloid_frag_cones_state(cones);
            pc.set_paraboloid_geo_details(details);
            pc.set_tint(tintColor);
        }

        protected override void update_parameter_from_gui(string updatedArgName) {
            update_from_current_config();
        }

        protected override void set_visibility(bool visibility) {
            gameObject.GetComponent<MeshRenderer>().enabled = visibility;
        }

    }
}