#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "Models/parser.h"
#include "Models/angle.h"
#include <Models/cl_algorithms.h>
#include <algorithm>

class MainController : public QObject
{
    Q_OBJECT
private:
    explicit MainController(const MainController& cont);
    explicit MainController(QObject *parent = 0);
    MainController& operator=(const MainController& cont);
    static MainController* p_contr;
public:
    static MainController* getInstance();
signals:

public slots:
};

#endif // MAINCONTROLLER_H
