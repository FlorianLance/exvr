/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// unity
using UnityEngine;

namespace Ex{

    public class AttachObjectToHandComponent : ExComponent{

        //private GameObject m_spongeGO = null;
        //private LeapMotionArmsDisplayComponent m_leapMotion = null;

        protected override bool initialize() {

            //// generate sponge
            //m_spongeGO = ExVR.GlobalResources().instantiate_prebab("Props/Sponge", transform);

            //// get leapmotion
            //string nameC = initC.get<string>("leap_motion_component");
            //if (nameC.Length > 0) {

            //    var component = get(nameC);
            //    if (component == null) {
            //        ExVR.Log().error("No component found with name " + nameC);
            //        return false;
            //    }
            //    m_leapMotion = component as LeapMotionArmsDisplayComponent;
            //    if (m_leapMotion == null) {
            //        ExVR.Log().error("No leap motion found");
            //        return false;
            //    }
            //}

            return true;
        }

        public override void update_from_current_config() {
            //if (!currentC.get<bool>("transform_do_not_apply")) {
                //currentC.update_transform("transform", m_spongeGO.transform);
            //}
        }

        protected override void set_visibility(bool visibility) {
            //m_spongeGO.SetActive(visibility );
        }

        protected override void update() {

            //if(m_leapMotion == null) {
            //    return;
            //}

            //var fingers = currentC.get<string>("arm") == "Left" ?  m_leapMotion.left_start_fingers() : m_leapMotion.right_start_fingers();
            //GameObject fingerToAttach = null;
            //foreach (var finger in fingers) {
            //    if (finger.name.Contains(currentC.get<string>("finger"))) {
            //        fingerToAttach = finger;
            //        break;
            //    }
            //}
            //if (fingerToAttach != null) {
            //    transform.localPosition = fingerToAttach.transform.position;
            //    transform.localRotation = fingerToAttach.transform.rotation;
            //}
        }
    }
}