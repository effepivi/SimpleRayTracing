#include <cmath>


inline Vec3 operator*(float t, const Vec3& aVector)
{
    return aVector * t;
}


inline std::ostream& operator<<(std::ostream& anOutput, const Vec3& aVector)
{
    anOutput << aVector.getX() << "\t" << aVector.getY() << "\t" <<aVector.getZ();
    return anOutput;
}

inline Vec3::Vec3(float x, float y, float z):
        m_x(x),
        m_y(y),
        m_z(z)
{}


inline Vec3::Vec3(const Vec3& aVector):
      m_x(aVector.m_x),
      m_y(aVector.m_y),
      m_z(aVector.m_z)
{}


inline Vec3& Vec3::operator=(const Vec3& aVector)
{
    m_x = aVector.m_x;
    m_y = aVector.m_y;
    m_z = aVector.m_z;

    return *this;
}


inline Vec3 Vec3::operator+(const Vec3& aVector) const
{
    return Vec3(m_x + aVector.m_x,
                m_y + aVector.m_y,
                m_z + aVector.m_z);
}


inline Vec3 Vec3::operator-(const Vec3& aVector) const
{
    return Vec3(m_x - aVector.m_x,
                m_y - aVector.m_y,
                m_z - aVector.m_z);
}


inline Vec3& Vec3::operator+=(const Vec3& aVector)
{
    m_x += aVector.m_x;
    m_y += aVector.m_y;
    m_z += aVector.m_z;

    return *this;
}


inline Vec3& Vec3::operator-=(const Vec3& aVector)
{
    m_x -= aVector.m_x;
    m_y -= aVector.m_y;
    m_z -= aVector.m_z;

    return *this;
}

inline Vec3 Vec3::operator*(float t) const
{
    return Vec3(m_x * t, m_y * t, m_z * t);
}


inline Vec3 Vec3::operator/(float t) const
{
    return Vec3(m_x / t, m_y / t, m_z / t);
}


inline Vec3& Vec3::operator*=(float t)
{
    m_x *= t;
    m_y *= t;
    m_z *= t;

    return *this;
}


inline Vec3& Vec3::operator/=(float t)
{
    m_x /= t;
    m_y /= t;
    m_z /= t;

    return *this;
}


inline float Vec3::dotProduct(const Vec3& aVector) const
{
    return m_x * aVector.m_x + m_y * aVector.m_y + m_z * aVector.m_z;
}


inline Vec3 Vec3::crossProduct(const Vec3& aVector) const
{
    return Vec3(
      m_y * aVector.m_z - m_z * aVector.m_y,
      m_z * aVector.m_x - m_x * aVector.m_z,
      m_x * aVector.m_y - m_y * aVector.m_x
    );
}

inline float Vec3::getX() const
{
    return m_x;
}


inline float Vec3::getY() const
{
    return m_y;
}

inline float Vec3::getZ() const
{
    return m_z;
}


inline void Vec3::setX(float x)
{
    m_x = x;
}

inline void Vec3::setY(float y)
{
    m_y = y;
}

inline void Vec3::setZ(float z)
{
    m_z = z;
}


inline float Vec3::getLength() const
{
    return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}


inline void Vec3::normalise()
{
    float length = getLength();
    m_x /= length;
    m_y /= length;
    m_z /= length;
}
