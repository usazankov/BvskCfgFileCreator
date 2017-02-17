#ifndef CL_ALGORITHMS_H
#define CL_ALGORITHMS_H

#include "io_structs.h"
#include "angle.h"
#include <iostream>
#include <ostream>

//CalculateCalibrateData - класс вычисления калибровочных коэффициентов
class CalculatorCalibrateData{
private:
    InputCalibrateData *d;
    std::vector< std::vector<CalibrateSector> > AllSectors;
    static double horizontLenght; /* Длина сектора в горизонте 10 град */
    static double verticaltLenght; /* Высота сектора 5 град */
public:
    CalculatorCalibrateData(InputCalibrateData *d);
    static void setHorizontLength(double length);
    static void setVerticalLength(double length);
    void process();
    void clearResult();
    std::vector< std::vector<CalibrateSector> >* getResult();
};
#endif // CL_ALGORITHMS_H
