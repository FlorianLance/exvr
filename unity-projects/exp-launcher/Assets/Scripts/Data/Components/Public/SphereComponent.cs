/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{

    public class SphereComponent : ExComponent{

        private MeshRenderer mr = null;
        private MeshFilter mf = null;
        private Material m = null;

        protected override bool initialize() {

            // slots
            add_slot("visibility", (visibility) => { set_visibility((bool)visibility); });
            add_slot("position", (position) => { transform.localPosition = (Vector3)position; });
            add_slot("rotation", (rotation) => { transform.localEulerAngles = (Vector3)rotation; });
            add_slot("scale", (scale) => {transform.localScale = (Vector3)scale;});
            add_slot("transform", (value) => {
                var transformV = (TransformValue)value;
                transform.localPosition = transformV.position;
                transform.localRotation = transformV.rotation;
                transform.localScale = transformV.scale;
            });
            // signals
            add_signal("visibility changed");

            // generate
            // # mesh renderer
            mr = gameObject.AddComponent<MeshRenderer>();
            if (initC.get<bool>("transparent")) {
                mr.material = (m = ExVR.GlobalResources().instantiate_default_transparent_mat());
            } else {
                mr.material = (m = ExVR.GlobalResources().instantiate_default_mat());
            }
            mr.enabled = false;
            // # mesh filter
            mf = gameObject.AddComponent<MeshFilter>();
            mf.mesh = Ex.PrimitivesMesh.SphereBuilder.generate(
                initC.get<float>("radius"), 
                initC.get<int>("nb_log"), 
                initC.get<int>("nb_lat")
            );

            return true;
        }
        public override void update_from_current_config() {
            if (!currentC.get<bool>("transform_do_not_apply")) {
                currentC.update_transform("transform", transform, true);
            }
            m.SetColor("_Color", currentC.get_color("color"));
            m.SetFloat("_Metallic", currentC.get<float>("metallic"));
            m.SetFloat("_Glossiness", currentC.get<float>("smoothness"));
        }

        protected override void update_parameter_from_gui(string updatedArgName) {
            update_from_current_config();
        }

        protected override void set_visibility(bool visibility) {
            mr.enabled = visibility;
            invoke_signal("visibility changed", visibility);
        }

    }
}