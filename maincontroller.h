#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "Models/parser.h"
#include "Models/angle.h"
#include "Models/cl_algorithms.h"
#include "GUI/documenthandler.h"
#include "GUI/errorshandle.h"
#include <algorithm>
#include <QtConcurrent/QtConcurrent>
class MainController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int typeProcess READ typeProcess WRITE setTypeProcess NOTIFY typeProcessChanged)
    Q_PROPERTY(DocumentHandler* docHandler READ docHandler WRITE setDocHandler NOTIFY docHandlerChanged)
private:
    explicit MainController(const MainController& cont);
    explicit MainController(QObject *parent = 0);
    MainController& operator=(const MainController& cont);
    bool parsingCalibrateOrTermoCalibrate();
    void processingCalibrate();
    static MainController* p_contr;
    int p_type; //0 - Calibration, 1 - Termocalibration, 2 - CheckCFG
    QString result_Txt;
    DocumentHandler* doc;
    Parser *parser;
public:
    static MainController* getInstance();
    Q_INVOKABLE void process();
    Q_INVOKABLE void check();
    int typeProcess()const;
    void setTypeProcess(int type);
    ~MainController();
    DocumentHandler *docHandler() const;
    void setDocHandler(DocumentHandler *value);
signals:
    void typeProcessChanged();
    void docHandlerChanged();
};

#endif // MAINCONTROLLER_H
