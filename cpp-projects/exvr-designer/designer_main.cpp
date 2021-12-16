
/***********************************************************************************
** exvr-designer                                                                  **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

// std
#include <format>
#include <algorithm>

// Qt
#include <QApplication>
#include <QSplashScreen>

// base
#include "utility/tuple_array.hpp"

// local
#include "controller/exvr_controller.hpp"
#include "utility/path_utility.hpp"


using namespace tool::ex;


//enum class testE : int {
//  A,B,C, SizeEnum
//};

//using TupleT = std::tuple<testE, std::string_view>;
//static constexpr tool::TupleArray<4, TupleT> tt = {{
//    TupleT
//    {testE::A, "A"sv},
//    {testE::B, "B"sv},
//    {testE::C, "C"sv},
//    {testE::B, "B2"sv},
//}};

//template<typename T>
//constexpr auto generate(int size, T value){
//    T *a = new T[size];
//    std::fill(a, a + size, value);
//    return a;
//}


//template<typename T>
//constexpr void deallocate(T *a){
//    delete[] a;
//}

//constexpr int test(){
//    auto g = generate<int>(10, 1);
//    int total = std::accumulate(g, g + 10, 0);
//    deallocate(g);
//    return total;
//}

//static bool comp1(const std::unique_ptr<int> &l, const std::unique_ptr<int> &r){
//    return (*l)< (*r);
//}

//static bool comp2(const std::unique_ptr<int> &l, const std::unique_ptr<int> &r){
//    return (*l) == (*r);
//}

//#include "geometry/point3.hpp"
//#include "geometry/point4.hpp"


int main(int argc, char *argv[]){


//    auto max = std::numeric_limits<int16_t>::max(); // 32767
//    auto min = std::numeric_limits<int16_t>::min(); // -32768
//    // -8192 / +8191
//    // -4096 / +4095
//    // -16384 / 16385

//    std::cout << min << " " << max << "\n";

//    // convert in mm
//    // * 1000.f

//    // check if depth < 8192
//    // substract 4096

//    // [-4096 / +4095]
//    //

//    tool::geo::Pt3<std::int16_t> p{4095, -4095, 7000};
//    tool::geo::Pt4<std::uint8_t> c{255, 0, 122, 254};

//    T1 t;
//    t.pack(p, c);


//    auto p1 = t.unpack_pos_f();
//    auto p2 = t.unpack_pos_i16();

//    auto c1 = t.unpack_col_3ui8();
//    auto c2 = t.unpack_col_4ui8();
//    auto c3 = t.unpack_col_3f();
//    auto c4 = t.unpack_col_4f();

//    std::cout << p1 << " " << p2 << "\n";
//    std::cout << c3 << " " << c4 << "\n";

////    tool::geo::Pt3f res;

////    std::cout << p << " " << t.x << " " << t.y << " " << t.z << "\n" <<
////        (int)t.r << " " << (int)t.g << " " << (int)t.b << "\n" <<
////        res <<  "\n";


//    return 0;


    // build parameters
    const QString numVersion = "1.0a16";
    bool lncoComponents = true;

    // compiler check
    std::cout << std::format("Start ExVR-designer v{}\n", numVersion.toStdString()); // c++20 check

    // build app
    QApplication a(argc, argv);

    QPixmap pixmap(":/splash/ex_vr_splash");
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.show();

    tool::ex::Paths::initialize_paths(QApplication::applicationDirPath());
    tool::ex::ExVrController controller(numVersion, lncoComponents);
    QCoreApplication::instance()->installEventFilter(&controller);

    QTimer::singleShot(1000, &splash, &QWidget::close);

    int ret = a.exec();
    std::cout << "Quit with: " << ret << "\n";
    return ret;
}

