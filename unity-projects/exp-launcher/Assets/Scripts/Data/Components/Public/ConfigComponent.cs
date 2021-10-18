
/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex {

    public class ConfigComponent : ExComponent {
        protected override bool initialize() {
            add_signal("current config");
            return true;
        }
        protected override void start_routine() {
            invoke_signal("current config", currentC.name);
        }
    }
}