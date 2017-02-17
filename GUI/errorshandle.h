#ifndef ERRORSHANDLE_H
#define ERRORSHANDLE_H

#include <QObject>
#include <QQuickTextDocument>
#include <QTextDocument>
#include <QTextBlock>
#include <QStringList>
#include <iostream>
class ErrorsHandle : public QObject
{
    Q_OBJECT
private:
    explicit ErrorsHandle(QObject *parent = 0);
    explicit ErrorsHandle(const ErrorsHandle& err);
    ErrorsHandle& operator=(const ErrorsHandle& err);
    static ErrorsHandle *p_instance;
    int t;
public:
    static ErrorsHandle* getInstance();
    enum TypeMessage{Normal, Error, Good};
    static void sendMessage(QString msg, TypeMessage type=Normal);
signals:
    Q_INVOKABLE void newMessage(QString txt);
};

#endif // ERRORSHANDLE_H
