#ifndef __Light_h
#define __Light_h

#ifndef __Vec3
#include "Vec3.h"
#endif


class Light
{
public:
	Light();
	Light(const Vec3& aColour, const Vec3& aDirection, const Vec3& aPosition);

	void setColour(const Vec3& aColour);
	void setDirection(const Vec3& aDirection);
	void setPosition(const Vec3& aPosition);

	Vec3& getColour();
	const Vec3& getColour() const;

	Vec3& getDirection();
	const Vec3& getDirection() const;

	Vec3& getPosition();
	const Vec3& getPosition() const;

private:
    Vec3 m_colour;
    Vec3 m_direction;
    Vec3 m_position;
};

#include "Light.inl"

#endif
