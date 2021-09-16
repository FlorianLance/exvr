
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

// qt-utility
#include "ex_widgets/ex_base_w.hpp"

namespace tool::ex {

class ConfigParametersSubPart{
protected:
    void block_signals(bool state);
    void add_input_ui(ExBaseW *w);
    void add_inputs_ui(std::vector<ExBaseW *> widgets);
public:
    std_v1<std::pair<QStringView, ExBaseW*>> inputUiElements;
    QFrame *frame = nullptr;
};

class TransformSubPart : public ConfigParametersSubPart{
public :
    TransformSubPart(QString name = "transform");
    ~TransformSubPart();
    TransformSubPart *init_widget(QString title = "Transform");
    void set_enable_state(bool s1, bool s2, bool s3);
    void set_scale_values(geo::Pt3d values);
    void set_rotation_values(geo::Pt3<qreal> v);
    void set_trans_decimals(int d);
    void set_trans_steps(geo::Pt3<qreal> s);
private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;
};

class WordSpaceCameraCanvasSubPart :  public ConfigParametersSubPart{
public:
    WordSpaceCameraCanvasSubPart();
    ~WordSpaceCameraCanvasSubPart();
    WordSpaceCameraCanvasSubPart *init_widget();
    void set_wh_enable_state(bool w, bool h);
private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;
};

class WordSpaceCanvasSubPart :  public ConfigParametersSubPart{
public:
    WordSpaceCanvasSubPart();
    ~WordSpaceCanvasSubPart();
    WordSpaceCanvasSubPart *init_widget();
    void set_wh_enable_state(bool w, bool h);
    void set_position_enable_state(bool x, bool y, bool z);
private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;
};

class EyeRendererSubPart : public ConfigParametersSubPart{
public:
    EyeRendererSubPart();
    ~EyeRendererSubPart();
    EyeRendererSubPart *init_widget();
private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;
};

class TextSubPart : public ConfigParametersSubPart{
public:
    TextSubPart(QString name, bool removeInputText = false);
    ~TextSubPart();
    TextSubPart *init_widget(QString defaultText = "Text...");

    QWidget *textW = nullptr;
    QWidget *settingsW = nullptr;

private:
    struct Impl;
    std::unique_ptr<Impl> m_p = nullptr;
};

}
