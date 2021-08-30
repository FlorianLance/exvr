
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
#include <QVector>
#include <QFile>
#include <QTextStream>

// qt-utility
#include "qt_str.hpp"

// base
#include "utility/tuple_array.hpp"

// local
#include "element.hpp"
#include "set.hpp"


namespace tool::ex {

using namespace std::literals::string_view_literals;

struct Loop;
using LoopUP = std::unique_ptr<Loop>;

struct LoopNode;
using LoopNodeUP = std::unique_ptr<LoopNode>;


struct Loop : public Element {

    enum class Mode : int {
        Fixed=0,
        Random,
        Shuffle,
        File,
        FixedRandomStart,
        FixedInstanceShiftStart,
        RandomOneForAllInstances,
        ShuffleOneForAllInstances,
        RandomEveryNInstances,
        ShuffleEveryNInstances,
        SizeEnum
    };

    using Name = std::string_view;
    using TLoopMode = std::tuple<
        Mode,                           Name>;
    static constexpr TupleArray<Mode::SizeEnum, TLoopMode> loopModes ={{
        TLoopMode
        {Mode::Fixed,                       "fixed"sv},
        {Mode::Random,                      "random"sv},
        {Mode::Shuffle,                     "shuffle"sv},
        {Mode::File,                        "file"sv},
        {Mode::FixedRandomStart,            "random_start_fixed"sv},
        {Mode::FixedInstanceShiftStart,     "instance_shift_start_fixed"sv},
        {Mode::RandomOneForAllInstances,    "only_once_random"sv},
        {Mode::ShuffleOneForAllInstances,   "only_once_shuffle"sv},
        {Mode::RandomEveryNInstances,       "every_n_instances_random"sv},
        {Mode::ShuffleEveryNInstances,      "every_n_instances_shuffle"sv},
    }};

    [[maybe_unused]] static Name get_name(Mode m) {
        return loopModes.at<0,1>(m);
    }

    [[maybe_unused]] static std::optional<Mode> get_mode(const Name name) {
        return loopModes.optional_at<1,0>(name);
    }

    Loop();
    Loop(QString n, ElementKey id);

    inline QString to_string() const{return QSL("Loop(") % name() % QSL("|") % QString::number(key()) % QSL(")");}

    static LoopUP copy_with_new_element_id(const Loop &loopToCopy, const QString &newName);

    bool is_file_mode() const noexcept;

    void set_nodes(LoopNode *start, LoopNode *end);
    void set_nb_reps(size_t nb) noexcept;
    void set_N(int N) noexcept;
    void set_loop_type(Mode m) noexcept;

    bool is_default() const;
    void set_sets(QStringList sets);
    bool add_set(QString setName, RowId id);
    void add_sets(QStringList setsName, RowId id);
    void remove_set(RowId id);
    bool modify_set_name(QString newSetName, RowId id);
    void modify_set_occurencies_nb(int occurrencies, RowId id);
    void move_set_up(RowId id);
    void move_set_down(RowId id);
    void sort_sets_lexico();
    void sort_sets_num();

    bool load_file(QString path);

    QString merge_sets_names() const;
    QString merge_sets_occurencies() const;

    Set* get_set(SetKey setKey);

    // settings
    size_t nbReps = 1;
    Mode mode = Mode::Fixed;
    QString filePath; /**< path for FILE loop mode */
    int N = 1;

    // sets
    QString currentSetName;
    std_v1<Set> sets;
    std_v1<Set> fileSets;

    // associated nodes
    LoopNode *start = nullptr;
    LoopNode *end   = nullptr;
};

struct LoopNode : public Element{

    LoopNode() : Element(Type::LoopStart, QSL("loop_node")){
    }

    LoopNode(Loop *l, bool start = true) : Element(start ? Type::LoopStart : Type::LoopEnd, l->name(), l->key()), loop(l){
    }

    // associated loop
    Loop *loop = nullptr;
};

}
