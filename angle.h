#ifndef ANGLE_H
#define ANGLE_H
#include <cmath>
#include <QDebug>
#include <iostream>
//В данном классе описывается объект угол, который находится в пределах +-180
class Angle
{
private:
    double angle;//В градусах
    double toEqualAngle(double value);//Функция приводит угол к эквивалентному, если он выходит за пределы +-180
public:
    Angle();
    Angle(double degrees);
    Angle(const Angle& a);
    double toRadians()const;
    double toDegrees()const;
    static double toRadians(double degrees);
    static double toDegrees(double radians);
    Angle& operator=(const Angle& a);
    Angle& operator=(double degrees);
    Angle operator+(const Angle& a);
    Angle operator-(const Angle& a);
    friend std::ostream &operator <<(std::ostream &os, const Angle &angle){
        os<<angle.toDegrees();
        return os;
    }
    friend QDebug &operator <<(QDebug &qdbg, const Angle &angle){
        qdbg<<angle.toDegrees();
        return qdbg;
    }
};


#endif // ANGLE_H
