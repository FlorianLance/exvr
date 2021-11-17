

/***********************************************************************************
** exvr-test                                                                      **
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

// catch
#include "catch.hpp"

// base
#include "utility/benchmark.hpp"

// qt-utility
#include "qt_logger.hpp"

// exvr-designer
#include "IO/xml_io_manager.hpp"
#include "utility/path_utility.hpp"

using namespace tool;
using namespace tool::ex;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "%s\n", localMsg.constData());
//        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "%s\n", localMsg.constData());
//        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "\033[1;33mWarning\033[0m: %s\n", localMsg.constData());
//        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "\033[31mCritical\033[0m: %s\n", localMsg.constData());
//        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "\033[31mFatal\033[0m: %s\n", localMsg.constData());
//        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    }
}



TEST_CASE("Experiments loading"){


    qInstallMessageHandler(myMessageOutput);

    tool::Bench::disable_display();

    // init logging system
    QtLogger::init(QApplication::applicationDirPath() % QSL("/logs/"), QSL("designer_test.html"));
    QtLogger::set_html_ui_type_message_color(QtLogger::MessageType::normal,  QColor(189,189,189));
    QtLogger::set_html_ui_type_message_color(QtLogger::MessageType::warning, QColor(243, 158, 3));
    QtLogger::set_html_ui_type_message_color(QtLogger::MessageType::error,   QColor(244,4,4));
    QtLogger::set_html_ui_type_message_color(QtLogger::MessageType::unknow,  Qt::white);

    size_t countMessages = 0;
    size_t countWarnings = 0;
    size_t countErrors = 0;
    QtLogger::connect(QtLogger::get(), &QtLogger::message_signal, [&](QString){++countMessages;});
    QtLogger::connect(QtLogger::get(), &QtLogger::warning_signal, [&](QString w){++countWarnings;
        qWarning() << w.remove("<p><font color=#f39e03>").remove("</font></p>\n");
    });
    QtLogger::connect(QtLogger::get(), &QtLogger::error_signal, [&](QString e){++countErrors;
        qCritical() << e.remove("<p><font color=#f40404>").remove("</font></p>\n");
    });

    tool::ex::Paths::initialize_paths(QApplication::applicationDirPath() + "/../exvr-designer");

    tool::ex::Experiment exp("0.99z52");
    tool::ex::XmlIoManager xmlIoM(&exp);
    REQUIRE(!xmlIoM.load_experiment_file(""));
    REQUIRE(!xmlIoM.load_experiment_file("///"));
    REQUIRE(!xmlIoM.load_experiment_file("../../../.."));
    REQUIRE(!xmlIoM.load_experiment_file("\aàé_gub"));

    REQUIRE(xmlIoM.load_experiment_file(Paths::expDir % QSL("/examples/button_press_reaction_time_using_connections.xml")));
    REQUIRE(xmlIoM.load_experiment_file(Paths::expDir % QSL("/examples/camera_trajectories.xml")));
    REQUIRE(xmlIoM.load_experiment_file(Paths::expDir % QSL("/examples/image.xml")));
    REQUIRE(xmlIoM.load_experiment_file(Paths::expDir % QSL("/examples/input_controllers.xml")));
    REQUIRE(xmlIoM.load_experiment_file(Paths::expDir % QSL("/examples/keyboard_with_slider.xml")));
    REQUIRE(xmlIoM.load_experiment_file(Paths::expDir % QSL("/examples/logger_conditions_sample.xml")));
    REQUIRE(xmlIoM.load_experiment_file(Paths::expDir % QSL("/examples/read_write_udp.xml")));
    REQUIRE(xmlIoM.load_experiment_file(Paths::expDir % QSL("/examples/slider_moving_value.xml")));
    REQUIRE(xmlIoM.load_experiment_file(Paths::expDir % QSL("/examples/write_data_to_csv_using_connections.xml")));
    REQUIRE(xmlIoM.load_experiment_file(Paths::expDir % QSL("/examples/write_data_to_file_using_scripting.xml")));

    REQUIRE(xmlIoM.load_experiment_file(Paths::expDir % QSL("/debug/test_duplicated_connections.xml")));

    qDebug() << "Messages: " << countMessages;
    qDebug() << "Warnings: " << countWarnings;
    qDebug() << "Errors: " << countErrors;
    // https://www.froglogic.com/blog/tip-of-the-week/unit-tests-for-qt-based-applications-with-catch/

//    SECTION("Matrix 3x3"){
//        REQUIRE(geo::equals(dm1,from_glm(glmdm1)));
//        REQUIRE(dm1.determinant() == glm::determinant(glmdm1));
//    }

//    SECTION("Look at"){
//        auto lightView1 = from_glm(glm::lookAt(
//            glm::vec3(-2.0f, 4.0f, -1.0f),
//            glm::vec3( 0.0f, 0.0f,  0.0f),
//            glm::vec3( 0.0f, 1.0f,  0.0f)
//        ));

//        auto lightView2 = geo::Mat4f::LookAt(
//            geo::Pt3f{-2.0f, 4.0f, -1.0f},
//            geo::Vec3f{0.0f, 0.0f,  0.0f},
//            geo::Vec3f{0.0f, 1.0f,  0.0f}
//        );

//        REQUIRE(geo::equals(clean(lightView1),clean(lightView2)));
//    }


}

