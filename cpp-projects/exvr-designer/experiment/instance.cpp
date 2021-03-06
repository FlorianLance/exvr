
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "instance.hpp"

// Qt
#include <QMessageBox>

using namespace tool;
using namespace tool::ex;

Instance::Instance(const Randomizer *randomizer, const std_v1<Element*> &elements, size_t idInstance){   

    this->idInstance = idInstance;

    QVector<LoopInfo> infos;
    auto get_index_from_loop_node = [&](Element *elem){
        for(int ii = 0; ii < to_signed(elements.size()); ++ii){
            if(elements[to_unsigned(ii)] == elem){
                return ii;
            }
        }
        return -1;
    };

    // retrieve cast elements
    std_v1<Routine *> routines;
    std_v1<Isi *> ISIs;
    std_v1<Loop *> loops;
    for(const auto elem : elements){
        if(elem->type == Element::Type::Isi){
            ISIs.push_back(dynamic_cast<Isi*>(elem));
            continue;
        }
        if(elem->type == Element::Type::Routine){
            routines.push_back(dynamic_cast<Routine*>(elem));
            continue;
        }
        if(elem->type == Element::Type::LoopStart){
            loops.push_back(dynamic_cast<LoopNode*>(elem)->loop);
            continue;
        }
    }


    // generate randomization for each loop
    std::unordered_map<int, std_v1<QString>> loopsSetsNames;
    std::unordered_map<int, size_t> loopsCurentSetId;        

    for(const auto loop : loops){

        size_t multiplier = 1;
        for(const auto outerLoop : loop->insideLoops){
            auto l = dynamic_cast<Loop*>(outerLoop);
            multiplier *= to_unsigned(l->nbReps);
        }

        const size_t totalNbReps = multiplier * to_unsigned(loop->nbReps);

        // fill list of sets
        std_v1<QString> setsOccurenciesStr;
        if(loop->mode != Loop::Mode::File){

            for(const auto &set : loop->sets){
                for(size_t ii = 0; ii < set.occurencies; ++ii){
                    setsOccurenciesStr.push_back(set.name);
                }
            }
        }else{
            for(const auto &set : loop->fileSets){
                for(size_t ii = 0; ii < set.occurencies; ++ii){
                    setsOccurenciesStr.push_back(set.name);
                }
            }
        }


        std_v1<QString> setsNames;
        setsNames.reserve(totalNbReps);

//        const bool randomizeOnce = true;
//        if(randomizeOnce){

        switch (loop->mode) {
            case Loop::Mode::Fixed:{

                for(size_t ii = 0; ii < totalNbReps; ++ii){
                    setsNames.push_back(setsOccurenciesStr[ii%setsOccurenciesStr.size()]);
                }

            break;}case Loop::Mode::File:{

                for(size_t ii = 0; ii < totalNbReps; ++ii){
                    setsNames.push_back(setsOccurenciesStr[ii%setsOccurenciesStr.size()]);
                }

            break;}case Loop::Mode::Shuffle:{

                for(auto &set : randomizer->shuffle(setsOccurenciesStr, totalNbReps)){
                    setsNames.push_back(std::move(set));
                }

            break;}case Loop::Mode::Random:{

                for(auto &set : randomizer->randomize(setsOccurenciesStr, totalNbReps)){
                    setsNames.push_back(std::move(set));
                }

            break;}case Loop::Mode::FixedRandomStart:{

                const size_t start = randomizer->randomize_start(setsOccurenciesStr.size());
                for(size_t ii = 0; ii < totalNbReps; ++ii){
                    setsNames.push_back(setsOccurenciesStr[(start+ii)%setsOccurenciesStr.size()]);
                }

            break;}case Loop::Mode::FixedInstanceShiftStart:{

                for(size_t ii = 0; ii < totalNbReps; ++ii){
                    setsNames.push_back(setsOccurenciesStr[(ii+idInstance)%setsOccurenciesStr.size()]);
                }

            break;}case Loop::Mode::RandomOneForAllInstances:{

                // generate
                if(idInstance == 0){
                    onlyOnceRandomLoopSets[loop->key()] = {};
                    for(auto &set : randomizer->randomize(setsOccurenciesStr, totalNbReps)){
                        onlyOnceRandomLoopSets[loop->key()].push_back(std::move(set));
                    }
                }
                // retrieve
                for(const auto &set : onlyOnceRandomLoopSets[loop->key()]){
                    setsNames.push_back(set);
                }

            break;}case Loop::Mode::ShuffleOneForAllInstances:{

                // generate
                if(idInstance == 0) {
                    onlyOnceShuffleLoopSets[loop->key()] = {};
                    for(auto &set : randomizer->shuffle(setsOccurenciesStr, totalNbReps)){
                        onlyOnceShuffleLoopSets[loop->key()].push_back(std::move(set));
                    }
                }
                // retrieve
                for(const auto &set : onlyOnceShuffleLoopSets[loop->key()]){
                    setsNames.push_back(set);
                }

            break;}case Loop::Mode::RandomEveryNInstances:{

                // generate
                if(idInstance % loop->N == 0){

                    if(everyNRandomLoopSets.count(loop->key()) != 0){
                        everyNRandomLoopSets[loop->key()] = {};
                    }

                    for(auto &set : randomizer->randomize(setsOccurenciesStr, totalNbReps)){
                        everyNRandomLoopSets[loop->key()].push_back(std::move(set));
                    }
                }
                // retrieve
                for(const auto &set : everyNRandomLoopSets[loop->key()]){
                    setsNames.push_back(set);
                }

            break;}case Loop::Mode::ShuffleEveryNInstances:{

                // generate
                 if(idInstance % loop->N == 0){

                     if(everyNShuffleLoopSets.count(loop->key()) != 0){
                         everyNShuffleLoopSets[loop->key()] = {};
                     }

                    for(auto &set : randomizer->shuffle(setsOccurenciesStr, totalNbReps)){
                        everyNShuffleLoopSets[loop->key()].push_back(std::move(set));
                    }
                }

                // retrieve
                for(const auto &set : everyNShuffleLoopSets[loop->key()]){
                    setsNames.push_back(set);
                }

            break;}
            default:
            break;
        }

        loopsSetsNames[loop->key()] = std::move(setsNames);
        loopsCurentSetId[loop->key()] = 0;
    }

    // generate randomization for each ISI
    std::unordered_map<int, std_v1<double>> isisIntervals;
    std::unordered_map<int, size_t> isisCurentIntervalId;
    for(const auto isi : ISIs){

        size_t multiplier = 1;
        for(const auto outerLoop : isi->insideLoops){
            auto l = dynamic_cast<Loop*>(outerLoop);
            multiplier *= to_unsigned(l->nbReps);
        }

        const bool randomizeOnce = true;

        std_v1<double> intervals;
        const size_t totalNbReps = multiplier;
        if(randomizeOnce){
            if(isi->randomized){
                for(auto &isi : randomizer->randomize(isi->intervals, totalNbReps)){
                    intervals.emplace_back(std::move(isi));
                }
            }else{
                for(size_t ii = 0; ii < to_unsigned(totalNbReps); ++ii){
                    intervals.emplace_back(isi->intervals[ii%isi->intervals.size()]);
                }
            }
        }else{
            // no interest
        }

        isisIntervals[isi->key()] = std::move(intervals);
        isisCurentIntervalId[isi->key()] = 0;
    }

    for(size_t ii = 0; ii < elements.size(); ++ii){

        if(elements[ii]->type == Element::Type::Routine){

            auto routine = dynamic_cast<Routine*>(elements[ii]);

            // generate new instance element with routine
            InstanceElement instanceElem;
            instanceElem.elem = routine;

            // retrieve condition
            for(const auto &loop : routine->insideLoops){
                instanceElem.condition += loopsSetsNames[loop->key()][loopsCurentSetId[loop->key()]] + "-";
            }

            if(instanceElem.condition.size() == 0){ // if no condition, set to "default"
                instanceElem.condition = "default";
            }else{                
                instanceElem.condition.resize(instanceElem.condition.size()-1); // remove last "-"
            }
            flow.emplace_back(std::move(instanceElem));

        }else if(elements[ii]->type == Element::Type::Isi){

            auto isi = dynamic_cast<Isi*>(elements[ii]);

            // generate new instance element with ISI
            InstanceElement instanceElem;
            instanceElem.elem = isi;

            instanceElem.condition = QString::number(isisIntervals[isi->key()][isisCurentIntervalId[isi->key()]]);
            isisCurentIntervalId[isi->key()]++;
            flow.emplace_back(std::move(instanceElem));


        }else if(elements[ii]->type == Element::Type::LoopStart){

            // store information about current loop
            auto loopNode = dynamic_cast<LoopNode*>(elements[ii]);

            LoopInfo info;
            info.l       = loopNode->loop;
            info.idStart = get_index_from_loop_node(loopNode);
            info.idEnd   = get_index_from_loop_node(loopNode->loop->end);
            infos << std::move(info);

        }else if(elements[ii]->type == Element::Type::LoopEnd){

            // increment loop set and go back to loop start if necessary
            auto loop = dynamic_cast<LoopNode*>(elements[ii])->loop;
            loopsCurentSetId[loop->key()]++;

            int idInfo = -1;
            LoopInfo *inf = nullptr;
            for(int jj = 0; jj < infos.size(); ++jj){
                if(loop == infos[jj].l){
                    idInfo = jj;
                    inf = &infos[jj];
                    break;
                }
            }

            if(inf != nullptr){

                inf->currentRep++;
                if(inf->currentRep < to_signed(inf->l->nbReps)){ // continue loop
                    ii = to_unsigned(inf->idStart);
                }else{ // end of loop
                    infos.removeAt(idInfo);
                }
            }else{
                QtLogger::error("Instance generation failed due to loop error.");
            }
        }
    }


    // count iterations
    std::unordered_map<int, int> routinesIterations;
    std::unordered_map<int, std::unordered_map<QString, int>> routinesConditionsIterations;

    std::unordered_map<int, int> isisIterations;
    std::unordered_map<int, std::unordered_map<QString, int>> isisConditionsIterations;

    for(auto &element : flow){

        const int key = element.elem->key();
        const QString cond = element.condition;

        if(element.elem->type == Element::Type::Routine){

            if(routinesIterations.count(key) == 0){
                routinesIterations[key] = 1;
            }
            if(routinesConditionsIterations.count(key) == 0){
                routinesConditionsIterations[key] = {};
            }
            if(routinesConditionsIterations[key].count(cond) == 0){
                routinesConditionsIterations[key][cond] = 1;
            }

            element.elementIteration   = routinesIterations[key];
            element.conditionIteration = routinesConditionsIterations[key][cond];

            routinesIterations[key]++;
            routinesConditionsIterations[key][cond]++;

        }else if(element.elem->type == Element::Type::Isi){

            if(isisIterations.count(key) == 0){
                isisIterations[key] = 1;
            }
            if(isisConditionsIterations.count(key) == 0){
                isisConditionsIterations[key] = {};
            }
            if(isisConditionsIterations[key].count(cond) == 0){
                isisConditionsIterations[key][cond] = 1;
            }

            element.elementIteration   = isisIterations[key];
            element.conditionIteration = isisConditionsIterations[key][cond];

            isisIterations[key]++;
            isisConditionsIterations[key][cond]++;
        }
    }
}


std::unique_ptr<Instance> Instance::generate_from_one_routine(Routine *routine){

    // retrieve current condition of the selected routine
    auto instance = std::make_unique<Instance>();
    QString conditionName;
    for(const auto &condition : routine->conditions){
        if(condition->selected){
            conditionName = condition->name;
            break;
        }
    }

    if(conditionName.length() == 0){
        conditionName = routine->conditions[0]->name;
    }

    instance->flow.emplace_back(InstanceElement{0, 0, routine, conditionName});
    return instance;
}

std::unique_ptr<Instance> Instance::generate_from_element_to_the_end(const Randomizer *randomizer, const Experiment &experiment, size_t idInstance){

    // check if an element is selected
    Element *selectedElement = experiment.selectedElement;
    if(!selectedElement){
        QtLogger::message("No selected element in the flow.");
        return nullptr;
    }

    // check if element inside a loop
    if(selectedElement->insideLoops.size() > 0){
        QtLogger::message("You must select a routine not inside a loop.");
        return nullptr;
    }

    // keep only pointers to elements from the right of the selected element
    auto elements = experiment.get_elements();
    for(size_t ii = 0; ii < elements.size(); ++ii){
        if(selectedElement->key() == elements[ii]->key()){
            if(ii > 0){
                elements.erase(elements.begin(), elements.begin()+to_signed(ii-1));
            }
            break;
        }
    }

    return std::make_unique<Instance>(randomizer, elements, idInstance);
}

std::unique_ptr<Instance> Instance::generate_from_start_to_element(const Randomizer *randomizer, const Experiment &experiment, size_t idInstance){

    // check if an element is selected
    Element *selectedElement = experiment.selectedElement;
    if(!selectedElement){
        QtLogger::message("No selected element in the flow.");
        return nullptr;
    }

    // check if element inside a loop
    if(selectedElement->insideLoops.size() > 0){
        QtLogger::message("You must select a routine not inside a loop.");
        return nullptr;
    }

    // keep only pointers to elements from the start to the current selected element
    auto elements = experiment.get_elements();
    for(size_t ii = 0; ii < elements.size(); ++ii){
        if(selectedElement->key() == elements[ii]->key()){
            if(ii < elements.size()-1){
                elements.erase(elements.begin()+to_signed(ii+1), elements.end());
            }
            break;
        }
    }

    return std::make_unique<Instance>(randomizer, elements, idInstance);
}

std::unique_ptr<Instance> Instance::generate_from_full_experiment(const Randomizer *randomizer, const Experiment &experiment, size_t idInstance){
    return std::make_unique<Instance>(randomizer, experiment.get_elements(), idInstance);
}

