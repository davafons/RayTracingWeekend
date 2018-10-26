#include <iostream>
#include <fstream>

#include "vec3.h"
#include "ray.h"

vec3 color(const ray& r)
{
  vec3 unit_direction = unit_vector(r.direction());
  float t = 0.5f*(unit_direction.y() + 1.0f);
  return (1.0f-t)*vec3(1.0f, 1.0f, 1.0f) + t*vec3(0.5f, 0.7f, 1.0f);
}

void createPpm(const std::string &filename)
{
  const int width = 200;
  const int height = 100;
  const int max_rgb_value = 255;

  std::ofstream outf;
  outf.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
  vec3 horizontal(4.0f, 0.0f, 0.0f);
  vec3 vertical(0.0f, 2.0f, 0.0f);
  vec3 origin(0.0f, 0.0f, 0.0f);

  try
  {
    outf.open(filename);
    outf << "P3\n" << width << " " << height << "\n" << max_rgb_value << "\n";
    for(int j = height - 1; j >= 0; --j)
    {
      for(int i = 0; i < width; ++i)
      {
        float u = float(i) / float(width);
        float v = float(j) / float(height);
        ray r(origin, lower_left_corner + u*horizontal + v*vertical);
        vec3 col = color(r);
        int ir = int(255.99 * col.r());
        int ig = int(255.99 * col.g());
        int ib = int(255.99 * col.b()); 
        outf << ir << " " << ig << " " << ib << "\n";
      }
    }
  }
  catch(const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  outf.close();
}

int main(int argc, char* argv[])
{
  std::string filename = "image.ppm";
  if(argc > 1)
    filename = argv[1];

  createPpm(filename);

  return 0;
}
