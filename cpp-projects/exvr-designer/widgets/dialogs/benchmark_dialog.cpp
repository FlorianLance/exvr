
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
}

void BenchmarkDialog::update(){
    model->update(sort->isChecked());
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
        auto id = index.row();
        if(index.column() == 0){
            return std::get<1>(elements[id]);
        }else if (index.column() == 1){
            return std::get<2>(elements[id]);
        }else if(index.column() == 2){
            return std::get<4>(elements[id]);
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
            auto id = index.row();
            return std::get<3>(elements.at(id)) ? QColor(Qt::green) : QColor(Qt::darkYellow);
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

void Table::update(bool sort){

    beginResetModel();

    // reset enabled state
    for(auto &element : elements){
        std::get<3>(element) = false;
    }

    size_t rowAdded = 0;
    for(auto &timeInfo : Bench::all_total_times(BenchUnit::microseconds, -1, false)){

        std::string_view nameView = std::get<0>(timeInfo);
        const auto time  = std::get<1>(timeInfo);
        const auto count = std::get<2>(timeInfo);

        if(!elementsRow.contains(nameView)){
            elementsRow[nameView] = elementsRow.size();
            elements.emplace_back(std::make_tuple(nameView, from_view(nameView), time, true, count));
            ++rowAdded;
        }else{
            auto &element = elements[elementsRow[nameView]];
            std::get<2>(element) = time;
            std::get<3>(element) = true;
            std::get<4>(element) = count;
        }
    }

    // name view / time / enabled / count
    using T = std::tuple<std::string_view, QString, std::int64_t, bool, size_t>;
    if(sort){
        std::sort(std::begin(elements), std::end(elements), [&](const T& l, const T& r){
            if(std::get<3>(l) && !std::get<3>(r)){
                return true;
            }
            if(!std::get<3>(l) && std::get<3>(r)){
                return false;
            }
            return std::get<2>(l) > std::get<2>(r);
        });
    }

    for(size_t ii = 0; ii < elements.size(); ++ii){
        elementsRow[std::get<0>(elements[ii])] = ii;
    }

    endResetModel();
}
