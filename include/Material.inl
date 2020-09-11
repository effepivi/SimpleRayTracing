#ifndef __Light_h
#include "Light.h"
#endif


inline Material::Material():
		m_ambient(1, 1, 1),
		m_diffuse(1, 1, 1),
		m_specular(1, 1, 1),
		m_shininess(1)
{}


inline Material::Material(const Vec3& ambient,
		const Vec3& diffuse,
		const Vec3& specular,
		float shininess):
		m_ambient(ambient),
		m_diffuse(diffuse),
		m_specular(specular),
		m_shininess(shininess)
{}


inline void Material::setAmbient(const Vec3& ambient)
{
	m_ambient = ambient;
}


inline void Material::setDiffuse(const Vec3& diffuse)
{
	m_diffuse = diffuse;
}


inline void Material::setSpecular(const Vec3& specular)
{
	m_specular = specular;
}


inline void Material::setShininess(float shininess)
{
	m_shininess = shininess;
}


inline Vec3& Material::getAmbient()
{
	return m_ambient;
}


inline const Vec3& Material::getAmbient() const
{
	return m_ambient;
}


inline Vec3& Material::getDiffuse()
{
	return m_diffuse;
}


inline const Vec3& Material::getDiffuse() const
{
	return m_diffuse;
}


inline Vec3& Material::getSpecular()
{
	return m_specular;
}


inline const Vec3& Material::getSpecular() const
{
	return m_specular;
}


inline float& Material::getShininess()
{
	return m_shininess;
}


inline float Material::getShininess() const
{
	return m_shininess;
}
