#ifndef PARSER_H
#define PARSER_H
#include <QStringList>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QDir>
namespace parser {
    const QString DEFAULT_COMMENT="#";
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
//ParserTableOfDouble - Парсер данных типа double
//Выходными данными парсера является Вектор векторов (QVector< QVector<double> >)
class ParserTableOfDouble: public Parser{
private:
    QStringList pathToFiles;
    QVector< QVector<double> > data;
    QRegExp regular;
    QString comment;
    void initialize();
public:
    ParserTableOfDouble(const QStringList &files);
    QVector< QVector<double> >* getData();
    // Reader interface
public:
    void read();
    void accept(Visitor *visitor);
};
//Структура выходных данных после парсинга файла калибровочных коэффициентов
struct CalibrateData{
    struct FormatStr{
        double Acu;
        double Bcu;
        double Aizm;
        double Bizm;
    };
    QMap<int,FormatStr> data;
};

//Класс Visitor - реализация паттерна посетитель, необходим для обхода наследников класса Parser
class Visitor{
public:
    virtual void visit(ParserTableOfDouble *reader)=0;
};
//GetterCalibrateData - для преобразования данных из парсера в удобный вид (CalibrateData) для дальнейшей обработки
class GetterCalibrateData: public Visitor{
private:
    CalibrateData d;
public:
    void visit(ParserTableOfDouble *reader);
    CalibrateData* dataCalibrateTextReader();
};
//CheckerCalibrateData - для проверки протокола входных данных
class CheckerCalibrateData: public Visitor{
private:
    bool CheckisValid;
    // Visitor interface
public:
    void visit(ParserTableOfDouble *reader);
    QString info();
    bool isValid();
};
#endif // PARSER_H
