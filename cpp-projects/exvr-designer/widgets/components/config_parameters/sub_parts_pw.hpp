
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QFileDialog>

// base
#include "geometry/point3.hpp"

// local
#include "ex_parameters_generator_w.hpp"
#include "ex_transformation_w.hpp"
#include "ex_float_spin_box_w.hpp"
#include "ex_spin_box_w.hpp"
#include "ex_vector3d_w.hpp"
#include "ex_combo_box_text_w.hpp"
#include "ex_resource_w.hpp"
#include "ex_checkbox_w.hpp"
#include "ex_select_color_w.hpp"
#include "ex_text_edit_w.hpp"
#include "ex_radio_button_w.hpp"

namespace tool::ex {


class ConfigParametersSubPart{
public:

    void block_signals(bool state);

    QFrame *frame = nullptr;
    std_v1<std::pair<QString, ExBaseW*>> inputUiElements;
};

class DefaultTransformSubPart : public ConfigParametersSubPart{
public :

    DefaultTransformSubPart();

    DefaultTransformSubPart *init_widget(QString title = "Transform", QString name = "transform");

    ExTransformationW tr;
    ExCheckBoxW doNotApply;
};

class WordSpaceCameraCanvasSubPart :  public ConfigParametersSubPart{

public:

    ExFloatSpinBoxW distance;
    ExFloatSpinBoxW scaleFactor;
    ExSpinBoxW width;
    ExSpinBoxW height;
    ExFloatSpinBoxW pivotX;
    ExFloatSpinBoxW pivotY;
    ExVector3dW rotation;

    WordSpaceCameraCanvasSubPart();

    WordSpaceCameraCanvasSubPart *init_widget();
};

class WordSpaceCanvasSubPart :  public ConfigParametersSubPart{
public:

    ExSpinBoxW width;
    ExSpinBoxW height;
    ExFloatSpinBoxW scaleFactor;
    ExVector3dW position;
    ExVector3dW rotation;

    WordSpaceCanvasSubPart();

    WordSpaceCanvasSubPart *init_widget();
};

class EyeRendererSubPart : public ConfigParametersSubPart{
public:

    EyeRendererSubPart();

    EyeRendererSubPart *init_widget();

    QLabel t;
    ExComboBoxTextW eye;
};

class TextSubPart : public ConfigParametersSubPart{
public:

    TextSubPart(bool removeInputText = false);

    TextSubPart *init_widget(QString baseName, QString defaultText = "Text...");

    QWidget *textW = nullptr;
    QWidget *settingsW = nullptr;

    // text
    ExResourceW resourceText;
    ExTextEditW text;
    ExCheckBoxW wrapping;
    ExCheckBoxW richtext;
    ExCheckBoxW automaticFontSize;
    ExFloatSpinBoxW fontSize;
    // font type
    // settings
    // # style
    ExCheckBoxW italic;
    ExCheckBoxW bold;
    ExCheckBoxW highlight;
    ExCheckBoxW underline;
    ExRadioButtonW none;
    ExRadioButtonW lowerCase;
    ExRadioButtonW upperCase;
    // # alignment
    ExComboBoxTextW alignment;
    // # spacing
    ExFloatSpinBoxW paragraphSpacing;
    ExFloatSpinBoxW lineSpacing;
    ExFloatSpinBoxW wordSpacing;
    ExFloatSpinBoxW characterSpacing;
    // # colors
    ExSelectColorW faceColor;
    ExSelectColorW outlineColor;
    // # outline
    ExFloatSpinBoxW outlineWidth;

private:
    bool noInputText = false;
};

}
