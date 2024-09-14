#include "ExpandedVector3.hpp"

ExpandedVector3::ExpandedVector3(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}

bool ExpandedVector3::operator == (const ExpandedVector3& v) const
{
    return (x == v.x && y == v.y && z == v.z);
}
ExpandedVector3& ExpandedVector3::operator += (const ExpandedVector3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}
ExpandedVector3 ExpandedVector3::operator + (const ExpandedVector3& v) const
{
    return ExpandedVector3{x+v.x, y+v.y, z+v.z};
}

ExpandedVector3 ExpandedVector3::operator - (const ExpandedVector3& v) const
{
    return ExpandedVector3{x-v.x, y-v.y, z-v.z};
}