
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// base
#include "utility/tuple_array.hpp"

namespace tool::ex {

    using namespace std::literals::string_view_literals;

    enum class UiType : int {
        Spin_box, Float_spin_box, Double_spin_box, Line_edit, Slider_integer, Slider_double, Check_box, Text_edit, Color_pick, Vector2D, Vector3D, Transformation, Combo_box_text,Combo_box_index,
        Button, Radio_button, Generator, List_labels, Non_ui_labels, Label, Color_frame, Curve, Camera_position, Tab, NonUI, Time, PushButton, Component, ComponentsList,
        Resource, ResourcesList, Component_config,
        SizeEnum};

    using UiT  = UiType;
    using Name = std::string_view;
    using Tooltip = std::string_view;
    using Generative = bool;

    using TUiType = std::tuple<
        UiType,                 Name,                    Tooltip,                          Generative>;
    static constexpr TupleArray<30, TUiType> uiTypes{{
        TUiType
        {UiT::Resource,         "Resource"sv,            "get_resource"sv,                 true},
        {UiT::ResourcesList,    "Resources list"sv,      "get_resource_list"sv,            true},
        {UiT::Component,        "Component"sv,           "get_component"sv,                true},
        {UiT::Component_config, "Component config"sv,    ""sv,                             true},
        {UiT::ComponentsList,   "Components list"sv,     "get_component_list"sv,           true},
        {UiT::Spin_box,         "Integer spin box"sv,    "int"sv,                          true},
        {UiT::Float_spin_box,   "Float spin box"sv,      "float"sv,                        true},
        {UiT::Slider_integer,   "Integer slider"sv,      "int"sv,                          true},
        {UiT::Slider_double,    "Float values slider"sv, "float"sv,                        true},
        {UiT::Check_box,        "Check box"sv,           "bool"sv,                         true},
        {UiT::Line_edit,        "Line text editor"sv,    "string"sv,                       true},
        {UiT::Text_edit,        "Block text editor"sv,   "string"sv,                       true},
        {UiT::Color_pick,       "Color pick"sv,          "get_color"sv,                    true},
        {UiT::Combo_box_text,   "Combo box text"sv,      "string"sv,                       true},
        {UiT::Combo_box_index,  "Combo box index"sv,     "int"sv,                          true},
        {UiT::Label,            "Label"sv,               "string"sv,                       true},
        {UiT::Vector2D,         "Vector 2D"sv,           "Vector2 or List<float>"sv,       true},
        {UiT::Vector3D,         "Vector 3D"sv,           "Vector3 or List<float>"sv,       true},
        {UiT::Button,           "Action button"sv,       "string"sv,                       false},
        {UiT::Double_spin_box,  "Double spin box"sv,     "double"sv,                       false},
        {UiT::Radio_button,     "Radio buttons"sv,       "bool"sv,                         false},
        {UiT::Generator,        "Generator"sv,           ""sv,                             false},
        {UiT::List_labels,      "List of lines"sv,       "List<string>"sv,                 false},
        {UiT::Transformation,   "Transformation"sv,      "Transform or List<Vector3>"sv,   true},
        {UiT::Non_ui_labels,    "Non ui labels"sv,       "List<string>"sv,                 false},
        {UiT::Curve,            "Curve"sv,               "List<float>"sv,                  false},
        {UiT::Color_frame,      "Color Frame"sv,         "bool"sv,                         false},
        {UiT::Camera_position,  "Camera position"sv,     "string"sv,                       false},
        {UiT::Tab,              "Tab"sv,                 "string"sv,                       false},
        {UiT::NonUI,            "No UI"sv,               ""sv,                             false},
    }};

    constexpr std::optional<UiType> get_ui_type(Name name) {
        return uiTypes.optional_at<1,0>(name);
    }

    constexpr Name get_name(UiType t) {
        return uiTypes.at<0,1>(t);
    }

    constexpr auto get_ui_types() {
        return uiTypes.tuple_column<0>();
    }

    constexpr auto get_names() {
        return uiTypes.tuple_column<1>();
    }

    constexpr Name get_tooltip_string(UiType t) {
        return uiTypes.at<0,2>(t);
    }

    constexpr bool is_generative(UiType t){
        return uiTypes.at<0,3>(t);
    }
}

