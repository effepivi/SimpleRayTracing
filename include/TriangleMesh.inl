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
*   @file       TriangleMesh.inl
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
//  Function definitions
//******************************************************************************


//----------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& anOutput,
                                const TriangleMesh& aTriangleMesh)
//----------------------------------------------------------------
{
	anOutput << "solid name" << std::endl;

	for (int i = 0; i < aTriangleMesh.getNumberOfTriangles(); ++i)
	{
		anOutput << aTriangleMesh.getTriangle(i) << std::endl;
	}
	anOutput << "endsolid name";

	return anOutput;
}


//******************************************************************************
//  Method definitions
//******************************************************************************


//---------------------------------
inline TriangleMesh::TriangleMesh()
//---------------------------------
{
	// Do nothing
}


//---------------------------------------------------------------------
inline TriangleMesh::TriangleMesh(const std::vector<float>& aVertexSet)
//---------------------------------------------------------------------
{
	setGeometry(aVertexSet);
}


//----------------------------------------------------------------------------
inline TriangleMesh::TriangleMesh(const std::vector<float>& aVertexSet,
		                          const std::vector<unsigned int>& anIndexSet)
//----------------------------------------------------------------------------
{
	setGeometry(aVertexSet, anIndexSet);
}


//--------------------------------------------------------------------------
inline TriangleMesh::TriangleMesh(const std::vector<Triangle>& aTriangleSet)
//--------------------------------------------------------------------------
{
	setGeometry(aTriangleSet);
}


//------------------------------------------------------------------------------
inline void TriangleMesh::setGeometry(const std::vector<Triangle>& aTriangleSet)
//------------------------------------------------------------------------------
{
	m_p_triangle_set = aTriangleSet;

	computeBoundingBox();
}


//--------------------------------------------------------------
inline void TriangleMesh::setMaterial(const Material& aMaterial)
//--------------------------------------------------------------
{
	m_material = aMaterial;
}


//------------------------------------------
inline Material& TriangleMesh::getMaterial()
//------------------------------------------
{
	return m_material;
}


//------------------------------------------------------
inline const Material& TriangleMesh::getMaterial() const
//------------------------------------------------------
{
	return m_material;
}


//------------------------------------------------------
inline size_t TriangleMesh::getNumberOfTriangles() const
//------------------------------------------------------
{
	return m_p_triangle_set.size();
}


//--------------------------------------------------------------------
inline const Triangle& TriangleMesh::getTriangle(unsigned int i) const
//--------------------------------------------------------------------
{
	return m_p_triangle_set[i];
}


//---------------------------------------------------------
inline const Vec3& TriangleMesh::getLowerBBoxCorner() const
//---------------------------------------------------------
{
	return m_lower_bbox_corner;
}


//---------------------------------------------------------
inline const Vec3& TriangleMesh::getUpperBBoxCorner() const
//---------------------------------------------------------
{
	return m_upper_bbox_corner;
}


//------------------------------------------------------------
inline bool TriangleMesh::intersectBBox(const Ray& aRay) const
//------------------------------------------------------------
{
	return true;
}
