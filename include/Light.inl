inline Light::Light():
		m_colour(1, 1, 1)
{}


inline Light::Light(const Vec3& aColour, const Vec3& aDirection, const Vec3& aPosition):
		m_colour(aColour),
		m_direction(aDirection),
		m_position(aPosition)
{
	m_direction.normalise();
}



inline void Light::setColour(const Vec3& aColour)
{
	m_colour = aColour;
}


inline void Light::setDirection(const Vec3& aDirection)
{
	m_direction = aDirection;
}


inline void Light::setPosition(const Vec3& aPosition)
{
	m_position = aPosition;
}


inline Vec3& Light::getColour()
{
	return m_colour;
}


inline const Vec3& Light::getColour() const
{
	return m_colour;
}


inline Vec3& Light::getDirection()
{
	return m_direction;
}


inline const Vec3& Light::getDirection() const
{
	return m_direction;
}


inline Vec3& Light::getPosition()
{
	return m_position;
}


inline const Vec3& Light::getPosition() const
{
	return m_position;
}

