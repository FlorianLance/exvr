/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex {

    public class FlagPoleComponent : ExComponent {

        private SkinnedMeshRenderer smr = null;
        private Cloth flagCloth = null;

        private GameObject flag = null;
        private GameObject pole = null;

        private ClothSkinningCoefficient[] coeffs = null;
        private List<int> poleCoeff = new List<int>();

        protected override bool initialize() {

            add_slot("hoist", (factor) => {
                var v = Mathf.Clamp((float)factor, 0f, 1f);
                udpate_flag_cloth_max_distance(0.5f - v*0.45f);
                update_flag_height(v);            
            });

            float width  = initC.get<float>("flag_width");
            float height = initC.get<float>("flag_height");
            float depth  = 0.001f;

            int nbVerticesH = initC.get<int>("flag_nb_vertices_horiz");
            int nbVerticesV = initC.get<int>("flag_nb_vertices_verti");

            // pole
            {
                pole = new GameObject("Pole");
                pole.transform.SetParent(transform);                
                pole.AddComponent<MeshFilter>().mesh = PrimitivesMesh.CylinderBuilder.generate(10, 3, 0.025f, initC.get<float>("pole_height"));
                pole.AddComponent<MeshRenderer>().material = ExVR.GlobalResources().instantiate_default_mat();
            }

            // flag
            {
                flag = new GameObject("Flag");
                flag.transform.SetParent(transform);
                
                var mesh = PrimitivesMesh.GridBuilder.generate(nbVerticesH, nbVerticesV, width, height, depth);
                flag.AddComponent<MeshFilter>().mesh = mesh;
                smr = flag.AddComponent<SkinnedMeshRenderer>();
                smr.material   = Instantiate(Resources.Load(string.Format("Materials/Procedural/Grid")) as Material);                   
                smr.sharedMesh = mesh;

                flagCloth = flag.AddComponent<Cloth>();
                flagCloth.randomAcceleration = new Vector3(0.1f, 0.1f, 0.1f);
                coeffs    = flagCloth.coefficients;

                for (int ii = 0; ii < coeffs.Length; ++ii) {
                    if (UnityEngine.Mathf.Approximately(flagCloth.vertices[ii].x, 0f)) {
                        poleCoeff.Add(ii);
                    }
                }
                udpate_flag_cloth_max_distance(0f);
            }

            pole.SetActive(false);
            flag.SetActive(false);

            return true;
        }

        public void udpate_flag_cloth_max_distance(float maxDistance) {

            for (int ii = 0; ii < coeffs.Length; ++ii) {
                coeffs[ii].maxDistance = maxDistance;     
            }
            foreach(var id in poleCoeff) {
                coeffs[id].maxDistance = 0f;
            }            
            flagCloth.coefficients = coeffs;
        }

        public void update_flag_height(float factor) {
            flag.transform.localPosition = new Vector3(0.025f, factor * (initC.get<float>("pole_height") - initC.get<float>("flag_height")), 0);
        }

        protected override void start_routine() {
            smr.material.mainTexture = currentC.get_resource_image("flag_image");
            update_from_current_config();
        }

        protected override void update_parameter_from_gui(XML.Arg arg) {

            if(arg.Name == "flag_image") {
                smr.material.mainTexture = currentC.get_resource_image("flag_image");
            }
            update_from_current_config();
        }

        public override void update_from_current_config() {
            currentC.update_transform("transform", transform, true);
            udpate_flag_cloth_max_distance(currentC.get<float>("cloth_max_dist"));
            update_flag_height(currentC.get<float>("height"));
        }

        protected override void set_visibility(bool visibility) {
            flag.SetActive(visibility);
            pole.SetActive(visibility);
        }

    }
}