#include <QCoreApplication>
#include "parser.h"
#include "angle.h"
#include <algorithm>
#include <cl_algorithms.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList list;
    list<<"/conf.txt";
    using namespace bvsk_cfg;
    Parser* reader=new ParserTableOfDouble(list);
    reader->read();
    GetterInputData getter;
    reader->accept(&getter);
    InputCalibrateData *d=getter.getInputData();
    CalculatorCalibrateData calc(d);
    calc.process();
    
    return a.exec();
}
