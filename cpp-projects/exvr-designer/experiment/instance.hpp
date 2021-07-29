/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "experiment/experiment.hpp"
#include "randomizer.hpp"
#include "qt_str.hpp"

namespace tool::ex {

struct LoopInfo{
    int currentRep = 0;
    int idStart;
    int idEnd;
    QStringList set;
    Loop *l = nullptr;
};

struct InstanceElement{
    int elementIteration = 0;
    int conditionIteration = 0;
    Element *elem;
    QString condition;
};

struct Instance {

    Instance() = default;
    Instance(const Randomizer *randomizer, const std_v1<Element*> &elements, size_t idInstance);

    static std::unique_ptr<Instance> generate_from_full_experiment(const Randomizer *randomizer, const Experiment &experiment, size_t idInstance);
    static std::unique_ptr<Instance> generate_from_one_routine(Routine *routine);
    static std::unique_ptr<Instance> generate_from_element_to_the_end(const Randomizer *randomizer, const Experiment &experiment, size_t idInstance);
    static std::unique_ptr<Instance> generate_from_start_to_element(const Randomizer *randomizer, const Experiment &experiment, size_t idInstance);

    static inline std::unordered_map<int, std_v1<QString>> onlyOnceShuffleLoopSets = {};
    static inline std::unordered_map<int, std_v1<QString>> onlyOnceRandomLoopSets = {};
    static inline std::unordered_map<int, std_v1<QString>> everyNShuffleLoopSets = {};
    static inline std::unordered_map<int, std_v1<QString>> everyNRandomLoopSets = {};

    QString filePath = "";
    QString fileName = "debug-instance";
    std_v1<InstanceElement> flow;
};

}
