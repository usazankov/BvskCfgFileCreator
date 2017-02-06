#include "cl_algorithms.h"

double CalculatorCalibrateData::horizontLenght=10;
double CalculatorCalibrateData::verticaltLenght=5;

CalculatorCalibrateData::CalculatorCalibrateData(InputData *d)
{
    this->d=d;
}

void CalculatorCalibrateData::process()
{
    using namespace std;
    struct Delta{
        Angle dEps;
        Angle dDelta;
    };
    map<int, vector<Delta> > map_delta;
    cout<<"count_d="<<d->data.size()<<endl;
    //Вычисляем дельты: разницы между ЦУ и ИЗМ (Aизм-Aцу, Bизм-Bцу) и записываем их в map_delta
    for(std::pair<const int, std::vector<InputData::FormatStr> > p: d->data)
    {
        cout<<p.first<<endl;
        vector<Delta> deltas;
        for_each(p.second.cbegin(),p.second.cend(), [&deltas](InputData::FormatStr f)
        {
            Delta delta;
            delta.dEps=f.Aizm-f.Acu;
            delta.dDelta=f.Bizm-f.Bcu;
            deltas.push_back(delta);
        });
        map_delta[p.first]=deltas;
    }
    //Вывести на дисплэй дельты
    for(std::pair<const int, std::vector<Delta> > p: map_delta)
    {
        cout<<"Сектор №"<<p.first<<endl;
        for_each(p.second.cbegin(),p.second.cend(),[](Delta temp)
        {
            cout<<"dDelta = "<<temp.dDelta<<" dEps = "<<temp.dEps<<std::endl;
        });
    }
    //Описываем выходную структуру данных для калибровочных коэффициентов
    struct CalibrateCorrect{
        Angle vertex;
        double hor_coef;
        double ver_coef;
    };
    //Вычисляем коэффициенты
    for(size_t i=0;i<map_delta.size();++i){
        cout<<"Сектор №"<<i<<endl;
        for_each(map_delta[i].cbegin(),map_delta[i].cend(),[](Delta temp)
        {
            cout<<"dDelta = "<<temp.dDelta<<" dEps = "<<temp.dEps<<std::endl;
        });
    }


}
