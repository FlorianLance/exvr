
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

// Qt
#include <QApplication>
#include <QSplashScreen>

// base
#include "utility/format.hpp"

// local
#include "controller/exvr_controller.hpp"


using namespace tool;
using namespace tool::ex;
using namespace Qt::Literals::StringLiterals;

auto generate_doc_in_console() -> void{

    Connector::Category cc = Connector::Category::Resource;
    for(auto t : Connector::all_types()){

        auto n = Connector::get_caption(t);

        std::string_view ccn = "-";
        if(Connector::get_category(t) != cc){
            cc  = Connector::get_category(t);
            ccn = Connector::get_name(cc);
        }
        std::cout << std::format("|{}|{}|[link](connectors/{}_info.md)|[link](connectors/{}_connections.md)|\n",
            ccn, n, ccn, ccn
        );
    }
    Component::Category c = Component::Category::Viewer;
    for(auto t : Component::all_components_types()){
        auto fn = Component::get_full_name(t);
        auto un = Component::get_unity_name(t);

        std::string_view cn = "-";
        if(Component::get_category(t) != c){
            c = Component::get_category(t);
            cn = Component::get_display_name(c);
        }
        std::cout << std::format("|{}|{}|[link](components/{}_info.md)|[link](components/{}_csharp.md)|[link](components/{}_connections.md)|\n",
            cn, fn, un, un, un
        );
    }
}


auto main(int argc, char *argv[]) -> int{

    // generate_doc_in_console();

    // build parameters
    const QString numVersion = "1.0b9";

    // compiler check
    std::cout << tool::fmt("Start ExVR-designer v{}\n", numVersion.toStdString()); // c++20 check

    // build app
    QApplication a(argc, argv);

    QPixmap pixmap(":/splash/ex_vr_splash");
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.show();

    // init logging system
    auto logger = BaseLogger::generate_logger_instance<QtLoggerM>();
    logger->init(u"%1/logs"_s.arg(QApplication::applicationDirPath()), u"designer_log.html"_s, true);
    logger->set_type_color(QtLoggerM::MessageType::normal,  QColor(189,189,189));
    logger->set_type_color(QtLoggerM::MessageType::warning, QColor(243, 158, 3));
    logger->set_type_color(QtLoggerM::MessageType::error,   QColor(244,4,4));
    logger->set_type_color(QtLoggerM::MessageType::unknow,  Qt::white);
    logger->set_html_file_background_color(u"black"_s);


    tool::ex::Paths::initialize_paths(QApplication::applicationDirPath());
    tool::ex::ExVrController controller(numVersion);
    QCoreApplication::instance()->installEventFilter(&controller);

    QTimer::singleShot(1500, &splash, &QWidget::close);

    int ret = a.exec();
    std::cout << "Exited with: " << ret << "\n";
    return ret;
}





