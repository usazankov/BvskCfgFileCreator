#include "errorshandle.h"

ErrorsHandle* ErrorsHandle::p_instance=Q_NULLPTR;
ErrorsHandle::ErrorsHandle(QObject *parent) : QObject(parent)
{

}

ErrorsHandle *ErrorsHandle::getInstance()
{
    if(p_instance==Q_NULLPTR){
        p_instance=new ErrorsHandle;
        return p_instance;
    }else
        return p_instance;
}

void ErrorsHandle::sendMessage(QString msg, ErrorsHandle::TypeMessage type)
{
    switch (type) {
    case Normal:
        emit ErrorsHandle::getInstance()->newMessage("<span>"+msg+"</span>");
        break;
    case Error:
        emit ErrorsHandle::getInstance()->newMessage("<span style='color:red'>"+msg+"</span>");
        break;
    case Good:
        emit ErrorsHandle::getInstance()->newMessage("<span style='color:green'>"+msg+"</span>");
        break;
    default:
        emit ErrorsHandle::getInstance()->newMessage("<span>"+msg+"</span>");
        break;
    }

}
