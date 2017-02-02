#include "parser.h"

Parser::Parser()
{

}

Parser::~Parser()
{

}

void ParserTableOfDouble::initialize()
{
    comment=parser::DEFAULT_COMMENT;
    regular.setPattern(parser::DEFAULT_REGULAR_DOUBLE);
}

ParserTableOfDouble::ParserTableOfDouble(const QStringList &files):Parser()
{
    pathToFiles=files;
    initialize();
}

QVector<QVector<double> > *ParserTableOfDouble::getData()
{
    return &data;
}

void ParserTableOfDouble::read()
{
    foreach (QString path, pathToFiles) {
        QFile file(QDir::currentPath()+path);
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"Невозможно открыть файл: "<<path;
            break;
        }
        QTextStream stream(&file);
        int row=0;
        int column=0;
        while(!stream.atEnd()){
            QString line=stream.readLine();
            int positionInLine = 0;
            if((regular.indexIn(line,positionInLine)) != -1){
                QVector<double> col;
                column=0;
                while((positionInLine = regular.indexIn(line,positionInLine)) != -1) {
                    QString cap = regular.cap(1);
                    col.push_back(cap.toDouble());
                    positionInLine += regular.matchedLength();
                    ++column;
                }
                data.push_back(col);
                ++row;
            }
        }
    }
    qDebug()<<"count vectors: "<<data.count();
    foreach (QVector<double> v, data) {
        QString a;
        foreach (double d, v) {
            a+=QString::number(d)+" ";
        }
        qDebug()<<a;
    }
}

void ParserTableOfDouble::accept(Visitor *visitor)
{
    visitor->visit(this);
}

void GetterCalibrateData::visit(ParserTableOfDouble *reader)
{

}

CalibrateData *GetterCalibrateData::dataCalibrateTextReader()
{

    return &d;
}

void CheckerCalibrateData::visit(ParserTableOfDouble *reader)
{

}

QString CheckerCalibrateData::info()
{

}
