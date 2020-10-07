/*

Copyright (c) 2020, Dr Franck P. Vidal (f.vidal@bangor.ac.uk),
http://www.fpvidal.net/
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

3. Neither the name of the Bangor University nor the names of its contributors
may be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/


/**
********************************************************************************
*
*   @file       Material.inl
*
*   @brief      Class to manipulate an object material.
*
*   @version    1.0
*
*   @date       11/09/2020
*
*   @author     Dr Franck P. Vidal
*
*   License
*   BSD 3-Clause License.
*
*   For details on use and redistribution please refer
*   to http://opensource.org/licenses/BSD-3-Clause
*
*   Copyright
*   (c) by Dr Franck P. Vidal (f.vidal@bangor.ac.uk),
*   http://www.fpvidal.net/, Sept 2020, 2020, version 1.0, BSD 3-Clause License
*
********************************************************************************
*/


//******************************************************************************
//  Include
//******************************************************************************
#ifndef __Light_h
#include "Light.h"
#endif


//******************************************************************************
//  Method definitions
//******************************************************************************


//--------------------------
inline Material::Material():
//--------------------------
		m_ambient(1, 1, 1),
		m_diffuse(1, 1, 1),
		m_specular(1, 1, 1),
		m_shininess(1)
//--------------------------
{}


//---------------------------------------------
inline Material::Material(const Vec3& ambient,
						  const Vec3& diffuse,
						  const Vec3& specular,
						  float shininess):
//---------------------------------------------
		m_ambient(ambient),
		m_diffuse(diffuse),
		m_specular(specular),
		m_shininess(shininess)
//---------------------------------------------
{}


//---------------------------------------------------
inline void Material::setAmbient(const Vec3& ambient)
//---------------------------------------------------
{
	m_ambient = ambient;
}


//---------------------------------------------------
inline void Material::setDiffuse(const Vec3& diffuse)
//---------------------------------------------------
{
	m_diffuse = diffuse;
}


//-----------------------------------------------------
inline void Material::setSpecular(const Vec3& specular)
//-----------------------------------------------------
{
	m_specular = specular;
}


//-------------------------------------------------
inline void Material::setShininess(float shininess)
//-------------------------------------------------
{
	m_shininess = shininess;
}


//---------------------------------
inline Vec3& Material::getAmbient()
//---------------------------------
{
	return m_ambient;
}


//---------------------------------------------
inline const Vec3& Material::getAmbient() const
//---------------------------------------------
{
	return m_ambient;
}


//---------------------------------
inline Vec3& Material::getDiffuse()
//---------------------------------
{
	return m_diffuse;
}


//---------------------------------------------
inline const Vec3& Material::getDiffuse() const
//---------------------------------------------
{
	return m_diffuse;
}


//----------------------------------
inline Vec3& Material::getSpecular()
//----------------------------------
{
	return m_specular;
}


//----------------------------------------------
inline const Vec3& Material::getSpecular() const
//----------------------------------------------
{
	return m_specular;
}


//------------------------------------
inline float& Material::getShininess()
//------------------------------------
{
	return m_shininess;
}


//-----------------------------------------
inline float Material::getShininess() const
//-----------------------------------------
{
	return m_shininess;
}
