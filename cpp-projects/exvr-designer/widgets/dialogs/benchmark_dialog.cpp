
#include "benchmark_dialog.hpp"

// Qt
#include <QDoubleSpinBox>

// base
#include "utility/benchmark.hpp"

// qt-utility
#include "qt_ui.hpp"

using namespace tool;
using namespace tool::ex;


BenchmarkDialog::BenchmarkDialog(){

    setWindowTitle("Benchmark:");
    setLayout(new QVBoxLayout());
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    setModal(false);

//    twBenchElements = new QTableWidget();
//    twBenchElements->setColumnCount(4);
    view = new QTableView();
    model = new Table();
    view->setModel(model);

    QString txt = "Select element to reach:";
    layout()->addWidget(new QLabel(txt));

    sort  = new QCheckBox("Sort");
    auto unit = new QComboBox();
    auto minT = new QDoubleSpinBox();
    layout()->addWidget(ui::F::gen(ui::L::HB(), {sort, ui::W::txt("Unit:"), unit, ui::W::txt("Min T:"), minT}, LStretch{true}, LMargins{true}, QFrame::NoFrame));
    layout()->addWidget(view);

//    connect(sort, &QPushButton::clicked, this, [&](){
//        std::sort(std::begin(model->order), std::end(model->order));
//    });
}

void BenchmarkDialog::update(){
    model->update();
    view->viewport()->update();
}

int Table::rowCount(const QModelIndex &) const{
    return elements.size();
}

int Table::columnCount(const QModelIndex &) const{
    return 3;
}

QVariant Table::data(const QModelIndex &index, int role) const{

    if (role == Qt::DisplayRole){
        auto id = order[index.row()];
        if(index.column() == 0){
            return std::get<0>(elements.at(id));
        }else if (index.column() == 1){
            return std::get<1>(elements.at(id));
        }else if(index.column() == 2){
            return std::get<3>(elements.at(id));
        }
    }else if (role == Qt::BackgroundRole){
         if(index.column() == 0){
            return QColor(Qt::lightGray);
         }else if (index.column() == 1){
            return QColor(Qt::black);
         }else if (index.column() == 1){
             return QColor(Qt::lightGray);
         }
    }else if (role == Qt::ForegroundRole){
        if(index.column() == 0){
            return QColor(Qt::black);
        }else if (index.column() == 1){
            auto id = order[index.row()];
            return std::get<2>(elements.at(id)) ? QColor(Qt::green) : QColor(Qt::darkYellow);
        }else if (index.column() == 2){
            return QColor(Qt::black);
        }
    }else if (role == Qt::TextAlignmentRole){
        if(index.column() == 0){
            return Qt::AlignLeft;
        }else if(index.column() == 1){
            return Qt::AlignCenter;
        }else if(index.column() == 1){
            return Qt::AlignCenter;
        }
    }

    return QVariant();
}

void Table::update(){

    auto currentNb = elements.size();
    times = Bench::all_total_times(BenchUnit::microseconds, -1, true);
    for(auto &element : elements){
        std::get<2>(element.second) = false;
    }

    for(const auto& time : times){
        if(!elements.contains(std::get<0>(time))){
            elements[std::get<0>(time)] = std::make_tuple(from_view(std::get<0>(time)), 0, true, std::get<2>(time));
            order.emplace_back(std::get<0>(time));
        }else{
            std::get<1>(elements[std::get<0>(time)]) = std::get<1>(time);
            std::get<2>(elements[std::get<0>(time)]) = true;
            std::get<3>(elements[std::get<0>(time)]) = std::get<2>(time);
        }
    }

    if(currentNb < elements.size()){
        insertRows(0, elements.size()-currentNb);
    }
}
