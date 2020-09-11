#ifndef __Material_h
#define __Material_h

#include <iostream>

#include "Vec3.h"

class Light;

class Material
{
public:
	Material();

	Material(const Vec3& ambient,
			const Vec3& diffuse,
			const Vec3& specular,
			float shininess);

	void setAmbient(const Vec3& ambient);

	void setDiffuse(const Vec3& diffuse);

	void setSpecular(const Vec3& specular);

	void setShininess(float shininess);

	Vec3& getAmbient();
	const Vec3& getAmbient() const;

	Vec3& getDiffuse();
	const Vec3& getDiffuse() const;

	Vec3& getSpecular();
	const Vec3& getSpecular() const;

    float& getShininess();
    float getShininess() const;

private:
    Vec3 m_ambient;
    Vec3 m_diffuse;
    Vec3 m_specular;
    float m_shininess;
};

#include "Material.inl"

#endif
