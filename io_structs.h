#ifndef CALIBRATEDATA_H
#define CALIBRATEDATA_H
#include <vector>
#include "angle.h"
namespace bvsk_cfg {

//Структура входных данных
struct InputData{
    struct FormatStr{
        Angle Acu;
        Angle Bcu;
        Angle Aizm;
        Angle Bizm;
    };
    std::map<const int, std::vector<FormatStr> >data;//Ключ - номер сектора по B
};
//Выходная структура данных после прохода алгоритма расчета коэффициентов
struct CalibrateCorrect{
    Angle vertex;
    double hor_coef;
    double ver_coef;
};
struct TCalibrateData{

};
}
#endif // CALIBRATEDATA_H
