
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QDialog>
#include <QTableWidget>
#include <QAbstractTableModel>

namespace tool::ex {

class Table : public QAbstractTableModel{

public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    void update();

    std::vector<std::tuple<std::string_view, std::int64_t, size_t>> times;
    //int headerData(int section, Qt::Orientation orientation, int role) const;


    std::unordered_map<std::string_view, std::tuple<QString, std::int64_t, bool, size_t>> elements;
    std::vector<std::string_view> order;

//    std::vector<
};

class BenchmarkDialog : public QDialog{

    Q_OBJECT

public :

    BenchmarkDialog();


public slots:

    void update();

    void show_dialog(){
        show();
        raise();
    }

private:

    QTableView *view = nullptr;
    Table *model = nullptr;

    QCheckBox *sort = nullptr;
};
}
