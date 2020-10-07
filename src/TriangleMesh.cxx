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
*   @file       TriangleMesh.cxx
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
#include <limits> // for inf
#include <algorithm> // for max
#include <stdexcept> // for exceptions

#ifndef TriangleMesh_h
#include "TriangleMesh.h"
#endif


//******************************************************************************
//  Method definitions
//******************************************************************************


//------------------------------------------------------------------
void TriangleMesh::setGeometry(const std::vector<float>& aVertexSet)
//------------------------------------------------------------------
{
	m_p_triangle_set.clear();
	if (aVertexSet.size() % 9 == 0)
	{
		for (int i = 0; i < aVertexSet.size() / 9; ++i)
		{
			m_p_triangle_set.push_back(Triangle(
			Vec3(aVertexSet[i * 9 + 0], aVertexSet[i * 9 + 1], aVertexSet[i * 9 + 2]),
			Vec3(aVertexSet[i * 9 + 3], aVertexSet[i * 9 + 4], aVertexSet[i * 9 + 5]),
			Vec3(aVertexSet[i * 9 + 6], aVertexSet[i * 9 + 7], aVertexSet[i * 9 + 8])));
		}

		computeBoundingBox();
	}
	else
	{
		throw std::length_error("buffer size error");
	}
}


//-------------------------------------------------------------------------
void TriangleMesh::setGeometry(const std::vector<float>& aVertexSet,
		                       const std::vector<unsigned int>& anIndexSet)
//-------------------------------------------------------------------------
{
	m_p_triangle_set.clear();
	if (aVertexSet.size() % 3 == 0 && anIndexSet.size() % 3 == 0)
	{
		for (int i = 0; i < anIndexSet.size() / 3; ++i)
		{
			unsigned int i1 = anIndexSet[i * 3 + 0];
			unsigned int i2 = anIndexSet[i * 3 + 1];
			unsigned int i3 = anIndexSet[i * 3 + 2];

			m_p_triangle_set.push_back(Triangle(
			Vec3(aVertexSet[i1 * 3 + 0], aVertexSet[i1 * 3 + 1], aVertexSet[i1 * 3 + 2]),
			Vec3(aVertexSet[i2 * 3 + 0], aVertexSet[i2 * 3 + 1], aVertexSet[i2 * 3 + 2]),
			Vec3(aVertexSet[i3 * 3 + 0], aVertexSet[i3 * 3 + 1], aVertexSet[i3 * 3 + 2])));
		}

		computeBoundingBox();
	}
	else
	{
		throw std::length_error("buffer size error");
	}
}


//---------------------------------------------------------------------
void TriangleMesh::setGeometry(const std::vector<float>& aVertexSet,
		                       const std::vector<float>& aTextCoordSet)
//---------------------------------------------------------------------
{
	setGeometry(aVertexSet);
	if (aVertexSet.size() == aTextCoordSet.size())
	{
		for (size_t i = 0; i < m_p_triangle_set.size(); ++i)
		{
			unsigned int i1 = i * 3 + 0;
			unsigned int i2 = i * 3 + 1;
			unsigned int i3 = i * 3 + 2;

			Vec3 a(aTextCoordSet[i1 * 3 + 0], aTextCoordSet[i1 * 3 + 1], aTextCoordSet[i1 * 3 + 2]);
			Vec3 b(aTextCoordSet[i2 * 3 + 0], aTextCoordSet[i2 * 3 + 1], aTextCoordSet[i2 * 3 + 2]);
			Vec3 c(aTextCoordSet[i3 * 3 + 0], aTextCoordSet[i3 * 3 + 1], aTextCoordSet[i3 * 3 + 2]);

			m_p_triangle_set[i].setTextCoords(a, b, c);
		}
	}
	else
	{
		throw std::length_error("buffer size error");
	}
}


//-------------------------------------------------------------------------
void TriangleMesh::setGeometry(const std::vector<float>& aVertexSet,
		                       const std::vector<unsigned int>& anIndexSet,
							   const std::vector<float>& aTextCoordSet)
//-------------------------------------------------------------------------
{
	setGeometry(aVertexSet, anIndexSet);
	if (aVertexSet.size() == aTextCoordSet.size())
	{
		for (int i = 0; i < anIndexSet.size() / 3; ++i)
		{
			unsigned int i1 = anIndexSet[i * 3 + 0];
			unsigned int i2 = anIndexSet[i * 3 + 1];
			unsigned int i3 = anIndexSet[i * 3 + 2];

			Vec3 a(aTextCoordSet[i1 * 3 + 0], aTextCoordSet[i1 * 3 + 1], aTextCoordSet[i1 * 3 + 2]);
			Vec3 b(aTextCoordSet[i2 * 3 + 0], aTextCoordSet[i2 * 3 + 1], aTextCoordSet[i2 * 3 + 2]);
			Vec3 c(aTextCoordSet[i3 * 3 + 0], aTextCoordSet[i3 * 3 + 1], aTextCoordSet[i3 * 3 + 2]);

			m_p_triangle_set[i].setTextCoords(a, b, c);
		}
	}
	else
	{
		throw std::length_error("buffer size error");
	}
}


//-------------------------------------
void TriangleMesh::computeBoundingBox()
//-------------------------------------
{
	float inf = std::numeric_limits<float>::infinity();

	m_lower_bbox_corner = Vec3( inf,  inf,  inf);
	m_upper_bbox_corner = Vec3(-inf, -inf, -inf);

	for (std::vector<Triangle>::const_iterator ite = m_p_triangle_set.begin();
			ite != m_p_triangle_set.end();
			++ite)
	{
		m_lower_bbox_corner[0] = std::min(m_lower_bbox_corner[0], ite->getP1()[0]);
		m_lower_bbox_corner[1] = std::min(m_lower_bbox_corner[1], ite->getP1()[1]);
		m_lower_bbox_corner[2] = std::min(m_lower_bbox_corner[2], ite->getP1()[2]);

		m_upper_bbox_corner[0] = std::max(m_upper_bbox_corner[0], ite->getP1()[0]);
		m_upper_bbox_corner[1] = std::max(m_upper_bbox_corner[1], ite->getP1()[1]);
		m_upper_bbox_corner[2] = std::max(m_upper_bbox_corner[2], ite->getP1()[2]);

		m_lower_bbox_corner[0] = std::min(m_lower_bbox_corner[0], ite->getP2()[0]);
		m_lower_bbox_corner[1] = std::min(m_lower_bbox_corner[1], ite->getP2()[1]);
		m_lower_bbox_corner[2] = std::min(m_lower_bbox_corner[2], ite->getP2()[2]);

		m_upper_bbox_corner[0] = std::max(m_upper_bbox_corner[0], ite->getP2()[0]);
		m_upper_bbox_corner[1] = std::max(m_upper_bbox_corner[1], ite->getP2()[1]);
		m_upper_bbox_corner[2] = std::max(m_upper_bbox_corner[2], ite->getP2()[2]);

		m_lower_bbox_corner[0] = std::min(m_lower_bbox_corner[0], ite->getP3()[0]);
		m_lower_bbox_corner[1] = std::min(m_lower_bbox_corner[1], ite->getP3()[1]);
		m_lower_bbox_corner[2] = std::min(m_lower_bbox_corner[2], ite->getP3()[2]);

		m_upper_bbox_corner[0] = std::max(m_upper_bbox_corner[0], ite->getP3()[0]);
		m_upper_bbox_corner[1] = std::max(m_upper_bbox_corner[1], ite->getP3()[1]);
		m_upper_bbox_corner[2] = std::max(m_upper_bbox_corner[2], ite->getP3()[2]);
	}
}
