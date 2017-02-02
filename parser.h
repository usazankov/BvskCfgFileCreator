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

struct CalibrateData{
    struct FormatStr{
        double Acu;
        double Bcu;
        double Aizm;
        double Bizm;
    };
    QMap<int,FormatStr> data;
};
class Visitor{
public:
    virtual void visit(ParserTableOfDouble *reader)=0;
};

class GetterCalibrateData: public Visitor{
private:
    CalibrateData d;
public:
    void visit(ParserTableOfDouble *reader);
    CalibrateData* dataCalibrateTextReader();
};
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
