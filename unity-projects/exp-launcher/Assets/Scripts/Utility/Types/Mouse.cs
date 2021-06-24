/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex.Input {

    static public class Mouse {

        public static readonly List<KeyCode> Codes = new List<KeyCode>(new KeyCode[] {
            KeyCode.Mouse0,
            KeyCode.Mouse1,
            KeyCode.Mouse2,
            KeyCode.Mouse3,
            KeyCode.Mouse4,
            KeyCode.Mouse5,
            KeyCode.Mouse6
        });
    }

    public class MouseButtonEvent {
        public MouseButtonEvent(KeyCode code) {
            this.code = code;
            state = Button.State.None;
            triggeredExperimentTime = 0.0;
        }

        public KeyCode code;
        public Button.State state;
        public double triggeredExperimentTime;
    }

    public class MouseMovementEvent {

    }
}