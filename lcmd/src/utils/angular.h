#pragma once

#include <math.h>
#include "gtest/gtest.h"

#define M_E        2.71828182845904523536
#define M_LOG2E    1.44269504088896340736
#define M_LOG10E   0.434294481903251827651
#define M_LN2      0.693147180559945309417
#define M_LN10     2.30258509299404568402
#define M_PI       3.14159265358979323846
#define M_2PI      6.28318530717958647692
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616
#define M_1_PI     0.318309886183790671538
#define M_2_PI     0.636619772367581343076
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT1_2  0.70710678118654752440

#define DEG2RAD(deg)    (deg)*M_PI/180.0
#define RAD2DEG(rad)    (rad)*180.0/M_PI

class Angular
{
public:
    /*
    转换角度到 [0, 2PI)
    */
    static float RoundTo2PI(float rad)
    {
        float r = fmod(rad, M_2PI);		
        if(r<0) r+= M_2PI;
        return r;
    }

    /*
        转换角度到 [-PI, PI)
    */
    static float RoundToPi(float rad)
    {
        return RoundTo2PI(rad + M_PI) - M_PI;
    }
    /*
        转换角度到 [0, 360)
    */
    static float RoundTo360(float deg)
    {
        float r = fmod(deg, 360);
        if(r<0) r+= 360;
        return r;
    }
    /*
        转换角度到 [-180, 180)
    */
    static float RoundTo180(float deg)
    {
        return RoundTo360(deg+180) - 180;
    }
};
