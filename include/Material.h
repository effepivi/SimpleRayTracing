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


#ifndef __Material_h
#define __Material_h


/**
********************************************************************************
*
*   @file       Material.h
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
#include <iostream>

#include "Vec3.h"


//******************************************************************************
//  Class declaration
//******************************************************************************
class Light;


//==============================================================================
/**
*   @class  Material
*   @brief  Material is a class to handle an object material.
*/
//==============================================================================
class Material
//------------------------------------------------------------------------------
{
//******************************************************************************
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

//******************************************************************************
private:
    Vec3 m_ambient;
    Vec3 m_diffuse;
    Vec3 m_specular;
    float m_shininess;
};

#include "Material.inl"

#endif
