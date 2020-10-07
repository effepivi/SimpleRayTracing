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

Image g_output_image(128, 128);

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
	//cout << g_mesh_set[0] << endl;

	Vec3 range = upper_bbox_corner - lower_bbox_corner;
	Vec3 bbox_centre = lower_bbox_corner + range / 2.0;

	float diagonal = range.getLength();

	Vec3 g_up(0.0, 0.0, 1.0);

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

	unsigned char* p_image = new unsigned char[3 * g_output_image.getWidth() * g_output_image.getHeight()];
	if (p_image)
	{
		// Process every row
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

				// Initialise the nearest intersection position and the fragment colour
				float nearest_intersection = inf;
				Vec3 colour = g_background_colour;

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
								if (t < nearest_intersection)
								{
									colour = getFragment(g_light, material, triangle.getNormal(), ray.getOrigin() + t * ray.getDirection(), ray.getOrigin());
								}
							}
						}
					}
				}

				unsigned char r, g, b;

				if (255.0 * colour[0] < 0) r = 0;
				else if (255.0 * colour[0] > 255) r = 255;
				else r = int(255.0 * colour[0]);

				if (255.0 * colour[1] < 0) g = 0;
				else if (255.0 * colour[1] > 255) g = 255;
				else g = int(255.0 * colour[1]);

				if (255.0 * colour[2] < 0) b = 0;
				else if (255.0 * colour[2] > 255) b = 255;
				else b = int(255.0 * colour[2]);

				r = b = 0 ;
				g_output_image.setPixel(col, row, r, g, b);

				p_image[row * g_output_image.getWidth() * 3 + col * 3 + 0] = r;
				p_image[row * g_output_image.getWidth() * 3 + col * 3 + 2] = g;
				p_image[row * g_output_image.getWidth() * 3 + col * 3 + 1] = b;
			}
		}

		// Save the image
		g_output_image.saveJPEGFile("test.jpg");
		FILE* p_file(fopen("test.tga", "wb"));

		if (p_file)
		{
			putc(0, p_file);
			putc(0, p_file);
			putc(2, p_file);                         /* uncompressed RGB */
			putc(0, p_file);
			putc(0, p_file);
			putc(0, p_file);
			putc(0, p_file);
			putc(0, p_file);
			putc(0, p_file);
			putc(0, p_file);           /* X origin */
			putc(0, p_file);
			putc(0, p_file);           /* y origin */
			putc((g_output_image.getWidth() & 0xFF), p_file);
			putc((g_output_image.getWidth() >> 8)  & 0xFF, p_file);
			putc((g_output_image.getHeight() & 0xFF), p_file);
			putc((g_output_image.getHeight() >> 8)  & 0xFF, p_file);
			putc(24, p_file);                        /* 24 bit bitmap */

			for (int row = 0; row < g_output_image.getHeight(); ++row)
			{
				fwrite(p_image + row * g_output_image.getWidth() * 3,
				sizeof(unsigned char), g_output_image.getWidth() * 3,
				p_file);
			}
		}
		fclose(p_file);
		delete [] p_image;
	}

	return 0;
}
