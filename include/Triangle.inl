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
*   @file       Triangle.inl
*
*   @brief      Class to manipulate a triangle.
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


//******************************************************************************
//  Method definitions
//******************************************************************************


//---------------------------------------
inline Triangle::Triangle(const Vec3& a,
						  const Vec3& b,
						  const Vec3& c,
						  const Vec3& d,
						  const Vec3& e,
						  const Vec3& f):
//---------------------------------------
        m_p1(a),
        m_p2(b),
        m_p3(c),
        m_text_coord1(d),
        m_text_coord2(e),
        m_text_coord3(f)
//---------------------------------------
{
    computeNormal();
}


//-------------------------------------------------------------
inline Triangle& Triangle::operator=(const Triangle& aTriangle)
//-------------------------------------------------------------
{
    m_p1 = aTriangle.m_p1;
    m_p2 = aTriangle.m_p2;
    m_p3 = aTriangle.m_p3;

    m_normal = aTriangle.m_normal;

    m_text_coord1 = aTriangle.m_text_coord1;
    m_text_coord2 = aTriangle.m_text_coord2;
    m_text_coord3 = aTriangle.m_text_coord3;

    return *this;
}


//----------------------------------------
inline const Vec3& Triangle::getP1() const
//----------------------------------------
{
    return m_p1;
}


//----------------------------------------
inline const Vec3& Triangle::getP2() const
//----------------------------------------
{
    return m_p2;
}


//----------------------------------------
inline const Vec3& Triangle::getP3() const
//----------------------------------------
{
    return m_p3;
}


//--------------------------------------------
inline const Vec3& Triangle::getNormal() const
//--------------------------------------------
{
    return m_normal;
}


//----------------------------------------------
inline void Triangle::setVertices(const Vec3& a,
						          const Vec3& b,
						          const Vec3& c)
//----------------------------------------------
{
    m_p1 = a;
    m_p2 = b;
    m_p3 = c;

    computeNormal();
}


//------------------------------------------------
inline void Triangle::setTextCoords(const Vec3& a,
						            const Vec3& b,
						            const Vec3& c)
//------------------------------------------------
{
    m_text_coord1 = a;
    m_text_coord2 = b;
    m_text_coord3 = c;
}


//-----------------------------------
inline void Triangle::computeNormal()
//-----------------------------------
{
	Vec3 u(m_p2 - m_p1);
	Vec3 v(m_p3 - m_p1);

	m_normal = u.crossProduct(v);
	m_normal.normalise();
}


//------------------------------------------------
inline const Vec3& Triangle::getTextCoord1() const
//------------------------------------------------
{
    return m_text_coord1;
}


//------------------------------------------------
inline const Vec3& Triangle::getTextCoord2() const
//------------------------------------------------
{
    return m_text_coord2;
}


//------------------------------------------------
inline const Vec3& Triangle::getTextCoord3() const
//------------------------------------------------
{
    return m_text_coord3;
}


//------------------------------------
inline float Triangle::getArea() const
//------------------------------------
{
	// See https://math.stackexchange.com/questions/128991/how-to-calculate-the-area-of-a-3d-triangle
	Vec3 AB = m_p2 - m_p1;
	Vec3 AC = m_p3 - m_p1;
	
	return 0.5 * sqrt(pow(AB[1] * AC[2] - AB[2] * AC[1], 2) +
		pow(AB[2] * AC[0] - AB[0] * AC[2], 2) +
		pow(AB[0] * AC[1] - AB[1] * AC[0], 2)); 
}
