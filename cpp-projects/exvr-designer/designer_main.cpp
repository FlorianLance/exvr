
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// std
#include <format>

// Qt
#include <QApplication>
#include <QSplashScreen>

// base
#include "utility/tuple_array.hpp"

// local
#include "controller/exvr_controller.hpp"
#include "utility/path_utility.hpp"


using namespace tool::ex;


enum class testE : int {
  A,B,C, SizeEnum
};

using TupleT = std::tuple<testE, std::string_view>;
static constexpr tool::TupleArray<4, TupleT> tt = {{
    TupleT
    {testE::A, "A"sv},
    {testE::B, "B"sv},
    {testE::C, "C"sv},
    {testE::B, "B2"sv},
}};

template<typename T>
constexpr auto generate(int size, T value){
    T *a = new T[size];
    std::fill(a, a + size, value);
    return a;
}

template<typename T>
constexpr void deallocate(T *a){
    delete[] a;
}

constexpr int test(){
    auto g = generate<int>(10, 1);
    int total = std::accumulate(g, g + 10, 0);
    deallocate(g);
    return total;
}

static bool comp1(const std::unique_ptr<int> &l, const std::unique_ptr<int> &r){
    return (*l)< (*r);
}

static bool comp2(const std::unique_ptr<int> &l, const std::unique_ptr<int> &r){
    return (*l) == (*r);
}


int main(int argc, char *argv[]){

    std::vector<std::unique_ptr<int>> bb;
    bb.emplace_back(std::make_unique<int>(9));
    bb.emplace_back(std::make_unique<int>(8));
    bb.emplace_back(std::make_unique<int>(9));
    bb.emplace_back(std::make_unique<int>(2));
    bb.emplace_back(std::make_unique<int>(9));
    bb.emplace_back(std::make_unique<int>(3));
    bb.emplace_back(std::make_unique<int>(5));
    bb.emplace_back(std::make_unique<int>(3));


    std::vector<int> aa = {9,9,8,9,9,2,3,3,4,5,4,7};

    for(const auto& v : bb){
        std::cout << *v << " ";
    }
    std::cout << "\n";

    std::sort( bb.begin(), bb.end(), comp1);
    bb.erase( std::unique( bb.begin(), bb.end(), comp2), bb.end() );

    for(const auto& v : bb){
        std::cout << *v << " ";
    }
    std::cout << "\n";



    // build parameters
    const QString numVersion = "0.99z57";
    bool lncoComponents = true;

    // compiler check
    std::cout << std::format("Start ExVR-designer v{}\n", numVersion.toStdString()); // c++20 check

    // build app
    QApplication a(argc, argv);

    QPixmap pixmap(":/splash/ex_vr_splash");
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.show();
    QTimer::singleShot(1000, &splash, &QWidget::close);

    tool::ex::Paths::initialize_paths(QApplication::applicationDirPath());
    tool::ex::ExVrController controller(numVersion, lncoComponents);

    QCoreApplication::instance()->installEventFilter(&controller);

    int ret = a.exec();
    std::cout << "Quit with: " << ret << "\n";
    return ret;
}

