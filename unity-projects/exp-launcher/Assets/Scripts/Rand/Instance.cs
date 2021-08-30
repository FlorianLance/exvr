/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex{

    public class Instance{

        public int idInstance = 0;

        [SerializeField]
        private List<FlowElementInfo> elementsOrder = new List<FlowElementInfo>();
        [SerializeField]
        private List<FlowElementInfo> randomizerElementsOrder = new List<FlowElementInfo>();

        public bool generate(XML.ExperimentFlow experimentFlow) {

            // clean
            elementsOrder.Clear();
            randomizerElementsOrder.Clear();

            idInstance = experimentFlow.IdInstance;

            var routinesManager = ExVR.Routines();
            var isisManager = ExVR.ISIs();

            //experimentFlow.IdInstance;

            // create flow experiment from instance xml
            foreach (XML.Element element in experimentFlow.Elements) {

                if (element.Type == "routine") { // Routine

                    // retrieve routine
                    var routine = routinesManager.get(element.Key);
                    if (!routine) {
                        ExVR.Log().error(string.Format("Routine with id {0} from instance not found in experiment.", element.Key));
                        return false;
                    }

                    // retrieve the end routine time
                    Condition currentCondition = routine.condition_from_name(element.Cond);
                    if (!currentCondition) {
                        ExVR.Log().error(string.Format("Condition {0} from instance not found in experiment.", element.Cond));
                        return false;
                    }

                    // add element info                                        
                    if (routine.is_a_randomizer()) {
                        randomizerElementsOrder.Add(new RoutineInfo(
                            routine,
                            currentCondition,
                            new Interval(0, 0),
                            randomizerElementsOrder.Count,
                            element.ElemIteration,
                            element.ConditionIteration
                        ));

                    } else {
                        elementsOrder.Add(new RoutineInfo(
                            routine,
                            currentCondition,
                            new Interval(0, currentCondition.duration()),
                            elementsOrder.Count,
                            element.ElemIteration,
                            element.ConditionIteration
                        ));
                    }

                } else { // ISI

                    // retrieve ISI
                    var isi = isisManager.get(element.Key);
                    if (!isi) {
                        ExVR.Log().error(string.Format("IIS with id {0} from instance not found in experiment.", element.Key));
                        return false;
                    }

                    // add element info
                    elementsOrder.Add(new ISIInfo(
                        isi,
                        element.Cond,
                        new Interval(0, Converter.to_double(element.Cond)),
                        elementsOrder.Count,
                        element.ElemIteration,
                        element.ConditionIteration
                    ));
                }
            }


            return true;
        }

        public FlowElementInfo element_order(int id) {
            return elementsOrder[id];
        }

        public int total_number_of_elements() {
            return elementsOrder.Count;
        }

        public List<FlowElementInfo> get_elements_info_order(bool isARandomizer) {
            if (isARandomizer) {
                return new List<FlowElementInfo>(randomizerElementsOrder);
            } else {
                return new List<FlowElementInfo>(elementsOrder);
            }
        }

        public List<RoutineInfo> get_routine_infos_order(int elementKey, bool isARandomizer) {

            List<RoutineInfo> infos = new List<RoutineInfo>();
            var elements = isARandomizer ? randomizerElementsOrder : elementsOrder;
            foreach (var info in elements) {
                if (info.key() == elementKey) {
                    infos.Add((RoutineInfo)info);
                }
            }
            return infos;
        }

        public List<Condition> get_routine_conditions_order(int elementKey, bool isARandomizer) {

            List<Condition> conditions = new List<Condition>();
            var elements = isARandomizer ? randomizerElementsOrder : elementsOrder;
            foreach (var info in elements) {
                if (info.key() == elementKey) {
                    conditions.Add(((RoutineInfo)info).condition());
                }
            }
            return conditions;
        }

        public List<string> get_routine_conditions_names_order(int elementKey, bool isARandomizer) {

            List<string> conditionsName = new List<string>();
            var elements = isARandomizer ? randomizerElementsOrder : elementsOrder;
            foreach (var info in elements) {
                if (info.key() == elementKey) {
                    conditionsName.Add(((RoutineInfo)info).condition().name);
                }
            }
            return conditionsName;
        }
    }
}