#ifndef CL_ALGORITHMS_H
#define CL_ALGORITHMS_H

#include "io_structs.h"
#include "angle.h"
#include <iostream>
using namespace bvsk_cfg;
//DisplayCalibrateData - функтор вывода данных Calibrate Data на консоль
class DisplayCalibrateData{
public:
    void operator()(std::pair<const int, std::vector<InputData::FormatStr> > p){
        std::cout<<"Сектор №"<<p.first<<std::endl;
        foreach (InputData::FormatStr value, p.second) {
            std::cout<<"Aцу = "<<value.Acu<<" Bцу = "<<value.Bcu<<" Aизм = "<<value.Aizm<<" Bизм = "<<value.Bizm<<std::endl;
        }
    }
};

//CalculateCalibrateData - класс вычисления калибровочных коэффициентов
class CalculatorCalibrateData{
private:
    InputData *d;
    static double horizontLenght; /* Длина сектора в горизонте 10 град */
    static double verticaltLenght; /* Высота сектора 5 град */
public:
    CalculatorCalibrateData(InputData *d);
    void process();
};
#endif // CL_ALGORITHMS_H
