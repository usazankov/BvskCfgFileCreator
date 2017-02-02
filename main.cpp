#include <QCoreApplication>
#include "parser.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList list;
    list<<QString("/B45.txt")<<"/B50.txt";
    Parser* reader=new ParserTableOfDouble(list);
    reader->read();
    return a.exec();
}
