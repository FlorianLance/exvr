
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;

// unity
using UnityEngine;

namespace Ex {

    public class FilterKeyboardButtonConnector : ExConnector {

        KeyCode codeToCompare;

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            update_from_gui();

            add_signals(1);
            add_slot(0, (arg) => { base_slot1(arg); });
        }

        protected override void update_from_gui() {
            codeToCompare = (KeyCode)Enum.Parse(typeof(KeyCode), m_config.get<string>(valueStr));
        }

        protected override void slot1(object arg) {

            var state = (Input.KeyboardButtonEvent)arg;
            if (state.code == codeToCompare) {
                invoke_signal(0, state);
            }
        }
    }
}

