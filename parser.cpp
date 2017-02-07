#include "parser.h"

Parser::Parser()
{

}

Parser::~Parser()
{

}

void ParserTableOfDouble::initialize()
{
    comment=bvsk_cfg::DEFAULT_COMMENT;
    regular.setPattern(bvsk_cfg::DEFAULT_REGULAR_DOUBLE);
}

ParserTableOfDouble::ParserTableOfDouble(const QStringList &files):Parser()
{
    pathToFiles=files;
    initialize();
}

std::vector<std::vector<double> > *ParserTableOfDouble::getData()
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
                std::vector<double> col;
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
}

void ParserTableOfDouble::accept(Visitor *visitor)
{
    visitor->visit(this);
}

void GetterInputData::visit(ParserTableOfDouble *reader)
{
    using namespace std;
    using namespace bvsk_cfg;
    std::vector< std::vector<double> > *data=reader->getData();
    int previous_Bcu=0;
    int current_Bcu=0;
    int count_sectors=0;
    std::vector<InputCalibrateData::FormatStr> temp;
    for(unsigned int j=0;j<data->size();++j) {
        InputCalibrateData::FormatStr line;
        for(unsigned int i=0;i<(*data)[j].size();++i){
            switch (i) {
            case 0:
                line.Acu=(*data)[j][i];
                break;
            case 1:
                line.Bcu=(*data)[j][i];
                current_Bcu=(*data)[j][i];
                break;
            case 2:
                line.Aizm=(*data)[j][i];
                break;
            case 3:
                line.Bizm=(*data)[j][i];
                break;
            default:
                break;
            }
        }
        //Загоняем в map если: текущее значение Bcu не равно предыдущему и при этом текущая строка не равна первой
        if((current_Bcu!=previous_Bcu&&(j!=0))||j==data->size()-1){
            if(j==data->size()-1)
                temp.push_back(line);//Для последней строки
            d.data[count_sectors++]=temp;
            temp.clear();
        }
        temp.push_back(line);
        previous_Bcu=current_Bcu;
    }
    /*for(unsigned int i=0;i<d.data.size(); ++i) {
        cout<<"size_parsing="<<d.data[i].size()<<endl;
    }*/
}

InputCalibrateData *GetterInputData::getInputData()
{
    return &d;
}

void CheckerInputData::visit(ParserTableOfDouble *reader)
{

}

QString CheckerInputData::info()
{
    return "";
}
