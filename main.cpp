#ifdef QT_WIDGETS_LIB
#include <QApplication>
#else
#include <QGuiApplication>
#endif
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFontDatabase>
#include "GUI/documenthandler.h"
#include "GUI/errorshandle.h"
#include "maincontroller.h"
int main(int argc, char *argv[])
{
    //GUI
    QGuiApplication::setApplicationName("BvskCfgFileCreator");
    QGuiApplication::setOrganizationName("MIEA");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

#ifdef QT_WIDGETS_LIB
    QApplication app(argc, argv);
#else
    QGuiApplication app(argc, argv);
#endif
    QQmlApplicationEngine engine;
    QFontDatabase fontDatabase;
    if (fontDatabase.addApplicationFont(":/GUI/fonts/fontello.ttf") == -1)
        qWarning() << "Failed to load fontello.ttf";
    qmlRegisterType<DocumentHandler>("io.qt.BvskCfgFileCreatorGUI", 1, 0, "DocumentHandler");
    QQmlContext *pcon=engine.rootContext();

    pcon->setContextProperty("errHandle", ErrorsHandle::getInstance());
    engine.load(QUrl(QLatin1String("qrc:/GUI/main.qml")));
    //Models
    pcon->setContextProperty("controller", MainController::getInstance());
    return app.exec();
}
