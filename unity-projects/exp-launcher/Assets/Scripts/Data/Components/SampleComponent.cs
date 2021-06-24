/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

//// system
//using System.Reflection;

//// unity
//using UnityEngine;

//namespace Expy{

//    namespace Events{

//        public class Foo2 : UnityEvent<int>
//        {
//            public Foo2() {
//                AddListener((value) => {
//                    m_slots.invoke_all_slots(value);
//                });
//            }

//            private SlotsEvent m_slots = new SlotsEvent();
//            public SlotsEvent slots() { return m_slots; }
//        }
//    }

//    public class SampleComponent : ExComponent
//    {

//        protected override bool initialize() {

//            // bool addDateToFileName
//            // string directoryPath;
//            // string baseFileName

//            return true;
//        }

//        protected override void start_routine() {
//            // ...
//        }

//        protected override void set_visibility(bool visibility) {
//            // not used
//        }

//        protected override void update() {
//            // ...
//        }

//        protected override void clean() {
//            // ...
//        }


//        public Events.Foo2 m_fooEvent = new Events.Foo2();

//        protected override void connect_signal_to_slot(string signal, MethodInfo slotMethod, object slotObject) {
//            if (signal == nameof(m_fooEvent)) {
//                m_fooEvent.slots().add_slot(slotMethod, slotObject);
//            }
//        }

//        protected override void remove_connections() {
//            m_fooEvent.slots().remove_slots();
//        }

//        protected override void update_parameter_from_gui(XML.Arg arg) {
//            // ...
//        }

//    }
//}