#ifndef __VECTOR3
#define __VECTOR3 

#include <math.h>

struct ExpandedVector3{
    double x;
    double y;
    double z;
    ExpandedVector3(double xx, double yy, double zz);
    bool operator == (const ExpandedVector3& v) const;
    ExpandedVector3& operator += (const ExpandedVector3& v);
    ExpandedVector3 operator + (const ExpandedVector3& v) const;
    ExpandedVector3& operator -= (const ExpandedVector3& v);
    ExpandedVector3 operator - (const ExpandedVector3& v) const;

};

#endif