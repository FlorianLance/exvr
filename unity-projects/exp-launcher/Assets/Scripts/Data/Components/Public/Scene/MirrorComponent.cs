
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Collections.Generic;
using Ex.XML;
// unity
using UnityEngine;

namespace Ex{

    public class MirrorComponent : ExComponent {

        GameObject m_mirrorGO = null;

        protected override bool initialize() {
            m_mirrorGO = ExVR.GlobalResources().instantiate_prebab("Components/Mirror", transform);
            m_mirrorGO.name = "Mirror";
            return true;
        }


        public override void update_from_current_config() {

            if (!currentC.get<bool>("transform_do_not_apply")) {
                currentC.update_transform("transform", m_mirrorGO.transform, true);
            }
            m_mirrorGO.transform.Find("MirrorFrame").gameObject.SetActive(currentC.get<bool>("show_frame"));            
        }

        protected override void set_visibility(bool visibility) {
            m_mirrorGO.SetActive(visibility);
        }

        public void apply_mirror_only_layer(GameObject go) {

            foreach (Transform tr in go.GetComponentsInChildren<Transform>(true)) {
                tr.gameObject.layer = Layers.MirrorOnly;
            }
        }
    }
}