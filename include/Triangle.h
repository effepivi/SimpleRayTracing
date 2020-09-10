#ifndef Triangle_h
#define Triangle_h

#include "Vec3.h"

class Triangle
{
public:
    Triangle(const Triangle& aTriangle);
    Triangle(const Vec3& a, const Vec3& b, const Vec3& c);


    Triangle& operator=(const Triangle& aTriangle);


    const Vec3& getP1() const;
    const Vec3& getP2() const;
    const Vec3& getP3() const;
    const Vec3& getNormal() const;

    void set(const Vec3& a, const Vec3& b, const Vec3& c);


private:
    void computeNormal();

    Vec3 m_p1;
    Vec3 m_p2;
    Vec3 m_p3;

    Vec3 m_normal;
};


#include "Triangle.inl"


#endif
