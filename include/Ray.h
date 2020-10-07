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


#ifndef __Ray_h
#define __Ray_h


/**
********************************************************************************
*
*   @file       Ray.h
*
*   @brief      Class to manipulate a ray.
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
#ifndef Vec3_h
#include "Vec3.h"
#endif

#ifndef Triangle_h
#include "Triangle.h"
#endif


//==============================================================================
/**
*   @class  Ray
*   @brief  Ray is a class to handle a ray.
*/
//==============================================================================
class Ray
//------------------------------------------------------------------------------
{
public:
    Ray(const Ray& aRay);
    Ray(const Vec3& anOrigin, const Vec3& aDirection);

    Ray& operator=(const Ray& aRay);

    const Vec3& getOrigin() const;
    const Vec3& getDirection() const;

    void setOrigin(const Vec3& aPoint);
    void setDirection(const Vec3& aUnitVector);

    Vec3 getPointAt(float t) const;

    bool intersect(const Triangle& aTriangle, float& t) const;

//******************************************************************************
private:
    Vec3 m_origin;
    Vec3 m_direction;
};

#include "Ray.inl"

#endif // Ray_h
