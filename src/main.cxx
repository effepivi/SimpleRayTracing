#include <cstdio>
#include <iostream>
#include <algorithm> // for max
#include <cmath> // for pow
#include <limits> // for inf

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

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


using namespace std;


const Vec3 g_black(0, 0, 0);
const Vec3 g_white(1, 1, 1);

const Vec3 g_red(1, 0, 0);
const Vec3 g_green(0, 1, 0);
const Vec3 g_blue(0, 0, 1);

const Vec3 g_background_colour = g_black;

Image g_output_image(2048, 2048, 128, 128, 128);

std::vector<TriangleMesh> g_mesh_set;


Vec3 getFragment(const Light& aLight,
		         const Material& aMaterial,
				 const Vec3& aNormalVector,
				 const Vec3& aPosition,
				 const Vec3& aViewPosition)
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


bool loadMesh(const std::string& aFileName)
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
	if( !scene) {
		std::cerr << importer.GetErrorString() << std::endl;
		return false;
	}

	// Now we can access the file's contents.
	if (scene->HasMeshes())
	{
		g_mesh_set.clear();

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
			g_mesh_set.push_back(mesh);
		}
	}
//	std::cout << scene->HasMaterials() << std::endl;
//	std::cout <<  << std::endl;

	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}


int main(int argc, char** argv)
{
	try
	{
		Material g_material(0.2 * g_red, g_green, g_blue, 1);

		loadMesh("../dragon.ply");

		// Get the scene's bbox
		float inf = std::numeric_limits<float>::infinity();

		Vec3 lower_bbox_corner( inf,  inf,  inf);
		Vec3 upper_bbox_corner(-inf, -inf, -inf);

		for (std::vector<TriangleMesh>::const_iterator ite = g_mesh_set.begin();
				ite != g_mesh_set.end();
				++ite)
		{
			Vec3 mesh_lower_bbox_corner = ite->getLowerBBoxCorner();
			Vec3 mesh_upper_bbox_corner = ite->getUpperBBoxCorner();

			lower_bbox_corner[0] = std::min(lower_bbox_corner[0], mesh_lower_bbox_corner[0]);
			lower_bbox_corner[1] = std::min(lower_bbox_corner[1], mesh_lower_bbox_corner[1]);
			lower_bbox_corner[2] = std::min(lower_bbox_corner[2], mesh_lower_bbox_corner[2]);

			upper_bbox_corner[0] = std::max(upper_bbox_corner[0], mesh_upper_bbox_corner[0]);
			upper_bbox_corner[1] = std::max(upper_bbox_corner[1], mesh_upper_bbox_corner[1]);
			upper_bbox_corner[2] = std::max(upper_bbox_corner[2], mesh_upper_bbox_corner[2]);

		}


		g_mesh_set[0].setMaterial(g_material);

		Vec3 range = upper_bbox_corner - lower_bbox_corner;
		Vec3 bbox_centre = lower_bbox_corner + range / 2.0;

		float diagonal = range.getLength();

		Vec3 g_up(0.0, 0.0, -1.0);

		Vec3 g_origin(bbox_centre - Vec3(diagonal * 1, 0, 0));
		Vec3 g_detector_position(bbox_centre + Vec3(diagonal * 0.6, 0, 0));

		Vec3 g_direction((g_detector_position - g_origin));
		g_direction.normalize();

		float res1 = range[2] / g_output_image.getWidth();
		float res2 = range[1] / g_output_image.getHeight();
		float g_pixel_spacing[] = {2 * std::max(res1, res2), 2 * std::max(res1, res2)};

		Light g_light(g_white, g_direction, g_origin);

		g_direction.normalise();
		Vec3 right(g_direction.crossProduct(g_up));

		std::vector<float> vertices = {
				upper_bbox_corner[0] + range[0] * 0.1f, lower_bbox_corner[1] - range[1] * 0.5f, lower_bbox_corner[2] - range[2] * 0.5f,
				upper_bbox_corner[0] + range[0] * 0.1f, upper_bbox_corner[1] + range[1] * 0.5f, lower_bbox_corner[2] - range[2] * 0.5f,
				upper_bbox_corner[0] + range[0] * 0.1f, upper_bbox_corner[1] + range[1] * 0.5f, upper_bbox_corner[2] + range[2] * 0.5f,
				upper_bbox_corner[0] + range[0] * 0.1f, lower_bbox_corner[1] - range[1] * 0.5f, upper_bbox_corner[2] + range[2] * 0.5f,
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


		g_mesh_set.push_back(background_mesh);



		// Process every row
		std::vector<float> z_buffer(g_output_image.getWidth() * g_output_image.getHeight(), inf);

#pragma omp parallel for collapse(2)
		for (int row = 0; row < g_output_image.getHeight(); ++row)
		{
			// Process every column
			for (int col = 0; col < g_output_image.getWidth(); ++col)
			{
				float v_offset = g_pixel_spacing[1] * (0.5 + row - g_output_image.getHeight() / 2.0);
				float u_offset = g_pixel_spacing[0] * (0.5 + col - g_output_image.getWidth() / 2.0);

				// Initialise the ray direction
				Vec3 direction = g_detector_position + g_up * v_offset + right * u_offset - g_origin;
				direction.normalise();
				Ray ray(g_origin, direction);

				// Process every mesh
				for (std::vector<TriangleMesh>::const_iterator mesh_ite = g_mesh_set.begin();
						mesh_ite != g_mesh_set.end();
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
							float t;

							const Triangle& triangle = mesh_ite->getTriangle(triangle_id);
							bool intersect = ray.intersect(triangle, t);

							if (intersect)
							{
								if (z_buffer[row * g_output_image.getWidth() + col] > t)
								{
									z_buffer[row * g_output_image.getWidth() + col] = t;
									Vec3 colour = getFragment(g_light, material, triangle.getNormal(), ray.getOrigin() + t * ray.getDirection(), ray.getOrigin());

									unsigned char r, g, b;

									const Image& texture = mesh_ite->getTexture();

									// Use texturing
									if (texture.getWidth() * texture.getHeight())
									{
										Vec3 P = g_origin + t * direction;

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

										Vec3 texel_coord(w * triangle.getTextCoord1() + u * triangle.getTextCoord2() + v * triangle.getTextCoord3());

										unsigned char texel_r;
										unsigned char texel_g;
										unsigned char texel_b;

										texture.getPixel(texel_coord[0] * (texture.getWidth() - 1),
												texel_coord[1] * (texture.getHeight() - 1),
												texel_r, texel_g, texel_b);

										colour[0] *= texel_r;
										colour[1] *= texel_g;
										colour[2] *= texel_b;

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
									g_output_image.setPixel(col, row, r, g, b);
								}
							}
						}
					}
				}
			}
		}

		// Save the image
		g_output_image.saveJPEGFile("test.jpg");
		g_output_image.saveTGAFile("test.tga");

	}
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
