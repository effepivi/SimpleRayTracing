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
*   @file       Ray.cxx
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
#ifndef __Ray_h
#include "Ray.h"
#endif



//------------------------------------------------------------
bool Ray::intersect(const Triangle& aTriangle, float& t) const
//------------------------------------------------------------
{
		//	ARTICLE
		//    Fast, minimum storage ray/triangle intersection
		//    Share on
		//	Authors:
		//    Tomas Möller profile imageTomas Möller, Ben  Trumbore profile imageBen Trumbore
		//
		// Publication: SIGGRAPH '05: ACM SIGGRAPH 2005 CoursesJuly 2005 Pages 7–eshttps://doi.org/10.1145/1198555.1198746

		// See https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf

		// Find vectors for two edges sharing vert
		Vec3 edge1 = aTriangle.getP2() - aTriangle.getP1();
		Vec3 edge2 = aTriangle.getP3() - aTriangle.getP1();

		// Begin calculating determinant - also used to calculate U parameter
		Vec3 pvec = m_direction.crossProduct(edge2);

		// If determinant is near zero, ray lies in plane of triangle
		float det = edge1.dotProduct(pvec);
		if (std::fpclassify(det) == FP_ZERO)
		{
				return false;
		}

		float inv_det = 1.0 / det;

		// Calculate distance from vert P1 to ray origin
		Vec3 tvec = m_origin - aTriangle.getP1();

		// Calculate V parameter and test bounds
		float u = tvec.dotProduct(pvec) * inv_det;
		if (u < 0.0 || u > 1.0)
		{
				return false;
		}

		// Prepare to test V parameter
		Vec3 qvec = tvec.crossProduct(edge1);

		// Calculate V parameter and test bounds
		float v = m_direction.dotProduct(qvec) * inv_det;
		if (v < 0.0 || u + v > 1.0)
		{
				return false;
		}

		// Calculate t, ray intersects triangle
		t = edge2.dotProduct(qvec) * inv_det;

		return true;
}
