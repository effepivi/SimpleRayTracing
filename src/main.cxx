#include <cstdio>
#include <iostream>

#ifndef Vec3_h
#include "Vec3.h"
#endif

#ifndef Ray_h
#include "Ray.h"
#endif

#ifndef Ray_h
#include "Ray.h"
#endif

#ifndef TriangleMesh_h
#include "TriangleMesh.h"
#endif


Vec3 g_A(0.0, 0.0, 0.0);
Vec3 g_B(-256.0, -192.0, 0.0);
Vec3 g_C(256.0, 192.0, 0.0);

Triangle g_triangle(g_A, g_B, g_C);

Vec3 g_up(0.0, 1.0, 0.0);
Vec3 g_origin(0.0, 0.0, -100.0);
Vec3 g_detector_position(0.0, 0.0, 1.0);
Vec3 g_direction((g_detector_position - g_origin));
float g_pixel_spacing[] = {0.5, 0.5};
unsigned int g_detector_size_in_px[] = {1, 1};

int main()
{
  std::cout << g_direction << std::endl;
  g_direction.normalise();
  std::cout << g_direction << std::endl;

  Vec3 right(g_direction.crossProduct(g_up));
  std::cout << right << std::endl;

  FILE* p_file(fopen("test.raw", "wb"));

  if (p_file)
  {
      float* p_image = new float[g_detector_size_in_px[0] * g_detector_size_in_px[1]];
      if (p_image)
      {
          float* p_temp = p_image;
          for (int row = 0; row < g_detector_size_in_px[1]; ++row)
          {
              float v_offset = g_pixel_spacing[1] * (0.5 + row - g_detector_size_in_px[1] / 2.0);

              for (int col = 0; col < g_detector_size_in_px[0]; ++col)
              {
                  float u_offset = g_pixel_spacing[0] * (0.5 + col - g_detector_size_in_px[0] / 2.0);

                  // std::cout << u_offset << "\t" << v_offset << std::endl;
                  // std::cout << g_detector_position << std::endl;
                  // std::cout << g_up * v_offset << std::endl;
                  // std::cout << right * u_offset << std::endl;

                  Vec3 direction = g_detector_position + g_up * v_offset + right * u_offset - g_origin;
                  // std::cout << direction << std::endl;
                  direction.normalise();
                  // return 0;
                  Ray ray(g_origin, direction);
                  float t;
                  *p_temp++ = (ray.intersect(g_triangle, t)? 1.0 : 0.0);
              }
          }
          for (int row = 0; row < g_detector_size_in_px[1]; ++row)
          {
              fwrite(p_image + row * g_detector_size_in_px[0],
                  sizeof(float), g_detector_size_in_px[0],
                  p_file);
          }
          delete [] p_image;
      }
      fclose(p_file);
  }
  return 0;
}
