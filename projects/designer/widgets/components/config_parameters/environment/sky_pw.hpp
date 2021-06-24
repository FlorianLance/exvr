/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "config_pw.hpp"

// Qt
#include "ex_checkbox_w.hpp"
#include "ex_line_edit_w.hpp"
#include "ex_select_color_w.hpp"
#include "ex_resource_w.hpp"
#include "ex_combo_box_index_w.hpp"

namespace tool::ex {

class SkyInitConfigParametersW : public ConfigParametersW{

public :

    void insert_widgets() override{}
    void init_and_register_widgets() override{}
    void create_connections() override{}
    void late_update_ui() override{}

};

class SkyConfigParametersW : public ConfigParametersW{

public :

    QTabWidget *m_tabs = nullptr;

    // sun light
    QWidget *m_sunLightW = nullptr;
    QTabWidget *m_sunLightTab = nullptr;
    ExVector3dW m_sunRotation;
    ExFloatSpinBoxW m_sunIntensity;
    ExFloatSpinBoxW m_sunBounceIntensity;
    ExSelectColorW m_sunColor;
    ExComboBoxIndexW m_sunShadowMode;
    ExFloatSpinBoxW m_sunShadowStrength;
    ExFloatSpinBoxW m_sunShadowBias;
    ExFloatSpinBoxW m_sunShadowNormalBias;
    ExFloatSpinBoxW m_sunShadowNearPlane;

    // ambient light
    QWidget *m_ambientLightW = nullptr;
    QTabWidget *m_ambientTab = nullptr;
    ExComboBoxIndexW m_ambientMode;
    ExFloatSpinBoxW m_ambientIntensity;
    ExSelectColorW m_ambientFlatColor;
    ExSelectColorW m_ambientGradientGroundColor;
    ExSelectColorW m_ambientGradientEquatorColor;
    ExSelectColorW m_ambientGradientSkyColor;

    // skybox
    QWidget *m_skyboxW = nullptr;
    QTabWidget *m_skyboxTab = nullptr;
    ExCheckBoxW m_zPlusInvert;
    ExCheckBoxW m_zMinusInvert;
    ExCheckBoxW m_xPlusInvert;
    ExCheckBoxW m_xMinusInvert;
    ExCheckBoxW m_yPlusInvert;
    ExCheckBoxW m_yMinusInvert;
    ExCheckBoxW m_panoramicInvert;
    ExCheckBoxW m_cubeMapInvert;

    ExResourceW m_xMinus;
    ExResourceW m_yMinus;
    ExResourceW m_zMinus;
    ExResourceW m_xPlus;
    ExResourceW m_yPlus;
    ExResourceW m_zPlus;
    ExResourceW m_panoramic;
    ExResourceW m_cubemap;

    ExComboBoxIndexW m_mode;    
    ExSelectColorW m_backgroundColor;

    ExSelectColorW m_6SidedTintColor;
    ExFloatSpinBoxW m_6sidedExposure;
    ExFloatSpinBoxW m_6sidedRotation;

    ExSelectColorW m_cubeMapTintColor;
    ExFloatSpinBoxW m_cubeMapExposure;
    ExFloatSpinBoxW m_cubeMapRotation;

    ExSelectColorW m_panoramicTintColor;
    ExFloatSpinBoxW m_panoramicExposure;
    ExFloatSpinBoxW m_panoramicRotation;
    ExComboBoxIndexW m_panoramicMapping;
    ExCheckBoxW m_panoramicMirrorBack;
    ExComboBoxIndexW m_panoramicType;
    ExComboBoxIndexW m_panoramicLayout;

    ExComboBoxIndexW m_proceduralSun;
    ExFloatSpinBoxW m_proceduralSunSize;
    ExFloatSpinBoxW m_proceduralConvergence;
    ExFloatSpinBoxW m_proceduralAtmoshpereThickness;
    ExSelectColorW m_proceduralSkyTint;
    ExSelectColorW m_proceduralGroundColor;
    ExFloatSpinBoxW m_proceduralExposure;

    void insert_widgets() override;
    void init_and_register_widgets() override;
    void create_connections() override;
    void late_update_ui() override;
};

}
