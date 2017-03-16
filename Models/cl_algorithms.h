#ifndef CL_ALGORITHMS_H
#define CL_ALGORITHMS_H

#include "io_structs.h"
#include "angle.h"
#include <iostream>
#include <ostream>

//CalculateCalibrateData - класс вычисления калибровочных коэффициентов
namespace bvsk_cfg {
    const int precision=6;//precision of output calibrate coef
}
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
    QString result();
    void saveToFile(const QUrl &path)const;
    std::vector< std::vector<CalibrateSector> >* getResultStruct();
};

#endif // CL_ALGORITHMS_H
