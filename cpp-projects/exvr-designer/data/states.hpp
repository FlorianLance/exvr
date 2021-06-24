
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// base
#include "utility/tuple_array.hpp"

// local
#include "element.hpp"

namespace tool::ex {

    using namespace std::literals::string_view_literals;

    enum class ExpLauncherCommand : int{
        Load=0, Play, Pause, Stop, Next, Previous, UpdateComponent, UpdateConnector, Quit,
        Action, GoToSpecificInstanceElement, PlayPause, PlayDelay, Error,
        SizeEnum
    };

    enum class ExpLauncherState : int{
        NotStarted=0,
        Starting,
        Idle,
        LoadingExperiment,
        Closing,
        SizeEnum
    };

    enum class ExpState : int{
        NotLoaded = 0,
        Loaded,
        Running,
        Paused,
        SizeEnum
    };

    using Description = std::string_view;
    using TExpLauncherState = std::tuple<ExpLauncherState, Description>;
    static constexpr TupleArray<ExpLauncherState::SizeEnum, TExpLauncherState> expLauncherStates = {{
        TExpLauncherState
        {ExpLauncherState::NotStarted,          "[ExVR-exp] ExVR-exp not launched."sv},
        {ExpLauncherState::Starting,            "[ExVR-exp] ExVR-exp is starting."sv},
        {ExpLauncherState::Idle,                "[ExVR-exp] Idle."sv},
        {ExpLauncherState::LoadingExperiment,   "[ExVR-exp] ExVR-exp is loading an experiment..."sv},
        {ExpLauncherState::Closing,             "[ExVR-exp] ExVR-exp is closing."sv},
    }};

    [[maybe_unused]] static Description get_description(ExpLauncherState s) {
        return expLauncherStates.at<0,1>(s);
    }

    using TExpState = std::tuple<ExpState, Description>;
    static constexpr TupleArray<ExpState::SizeEnum, TExpState> expStates = {{
        TExpState
        {ExpState::NotLoaded,    "[ExVR-exp] No experiment loaded."sv},
        {ExpState::Loaded,       "[ExVR-exp] Experiment loaded"sv},
        {ExpState::Running,      "[ExVR-exp] Experiment is running"sv},
        {ExpState::Paused,       "[ExVR-exp] Experiment paused"sv},
    }};

    [[maybe_unused]] static Description get_description(ExpState s) {
        return expStates.at<0,1>(s);
    }

    [[maybe_unused]] static QString to_command_id(ExpLauncherCommand cmd){
        return QString::number(static_cast<int>(cmd));
    }

    enum class FontStyle : int {
        Normal = 0, Bold = 1, Italic =2, Bold_and_italic =3,
        SizeEnum};

    enum class Alignment : int {
        UpperLeft = 0, UpperCenter = 1, UpperRight =2, MiddleLeft =3, MiddleCenter = 4, MiddleRight = 5, LowerLeft = 6, LowerCenter =7, LowerRight = 8,
        SizeEnum};

    enum class TextOverlflow : int {
        Wrap = 0, Overflow = 1,
        SizeEnum};

    enum class UnityType : int {
        System_boolean,
        System_sbyte, System_int16, System_int32, System_int64, System_decimal,
        System_byte, System_uint16, System_uint32, System_uint64,
        System_single, System_double,
        System_char, System_string,
        None, Mixed, Unknow, SizeEnum};

    using UniT = UnityType;
    using Name    = std::string_view;
    using StrType = std::string_view;

    using TUnityType = std::tuple<UnityType, Name, StrType>;
    static constexpr TupleArray<UnityType::SizeEnum, TUnityType> unityTypes {{
        TUnityType
        {UnityType::System_boolean,    "bool"sv,       "System.Boolean"sv },
        {UnityType::System_single,     "float"sv,      "System.Single"sv  },
        {UnityType::System_double,     "double"sv,     "System.Double"sv  },
        {UnityType::System_sbyte,      "sbyte"sv,      "System.Sbyte"sv   },
        {UnityType::System_int16,      "short"sv,      "System.In16"sv    },
        {UnityType::System_int32,      "int"sv,        "System.Int32"sv   },
        {UnityType::System_int64,      "long"sv,       "System.Int64"sv   },
        {UnityType::System_decimal,    "decimal"sv,    "System.Decimal"sv },
        {UnityType::System_byte,       "byte"sv,       "System.Byte"sv    },
        {UnityType::System_uint16,     "ushort"sv,     "System.UIn16"sv   },
        {UnityType::System_uint32,     "uint"sv,       "System.UInt32"sv  },
        {UnityType::System_uint64,     "ulong"sv,      "System.UInt64"sv  },
        {UnityType::System_char,       "char"sv,       "System.Char"sv    },
        {UnityType::System_string,     "string"sv,     "System.String"sv  },
        {UnityType::None,              "none"sv,       "None"sv           },
        {UnityType::Unknow,            "unknow"sv,     "Unknow"sv         },
        {UnityType::Mixed,             "mixed types"sv,"None"sv           },
    }};

    constexpr StrType get_unity_type_string(UnityType t) {
        return unityTypes.at<0,2>(t);
    }

    constexpr std::optional<UnityType> get_unity_type(StrType strType){
        return unityTypes.optional_at<2,0>(strType);
    }

    struct States{

        States(QString nVersion) : numVersion(nVersion){
            auto split = numVersion.split(".");
            majorNumVersion = split[0].toInt();
            minorNumVersion = split[1].toInt();
        }

        const QString numVersion;
        int majorNumVersion;
        int minorNumVersion;
        int maximumDeepLevel = -1;

        QString loadedExpDesignerVersion = "unknow";
        QString designerPathUsedForLoadedExp = "unknow";

        QString currentExpfilePath = "unknow";
        QString currentName = "unknow";
        QString currentMode = "designer";
        QString currentInstanceName = "debug-instance.xml";

        ExpLauncherState explauncherState = ExpLauncherState::NotStarted;
        ExpState expState = ExpState::NotLoaded;


        int currentElementKey=-1;
        int currentConditionKey=-1;
        Element::Type currentElementType;
        QString currentElementName = "";

        QString currentTypeSpecificInfo = "";
        double experimentTimeS = 0.0;
        double currentElementTimeS = 0.0;
        double currentIntervalEndTimeS = 0.0;
        QString currentOrder = "";

        unsigned int randomizationSeed = 0;

        bool followsCurrentCondition = false;
    };

}
