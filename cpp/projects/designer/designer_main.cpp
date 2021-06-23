
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

int main(int argc, char *argv[]){

    // build parameters
    const QString numVersion = "0.99z47";
    bool onlyPublicComponents = false;
    bool onlyStableComponents = false;

    // compiler check
    std::cout << std::format("Start ExVR-designer v{}\n", numVersion.toStdString()); // c++20 check

    // build app
    QApplication a(argc, argv);

    QPixmap pixmap(":/splash/ex_vr_splash");
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.show();
    QTimer::singleShot(1000, &splash, &QWidget::close);

    tool::ex::Paths::initialize_paths();        
    tool::ex::ExVrController controller(numVersion, onlyPublicComponents, onlyStableComponents);

    QCoreApplication::instance()->installEventFilter(&controller);

    int ret = a.exec();
    std::cout << "Quit with: " << ret << "\n";
    return ret;
}

