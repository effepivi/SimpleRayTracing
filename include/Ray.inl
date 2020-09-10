#include <cmath>

inline Ray::Ray(const Vec3& anOrigin, const Vec3& aDirection):
    m_origin(anOrigin)
{
    float length = aDirection.getLength();
    if (fpclassify(length) != FP_ZERO)
    {
        m_direction = aDirection / length;
    }
}


inline Ray& Ray::operator=(const Ray& aRay)
{
    m_origin = aRay.m_origin;
    m_direction = aRay.m_direction;

    return *this;
}


inline const Vec3& Ray::getOrigin() const
{
    return m_origin;
}


inline const Vec3& Ray::getDirection() const
{
    return m_direction;
}


inline void Ray::setOrigin(const Vec3& aPoint)
{
    m_origin = aPoint;
}


inline void Ray::setDirection(const Vec3& aUnitVector)
{
    m_direction = aUnitVector / aUnitVector.getLength();
}


inline Vec3 Ray::getPointAt(float t) const
{
    return m_origin + m_direction * t;
}


inline bool Ray::intersect(const Triangle& aTriangle, float& t) const
{
  // See https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf

  // Find vectors for two edges sharing vert
  Vec3 edge1 = aTriangle.getP2() - aTriangle.getP1();
  std::cout << aTriangle.getP2() << "  " << aTriangle.getP1() << "   " << edge1 << std::endl;

  Vec3 edge2 = aTriangle.getP3() - aTriangle.getP1();
  std::cout << aTriangle.getP3() << "  " << aTriangle.getP1() << "   " << edge2 << std::endl;

  // Begin calculating determinant  also used to calculate U parameter
  Vec3 pvec = m_direction.crossProduct(edge2);
  std::cout << m_direction << "  " << edge2 << "   " << pvec << std::endl;

  // If determinant is near zero ray lies in plane of triangle
  float det = edge1.dotProduct(pvec);
  std::cout << edge1 << "  " << pvec << "   " << det << std::endl;
  exit(0);
  if (fpclassify(det) == FP_ZERO)
  {
      std::cout << "TOTO" << std::endl;
      return false;
  }

  float inv_det = 1.0 / det;

  // Calculate distance from vert to ray origin
  Vec3 tvec = m_origin - aTriangle.getP1();

  // Calculate V parameter and test bounds
  float u = tvec.dotProduct(pvec) * inv_det;
  if (u < 0.0 || u > 1.0)
  {
    std::cout << "TITI" << std::endl;
      return false;
  }

  // Prepare to test V parameter
  Vec3 qvec = tvec.crossProduct(edge1);

  // Calculate V parameter and test bounds
  float v = m_direction.dotProduct(qvec) * inv_det;
  if (v < 0.0 || u + v > 1.0)
  {
    std::cout << "TATA" << std::endl;
      return false;
  }

  // Calculate t ray intersects triangle
  t = edge2.dotProduct(qvec) * inv_det;

  return true;
}
