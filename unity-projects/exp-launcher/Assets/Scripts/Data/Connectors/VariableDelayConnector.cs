/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex{

    public class VariableDelayConnector : ExConnector{

        // min delay / max delay
        public AnimationCurve curve = null;
        public bool relativeValues = false;

        //int delay = 500;
        int maxNb = 10000;
        Queue<Tuple<double, double, object>> elements = new Queue<Tuple<double, double, object>>();

        protected override void initialize(XML.Connector connector) {

            base.initialize(connector);
            update_from_gui();

            add_signals(1);            
            add_slot(0, (arg) => { base_slot1(arg); });
            add_slot(1, (arg) => { base_slot2(arg); });
        }

        protected override void slot1(object arg) {
            curve = (AnimationCurve)arg;
        }

        protected override void slot2(object arg) {

            double currTimeMs = time().ellapsed_element_ms();
            double currentDelayMs = 0;

            // retrieve current delay from curve
            if (relativeValues) {
                currentDelayMs = curve.Evaluate((float)(currTimeMs / (associatedCondition.duration() * 1000.0)));
            } else {
                currentDelayMs = curve.Evaluate((float)(currTimeMs * 0.001));
            }

            // check previous time + delay
            if (elements.Count > 0) {

                var previousElement = elements.Peek();
                var previousTimeMs = previousElement.Item1;
                var previousDelayMs = previousElement.Item2;

                // cond not valid: t(n) + d(n) < t(n+1) + d(n+1) 
                if (previousTimeMs + previousDelayMs > currTimeMs + currentDelayMs) {
                    currentDelayMs = previousTimeMs + previousDelayMs - currTimeMs;
                    ExVR.Log().error("Variable delay values invalid: cond not valid: t(n) + d(n) < t(n+1) + d(n+1) ");
                }
            }
            //Debug.Log("Add value at time " + currTimeMs + " with delay " + currentDelayMs);

            // add element
            elements.Enqueue(new Tuple<double, double, object>(currTimeMs, currentDelayMs, arg));

            // check if reach max size
            if (elements.Count > maxNb) {
                elements.Dequeue();
            }
        }

        protected override void update_from_gui() {

            curve = new AnimationCurve();
            var values = m_config.get_list<float>(valueStr);
            for (int ii = 0; ii < values.Count; ii += 2) {
                curve.AddKey(values[ii], values[ii + 1]);
            }

            //relativeValues = ...;
            // check curve
            // ...
        }

        protected override void update() {

            var currTime = time().ellapsed_element_ms();
            double elemTime=0;
            double elemDelay=0;

            List<object> items = new List<object>();
            while (elements.Count > 0) {

                var lastElement = elements.Peek();
                if(lastElement.Item1 + lastElement.Item2 < currTime) {
                    elemTime  = lastElement.Item1;
                    elemDelay = lastElement.Item2;
                    items.Add(elements.Dequeue().Item3);
                } else {
                    break;
                }
            }

            foreach (var item in items) {
                invoke_signal(0, item);
            }
        }

        protected override void stop_routine() {
            elements.Clear();
        }
    }
}