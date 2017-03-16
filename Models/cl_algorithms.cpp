#include "cl_algorithms.h"

double CalculatorCalibrateData::horizontLenght=10;
double CalculatorCalibrateData::verticaltLenght=5;

CalculatorCalibrateData::CalculatorCalibrateData(InputCalibrateData *d)
{
    this->d=d;
}

void CalculatorCalibrateData::setHorizontLength(double length)
{
    horizontLenght=length;
}

void CalculatorCalibrateData::setVerticalLength(double length)
{
    verticaltLenght=length;
}

void CalculatorCalibrateData::process()
{
    using namespace std;
    struct Delta{
        Angle dEps;
        Angle dDelta;
    };
    map<int, vector<Delta> > map_delta;
    //Вычисляем дельты: разницы между ЦУ и ИЗМ (Aизм-Aцу, Bизм-Bцу) и записываем их в map_delta
    for(std::pair<const int, std::vector<InputCalibrateData::FormatStr> > p: d->data)
    {
        vector<Delta> deltas;
        for_each(p.second.cbegin(),p.second.cend(), [&deltas](InputCalibrateData::FormatStr f)
        {
            Delta delta;
            delta.dEps=f.Aizm-f.Acu;
            delta.dDelta=f.Bizm-f.Bcu;
            deltas.push_back(delta);
        });
        map_delta[p.first]=deltas;
    }
    //Вывести на дисплэй дельты
    /*for(std::pair<const int, std::vector<Delta> > p: map_delta)
    {
        cout<<"Сектор №"<<p.first<<endl;
        for_each(p.second.cbegin(),p.second.cend(),[](Delta temp)
        {
            cout<<"dDelta = "<<temp.dDelta<<" dEps = "<<temp.dEps<<std::endl;
        });
    }*/

    //Вычисляем линейные коэффициенты

    /* Здесь будут храниться коэффициенты и поправки для всех секторов */

    for(size_t i=1;i<map_delta.size();++i){
        /* Промежуточный массив для хранения коэффициентов по 12 азимутальным секторам */
        vector<CalibrateSector> AzSectors;
        for(size_t j=1;j<map_delta[i].size();++j){
            CalibrateSector Sect;
            /*Вершины сектора (прямоугольник), верх право не нужна*/
            Angle Eps00, Eps01, Eps10, Dlt00, Dlt01, Dlt10;
            Eps00=map_delta[i-1][j-1].dEps;
            Eps01=map_delta[i-1][j].dEps;
            Eps10=map_delta[i][j-1].dEps;

            Dlt00=map_delta[i-1][j-1].dDelta;
            Dlt01=map_delta[i-1][j].dDelta;
            Dlt10=map_delta[i][j-1].dDelta;

            Sect.eps.vertex=Eps00;
            Sect.eps.hor_coef=(Eps01-Eps00).toDegrees()/horizontLenght;
            Sect.eps.ver_coef=(Eps10-Eps00).toDegrees()/verticaltLenght;

            Sect.delta.vertex=Dlt00;
            Sect.delta.hor_coef=(Dlt01-Dlt00).toDegrees()/horizontLenght;
            Sect.delta.ver_coef=(Dlt10-Dlt00).toDegrees()/verticaltLenght;
            AzSectors.push_back(Sect);
        }
        AllSectors.push_back(AzSectors);
    }
    for(unsigned int i=0; i<AllSectors.size();++i){
        cout<<"^"<<d->data[i][0].Bcu<<endl;
        for(unsigned int j=0;j<AllSectors[i].size();++j){
            cout<<AllSectors[i][j]<<endl;
        }
    }
}

void CalculatorCalibrateData::clearResult()
{
    AllSectors.clear();
}

QString CalculatorCalibrateData::result()
{
    QString txt;
    char f='f';//Format Output
    for(unsigned int i=0; i<AllSectors.size();++i){
        txt+="^"+QString::number(d->data[i][0].Bcu.toDegrees())+"\n";
        for(unsigned int j=0;j<AllSectors[i].size();++j){
            CalibrateSector sector=AllSectors[i][j];
            txt+=QString::number(sector.eps.vertex.toDegrees(),f,bvsk_cfg::precision)
                    +" "+QString::number(sector.eps.hor_coef,f,bvsk_cfg::precision)+
                    " "+QString::number(sector.eps.ver_coef,f,bvsk_cfg::precision)+" "+
                    QString::number(sector.delta.vertex.toDegrees(),f,bvsk_cfg::precision)+
                    " "+QString::number(sector.delta.hor_coef,f,bvsk_cfg::precision)+
                    " "+QString::number(sector.delta.ver_coef,f,bvsk_cfg::precision)+"\n";
        }
    }
    return txt;
}

void CalculatorCalibrateData::saveToFile(const QUrl &path) const
{

}

std::vector<std::vector<CalibrateSector> > *CalculatorCalibrateData::getResultStruct()
{
    return &AllSectors;
}
