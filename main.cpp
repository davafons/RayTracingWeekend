#include <iostream>
#include <fstream>

#include "vec3.h"
#include "ray.h"

float hit_sphere(const vec3& center, float radius, const ray& r)
{
  vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = 2.0f * dot(oc, r.direction());
  float c = dot(oc, oc) - radius*radius;
  float discriminant = b*b - 4*a*c;

  if(discriminant < 0)
    return -1;
  else
    return (-b - sqrt(discriminant)) / (2.0f*a);
}

vec3 color(const ray& r)
{
  // Paint sphere (with normals)
  float t = hit_sphere(vec3(0, 0, -1), 0.5f, r);
  if(t > 0.0f)
  {
    vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
    return 0.5f*vec3(N.x()+1, N.y()+1, N.z()+1);
  }

  vec3 unit_direction = unit_vector(r.direction());
  // Background fade
  t = 0.5f*(unit_direction.y() + 1.0f);
  return (1.0f-t)*vec3(1.0f, 1.0f, 1.0f) + t*vec3(0.5f, 0.7f, 1.0f);
}

void createPpm(const std::string &filename)
{
  const int width = 400;
  const int height = 200;
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
