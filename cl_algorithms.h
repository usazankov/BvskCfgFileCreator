#ifndef CL_ALGORITHMS_H
#define CL_ALGORITHMS_H

#include "io_structs.h"
#include "angle.h"
#include <iostream>
using namespace bvsk_cfg;
//DisplayCalibrateData - функтор вывода данных Calibrate Data на консоль
class DisplayCalibrateData{
public:
    void operator()(std::pair<const int, std::vector<InputCalibrateData::FormatStr> > p){
        std::cout<<"Сектор №"<<p.first<<std::endl;
        foreach (InputCalibrateData::FormatStr value, p.second) {
            std::cout<<"Aцу = "<<value.Acu<<" Bцу = "<<value.Bcu<<" Aизм = "<<value.Aizm<<" Bизм = "<<value.Bizm<<std::endl;
        }
    }
};

//CalculateCalibrateData - класс вычисления калибровочных коэффициентов
class CalculatorCalibrateData{
private:
    InputCalibrateData *d;
    std::vector< std::vector<CalibrateSector> > AllSectors;
    static double horizontLenght; /* Длина сектора в горизонте 10 град */
    static double verticaltLenght; /* Высота сектора 5 град */
public:
    CalculatorCalibrateData(InputCalibrateData *d);
    void process();
    std::vector< std::vector<CalibrateSector> >* getResult();
};
#endif // CL_ALGORITHMS_H
