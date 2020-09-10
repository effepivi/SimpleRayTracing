Triangle::Triangle(const Vec3& a, const Vec3& b, const Vec3& c):
        m_p1(a),
        m_p2(b),
        m_p3(c)
{
    computeNormal();
}



Triangle& Triangle::operator=(const Triangle& aTriangle)
{
    m_p1 = aTriangle.m_p1;
    m_p2 = aTriangle.m_p2;
    m_p3 = aTriangle.m_p3;
    m_normal = aTriangle.m_normal;

    return *this;
}

const Vec3& Triangle::getP1() const
{
    return m_p1;
}


const Vec3& Triangle::getP2() const
{
    return m_p2;
}


const Vec3& Triangle::getP3() const
{
    return m_p3;
}


const Vec3& Triangle::getNormal() const
{
    return m_normal;
}

void Triangle::set(const Vec3& a, const Vec3& b, const Vec3& c)
{
    m_p1 = a;
    m_p2 = b;
    m_p3 = c;

    computeNormal();
}

void Triangle::computeNormal()
{
  Vec3 u(m_p2 - m_p1);
	Vec3 v(m_p3 - m_p1);

  m_normal = u.crossProduct(v);
}
