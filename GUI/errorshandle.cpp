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
        emit ErrorsHandle::getInstance()->newMessage("<span>"+msg.replace("\n","<br>")+"</span>");
        break;
    case Error:
        emit ErrorsHandle::getInstance()->newMessage("<span style='color:#CF5151'>"+msg.replace("\n","<br>")+"</span>");
        break;
    case Good:
        emit ErrorsHandle::getInstance()->newMessage("<span style='color:#008000'>"+msg.replace("\n","<br>")+"</span>");
        break;
    default:
        emit ErrorsHandle::getInstance()->newMessage("<span>"+msg.replace("\n","<br>")+"</span>");
        break;
    }
    msg.replace("<br>","\n");
    std::cout<<msg.toStdString()<<std::endl;
}
