/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

using UnityEngine;

namespace Ex{

    [RequireComponent(typeof(MeshFilter), typeof(MeshRenderer))]
    public class PointCloud : MonoBehaviour{

        public Mesh mesh = null;

        void Start() {

            mesh = new Mesh();
            mesh.triangles = new int[0];
            GetComponent<MeshFilter>().mesh = mesh;
            var renderer = GetComponent<MeshRenderer>();
            renderer.material = ExVR.GlobalResources().instantiate_mat("pointCloud");

            renderer.shadowCastingMode = UnityEngine.Rendering.ShadowCastingMode.Off;
            renderer.receiveShadows = false;

            renderer.lightProbeUsage = UnityEngine.Rendering.LightProbeUsage.Off;
            renderer.reflectionProbeUsage = UnityEngine.Rendering.ReflectionProbeUsage.Off;
        }

        public void set_pt_size(float size) {
            //GetComponent<MeshRenderer>().material.SetFloat("_PointSize", size);
        }
    }


}