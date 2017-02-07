#include <QCoreApplication>
#include "parser.h"
#include "angle.h"
#include <algorithm>
#include <cl_algorithms.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList list;
    list<<"/B45.txt"<<"/B50.txt"<<"/B55.txt"<<"/B60.txt"<<"/B65.txt"<<"/B70.txt"<<"/B75.txt"<<"/B80.txt";
    using namespace bvsk_cfg;
    Parser* reader=new ParserTableOfDouble(list);
    reader->read();
    GetterInputData getter;
    reader->accept(&getter);
    InputCalibrateData *d=getter.getInputData();
    CalculatorCalibrateData calc(d);
    calc.process();
    /*DisplayCalibrateData funct;
    std::for_each(d->data.begin(),d->data.end(),funct);*/
    return a.exec();
}
