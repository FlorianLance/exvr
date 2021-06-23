
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


#include "ex_transformation_w.hpp"

using namespace tool;
using namespace tool::ex;

ExTransformationW::ExTransformationW() : ExItemW<QFrame>(UiType::Transformation){

    w->setFrameShadow(QFrame::Raised);
    w->setFrameShape(QFrame::Shape::Box);

    // T    T       T       T
    // TTr  trX     trY     trZ
    // TRot rotX    rotY    rotZ
    // TSc  scX     scY     scZ
    layout = new QGridLayout();
    w->setLayout(layout);
    layout->addWidget(name = ui::W::txt("Default"),0,0,1,4);
    layout->addWidget(ui::W::txt("Translation"), 1, 0, 1, 1);
    layout->addWidget(trX(), 1, 1, 1, 1);
    layout->addWidget(trY(), 1, 2, 1, 1);
    layout->addWidget(trZ(), 1, 3, 1, 1);
    layout->addWidget(ui::W::txt("Rotation"), 2, 0, 1, 1);
    layout->addWidget(rotX(), 2, 1, 1, 1);
    layout->addWidget(rotY(), 2, 2, 1, 1);
    layout->addWidget(rotZ(), 2, 3, 1, 1);
    layout->addWidget(ui::W::txt("Scale"), 3, 0, 1, 1);
    layout->addWidget(scX(), 3, 1, 1, 1);
    layout->addWidget(scY(), 3, 2, 1, 1);
    layout->addWidget(scZ(), 3, 3, 1, 1);

    connect(&trX,   &ExBaseW::ui_change_signal, this, &ExBaseW::ui_change_signal);
    connect(&trY,   &ExBaseW::ui_change_signal, this, &ExBaseW::ui_change_signal);
    connect(&trZ,   &ExBaseW::ui_change_signal, this, &ExBaseW::ui_change_signal);
    connect(&rotX,  &ExBaseW::ui_change_signal, this, &ExBaseW::ui_change_signal);
    connect(&rotY,  &ExBaseW::ui_change_signal, this, &ExBaseW::ui_change_signal);
    connect(&rotZ,  &ExBaseW::ui_change_signal, this, &ExBaseW::ui_change_signal);
    connect(&scX,   &ExBaseW::ui_change_signal, this, &ExBaseW::ui_change_signal);
    connect(&scY,   &ExBaseW::ui_change_signal, this, &ExBaseW::ui_change_signal);
    connect(&scZ,   &ExBaseW::ui_change_signal, this, &ExBaseW::ui_change_signal);
}

ExTransformationW *ExTransformationW::init_widget(const QString &title, Vector3dSettings transS, Vector3dSettings rotationS, Vector3dSettings scaleS, bool enabled){

    name->setText(QSL("<b>") % title % QSL("</b>"));

    trX.init_widget(transS.sX);
    trY.init_widget(transS.sY);
    trZ.init_widget(transS.sZ);
    rotX.init_widget(rotationS.sX);
    rotY.init_widget(rotationS.sY);
    rotZ.init_widget(rotationS.sZ);
    scX.init_widget(scaleS.sX);
    scY.init_widget(scaleS.sY);
    scZ.init_widget(scaleS.sZ);
    w->setEnabled(enabled);
    return this;
}

void ExTransformationW::init_connection(const QString &nameParam){

    trX.init_connection(nameParam);
    trY.init_connection(nameParam);
    trZ.init_connection(nameParam);
    rotX.init_connection(nameParam);
    rotY.init_connection(nameParam);
    rotZ.init_connection(nameParam);
    scX.init_connection(nameParam);
    scY.init_connection(nameParam);
    scZ.init_connection(nameParam);
}


void ExTransformationW::update_from_arg(const Arg &arg){


    ExItemW::update_from_arg(arg);

    auto size = arg.count();
    if(size < 9){
        qWarning() << "Invalid argument value " << arg.name << " for transformation widget.";
        return;
    }

    w->blockSignals(true);

    if(generatorName.length() > 0){

        if(arg.generator.decimals.has_value()){
            if(const auto split = arg.generator.decimals.value().split(arg.separator()); split.size() > 2){
                set_trans_decimals(split[0].toInt());
                set_rotation_decimals(split[1].toInt());
                set_scale_decimals(split[2].toInt());
            }
        }

        if(arg.generator.min.has_value()){
            if(const auto split = arg.generator.min.value().split(arg.separator()); split.size() > 2){
                const auto tr = split[0].toDouble();
                const auto rt = split[1].toDouble();
                const auto sc = split[2].toDouble();
                set_trans_min({tr,tr,tr});
                set_rotation_min({rt,rt,rt});
                set_scale_min({sc,sc,sc});
            }
        }

        if(arg.generator.max.has_value()){
            if(const auto split = arg.generator.max.value().split(arg.separator()); split.size() > 2){
                const auto tr = split[0].toDouble();
                const auto rt = split[1].toDouble();
                const auto sc = split[2].toDouble();
                set_trans_max({tr,tr,tr});
                set_rotation_max({rt,rt,rt});
                set_scale_max({sc,sc,sc});
            }
        }

        if(arg.generator.step.has_value()){
            if(const auto split = arg.generator.step.value().split(arg.separator()); split.size() > 2){
                const auto tr = split[0].toDouble();
                const auto rt = split[1].toDouble();
                const auto sc = split[2].toDouble();
                set_trans_steps({tr,tr,tr});
                set_rotation_steps({rt,rt,rt});
                set_scale_steps({sc,sc,sc});
            }
        }
    }

    if(auto splitV = arg.value().split(arg.separator()); splitV.size() > 8){
        set_trans_values({splitV[0].toDouble(),splitV[1].toDouble(),splitV[2].toDouble()});
        set_rotation_values({splitV[3].toDouble(),splitV[4].toDouble(),splitV[5].toDouble()});
        set_scale_values({splitV[6].toDouble(),splitV[7].toDouble(),splitV[8].toDouble()});
    }

    w->blockSignals(false);
}

Arg ExTransformationW::convert_to_arg() const{

    Arg arg = ExItemW::convert_to_arg();    
    arg.init_from_args({
        trX.convert_to_arg(),trY.convert_to_arg(),trZ.convert_to_arg(),
        rotX.convert_to_arg(),rotY.convert_to_arg(),rotZ.convert_to_arg(),
        scX.convert_to_arg(),scY.convert_to_arg(),scZ.convert_to_arg()},
        " ", UnityType::System_single
    );

    // generator
    if(generatorName.length() > 0){
        arg.generator.min = QString::number(trX.w->minimum())   % arg.separator() %
                            QString::number(rotX.w->minimum())  % arg.separator() %
                            QString::number(scX.w->minimum());

        arg.generator.max = QString::number(trX.w->maximum())   % arg.separator() %
                            QString::number(rotX.w->maximum())  % arg.separator() %
                            QString::number(scX.w->maximum());

        arg.generator.step = QString::number(trX.w->singleStep())   % arg.separator() %
                             QString::number(rotX.w->singleStep())  % arg.separator() %
                             QString::number(scX.w->singleStep());

        arg.generator.decimals = QString::number(trX.w->decimals())   % arg.separator() %
                                 QString::number(rotX.w->decimals())  % arg.separator() %
                                 QString::number(scX.w->decimals());
    }

    return arg;
}

void ExTransformationW::set_from_transform(ExTransformationW *tr){
    trX.w->setValue(tr->trX.w->value());
    trY.w->setValue(tr->trY.w->value());
    trZ.w->setValue(tr->trZ.w->value());
    rotX.w->setValue(tr->rotX.w->value());
    rotY.w->setValue(tr->rotY.w->value());
    rotZ.w->setValue(tr->rotZ.w->value());
    scX.w->setValue(tr->scX.w->value());
    scY.w->setValue(tr->scY.w->value());
    scZ.w->setValue(tr->scZ.w->value());
}

void ExTransformationW::set_enable_state(bool enableTranslation, bool enableRotation, bool enableScale){
    trX.w->setEnabled(enableTranslation);
    trY.w->setEnabled(enableTranslation);
    trZ.w->setEnabled(enableTranslation);
    rotX.w->setEnabled(enableRotation);
    rotY.w->setEnabled(enableRotation);
    rotZ.w->setEnabled(enableRotation);
    scX.w->setEnabled(enableScale);
    scY.w->setEnabled(enableScale);
    scZ.w->setEnabled(enableScale);
}

void ExTransformationW::set_trans_decimals(int d){
    trX.blockSignals(true);
    trY.blockSignals(true);
    trZ.blockSignals(true);
    trX.w->setDecimals(d);
    trY.w->setDecimals(d);
    trZ.w->setDecimals(d);
    trX.blockSignals(false);
    trY.blockSignals(false);
    trZ.blockSignals(false);
}

void ExTransformationW::set_trans_min(geo::Pt3<qreal> m){
    trX.blockSignals(true);
    trY.blockSignals(true);
    trZ.blockSignals(true);
    trX.w->setMinimum(m.x());
    trY.w->setMinimum(m.y());
    trZ.w->setMinimum(m.z());
    trX.blockSignals(false);
    trY.blockSignals(false);
    trZ.blockSignals(false);
}

void ExTransformationW::set_trans_max(geo::Pt3<qreal> m){
    trX.blockSignals(true);
    trY.blockSignals(true);
    trZ.blockSignals(true);
    trX.w->setMaximum(m.x());
    trY.w->setMaximum(m.y());
    trZ.w->setMaximum(m.z());
    trX.blockSignals(false);
    trY.blockSignals(false);
    trZ.blockSignals(false);
}

void ExTransformationW::set_trans_steps(geo::Pt3<qreal> s){
    trX.blockSignals(true);
    trY.blockSignals(true);
    trZ.blockSignals(true);
    trX.w->setSingleStep(s.x());
    trY.w->setSingleStep(s.y());
    trZ.w->setSingleStep(s.z());
    trX.blockSignals(false);
    trY.blockSignals(false);
    trZ.blockSignals(false);
}

void ExTransformationW::set_trans_values(geo::Pt3<qreal> v){
    trX.blockSignals(true);
    trY.blockSignals(true);
    trZ.blockSignals(true);
    trX.w->setValue(v.x());
    trY.w->setValue(v.y());
    trZ.w->setValue(v.z());
    trX.blockSignals(false);
    trY.blockSignals(false);
    trZ.blockSignals(false);
}

void ExTransformationW::set_rotation_decimals(int d){
    rotX.blockSignals(true);
    rotY.blockSignals(true);
    rotZ.blockSignals(true);
    rotX.w->setDecimals(d);
    rotY.w->setDecimals(d);
    rotZ.w->setDecimals(d);
    rotX.blockSignals(false);
    rotY.blockSignals(false);
    rotZ.blockSignals(false);
}

void ExTransformationW::set_rotation_min(geo::Pt3<qreal> m){
    rotX.blockSignals(true);
    rotY.blockSignals(true);
    rotZ.blockSignals(true);
    rotX.w->setMinimum(m.x());
    rotY.w->setMinimum(m.y());
    rotZ.w->setMinimum(m.z());
    rotX.blockSignals(false);
    rotY.blockSignals(false);
    rotZ.blockSignals(false);
}

void ExTransformationW::set_rotation_max(geo::Pt3<qreal> m){
    rotX.blockSignals(true);
    rotY.blockSignals(true);
    rotZ.blockSignals(true);
    rotX.w->setMaximum(m.x());
    rotY.w->setMaximum(m.y());
    rotZ.w->setMaximum(m.z());
    rotX.blockSignals(false);
    rotY.blockSignals(false);
    rotZ.blockSignals(false);
}

void ExTransformationW::set_rotation_steps(geo::Pt3<qreal> s){
    rotX.blockSignals(true);
    rotY.blockSignals(true);
    rotZ.blockSignals(true);
    rotX.w->setSingleStep(s.x());
    rotY.w->setSingleStep(s.y());
    rotZ.w->setSingleStep(s.z());
    rotX.blockSignals(false);
    rotY.blockSignals(false);
    rotZ.blockSignals(false);
}

void ExTransformationW::set_rotation_values(geo::Pt3<qreal> v){
    rotX.blockSignals(true);
    rotY.blockSignals(true);
    rotZ.blockSignals(true);
    rotX.w->setValue(v.x());
    rotY.w->setValue(v.y());
    rotZ.w->setValue(v.z());
    rotX.blockSignals(false);
    rotY.blockSignals(false);
    rotZ.blockSignals(false);
}

void ExTransformationW::set_scale_decimals(int d){
    scX.blockSignals(true);
    scY.blockSignals(true);
    scZ.blockSignals(true);
    scX.w->setDecimals(d);
    scY.w->setDecimals(d);
    scZ.w->setDecimals(d);
    scX.blockSignals(false);
    scY.blockSignals(false);
    scZ.blockSignals(false);
}

void ExTransformationW::set_scale_min(geo::Pt3<qreal> m){
    scX.blockSignals(true);
    scY.blockSignals(true);
    scZ.blockSignals(true);
    scX.w->setMinimum(m.x());
    scY.w->setMinimum(m.y());
    scZ.w->setMinimum(m.z());
    scX.blockSignals(false);
    scY.blockSignals(false);
    scZ.blockSignals(false);
}

void ExTransformationW::set_scale_max(geo::Pt3<qreal> m){
    scX.blockSignals(true);
    scY.blockSignals(true);
    scZ.blockSignals(true);
    scX.w->setMaximum(m.x());
    scY.w->setMaximum(m.y());
    scZ.w->setMaximum(m.z());
    scX.blockSignals(false);
    scY.blockSignals(false);
    scZ.blockSignals(false);
}

void ExTransformationW::set_scale_steps(geo::Pt3<qreal> s){
    scX.blockSignals(true);
    scY.blockSignals(true);
    scZ.blockSignals(true);
    scX.w->setSingleStep(s.x());
    scY.w->setSingleStep(s.y());
    scZ.w->setSingleStep(s.z());
    scX.blockSignals(false);
    scY.blockSignals(false);
    scZ.blockSignals(false);
}

void ExTransformationW::set_scale_values(geo::Pt3<qreal> v){
    scX.blockSignals(true);
    scY.blockSignals(true);
    scZ.blockSignals(true);
    scX.w->setValue(v.x());
    scY.w->setValue(v.y());
    scZ.w->setValue(v.z());
    scX.blockSignals(false);
    scY.blockSignals(false);
    scZ.blockSignals(false);
}

void ExTransformationW::set_generator(QString genName){
    ExItemW::set_generator(genName);
    trX.set_generator(genName);
    trY.set_generator(genName);
    trZ.set_generator(genName);
    rotX.set_generator(genName);
    rotY.set_generator(genName);
    rotZ.set_generator(genName);
    scX.set_generator(genName);
    scY.set_generator(genName);
    scZ.set_generator(genName);
}

