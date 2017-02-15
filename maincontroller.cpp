#include "maincontroller.h"

MainController* MainController::p_contr=Q_NULLPTR;

MainController::MainController(QObject *parent) : QObject(parent)
{

}

MainController *MainController::getInstance()
{
    if(p_contr!=Q_NULLPTR){
        p_contr=new MainController;
        return p_contr;
    }else
        return p_contr;
}
