#ifndef Ray_h
#define Ray_h

#ifndef Vec3_h
#include "Vec3.h"
#endif

#ifndef Triangle_h
#include "Triangle.h"
#endif

class Ray
{
public:
    Ray(const Ray& aRay);
    Ray(const Vec3& anOrigin, const Vec3& aDirection);

    Ray& operator=(const Ray& aRay);

    const Vec3& getOrigin() const;
    const Vec3& getDirection() const;

    void setOrigin(const Vec3& aPoint);
    void setDirection(const Vec3& aUnitVector);

    Vec3 getPointAt(float t) const;

//    ARTICLE
//    Fast, minimum storage ray/triangle intersection
//    Share on
//Authors:
//    Tomas Möller profile imageTomas Möller
//
//    ,
//    Ben  Trumbore profile imageBen Trumbore
//
//    Authors Info & Affiliations
//Publication: SIGGRAPH '05: ACM SIGGRAPH 2005 CoursesJuly 2005 Pages 7–eshttps://doi.org/10.1145/1198555.1198746
    bool intersect(const Triangle& aTriangle, float& t) const;

private:
    Vec3 m_origin;
    Vec3 m_direction;
};

#include "Ray.inl"

#endif // Ray_h
