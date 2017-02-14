#ifndef IO_STRUCTS_H
#define IO_STRUCTS_H
#include <vector>
#include "angle.h"

//Структура входных данных
struct InputCalibrateData{
    struct FormatStr{
        Angle Acu;
        Angle Bcu;
        Angle Aizm;
        Angle Bizm;
    };
    std::map<const int, std::vector<FormatStr> >data;//Ключ - номер сектора по B
};
//Выходная структура данных после прохода алгоритма расчета коэффициентов
struct CalibrateSector{
    struct CalibrateCorrect{
        Angle vertex;
        double hor_coef;
        double ver_coef;
    };
    CalibrateCorrect eps;
    CalibrateCorrect delta;
    friend std::ostream& operator <<(std::ostream& os,const CalibrateSector& sector){
        os<<sector.eps.vertex.toDegrees()<<" "<<sector.eps.hor_coef<<" "<<sector.eps.ver_coef<<" ";
        os<<sector.delta.vertex.toDegrees()<<" "<<sector.delta.hor_coef<<" "<<sector.delta.ver_coef<<"\n";
        return os;
    }
};

struct TCalibrateData{

};

#endif // IO_STRUCTS_H
