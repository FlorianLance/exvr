
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

using UnityEngine;

namespace Ex{

    [RequireComponent(typeof(MeshFilter), typeof(MeshRenderer))]
    public class PointCloud : MonoBehaviour{
        public enum RenderingType {
            ParabloidFrag, ParabloidGeo
        };

        public enum ParabloidDetails {
            None = 0, Low = 1, Medium = 2, Hight = 3
        };

        Shader pointShader = null;
        Shader paraboloidFrag = null;
        Shader paraboloidGeoWorld = null;

        Material material = null;
        RenderingType currentRendering = RenderingType.ParabloidGeo;

        void Start() {

            Mesh mesh = new Mesh();
            mesh.triangles = new int[0];
            GetComponent<MeshFilter>().mesh = mesh;

            var renderer                  = GetComponent<MeshRenderer>();
            renderer.material             = (material = ExVR.GlobalResources().instantiate_mat("pointCloud"));
            renderer.shadowCastingMode    = UnityEngine.Rendering.ShadowCastingMode.Off;
            renderer.receiveShadows       = false;
            renderer.lightProbeUsage      = UnityEngine.Rendering.LightProbeUsage.Off;
            renderer.reflectionProbeUsage = UnityEngine.Rendering.ReflectionProbeUsage.Off;

            paraboloidFrag     = Shader.Find("Custom/Cloud/ParaboloidFragWorldSizeShader");
            paraboloidGeoWorld = Shader.Find("Custom/Cloud/ParaboloidGeoWorldSizeShader");

            set_rendering(currentRendering);
        }

        public void set_rendering(RenderingType rendering) {

            var renderer = GetComponent<MeshRenderer>();
            switch (currentRendering = rendering) {
                case RenderingType.ParabloidFrag:
                    renderer.material.shader = paraboloidFrag;
                    break;
                case RenderingType.ParabloidGeo:
                    renderer.material.shader = paraboloidGeoWorld;
                    break;
            }
        }

        public void set_paraboloid_circle_state(bool circle) {
            material.SetInt("_Circle", circle ? 1 : 0);
        }

        public void set_paraboloid_frag_cone_state(bool cone) {
            if (currentRendering == RenderingType.ParabloidFrag) {
                material.SetInt("_Cones", cone ? 1 : 0);
            }
        }

        public void set_paraboloid_geo_details(ParabloidDetails details) {
            if(currentRendering == RenderingType.ParabloidGeo) {
                material.SetInt("_Details", (int)details);
            }
        }

        public void set_tint(Color color) {
            material.SetColor("_Tint", color);
        }

        public void set_pt_size(float size) {
            material.SetFloat("_PointSize", size);
        }
    }


}