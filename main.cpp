#ifdef QT_WIDGETS_LIB
#include <QApplication>
#else
#include <QGuiApplication>
#endif
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include "Models/parser.h"
#include "Models/angle.h"
#include <algorithm>
#include <Models/cl_algorithms.h>
#include <GUI/documenthandler.h>

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
    if (fontDatabase.addApplicationFont(":/GUI/fonts/fontello.ttf") == -1)
        qWarning() << "Failed to load fontello.ttf";
    QStringList selectors;
#ifdef QT_EXTRA_FILE_SELECTOR
    selectors += QT_EXTRA_FILE_SELECTOR;
#else
    if (app.arguments().contains("-touch"))
        selectors += "touch";
#endif

    QQmlApplicationEngine engine;
    QQmlFileSelector::get(&engine)->setExtraSelectors(selectors);
    qmlRegisterType<DocumentHandler>("io.qt.BvskCfgFileCreatorGUI", 1, 0, "DocumentHandler");
    engine.load(QUrl(QLatin1String("qrc:/GUI/main.qml")));
    
    return app.exec();
}
