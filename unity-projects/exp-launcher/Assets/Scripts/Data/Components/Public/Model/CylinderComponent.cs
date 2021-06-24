/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{

    public class CylinderComponent : ExComponent{

        private MeshRenderer mr = null;
        private MeshFilter mf = null;
        private Material m = null;

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
            mf.mesh = Ex.PrimitivesMesh.ConeBuilder.generate(
                initC.get<int>("nb_sides"),
                initC.get<float>("radius"),
                initC.get<float>("radius"),
                initC.get<float>("length")
            );

            return true;
        }

        protected override void start_routine() {
            update_from_current_config();
        }

        protected override void update_parameter_from_gui(XML.Arg arg) {
            update_from_current_config();
        }

        public override void update_from_current_config() {
            currentC.update_transform("transform", transform, true);
            m.SetColor("_Color", currentC.get_color("color"));
            m.SetFloat("_Metallic", currentC.get<float>("metallic"));
            m.SetFloat("_Glossiness", currentC.get<float>("smoothness"));
        }

        protected override void set_visibility(bool visibility) {
            mr.enabled = visibility;
            invoke_signal("visibility changed", visibility);
        }

    }
}