
/***********************************************************************************
** exvr-designer                                                                  **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

#include "flow_sequence_object.hpp"

// local
#include "experiment/global_signals.hpp"

using namespace tool::ex;

void FlowSequenceO::reset(){
    nodesElements.clear();
    routinesElements.clear();
    ISIsElements.clear();
    loopsStart.clear();
    loopsEnd.clear();
    loopsElements.clear();
    elements.clear();
}

void FlowSequenceO::update_from_experiment(Experiment *exp){

    std_v1<NodeFlowElementO*>                   newNodesElements;
    std_v1<RoutineFlowElementO*>                newRoutinesElements;
    std_v1<IsiFlowElementO*>                    newISIsElements;
    std_v1<LoopNodeFlowElementO*>               newLoopsStart;
    std_v1<LoopNodeFlowElementO*>               newLoopsEnd;
    std_v1<std::unique_ptr<LoopFlowElementO>>   newLoopsElements;   // not in elements
    std_v1<std::unique_ptr<FlowElementO>>       newElements;        // all elements

    for(auto &newElement : exp->elements){

        bool found = false;
        std::unique_ptr<FlowElementO> oldE = nullptr;

        for(auto &oldElement : elements){
            if(oldElement == nullptr){
                continue;
            }

            if(newElement->key() == oldElement->key.v){
                found = true;
                oldE = std::move(oldElement);
                oldElement = nullptr;
                break;
            }
        }

        if(found){ // move from previous array
            // update
            oldE->update(newElement.get());
            switch (newElement->type) {
                case FlowElement::Type::Node:{
                    newNodesElements.emplace_back(dynamic_cast<NodeFlowElementO*>(oldE.get()));
                    newElements.emplace_back(std::move(oldE));
                }break;{
                case FlowElement::Type::Routine:
                    newRoutinesElements.emplace_back(dynamic_cast<RoutineFlowElementO*>(oldE.get()));
                    newElements.emplace_back(std::move(oldE));
                }break;{
                case FlowElement::Type::Isi:
                    newISIsElements.emplace_back(dynamic_cast<IsiFlowElementO*>(oldE.get()));
                    newElements.emplace_back(std::move(oldE));
                }break;{
                case FlowElement::Type::LoopStart:
                    newLoopsStart.emplace_back(dynamic_cast<LoopNodeFlowElementO*>(oldE.get()));
                    newElements.emplace_back(std::move(oldE));
                }break;{
                case FlowElement::Type::LoopEnd:
                    newLoopsEnd.emplace_back(dynamic_cast<LoopNodeFlowElementO*>(oldE.get()));
                    newElements.emplace_back(std::move(oldE));
                }break;
                default:
                break;
            }
        }else{ // create new
            switch (newElement->type) {{
                case FlowElement::Type::Node:
                    auto nodeElement = std::make_unique<NodeFlowElementO>(dynamic_cast<NodeFlow*>(newElement.get()));
                    newNodesElements.emplace_back(nodeElement.get());
                    newElements.emplace_back(std::move(nodeElement));
                }break;{
                case FlowElement::Type::Routine:
                    auto routineElement = std::make_unique<RoutineFlowElementO>(dynamic_cast<Routine*>(newElement.get()));
                    newRoutinesElements.emplace_back(routineElement.get());
                    newElements.emplace_back(std::move(routineElement));
                }break;{
                case FlowElement::Type::Isi:
                    auto isiElement = std::make_unique<IsiFlowElementO>(dynamic_cast<Isi*>(newElement.get()));
                    newISIsElements.emplace_back(isiElement.get());
                    newElements.emplace_back(std::move(isiElement));
                }break;{
                case FlowElement::Type::LoopStart:
                    auto loopStart = std::make_unique<LoopNodeFlowElementO>(dynamic_cast<LoopNode*>(newElement.get()));
                    newLoopsStart.emplace_back(loopStart.get());
                    newElements.emplace_back(std::move(loopStart));
                }break;{
                case FlowElement::Type::LoopEnd:
                    auto loopEnd = std::make_unique<LoopNodeFlowElementO>(dynamic_cast<LoopNode*>(newElement.get()));
                    newLoopsEnd.emplace_back(loopEnd.get());
                    newElements.emplace_back(std::move(loopEnd));
                }break;
                default:
                break;
            }
        }
    }

    nodesElements   = std::move(newNodesElements);
    routinesElements= std::move(newRoutinesElements);
    ISIsElements    = std::move(newISIsElements);
    loopsStart      = std::move(newLoopsStart);
    loopsEnd        = std::move(newLoopsEnd);
    elements        = std::move(newElements);

    // associate loops
    for(auto &newLoop : exp->loops){

        bool found = false;
        std::unique_ptr<LoopFlowElementO> oldL = nullptr;

        for(auto &oldLoop : loopsElements){
            if(oldLoop == nullptr){
                continue;
            }

            if(newLoop->key() == oldLoop->key.v){
                found = true;
                oldL = std::move(oldLoop);
                oldLoop = nullptr;
                break;
            }
        }

        if(found){
            oldL->update(newLoop.get());
            auto loopElementPtr = oldL.get();
            auto start = dynamic_cast<LoopNodeFlowElementO*>(elements[exp->get_element_position(newLoop->start)].get());
            auto end   = dynamic_cast<LoopNodeFlowElementO*>(elements[exp->get_element_position(newLoop->end)].get());
            loopElementPtr->startLoopNode = start;
            loopElementPtr->endLoopNode   = end;
            newLoopsElements.emplace_back(std::move(oldL));
        }else{
            auto loopElement = std::make_unique<LoopFlowElementO>(newLoop.get());
            auto loopElementPtr = loopElement.get();
            auto start = dynamic_cast<LoopNodeFlowElementO*>(elements[exp->get_element_position(newLoop->start)].get());
            auto end   = dynamic_cast<LoopNodeFlowElementO*>(elements[exp->get_element_position(newLoop->end)].get());
            loopElementPtr->startLoopNode = start;
            loopElementPtr->endLoopNode   = end;
            start->loopElement = loopElementPtr;
            end->loopElement   = loopElementPtr;
            newLoopsElements.emplace_back(std::move(loopElement));
        }
    }

    loopsElements = std::move(newLoopsElements);

    // active move elements
    for(auto &element : elements){
        if(element->type == FlowElement::Type::Node){
            continue;
        }

        auto moveElem = dynamic_cast<MovableFlowElementO*>(element.get());
        moveElem->canMoveToLeft = true;
        moveElem->canMoveToRight = true;

        size_t id = flow_position(element.get());
        moveElem->canMoveToLeft  &= id > 1;
        moveElem->canMoveToRight &= id < elements.size()-2;

        auto previousElem = moveElem->canMoveToLeft  ? dynamic_cast<MovableFlowElementO*>(elements[id-2].get()) : nullptr;
        auto nextElem     = moveElem->canMoveToRight ? dynamic_cast<MovableFlowElementO*>(elements[id+2].get()) : nullptr;

        if(previousElem){
            if(previousElem->type == FlowElement::Type::LoopStart && moveElem->type == FlowElement::Type::LoopEnd){
                moveElem->canMoveToLeft = false;
            }
            if(previousElem->type == FlowElement::Type::LoopStart && moveElem->type == FlowElement::Type::LoopStart){
                moveElem->canMoveToLeft = false;
            }
        }
        if(nextElem){
            if(nextElem->type == FlowElement::Type::LoopEnd && moveElem->type == FlowElement::Type::LoopStart){
                moveElem->canMoveToRight = false;
            }
            if(nextElem->type == FlowElement::Type::LoopEnd && moveElem->type == FlowElement::Type::LoopEnd){
                moveElem->canMoveToRight = false;
            }
        }
    }
}

FlowElementO *FlowSequenceO::mouse_on_element(const QPoint &mousePos){

    for(auto& elem : elements){
        if(elem->uiElemRect.contains(mousePos)){
            return elem.get();
        }
    }
    return nullptr;
}

LoopFlowElementO *FlowSequenceO::mouse_on_loop(const QPoint &mousePos){

    for(auto& elem : loopsElements){
        if(elem->uiElemRect.contains(mousePos)){
            return elem.get();
        }
    }
    return nullptr;
}

void FlowSequenceO::check_click_on_elements(QPoint clickPos) noexcept{

    // check in elements
    if(auto selectedElement = mouse_on_element(clickPos); selectedElement != nullptr){
        emit GSignals::get()->select_element_signal(selectedElement->key, true);
        return;
    }

    // check in loops
    if(auto selectedLoop = mouse_on_loop(clickPos); selectedLoop != nullptr){
        emit GSignals::get()->select_element_signal(selectedLoop->key, true);
        return;
    }

    // check in add elements
    for(auto& node : nodesElements){

        if(node == nullptr){
            return;
        }

        if(node->is_selected()){

            if(node->addRoutine->uiElemRect.contains(clickPos)){
                emit GSignals::get()->add_element_signal(FlowElement::Type::Routine,   flow_position(node));
                return;
            }else if(node->addIsi->uiElemRect.contains(clickPos)){
                emit GSignals::get()->add_element_signal(FlowElement::Type::Isi,       flow_position(node));
                return;
            }else if(node->addLoop->uiElemRect.contains(clickPos)){
                emit GSignals::get()->add_element_signal(FlowElement::Type::Loop,      flow_position(node));
                return;
            }
        }
    }

    // check in remove and move elements
    for(const auto& element : elements){

        if(element->type == FlowElement::Type::Node || !element->is_selected()){
            continue;
        }
        const auto moveElem =  dynamic_cast<MovableFlowElementO*>(element.get());
        if(moveElem->removeElement->uiElemRect.contains(clickPos)){
            emit GSignals::get()->remove_selected_element_signal();
            return;
        }

        int id = to_signed(flow_position(moveElem));
        if(moveElem->moveLeftElement->uiElemRect.contains(clickPos) && id > 1){
            emit GSignals::get()->move_element_left_signal(to_unsigned(id));
            return;
        }

        if(moveElem->moveRightElement->uiElemRect.contains(clickPos) && to_unsigned(id) < elements.size()-2){
            emit GSignals::get()->move_element_right_signal(to_unsigned(id));
            return;
        }
    }

    emit GSignals::get()->unselect_element_signal(true);
}

void FlowSequenceO::draw(QPainter &painter, qreal zoomLevel){

    for(auto& element : elements){
        element->draw(painter, zoomLevel);
    }

    for(auto& loop : loopsElements){
        loop->draw(painter, zoomLevel);
    }
}

FlowElementO *FlowSequenceO::current_selection() const{

    for(const auto &element : elements){
        if(element->is_selected()){
            return element.get();
        }
    }
    for(const auto &loop : loopsElements){
        if(loop->is_selected()){
            return loop.get();
        }
    }
    return nullptr;
}

size_t FlowSequenceO::flow_position(FlowElementO *elem) const{
    for(size_t ii = 0; ii < elements.size(); ++ii){
        if(elements[ii].get() == elem){
            return ii;
        }
    }
    qCritical() << "Cannot find flow element " << elem->key.v;
    return 0;
}
