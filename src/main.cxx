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
*   @file       main.cxx
*
*   @brief      A simple ray-tracer without parallelism.
*
*   @version    1.0
*
*   @date       14/10/2020
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
*   http://www.fpvidal.net/, Oct 2020, 2020, version 1.0, BSD 3-Clause License
*
********************************************************************************
*/


//******************************************************************************
//  Include
//******************************************************************************
#include <iostream>  // for cerr
#include <exception> // to catch exceptions
#include <algorithm> // for max
#include <cmath>     // for pow
#include <limits>    // for inf
#include <stdexcept> // for exceptions
#include <sstream>   // to format error messages
#include <string>

#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#ifndef __Vec3_h
#include "Vec3.h"
#endif

#ifndef __Ray_h
#include "Ray.h"
#endif

#ifndef __Ray_h
#include "Ray.h"
#endif

#ifndef __TriangleMesh_h
#include "TriangleMesh.h"
#endif

#ifndef __Material_h
#include "Material.h"
#endif

#ifndef __Image_h
#include "Image.h"
#endif


//******************************************************************************
//  Namespace
//******************************************************************************
using namespace std;


//******************************************************************************
//  Function declarations
//******************************************************************************
Vec3 applyShading(const Light& aLight,
		         		  const Material& aMaterial,
				 			    const Vec3& aNormalVector,
				          const Vec3& aPosition,
								  const Vec3& aViewPosition);

void loadMeshes(const std::string& aFileName,
								vector<TriangleMesh>& aMeshSet);

TriangleMesh createBackground(const Vec3& anUpperBBoxCorner,
	                            const Vec3& aLowerBBoxCorner);

void getBBox(const vector<TriangleMesh>& aMeshSet,
						 Vec3& anUpperBBoxCorner,
             Vec3& aLowerBBoxCorner);


//******************************************************************************
//  Constant global variables
//******************************************************************************
const unsigned int g_image_width = 2048;
const unsigned int g_image_height = 2048;

const Vec3 g_black(0, 0, 0);
const Vec3 g_white(1, 1, 1);

const Vec3 g_red(1, 0, 0);
const Vec3 g_green(0, 1, 0);
const Vec3 g_blue(0, 0, 1);

const Vec3 g_background_colour = g_black;


//-----------------------------
int main(int argc, char** argv)
//-----------------------------
{
		try
		{
				// Load the polygon meshes
				vector<TriangleMesh> p_mesh_set;
				loadMeshes("./dragon.ply", p_mesh_set);

				// Change the material of the 1st mesh
				Material material(0.2 * g_red, g_green, g_blue, 1);
				p_mesh_set[0].setMaterial(material);

				// Get the scene's bbox
				Vec3 lower_bbox_corner;
				Vec3 upper_bbox_corner;

				getBBox(p_mesh_set, upper_bbox_corner, lower_bbox_corner);

				// Initialise the ray-tracer properties
				Vec3 range = upper_bbox_corner - lower_bbox_corner;
				Vec3 bbox_centre = lower_bbox_corner + range / 2.0;

				float diagonal = range.getLength();

				Vec3 up(0.0, 0.0, -1.0);

				Vec3 origin(bbox_centre - Vec3(diagonal * 1, 0, 0));
				Vec3 detector_position(bbox_centre + Vec3(diagonal * 0.6, 0, 0));

				Vec3 direction((detector_position - origin));
				direction.normalize();

				Image output_image(g_image_width, g_image_height, 128, 128, 128);

				float res1 = range[2] / output_image.getWidth();
				float res2 = range[1] / output_image.getHeight();
				float pixel_spacing[] = {2 * std::max(res1, res2), 2 * std::max(res1, res2)};

				Light light(g_white, direction, origin);

				direction.normalise();
				Vec3 right(direction.crossProduct(up));

				// Create a mesh that will go behing the scene (some kind of background)
				p_mesh_set.push_back(createBackground(upper_bbox_corner, lower_bbox_corner));

				// Rendering loop

				// Process every row
				float inf = std::numeric_limits<float>::infinity();
				std::vector<float> z_buffer(output_image.getWidth() * output_image.getHeight(), inf);
				for (int row = 0; row < output_image.getHeight(); ++row)
				{
						// Process every column
						for (int col = 0; col < output_image.getWidth(); ++col)
						{
								float v_offset = pixel_spacing[1] * (0.5 + row - output_image.getHeight() / 2.0);
								float u_offset = pixel_spacing[0] * (0.5 + col - output_image.getWidth() / 2.0);

								// Initialise the ray direction for this pixel
								Vec3 direction = detector_position + up * v_offset + right * u_offset - origin;
								direction.normalise();
								Ray ray(origin, direction);

								// Process every mesh
								for (std::vector<TriangleMesh>::const_iterator mesh_ite = p_mesh_set.begin();
										mesh_ite != p_mesh_set.end();
										++mesh_ite)
								{
										Material material = mesh_ite->getMaterial();

										// The ray intersect the mesh's bbox
										if (mesh_ite->intersectBBox(ray))
										{
												// Process all the triangles of the mesh
												for (unsigned int triangle_id = 0;
														triangle_id < mesh_ite->getNumberOfTriangles();
														++triangle_id)
												{
														// Retrievethe triangle
														const Triangle& triangle = mesh_ite->getTriangle(triangle_id);

														// Retrieve the intersection if any
														float t;
														bool intersect = ray.intersect(triangle, t);

														// The ray interescted the triangle
														if (intersect)
														{
																// The intersection is closer to the view point than the previously recorded intersection
																// Update the pixel value
																if (z_buffer[row * output_image.getWidth() + col] > t)
																{
																		z_buffer[row * output_image.getWidth() + col] = t;
																		Vec3 colour = applyShading(light, material, triangle.getNormal(), ray.getOrigin() + t * ray.getDirection(), ray.getOrigin());

																		unsigned char r, g, b;

																		const Image& texture = mesh_ite->getTexture();

																		// Use texturing
																		if (texture.getWidth() * texture.getHeight())
																		{
																				// Get the position of the intersection
																				Vec3 P = origin + t * direction;

																				// See https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/barycentric-coordinates
																				Vec3 A = triangle.getP1();
																				Vec3 B = triangle.getP2();
																				Vec3 C = triangle.getP3();

																				Triangle ABC(A, B, C);
																				Triangle ABP(A, B, P);
																				Triangle BCP(B, C, P);
																				Triangle CAP(C, A, P);

																				float area_ABC = ABC.getArea();
																				float u = CAP.getArea() / area_ABC;
																				float v = ABP.getArea() / area_ABC;
																				float w = BCP.getArea() / area_ABC;

																				// Getthe texel cooredinate
																				Vec3 texel_coord(w * triangle.getTextCoord1() + u * triangle.getTextCoord2() + v * triangle.getTextCoord3());

																				unsigned char texel_r;
																				unsigned char texel_g;
																				unsigned char texel_b;

																				// Retrieve the pixel value from the texture
																				texture.getPixel(texel_coord[0] * (texture.getWidth() - 1),
																						texel_coord[1] * (texture.getHeight() - 1),
																						texel_r, texel_g, texel_b);

																				colour[0] *= texel_r;
																				colour[1] *= texel_g;
																				colour[2] *= texel_b;

																				// Clamp the value to the range 0 to 255
																				if (colour[0] < 0) r = 0;
																				else if (colour[0] > 255) r = 255;
																				else r = int(colour[0]);

																				if (colour[1] < 0) g = 0;
																				else if (colour[1] > 255) g = 255;
																				else g = int(colour[1]);

																				if (colour[2] < 0) b = 0;
																				else if (colour[2] > 255) b = 255;
																				else b = int(colour[2]);
																		}
																		else
																		{
																				// Convert from float to UCHAR and
																				// clamp the value to the range 0 to 255
																				if (255.0 * colour[0] < 0) r = 0;
																				else if (255.0 * colour[0] > 255) r = 255;
																				else r = int(255.0 * colour[0]);

																				if (255.0 * colour[1] < 0) g = 0;
																				else if (255.0 * colour[1] > 255) g = 255;
																				else g = int(255.0 * colour[1]);

																				if (255.0 * colour[2] < 0) b = 0;
																				else if (255.0 * colour[2] > 255) b = 255;
																				else b = int(255.0 * colour[2]);
																		}

																		// Update the pixel value
																		output_image.setPixel(col, row, r, g, b);
																}
														}
												}
										}
								}
						}
				}

				// Save the image
				output_image.saveJPEGFile("test.jpg");
				output_image.saveTGAFile("test.tga");
		}
		// Catch exceptions and error messages
		catch (const std::exception& e)
		{
				std::cerr << "ERROR: " << e.what() << std::endl;
				return 1;
		}
		catch (const std::string& e)
		{
				std::cerr << "ERROR: " << e << std::endl;
				return 2;
		}
		catch (const char* e)
		{
				std::cerr << "ERROR: " << e << std::endl;
				return 3;
		}

		return 0;
}


//******************************************************************************
//  Function definitions
//******************************************************************************

//------------------------------------------
Vec3 applyShading(const Light& aLight,
		         		  const Material& aMaterial,
				 			    const Vec3& aNormalVector,
				          const Vec3& aPosition,
								  const Vec3& aViewPosition)
//------------------------------------------
{
		Vec3 ambient, diffuse, specular;

		// ambient
		ambient = aLight.getColour() * aMaterial.getAmbient();

		// diffuse
		Vec3 lightDir = (aLight.getPosition() - aPosition);
		lightDir.normalize();
		float diff = std::max(std::abs(aNormalVector.dotProduct(lightDir)), 0.0f);
		diffuse = aLight.getColour() * (diff * aMaterial.getDiffuse());

		// specular
		Vec3 viewDir(aViewPosition - aPosition);
		viewDir.normalize();

		Vec3 reflectDir = reflect(-viewDir, aNormalVector);
		float spec = std::pow(std::max(dot(viewDir, reflectDir), 0.0f), aMaterial.getShininess());
		specular = aLight.getColour() * (spec * aMaterial.getSpecular());

		return ambient + diffuse + specular;
}


//---------------------------------------------
void loadMeshes(const std::string& aFileName,
								vector<TriangleMesh>& aMeshSet)
//-----------------------------==--------------
{
		// Create an instance of the Importer class
		Assimp::Importer importer;

		// And have it read the given file with some example postprocessing
		// Usually - if speed is not the most important aspect for you - you'll
		// probably to request more postprocessing than we do in this example.
		const aiScene* scene = importer.ReadFile( aFileName,
				aiProcess_CalcTangentSpace       |
				aiProcess_Triangulate            |
				aiProcess_JoinIdenticalVertices  |
				aiProcess_SortByPType);

		// If the import failed, report it
		if( !scene)
		{
				std::stringstream error_message;
				error_message << importer.GetErrorString() << ", in File " << __FILE__ <<
						", in Function " << __FUNCTION__ <<
						", at Line " << __LINE__;

				throw std::runtime_error(error_message.str());
		}

		// Now we can access the file's contents.
		if (scene->HasMeshes())
		{
				aMeshSet.clear();

				for (int mesh_id = 0; mesh_id < scene->mNumMeshes; ++mesh_id)
				{
						aiMesh* p_mesh = scene->mMeshes[mesh_id];
						TriangleMesh mesh;

						// This is a triangle mesh
						if (p_mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE)
						{
								aiMaterial* p_mat = scene->mMaterials[p_mesh->mMaterialIndex];

								aiColor3D ambient, diffuse, specular;
								float shininess;

								p_mat->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
								p_mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
								p_mat->Get(AI_MATKEY_COLOR_SPECULAR, specular);
								p_mat->Get(AI_MATKEY_SHININESS, shininess);

								Material material;
								material.setAmbient(Vec3(ambient.r, ambient.g, ambient.b));
								material.setDiffuse(Vec3(diffuse.r, diffuse.g, diffuse.b));
								material.setSpecular(Vec3(specular.r, specular.g, specular.b));
								material.setShininess(shininess);

								mesh.setMaterial(material);

								// Load the vertices
								std::vector<float> p_vertices;
								for (unsigned int vertex_id = 0; vertex_id < p_mesh->mNumVertices; ++vertex_id)
								{
										p_vertices.push_back(p_mesh->mVertices[vertex_id].x);
										p_vertices.push_back(p_mesh->mVertices[vertex_id].y);
										p_vertices.push_back(p_mesh->mVertices[vertex_id].z);
								}

								// Load indices
								std::vector<unsigned int> p_index_set;
								for (unsigned int index_id = 0; index_id < p_mesh->mNumFaces; ++index_id)
								{
										if (p_mesh->mFaces[index_id].mNumIndices == 3)
										{
											p_index_set.push_back(p_mesh->mFaces[index_id].mIndices[0]);
											p_index_set.push_back(p_mesh->mFaces[index_id].mIndices[1]);
											p_index_set.push_back(p_mesh->mFaces[index_id].mIndices[2]);
										}
								}
								mesh.setGeometry(p_vertices, p_index_set);
						}
						aMeshSet.push_back(mesh);
				}
		}
}


//----------------------------------------------------------
TriangleMesh createBackground(const Vec3& anUpperBBoxCorner,
	                            const Vec3& aLowerBBoxCorner)
//----------------------------------------------------------
{
		Vec3 range = anUpperBBoxCorner - aLowerBBoxCorner;

		std::vector<float> vertices = {
				anUpperBBoxCorner[0] + range[0] * 0.1f, aLowerBBoxCorner[1] - range[1] * 0.5f, aLowerBBoxCorner[2] - range[2] * 0.5f,
				anUpperBBoxCorner[0] + range[0] * 0.1f, anUpperBBoxCorner[1] + range[1] * 0.5f, aLowerBBoxCorner[2] - range[2] * 0.5f,
				anUpperBBoxCorner[0] + range[0] * 0.1f, anUpperBBoxCorner[1] + range[1] * 0.5f, anUpperBBoxCorner[2] + range[2] * 0.5f,
				anUpperBBoxCorner[0] + range[0] * 0.1f, aLowerBBoxCorner[1] - range[1] * 0.5f, anUpperBBoxCorner[2] + range[2] * 0.5f,
		};

		std::vector<float> text_coords = {
				0, 1, 0,
				1, 1, 0,
				1, 0, 0,
				0, 0, 0,
		};

		std::vector<unsigned int> indices = {
				0, 1, 2,
				0, 2, 3,
		};

		TriangleMesh background_mesh(vertices, indices, text_coords);
		Image cloud_texture("Bangor_Logo_A1.jpg" /*"cloud2.jpg"*/);
		background_mesh.setTexture(cloud_texture);

		return (background_mesh);
}


//------------------------------------------------
void getBBox(const vector<TriangleMesh>& aMeshSet,
						 Vec3& anUpperBBoxCorner,
						 Vec3& aLowerBBoxCorner)
//------------------------------------------------
{
		float inf = std::numeric_limits<float>::infinity();

		aLowerBBoxCorner = Vec3( inf,  inf,  inf);
		anUpperBBoxCorner = Vec3(-inf, -inf, -inf);

		for (std::vector<TriangleMesh>::const_iterator ite = aMeshSet.begin();
				ite != aMeshSet.end();
				++ite)
		{
				Vec3 mesh_lower_bbox_corner = ite->getLowerBBoxCorner();
				Vec3 mesh_upper_bbox_corner = ite->getUpperBBoxCorner();

				aLowerBBoxCorner[0] = std::min(aLowerBBoxCorner[0], mesh_lower_bbox_corner[0]);
				aLowerBBoxCorner[1] = std::min(aLowerBBoxCorner[1], mesh_lower_bbox_corner[1]);
				aLowerBBoxCorner[2] = std::min(aLowerBBoxCorner[2], mesh_lower_bbox_corner[2]);

				anUpperBBoxCorner[0] = std::max(anUpperBBoxCorner[0], mesh_upper_bbox_corner[0]);
				anUpperBBoxCorner[1] = std::max(anUpperBBoxCorner[1], mesh_upper_bbox_corner[1]);
				anUpperBBoxCorner[2] = std::max(anUpperBBoxCorner[2], mesh_upper_bbox_corner[2]);
		}
}
