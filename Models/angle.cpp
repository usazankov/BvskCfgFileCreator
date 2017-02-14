#include "angle.h"

Angle::Angle():angle(0)
{

}

Angle::Angle(double degrees)
{
    if(degrees<=-180||degrees>180){
        angle=toEqualAngle(degrees);
    }else
        angle=degrees;
}

Angle::Angle(const Angle &a)
{
    angle=a.angle;
}

double Angle::toRadians()const
{
    return (M_PI/180.0)*angle;
}

double Angle::toDegrees() const
{
    return angle;
}

double Angle::toEqualAngle(double value)
{
    double temp;
    int n=abs(value/360.0);
    if(value>=0){
        temp=value-n*360;
    }else{
        temp=value+n*360;
    }
    if(temp>180){
        temp=temp-360;
    }else if(temp<=-180){
        temp=temp+360;
    }
    return temp;
}

double Angle::toRadians(double degrees)
{
    return (M_PI/180.0)*degrees;
}

double Angle::toDegrees(double radians)
{
    return (180.0/M_PI)*radians;
}

Angle &Angle::operator=(const Angle &a)
{
    angle=a.angle;
    return (*this);
}

Angle &Angle::operator=(double degrees)
{
    if(degrees<=-180||degrees>180){
        angle=toEqualAngle(degrees);
    }else
        angle=degrees;
    return (*this);
}

Angle Angle::operator+(const Angle &a)
{
    Angle temp(this->angle+a.angle);
    return temp;
}

Angle Angle::operator-(const Angle &a)
{
    Angle temp(this->angle-a.angle);
    return temp;
}

