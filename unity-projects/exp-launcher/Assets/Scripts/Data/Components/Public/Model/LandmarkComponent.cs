/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex {

    public class LandmarkComponent : ExComponent {

        private GameObject landmarkGO = null;

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
            landmarkGO = GO.generate_landmark("landmark");
            landmarkGO.transform.SetParent(transform);
            landmarkGO.SetActive(false);

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
        }

        protected override void set_visibility(bool visibility) {
            landmarkGO.SetActive(visibility);
            invoke_signal("visibility changed", visibility);
        }

    }
}