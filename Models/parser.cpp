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

bool ParserTableOfDouble::isComment(const QString &str)const
{
    if(str!=0){
        if(str.contains(bvsk_cfg::DEFAULT_COMMENT)){
            return 1;
        }
    }
    return 0;
}

bool ParserTableOfDouble::checkLine(const QString &str)const
{
    if(str!=0){
        QString temp;
        QRegExp reg("[^-0-9,.\\s]");
        for(int i=0;i<str.size();++i){
            if(str.at(i)==' '||i==str.size()-1){
                if(i==str.size()-1)
                    temp.append(str.at(i));
                if(temp.contains(reg)){
                    return false;
                }
                temp.clear();
            }else{
                temp.append(str.at(i));
            }
        }
    }
    return true;
}

ParserTableOfDouble::ParserTableOfDouble(const QString &txt)
{
    this->txt=txt;
    initialize();
}

ParserTableOfDouble::ParserTableOfDouble():Parser()
{
    this->txt="";
    initialize();
}

std::vector<std::vector<double> > *ParserTableOfDouble::getData()
{
    return &data;
}

void ParserTableOfDouble::setTxt(const QString &txt)
{
    this->txt=txt;
}

void ParserTableOfDouble::read()
{
    QTextStream stream(&txt);
    int row=0;
    int column=0;
    while(!stream.atEnd()){
        QString line=stream.readLine();
        int positionInLine = 0;
        if(!isComment(line)){
            if(checkLine(line)){
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
                }
            }else{
                throw ParsingEx("Not double", row+1);
            }
        }
        ++row;
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

CheckerInputData::CheckerInputData()
{
    checkisValid=1;
}

void CheckerInputData::visit(ParserTableOfDouble *reader)
{

}

bool CheckerInputData::isValid()
{
    return checkisValid;
}
