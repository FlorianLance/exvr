
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


// unity
using Ex.XML;
using UnityEngine;

namespace Ex{

    public class FlashingDotComponent : ExComponent{

        GameObject dot = null;

        protected override bool initialize() {

            dot = GameObject.CreatePrimitive(PrimitiveType.Sphere);
            dot.transform.SetParent(transform);
            GO.init_local_transform(dot, new Vector3(), new Vector3(), new Vector3(0.1f, 0.1f, 0.1f));
            dot.layer = Layers.Default;            
            dot.name = "Flashing dot";
            dot.SetActive(false);
            Destroy(dot.GetComponent<SphereCollider>());
            dot.GetComponent<Renderer>().material.shader = Shader.Find("Unlit/Color");

            return true;
        }

        protected override void start_routine() {
            update_from_current_config();
        }

        protected override void set_visibility(bool visibility) {
            dot.SetActive(visibility);
        }

        protected override void update_parameter_from_gui(Arg arg) {
            update_from_current_config();
        }

        public override void update_from_current_config() {
            currentC.update_transform("transform", dot.transform);
            dot.GetComponent<MeshRenderer>().material.color = currentC.get<bool>("on") ? currentC.get_color("on_color") : currentC.get_color("off_color");
        }
    }
}