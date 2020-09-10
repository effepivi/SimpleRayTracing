#ifndef Vec3_h
#define Vec3_h

#include <iostream>

class Vec3;


Vec3 operator*(float t, const Vec3& aVector);

std::ostream& operator<<(std::ostream& anOutput, const Vec3& aVector);

class Vec3
{
public:
    Vec3(float x = 0.0, float y = 0.0, float z = 0.0);
    Vec3(const Vec3& aVector);

    Vec3& operator=(const Vec3& aVector);

    Vec3 operator+(const Vec3& aVector) const;
    Vec3 operator-(const Vec3& aVector) const;

    Vec3& operator+=(const Vec3& aVector);
    Vec3& operator-=(const Vec3& aVector);

    Vec3 operator*(float t) const;
    Vec3 operator/(float t) const;

    Vec3& operator*=(float t);
    Vec3& operator/=(float t);

    float dotProduct(const Vec3& aVector) const;
    Vec3 crossProduct(const Vec3& aVector) const;

    float getX() const;
    float getY() const;
    float getZ() const;

    void setX(float x);
    void setY(float x);
    void setZ(float x);

    float getLength() const;

    void normalise();

private:
    float m_x;
    float m_y;
    float m_z;
};
#include "Vec3.inl"

#endif
