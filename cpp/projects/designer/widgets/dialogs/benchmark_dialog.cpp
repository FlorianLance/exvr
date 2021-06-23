
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

    auto sort  = new QCheckBox("Sort");
    auto unit = new QComboBox();
    auto minT = new QDoubleSpinBox();
    layout()->addWidget(ui::F::gen(ui::L::HB(), {sort, ui::W::txt("Unit:"), unit, ui::W::txt("Min T:"), minT}, LStretch{true}, LMargins{true}, QFrame::NoFrame));
    layout()->addWidget(view);
}

void BenchmarkDialog::update(){
    model->update();
    view->viewport()->update();
}

int Table::rowCount(const QModelIndex &) const{
    return elements.size();
}

int Table::columnCount(const QModelIndex &) const{
    return 2;
}

QVariant Table::data(const QModelIndex &index, int role) const{

    if (role == Qt::DisplayRole){
        auto id = order[index.row()];
        if(index.column() == 0){
            return elements.at(id).first;
        }else if (index.column() == 1){
            return elements.at(id).second;
        }
    }
    return QVariant();
}

void Table::update(){
    auto currentNb = elements.size();

    times = Bench::all_total_times(BenchUnit::microseconds, -1, true);
    for(const auto& time : times){
        if(!elements.contains(time.first)){
            elements[time.first] = std::make_pair(from_view(time.first), 0);
            order.emplace_back(time.first);
        }else{
            elements[time.first].second = time.second;
        }
    }

    if(currentNb < elements.size()){
        insertRows(0, elements.size()-currentNb);
    }
}
