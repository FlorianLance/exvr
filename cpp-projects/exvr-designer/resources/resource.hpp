
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// std
#include <optional>

// Qt
#include <QStringList>
#include <QStringBuilder>

// base
#include "utility/types_utility.hpp"
#include "utility/vector_utility.hpp"
#include "utility/tuple_array.hpp"

// qt-utility
#include "data/id_key.hpp"
#include "qt_str.hpp"

namespace tool::ex {

using namespace std::literals::string_view_literals;

struct Resource{

    enum class Type : std::uint8_t {
        Image, Video, Audio, Text, AssetBundle, Mesh, PythonScript, CSharpScript, Cloud, ScanerVideo, Plot, Directory,
        SizeEnum
    };

    using Filters     = std::string_view;
    using Name        = std::string_view;
    using IconPath    = std::string_view;
    using DisplayName = std::string_view;
    using CanOpen     = bool;
    using CanGenerate = bool;
    static constexpr Filters videoFilters   = "(*.avi *.dv *.m4v *.mov *.mp4 *.mpg *.mpeg *.ogv *.webm *.wmv)"sv;
    static constexpr Filters txtFilters     = "(*.txt *.calib *.config *.xml *.json *.csv)"sv;
    static constexpr Filters audioFilters   = "(*.ogg *.wav *.aiff *.aif)"sv;
    static constexpr Filters imageFilters   = "(*.jpg *.jpeg *.png *.PNG)"sv;

    using TResource = std::tuple<
        Type,                Filters,          Name,                 IconPath,                       DisplayName,              CanOpen, CanGenerate>;
    static constexpr TupleArray<Type::SizeEnum,TResource> resources{{
        TResource
        {Type::Image,        imageFilters,     "Image"sv,            ":/icons/Image"sv,              "Images"sv,               true,    false},
        {Type::Video,        videoFilters,     "Video"sv,            ":/icons/Video"sv,              "Videos"sv,               true,    false},
        {Type::Audio,        audioFilters,     "Audio"sv,            ":/icons/Sound"sv,              "Audio"sv,                true,    false},
        {Type::Text,         txtFilters,       "Text"sv,             ":/icons/Text"sv,               "Textes"sv,               true,    false},
        {Type::AssetBundle,  "(*.unity3d)"sv,  "UnityAssetBundle"sv, ":/icons/Unity_scene_bundle"sv, "Unity assets bundles"sv, false,   false},
        {Type::Mesh,         "(*.obj)"sv,      "Mesh"sv,             ":/icons/Cube"sv,               "Meshes"sv,               true,    false},
        {Type::PythonScript, "(*.py)"sv,       "PythonScript"sv,     ":/icons/Python_script"sv,      "Python scripts"sv,       true,    true},
        {Type::CSharpScript, "(*.cs)"sv,       "CSharpScript"sv,     ":/icons/CSharp"sv,             "C# scripts"sv,           true,    true},
        {Type::Cloud,        "(*.asc)"sv,      "Cloud"sv,            ":/icons/Sphere"sv,             "Clouds points"sv,        false,   false},
        {Type::ScanerVideo,  "(*.kvid)"sv,     "ScanerVideo"sv,      ":/icons/Video"sv,              "Scaner videos"sv,        false,   false},
        {Type::Plot,         "(*.csv)"sv,      "Plot"sv,             ":/icons/Plot"sv,               "Plots"sv,                true,    false},
        {Type::Directory,    ""sv,             "Directory"sv,        ":/icons/Folder"sv,             "Directories"sv,          true,    false},
    }};

    static auto get_types() {
        return resources.tuple_column<0>();
    }

    static auto get_names() {
        return resources.tuple_column<2>();
    }

    [[maybe_unused]] static std::optional<Type> get_type(const Name name) {
        return resources.optional_at<2,0>(name);
    }

    static constexpr Filters get_filters(Type t) {
        return resources.at<0,1>(t);
    }

    static constexpr Name get_name(Type t) {
        return resources.at<0,2>(t);
    }

    static constexpr IconPath get_icon_path(Type t) {
        return resources.at<0,3>(t);
    }

    static constexpr DisplayName get_display_name(Type t) {
        return resources.at<0,4>(t);
    }

    static constexpr bool can_open(Type t) {
        return resources.at<0,5>(t);
    }

    static constexpr bool can_generate(Type t) {
        return resources.at<0,6>(t);
    }

    Resource() = delete;

    Resource(Type t, int id, QString path, QString alias = "") : key(IdKey::Type::Resource, id), type(t){

        this->path  = path;
        this->alias = alias;

        // separate path using .
        const auto split = this->path.split("/").last().split(".");

        // update alias from path is empty
        if(this->alias.length() == 0){
            this->alias = split.first();
        }

        // update extension
        if(split.size() > 1){
            extension = split.last();
        }else{
            extension = ""; // no extension or directory
        }


    }

    inline QString display_name() const noexcept{
        if(extension.length() == 0){
            return alias;
        }else{
            return QSL("[") % extension % QSL("] ") % alias;
        }
    }

    IdKey key;
    Type type;
    bool exist = false;
    bool preview = false;
    QString alias;
    QString path;
    QString extension;

};
}
