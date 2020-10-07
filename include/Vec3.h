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


#ifndef __Vec3_h
#define __Vec3_h


/**
********************************************************************************
*
*   @file       Vec3.h
*
*   @brief      Class to manipulate 3D vectors (XYZ or RGB).
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


//******************************************************************************
//  Class declaration
//******************************************************************************
class Vec3;


//******************************************************************************
//  Function declarations
//******************************************************************************


//------------------------------------------------------------------------------
/// Normalise aVector
/**
*   @param  aVector: the vector to normalise
*   @return the normalised vector stream
*/
//------------------------------------------------------------------------------
Vec3 normalise(const Vec3& aVector);


//------------------------------------------------------------------------------
/// Normalise aVector
/**
*   @param  aVector: the vector to normalise
*   @return the normalised vector stream
*/
//------------------------------------------------------------------------------
Vec3 normalize(const Vec3& aVector);


//------------------------------------------------------------------------------
/// Calculate the reflection direction for an incident vector
/**
*   @param  I: the incident vector
*   @param NI: the normal vector
*   @return the reflection direction
*/
//------------------------------------------------------------------------------
Vec3 reflect(const Vec3& I, const Vec3& N);


//------------------------------------------------------------------------------
/// Calculate the dot product between two vectors
/**
*   @param  A: the 1st vector vector
*   @param B: the 2nd vector vector
*   @return the dot product
*/
//------------------------------------------------------------------------------
float dot(const Vec3& A, const Vec3& B);


Vec3 operator*(float t, const Vec3& aVector);
Vec3 operator*(double t, const Vec3& aVector);

std::ostream& operator<<(std::ostream& anOutput, const Vec3& aVector);



//==============================================================================
/**
*   @class  Vec3
*   @brief  Vec3 is a class to handle a 3D vector (XYZ or RGB).
*/
//==============================================================================
class Vec3
//------------------------------------------------------------------------------
{
//******************************************************************************
public:
    Vec3(float x = 0.0, float y = 0.0, float z = 0.0);
    Vec3(const Vec3& aVector);

    Vec3 operator-() const;

    Vec3 operator+(const Vec3& aVector) const;
    Vec3 operator-(const Vec3& aVector) const;

    Vec3& operator+=(const Vec3& aVector);
    Vec3& operator-=(const Vec3& aVector);

    Vec3 operator*(float t) const;
    Vec3 operator/(float t) const;

    Vec3 operator*(double t) const;
    Vec3 operator/(double t) const;

    Vec3& operator*=(float t);
    Vec3& operator/=(float t);

    Vec3& operator*=(double t);
    Vec3& operator/=(double t);

    Vec3 operator*(const Vec3& aVector) const;
    Vec3& operator*=(const Vec3& aVector);

    float dotProduct(const Vec3& aVector) const;
    Vec3 crossProduct(const Vec3& aVector) const;

    float& operator[](unsigned int i);
    const float& operator[](unsigned int i) const;

    float getX() const;
    float getY() const;
    float getZ() const;

    float getR() const;
    float getG() const;
    float getB() const;

    void setX(float x);
    void setY(float y);
    void setZ(float z);

    void setR(float r);
	void setG(float g);
	void setB(float b);

	float getLength() const;

    void normalise();
    void normalize();

//******************************************************************************
private:
    float m_x;
    float m_y;
    float m_z;
};
#include "Vec3.inl"

#endif
