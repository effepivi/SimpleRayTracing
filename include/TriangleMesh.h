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
*   @file       TriangleMesh.h
*
*   @brief      Class to manipulate a triangle mesh.
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
#ifndef __TriangleMesh_h
#define __TriangleMesh_h

#include <iostream>
#include <vector>

#ifndef __Triangle_h
#include "Triangle.h"
#endif

#ifndef __Material
#include "Material.h"
#endif

#ifndef __Ray
#include "Ray.h"
#endif


//******************************************************************************
//  Class declaration
//******************************************************************************
class TriangleMesh;


//******************************************************************************
//  Function declarations
//******************************************************************************
std::ostream& operator<<(std::ostream& anOutput, const TriangleMesh& aTriangleMesh);


//==============================================================================
/**
*   @class  TriangleMesh
*   @brief  TriangleMesh is a class to a triangle mesh.
*/
//==============================================================================
class TriangleMesh
//------------------------------------------------------------------------------
{
//******************************************************************************
public:
	TriangleMesh();
	TriangleMesh(const std::vector<float>& aVertexSet);
	TriangleMesh(const std::vector<float>& aVertexSet, const std::vector<unsigned int>& anIndexSet);
	TriangleMesh(const std::vector<Triangle>& aTriangleSet);

	void setGeometry(const std::vector<float>& aVertexSet);
	void setGeometry(const std::vector<float>& aVertexSet, const std::vector<unsigned int>& anIndexSet);
	void setGeometry(const std::vector<Triangle>& aTriangleSet);

	void setMaterial(const Material& aMaterial);
	Material& getMaterial();
	const Material& getMaterial() const;

	size_t getNumberOfTriangles() const;
	const Triangle& getTriangle(unsigned int i) const;

	const Vec3& getLowerBBoxCorner() const;
	const Vec3& getUpperBBoxCorner() const;

	bool intersectBBox(const Ray& aRay) const;


//******************************************************************************
protected:
	void computeBoundingBox();

	std::vector<Triangle> m_p_triangle_set;
	Material m_material;

	Vec3 m_lower_bbox_corner;
	Vec3 m_upper_bbox_corner;
};


#include "TriangleMesh.inl"

#endif // TriangleMesh_h
