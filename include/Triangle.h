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


#ifndef __Triangle_h
#define __Triangle_h


/**
********************************************************************************
*
*   @file       Triangle.h
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
#include <iostream>

#include "Vec3.h"


//******************************************************************************
//  Class declaration
//******************************************************************************
class Triangle;


//******************************************************************************
//  Function declarations
//******************************************************************************
std::ostream& operator<<(std::ostream& anOutput, const Triangle& aTriangle);


//==============================================================================
/**
*   @class  Triangle
*   @brief  Triangle is a class to handle a triangle.
*/
//==============================================================================
class Triangle
//------------------------------------------------------------------------------
{
//******************************************************************************
public:
    Triangle(const Vec3& a, const Vec3& b, const Vec3& c);


    Triangle& operator=(const Triangle& aTriangle);


    const Vec3& getP1() const;
    const Vec3& getP2() const;
    const Vec3& getP3() const;
    const Vec3& getNormal() const;

    void set(const Vec3& a, const Vec3& b, const Vec3& c);


//******************************************************************************
private:
    void computeNormal();

    Vec3 m_p1;
    Vec3 m_p2;
    Vec3 m_p3;

    Vec3 m_normal;
};


#include "Triangle.inl"


#endif
