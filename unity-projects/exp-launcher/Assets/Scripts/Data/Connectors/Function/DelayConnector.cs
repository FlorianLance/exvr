/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Collections.Generic;

namespace Ex{

    public class DelayConnector : ExConnector{

        int delay = 500;
        int maxNb = 10000;
        Queue<Tuple<double, object>> elements = new Queue<Tuple<double, object>>();

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            update_from_gui();

            add_signals(1);
            add_slot(0, (arg) => { base_slot1(arg); });
        }

        protected override void slot1(object arg) {
            elements.Enqueue(new Tuple<double, object>(time().ellapsed_element_ms(), arg));
            if (elements.Count > maxNb) {
                elements.Dequeue();
            }
        }

        protected override void update_from_gui() {
            delay = m_config.get<int>(valueStr);
        }

        protected override void update() {

            var currTime = time().ellapsed_element_ms();

            List<object> items = new List<object>();
            while (elements.Count > 0) {

                if(elements.Peek().Item1 + delay < currTime) {
                    items.Add(elements.Dequeue().Item2);
                } else {
                    break;
                }
            }

            foreach(var item in items) {
                invoke_signal(0, item);
            }
        }

        protected override void stop_routine() {
            elements.Clear();
        }
    }
}