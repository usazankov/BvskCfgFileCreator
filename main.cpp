#ifdef QT_WIDGETS_LIB
#include <QApplication>
#else
#include <QGuiApplication>
#endif
#include <QQmlApplicationEngine>
#include <documenthandler.h>
#include <QFontDatabase>
#include "parser.h"
#include "angle.h"
#include <algorithm>
#include <cl_algorithms.h>
int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("Text Editor");
    QGuiApplication::setOrganizationName("QtProject");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

#ifdef QT_WIDGETS_LIB
    QApplication app(argc, argv);
#else
    QGuiApplication app(argc, argv);
#endif
    QFontDatabase fontDatabase;
    if (fontDatabase.addApplicationFont(":/fonts/fontello.ttf") == -1)
        qWarning() << "Failed to load fontello.ttf";
    QQmlApplicationEngine engine;
    qmlRegisterType<DocumentHandler>("io.qt.BvskCfgCreatorGUI", 1, 0, "DocumentHandler");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    
    return app.exec();
}
