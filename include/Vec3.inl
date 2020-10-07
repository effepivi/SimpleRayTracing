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
*   @file       Vec3.inl
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
#include <cmath>
#include <stdexcept>


//******************************************************************************
//  Function definitions
//******************************************************************************


//----------------------------------------
inline Vec3 normalise(const Vec3& aVector)
//----------------------------------------
{
	Vec3 temp = aVector;
	temp.normalise();
	return temp;
}


//----------------------------------------
inline Vec3 normalize(const Vec3& aVector)
//----------------------------------------
{
	return normalise(aVector);
}
	

//-------------------------------------------------
inline Vec3 operator*(float t, const Vec3& aVector)
//-------------------------------------------------
{
    return aVector * t;
}


//--------------------------------------------------
inline Vec3 operator*(double t, const Vec3& aVector)
//--------------------------------------------------
{
    return aVector * t;
}



//-----------------------------------------------------
inline std::ostream& operator<<(std::ostream& anOutput,
								const Vec3& aVector)
//-----------------------------------------------------
{
    anOutput << aVector.getX() << " " << aVector.getY() << " " <<aVector.getZ();
    return anOutput;
}


//-----------------------------------------------
inline Vec3 reflect(const Vec3& I, const Vec3& N)
//-----------------------------------------------
{
	return I - 2.0 * N.dotProduct(I) * N;
}


//--------------------------------------------
inline float dot(const Vec3& A, const Vec3& B)
//--------------------------------------------
{
	return A.dotProduct(B);
}


//******************************************************************************
//  Method definitions
//******************************************************************************


//-------------------------------------------
inline Vec3::Vec3(float x, float y, float z):
//-------------------------------------------
        m_x(x),
        m_y(y),
        m_z(z)
//-------------------------------------------
{}


//-------------------------------------
inline Vec3::Vec3(const Vec3& aVector):
//-------------------------------------
      m_x(aVector.m_x),
      m_y(aVector.m_y),
      m_z(aVector.m_z)
//-------------------------------------
{}


//---------------------------------
inline Vec3 Vec3::operator-() const
//---------------------------------
{
	return Vec3(-m_x, -m_y, -m_z);
}
	
	
//----------------------------------------------------
inline Vec3 Vec3::operator+(const Vec3& aVector) const
//----------------------------------------------------
{
    return Vec3(m_x + aVector.m_x,
                m_y + aVector.m_y,
                m_z + aVector.m_z);
}


//-----------------------------------------------------
inline Vec3 Vec3::operator-(const Vec3& aVector) const
//-----------------------------------------------------
{
    return Vec3(m_x - aVector.m_x,
                m_y - aVector.m_y,
                m_z - aVector.m_z);
}


//------------------------------------------------
inline Vec3& Vec3::operator+=(const Vec3& aVector)
//------------------------------------------------
{
    m_x += aVector.m_x;
    m_y += aVector.m_y;
    m_z += aVector.m_z;

    return *this;
}


//------------------------------------------------
inline Vec3& Vec3::operator-=(const Vec3& aVector)
//------------------------------------------------
{
    m_x -= aVector.m_x;
    m_y -= aVector.m_y;
    m_z -= aVector.m_z;

    return *this;
}


//----------------------------------------
inline Vec3 Vec3::operator*(float t) const
//----------------------------------------
{
    return Vec3(m_x * t, m_y * t, m_z * t);
}


//----------------------------------------
inline Vec3 Vec3::operator/(float t) const
//----------------------------------------
{
    return Vec3(m_x / t, m_y / t, m_z / t);
}


//-----------------------------------------
inline Vec3 Vec3::operator*(double t) const
//-----------------------------------------
{
    return Vec3(m_x * t, m_y * t, m_z * t);
}


//-----------------------------------------
inline Vec3 Vec3::operator/(double t) const
//-----------------------------------------
{
    return Vec3(m_x / t, m_y / t, m_z / t);
}


//------------------------------------
inline Vec3& Vec3::operator*=(float t)
//------------------------------------
{
    m_x *= t;
    m_y *= t;
    m_z *= t;

    return *this;
}


//------------------------------------
inline Vec3& Vec3::operator/=(float t)
//------------------------------------
{
    m_x /= t;
    m_y /= t;
    m_z /= t;

    return *this;
}


//-------------------------------------
inline Vec3& Vec3::operator*=(double t)
//-------------------------------------
{
    m_x *= t;
    m_y *= t;
    m_z *= t;

    return *this;
}


//-------------------------------------
inline Vec3& Vec3::operator/=(double t)
//-------------------------------------
{
    m_x /= t;
    m_y /= t;
    m_z /= t;

    return *this;
}


//----------------------------------------------------
inline Vec3 Vec3::operator*(const Vec3& aVector) const
//----------------------------------------------------
{
    return Vec3(m_x * aVector.m_x, m_y * aVector.m_y, m_z * aVector.m_z);
}


//------------------------------------------------
inline Vec3& Vec3::operator*=(const Vec3& aVector)
//------------------------------------------------
{
	m_x *= aVector.m_x;
	m_y *= aVector.m_y;
	m_z *= aVector.m_z;
	
    return *this;
}


//------------------------------------------------------
inline float Vec3::dotProduct(const Vec3& aVector) const
//------------------------------------------------------
{
    return m_x * aVector.m_x + m_y * aVector.m_y + m_z * aVector.m_z;
}


//-------------------------------------------------------
inline Vec3 Vec3::crossProduct(const Vec3& aVector) const
//-------------------------------------------------------
{
    return Vec3(
      m_y * aVector.m_z - m_z * aVector.m_y,
      m_z * aVector.m_x - m_x * aVector.m_z,
      m_x * aVector.m_y - m_y * aVector.m_x
    );
}


//--------------------------------------------
inline float& Vec3::operator[](unsigned int i)
//--------------------------------------------
{
	switch (i)
	{
	case 0:
		return m_x;
	case 1:
		return m_y;
	case 2:
		return m_z;
	default:
		throw std::out_of_range("Valid range is [0, 2]");
	}
}


//--------------------------------------------------------
inline const float& Vec3::operator[](unsigned int i) const
//--------------------------------------------------------
{
	switch (i)
	{
	case 0:
		return m_x;
	case 1:
		return m_y;
	case 2:
		return m_z;
	default:
		throw std::out_of_range("Valid range is [0, 2]");
	}
}


//-----------------------------
inline float Vec3::getX() const
//-----------------------------
{
    return m_x;
}


//-----------------------------
inline float Vec3::getY() const
//-----------------------------
{
    return m_y;
}

//-----------------------------
inline float Vec3::getZ() const
//-----------------------------
{
    return m_z;
}


//-----------------------------
inline float Vec3::getR() const
//-----------------------------
{
    return m_x;
}


//-----------------------------
inline float Vec3::getG() const
//-----------------------------
{
    return m_y;
}


//-----------------------------
inline float Vec3::getB() const
//-----------------------------
{
    return m_z;
}


//-----------------------------
inline void Vec3::setX(float x)
//-----------------------------
{
    m_x = x;
}

//-----------------------------
inline void Vec3::setY(float y)
//-----------------------------
{
    m_y = y;
}

//-----------------------------
inline void Vec3::setZ(float z)
//-----------------------------
{
    m_z = z;
}


//-----------------------------
inline void Vec3::setR(float r)
//-----------------------------
{
    m_x = r;
}

//-----------------------------
inline void Vec3::setG(float g)
//-----------------------------
{
    m_y = g;
}


//-----------------------------
inline void Vec3::setB(float b)
//-----------------------------
{ 
    m_z = b;
}


//----------------------------------
inline float Vec3::getLength() const
//----------------------------------
{
    return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}


//---------------------------
inline void Vec3::normalise()
//---------------------------
{
    float length = getLength();
    m_x /= length;
    m_y /= length;
    m_z /= length;
}


//---------------------------
inline void Vec3::normalize()
//---------------------------
{
	normalise();
}

