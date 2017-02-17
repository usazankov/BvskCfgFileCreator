#ifndef PARSER_H
#define PARSER_H
#include <QStringList>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include "io_structs.h"
#include <QDoubleValidator>
namespace bvsk_cfg {
    const QChar DEFAULT_COMMENT='#';
    const QString DEFAULT_REGULAR_DOUBLE="(-?\\d+(?:[.,]\\d+)?)";
}
class Visitor;
class Parser
{
public:
    Parser();
    virtual void read()=0;
    virtual void accept(Visitor* visitor)=0;
    virtual ~Parser();
};
//ParserTableOfDouble - Парсер данных типа double, парсить таблицу double-ов разделенных пробелами
//Выходными данными парсера является Вектор векторов (std::vector< std::vector<double> >)
class ParserTableOfDouble: public Parser{
private:
    QString txt;
    std::vector< std::vector<double> > data;
    QRegExp regular;
    QString comment;
    void initialize();
    bool checkLine(const QString &str) const;
    bool isComment(const QString &str) const;
public:
    ParserTableOfDouble(const QString &txt);
    ParserTableOfDouble();
    std::vector< std::vector<double> >* getData();
    // Class of Exceptions
        class ParsingEx{
        public:
            QString infoEx;
            int numberStrEx;
            ParsingEx(const QString &txt, int number){
                infoEx = txt;
                numberStrEx = number;
            }
        };
    // Reader interface
public:
    void setTxt(const QString &txt);
    void read();
    void accept(Visitor *visitor);
};

//Класс Visitor - реализация паттерна посетитель, необходим для обхода наследников класса Parser
class Visitor{
public:
    virtual void visit(ParserTableOfDouble *reader)=0;
};
//GetterInputData - для преобразования данных из парсера в удобный вид (InputData) для дальнейшей обработки
class GetterInputData: public Visitor{
private:
    InputCalibrateData d;
public:
    void visit(ParserTableOfDouble *reader);
    InputCalibrateData* getInputData();
};
//CheckerInputData - для проверки протокола входных данных
class CheckerInputData: public Visitor{
private:
    bool checkisValid;
    // Visitor interface
public:
    CheckerInputData();
    class CheckingEx{
    public:
        QString infoEx;
        int numberStrEx;
        CheckingEx(const QString &txt, int number){
            infoEx = txt;
            numberStrEx = number;
        }
    };
    void visit(ParserTableOfDouble *reader);
    bool isValid();
};

#endif // PARSER_H
