
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// qt-utility
#include "data/argument.hpp"

// local
#include "connection_node.hpp"

namespace tool::ex {


    struct Connector;
    using ConnectorUP = std::unique_ptr<Connector>;

    struct Connector{

        // # Connector categories
        enum class Category : int {
            Convertor=0, Function, Generator, Operator, Component, Action, Flow, Link, Event, Display,
            SizeEnum
        };

        using Name = std::string_view;
        using C    = Category;
        using TCategory = std::tuple<Category, Name>;
        static constexpr TupleArray<Category::SizeEnum, TCategory> categories ={{
            TCategory
            {C::Action,    "Action"sv      },
            {C::Convertor, "Convertor"sv   },
            {C::Display,   "Display"sv     },
            {C::Event,     "Event"sv       },
            {C::Flow,      "Flow"sv        },
            {C::Function,  "Function"sv    },
            {C::Generator, "Generator"sv   },
            {C::Link,      "Link"sv        },
            {C::Operator,  "Operator"sv    },
            {C::Component, "Component"sv   },
        }};

        static auto get_name(C c) {
            return categories.at<0,1>(c);
        }

        static auto all_categories() {
            return categories.tuple_column<0>();
        }

        static auto all_categories_name() {
            return categories.tuple_column<1>();
        }

        static auto get_category_from_name(Name n) {
            return categories.optional_at<1,0>(n);
        }


        // Connectors types
        enum class Type : int {
            Component, // Component
            Boolean, Integer,Real, String, Vector3, Transform, Id_any, String_any,  // Generator
            Reals_to_vec2, Reals_to_vec3, Vec2_to_reals, Vec3_to_reals, String_list_to_id_any, Transform_to_vectors, Vectors_to_transform,// Convertor
            Curve_x, Logger, // Display
            Decimal_trigonometry, Decimal_counter, Delay, Variable_delay, // Function
            Binary_operation, Decimal_operation, String_operation, // Operator
            Pass_value_trigger, Conditional_trigger, Pass_values, Conditional_gate, Check_id, Check_str, // Link
            Filter_keyboard_button, Check_joypad_button, Check_joypad_axis, Check_mouse_button, Check_keyboard_button, // Event
            Next, Previous, Stop, Pause, Next_with_name, Next_with_cond, Previous_with_name, Previous_with_cond, Force_component_config, // Action
            Time, Start_routine, Stop_routine, Update_routine, Pre_update_routine, Post_update_routine,// Flow
            SizeEnum};


        using T       = Type;        
        using Caption = std::string_view;
        using TType = std::tuple<Type,Name,Caption>;
        static constexpr TupleArray<Type::SizeEnum,TType> types ={{
            TType
            // # Action
            {T::Next,                   "Next"sv,                       "Next routine"sv},
            {T::Next_with_cond,         "NextElementWithCond"sv,        "Next element with cond"sv},
            {T::Next_with_name,         "NextElementWithName"sv,        "Next element with name"sv},
            {T::Previous,               "Previous"sv,                   "Previous routine"sv},
            {T::Previous_with_name,     "PreviousElementWithName"sv,    "Previous element with name"sv},
            {T::Previous_with_cond,     "PreviousElementWithCond"sv,    "Previous element with cond"sv},
            {T::Force_component_config, "ForceComponentConfig"sv,       "Force component config"sv},
            {T::Stop,                   "Stop"sv,                       "Stop experiment"sv},
            {T::Pause,                  "PauseAction"sv,                "Pause experiment"sv},
            // # Convertors
            {T::Reals_to_vec2,          "RealsToVector2"sv,             "To vec2"sv},
            {T::Vec2_to_reals,          "Vector2ToReals"sv,             "From vec2"sv},
            {T::Reals_to_vec3,          "RealsToVector3"sv,             "To vec3"sv},            
            {T::Vec3_to_reals,          "Vector3ToReals"sv,             "From vec3"sv},
            {T::String_list_to_id_any,  "StringListToIdAny"sv,          "String list to id any"sv},
            {T::Transform_to_vectors,   "TransformToVectors"sv,         "Transform to vectors"sv},
            {T::Vectors_to_transform,   "VectorsToTransform"sv,         "Vectors to transform"sv},
            // # Display
            {T::Curve_x,                "CurveX"sv,                     "Curve X"sv},
            {T::Logger,                 "Logger"sv,                     "Logger"sv},
            // # Event            
            {T::Check_keyboard_button,  "CheckKeyboardButton"sv,        "Check keyboard button"sv},
            {T::Filter_keyboard_button, "FilterKeyboardButton"sv,       "Filter keyboard button"sv},
            {T::Check_joypad_button,    "CheckJoypadButton"sv,          "Check joypad button"sv},
            {T::Check_joypad_axis,      "CheckJoypadAxis"sv,            "Check joypad axis"sv},            
            {T::Check_mouse_button,     "CheckMouseButton"sv,           "Check mouse button"sv},
            // # Flow
            {T::Time,                   "Time"sv,                       "Time"sv},
            {T::Start_routine,          "StartRoutine"sv,               "Start routine"sv},
            {T::Stop_routine,           "StopRoutine"sv,                "Stop routine"sv},
            {T::Pre_update_routine,     "PreUpdateRoutine"sv,           "Pre-update routine"sv},
            {T::Update_routine,         "UpdateRoutine"sv,              "Update routine"sv},
            {T::Post_update_routine,    "PostUpdateRoutine"sv,          "Post-update routine"sv},
            // # Function
            {T::Decimal_trigonometry,   "DecimalTrigonometry"sv,        "Trigonometry"sv},
            {T::Decimal_counter,        "DecimalCounter"sv,             "Counter"sv},
            {T::Delay,                  "Delay"sv,                      "Delay"sv},
            {T::Variable_delay,         "VariableDelay"sv,              "Variable delay"sv},
            // # Generator
            {T::Boolean,                "Boolean"sv,                    "Boolean"sv},
            {T::Integer,                "Integer"sv,                    "Integer"sv},
            {T::Real,                   "Real"sv,                       "Real"sv},
            {T::String,                 "String"sv,                     "String"sv},
            {T::Vector3,                "Vector3"sv,                    "Vector3"sv},
            {T::Transform,              "Transform"sv,                  "Transform"sv},
            {T::Id_any,                 "IdAny"sv,                      "Id any"sv},
            {T::String_any,             "StringAny"sv,                  "String any"sv},
            // # Link
            {T::Pass_values,            "PassValues"sv,                 "Pass values"sv},
            {T::Pass_value_trigger,     "PassValueTrigger"sv,           "Pass value trigger"sv},
            {T::Conditional_trigger,    "ConditionalTrigger"sv,         "Conditional trigger"sv},
            {T::Conditional_gate,       "ConditionalGate"sv,            "Conditional gate"sv},
            {T::Check_id,               "CheckId"sv,                    "Check id any"sv},
            {T::Check_str,              "CheckStr"sv,                   "Check string any"sv},
            // # Operator
            {T::Decimal_operation,      "DecimalOperation"sv,           "Decimal operation"sv},
            {T::Binary_operation,       "BinaryOperation"sv,            "Binary operation"sv},
            {T::String_operation,       "StringOperation"sv,            "String operation"sv},
            // # Component
            {T::Component,              "-"sv,                          "-"sv},
        }};

        static auto get_type_from_name(Name n) {
            return types.optional_at<1,0>(n);
        }

        static auto get_type_from_caption(Caption c) {
            return types.optional_at<2,0>(c);
        }

        static auto get_name(Type t) {
            return types.at<0,1>(t);
        }

        static auto get_caption(Type t) {
            return types.at<0,2>(t);
        }

        enum class Priority : int {
            Low=0, Medium, Hight
        };

        struct Text{
            const std::string_view name;
            const std::string_view caption;            
        };

        static constexpr int maxInputConnection  = 10;
        static constexpr int maxOutputConnection = 10;

        struct IO{
            size_t inNb;
            std_a1<ConnectionNode::Type,maxInputConnection> inTypes;
            size_t outNb;
            std_a1<ConnectionNode::Type,maxOutputConnection> outTypes;
        };

        struct IO2{

            constexpr IO2(std_a1<ConnectionNode::Type,maxInputConnection> in, std_a1<ConnectionNode::Type,maxOutputConnection> out):
                  inTypes(in), outTypes(out),inNb(in.size()),outNb(out.size()){
            }

            std_a1<ConnectionNode::Type,maxInputConnection> inTypes;
            std_a1<ConnectionNode::Type,maxOutputConnection> outTypes;
            size_t inNb;
            size_t outNb;
        };



        struct Style{
            bool captionVisibility;
            std_a1<bool, maxInputConnection> inPortsVisibility;
            std_a1<bool, maxOutputConnection> outPortsVisibility;
        };

        enum class Interactivity{
            Interactive,Locked
        };

        enum class WidgetMode{
            Focus,
            Popup
        };

        using Inter = size_t;
        using P   = Priority;
        using Te  = Text;

        using S   = Style;
        using I   = Interactivity;
        using WM  = WidgetMode;

        using CNT = ConnectionNode::Type;
        static constexpr auto t_void        = CNT::void_t;
        static constexpr auto t_bool        = CNT::boolean_t;
        static constexpr auto t_int         = CNT::integer_t;
        static constexpr auto t_float       = CNT::float_t;
        static constexpr auto t_real        = CNT::real_t;
        static constexpr auto t_vec2        = CNT::vector2_t;
        static constexpr auto t_vec3        = CNT::vector3_t;
        static constexpr auto t_transform   = CNT::transform_t;
        static constexpr auto t_str         = CNT::string_t;


        static constexpr auto t_str_l       = CNT::string_list_t;
        static constexpr auto t_real_l      = CNT::real_list_t;
        static constexpr auto t_any         = CNT::any_t;
        static constexpr auto t_id_any      = CNT::id_any_t;
        static constexpr auto t_str_any     = CNT::string_any_t;
        static constexpr auto t_dec         = CNT::decimal_t;
        static constexpr auto t_plot        = CNT::plot_t;
        static constexpr auto t_variant     = CNT::variant_t;

        static constexpr auto t_joy_but_s   = CNT::joypad_button_event_t;
        static constexpr auto t_joy_ax_s    = CNT::joypad_axis_event_t;
        static constexpr auto t_key_but_s   = CNT::keyboard_button_event_t;
        static constexpr auto t_mou_but_s   = CNT::mouse_button_event_t;

        static constexpr auto L = P::Low;
        static constexpr auto M = P::Medium;
        static constexpr auto H = P::Hight;

        static constexpr auto v = true;
        static constexpr auto i = false;

        static constexpr auto LO = I::Locked;
        static constexpr auto IN = I::Interactive;

        static constexpr auto FO = WM::Focus;
        static constexpr auto PO = WM::Popup;

        using TConnector = std::tuple<
            Type,                       Category,     P, IO,                                                          Style,                  I,  WM, Inter>;
        static constexpr TupleArray<Type::SizeEnum,TConnector> connectors ={{
            TConnector
            // # Component
            {T::Component,              C::Component, M, {0,{},                            0,{}},                     {i,{},        {}},      LO, FO, 0},
            // # Convertor
            {T::Reals_to_vec2,          C::Convertor, M, {2,{t_real,t_real},               1,{t_vec2}},               {v,{v,v},     {v}},     LO, FO, 0},
            {T::Vec2_to_reals,          C::Convertor, M, {1,{t_vec2},                      2,{t_real,t_real}},        {v,{v},       {v,v}},   LO, FO, 0},
            {T::Reals_to_vec3,          C::Convertor, M, {3,{t_real,t_real,t_real},        1,{t_vec3}},               {v,{v,v,v},   {v}},     LO, FO, 0},            
            {T::Vec3_to_reals,          C::Convertor, M, {1,{t_vec3},                      3,{t_real,t_real,t_real}}, {v,{v},       {v,v,v}}, LO, FO, 0},
            {T::String_list_to_id_any,  C::Convertor, M, {1,{t_str_l},                     1,{t_id_any}},             {v,{v},       {v,}},    LO, FO, 0},
            {T::Transform_to_vectors,   C::Convertor, M, {1,{t_transform},                 3,{t_vec3,t_vec3,t_vec3}}, {v,{v},       {v,v,v}}, LO, FO, 0},
            {T::Vectors_to_transform,   C::Convertor, M, {3,{t_vec3,t_vec3,t_vec3},        1,{t_transform}},          {v,{v,v,v},   {v}},     LO, FO, 0},
            // # Display
            {T::Curve_x,                C::Display,   M, {1,{t_real_l},                    0,{}},                     {i,{v},       {}},      IN, PO, 0},
            {T::Logger,                 C::Display,   M, {1,{t_any},                       0,{}},                     {v,{v},       {}},      LO, FO, 0},
            // # Function
            {T::Decimal_trigonometry,   C::Function,  M, {1,{t_dec},                       1,{t_dec}},                {v,{v},       {v}},     IN, FO, 1},
            {T::Decimal_counter,        C::Function,  M, {3,{t_dec,t_dec,t_void},          1,{t_dec}},                {v,{v,v,v},   {v}},     LO, FO, 1},
            {T::Delay,                  C::Function,  M, {1,{t_any},                       1,{t_any}},                {v,{v},       {v}},     IN, FO, 1},
            {T::Variable_delay,         C::Function,  M, {2,{t_plot,t_any},                1,{t_any}},                {v,{v},       {v}},     IN, FO, 1},
            // # Generator
            {T::Boolean,                C::Generator, M, {2,{t_bool,t_void},               1,{t_bool}},               {v,{v,v},     {v}},     IN, FO, 1},
            {T::Integer,                C::Generator, M, {1,{t_int},                       1,{t_int}},                {v,{v},       {v}},     IN, FO, 1},
            {T::Real,                   C::Generator, M, {1,{t_real},                      1,{t_real}},               {v,{v},       {v}},     IN, FO, 1},
            {T::String,                 C::Generator, M, {1,{t_str},                       1,{t_str}},                {v,{v},       {v}},     IN, FO, 1},
            {T::Vector3,                C::Generator, M, {1,{t_vec3},                      1,{t_vec3}},               {v,{v},       {v}},     IN, FO, 1},
            {T::Transform,              C::Generator, M, {1,{t_transform},                 1,{t_transform}},          {v,{v},       {v}},     IN, PO, 1},
            {T::Id_any,                 C::Generator, M, {1,{t_any},                       1,{t_id_any}},             {v,{v},       {v}},     IN, FO, 1},
            {T::String_any,             C::Generator, M, {1,{t_any},                       1,{t_str_any}},            {v,{v},       {v}},     IN, FO, 1},
            // # Operator
            {T::Decimal_operation,      C::Operator,  M, {2,{t_dec,t_dec},                 1,{t_variant}},            {v,{v,v},     {v}},     IN, FO, 1},
            {T::Binary_operation,       C::Operator,  M, {2,{t_bool,t_bool},               1,{t_bool}},               {v,{v,v},     {v}},     IN, FO, 1},            
            {T::String_operation,       C::Operator,  M, {2,{t_str,t_str},                 1,{t_variant}},            {v,{v,v},     {v}},     IN, FO, 1},
            // # Link
            {T::Check_id,               C::Link,      M, {1,{t_id_any},                    1,{t_any}},                {v,{v},       {v}},     IN, FO, 1},
            {T::Check_str,              C::Link,      M, {1,{t_str_any},                   1,{t_any}},                {v,{v},       {v}},     IN, FO, 1},
            {T::Pass_values,            C::Link,      M, {4,{t_any,t_any,t_any,t_any},     1,{t_any}},                {v,{v,v,v,v}, {v}},     LO, FO, 1},
            {T::Pass_value_trigger,     C::Link,      M, {2,{t_any, t_void},               1,{t_any}},                {v,{v,v},     {v}},     LO, FO, 1},
            {T::Conditional_trigger,    C::Link,      M, {1,{t_bool},                      1,{t_void}},               {v,{v},       {v}},     LO, FO, 1},
            {T::Conditional_gate,       C::Link,      M, {2,{t_any, t_bool},               1,{t_any}},                {v,{v,v},     {v}},     IN, FO, 1},
            // # Event
            {T::Check_keyboard_button,  C::Event,     M, {1,{t_key_but_s},                 4,{t_void,t_void,t_void, t_real}},  {v,{v},       {v,v,v,v}}, IN, FO, 1},
            {T::Filter_keyboard_button, C::Event,     M, {1,{t_key_but_s},                 1,{t_key_but_s}},                   {v,{v},       {v}},       IN, FO, 1},
            {T::Check_joypad_button,    C::Event,     M, {1,{t_joy_but_s},                 4,{t_void,t_void,t_void, t_real}},  {v,{v},       {v,v,v,v}}, IN, FO, 1},
            {T::Check_joypad_axis,      C::Event,     M, {1,{t_joy_ax_s},                  2,{t_float,t_real}},                {v,{v},       {v,v}},     IN, FO, 1},
            {T::Check_mouse_button,     C::Event,     M, {1,{t_mou_but_s},                 4,{t_void,t_void,t_void, t_real}},  {v,{v},       {v,v,v,v}}, IN, FO, 1},
            // # Action                        
            {T::Next,                   C::Action,    M, {1,{t_void},                      0,{}},                     {v,{v},       {}},      LO, FO, 0},
            {T::Next_with_name,         C::Action,    M, {1,{t_void},                      0,{}},                     {v,{v},       {}},      IN, FO, 0},            
            {T::Next_with_cond,         C::Action,    M, {1,{t_void},                      0,{}},                     {v,{v},       {}},      IN, FO, 0},
            {T::Previous,               C::Action,    M, {1,{t_void},                      0,{}},                     {v,{v},       {}},      LO, FO, 0},
            {T::Previous_with_name,     C::Action,    M, {1,{t_void},                      0,{}},                     {v,{v},       {}},      IN, FO, 0},
            {T::Previous_with_cond,     C::Action,    M, {1,{t_void},                      0,{}},                     {v,{v},       {}},      IN, FO, 0},
            {T::Stop,                   C::Action,    M, {1,{t_void},                      0,{}},                     {v,{v},       {}},      LO, FO, 0},
            {T::Pause,                  C::Action,    M, {1,{t_void},                      0,{}},                     {v,{v},       {}},      LO, FO, 0},
            {T::Force_component_config, C::Action,    H, {1,{t_void},                      0,{}},                     {v,{v},       {}},      IN, FO, 0},
            // # Flow
            {T::Time,                   C::Flow,      M, {0,{},                            1,{t_real}},               {v,{},        {v}},     IN, FO, 1},
            {T::Start_routine,          C::Flow,      H, {0,{},                            4,{t_str, t_str, t_int, t_int}},  {v,{},        {v,v,v,v}}, LO, FO, 0},
            {T::Stop_routine,           C::Flow,      H, {0,{},                            2,{t_str, t_str}},         {v,{},        {v,v}},   LO, FO, 0},
            {T::Pre_update_routine,     C::Flow,      H, {0,{},                            1,{t_real}},                {v,{},        {v}},     LO, FO, 0},
            {T::Update_routine,         C::Flow,      H, {0,{},                            1,{t_real}},                {v,{},        {v}},     LO, FO, 0},
            {T::Post_update_routine,    C::Flow,      H, {0,{},                            1,{t_real}},                {v,{},        {v}},     LO, FO, 0},
        }};


        template<Category c>
        static size_t connectors_count() {
            return connectors.count_equal<1>(c);
        }

        static auto all_types() {
            return connectors.tuple_column<0>();
        }

        template<Category c>
        static std::vector<Type> types_with_category() {
            return connectors.elements_matching_columns_values<1,0>(c);
        }

        static auto get_category(Type t) {
            return connectors.at<0,1>(t);
        }

        static auto get_io(Type t) {
            return connectors.at<0,3>(t);
        }

        static auto get_caption_visibility(Type t) {
            return connectors.at<0,4>(t).captionVisibility;
        }

        static auto get_in_port_visibility(Type t, size_t index) {
            return connectors.at<0,4>(t).inPortsVisibility[index];
        }

        static auto get_out_port_visibility(Type t, size_t index) {
            return connectors.at<0,4>(t).outPortsVisibility[index];
        }

        static auto get_interactivity(Type t) {
            return connectors.at<0,5>(t);
        }

        static auto get_widget_mode(Type t) {
            return connectors.at<0,6>(t);
        }

        static auto get_inter_number(Type t) {
            return connectors.at<0,7>(t);
        }

        explicit Connector(ConnectorKey id, Type t, QString n, QPointF p)
            : key(IdKey::Type::Connector, id.v), name(n), pos(p), type(t){
        }

        explicit Connector(ConnectorKey id, Type t, QString n, QPointF p, Arg a)
            : key(IdKey::Type::Connector, id.v), name(n), pos(p), arg(a), type(t){
        }

        static ConnectorUP copy_with_new_element_id(const Connector &connectorToCopy);

        inline QString to_string() const{return QSL("Connector(") % name % QSL("|") %
                   QString::number(key()) % QSL(")");}


        IdKey key;        
        QString name;
        QPointF pos;
        Arg arg;        
        bool inputValidity = true;
        Type type;
        QSize size; // TO REMOVE
        bool selected = false;
    };

    static bool operator<(const ConnectorUP &l, const ConnectorUP &r){
        if(l->key() == r->key()){
            return false;
        }
        return true;
    }

    static bool operator==(const ConnectorUP &l, const ConnectorUP &r){
        return !(l < r) && !(r < l);
    }

}
