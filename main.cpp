#include <iostream>
#include <fstream>
#include <limits>

#include "Vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitablelist.h"


Vec3 color(const Ray& r, HitableList world)
{
  HitRecord rec;
  if(world.hit(r, 0.0f, std::numeric_limits<float>::max(), rec))
    return 0.5f*Vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
  else
  {
    // Paint background
    Vec3 unit_direction = unit_vector(r.direction());
    // Background fade
    float t = 0.5f*(unit_direction.y() + 1.0f);
    return (1.0f-t)*Vec3(1.0f, 1.0f, 1.0f) + t*Vec3(0.5f, 0.7f, 1.0f);
  }
}

void createPpm(const std::string &filename)
{
  const int width = 400;
  const int height = 200;
  const int max_rgb_value = 255;

  Vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
  Vec3 horizontal(4.0f, 0.0f, 0.0f);
  Vec3 vertical(0.0f, 2.0f, 0.0f);
  Vec3 origin(0.0f, 0.0f, 0.0f);

  HitableList world;
  world.push_back(std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5f));
  world.push_back(std::make_shared<Sphere>(Vec3(0, -100.5f, -1), 100));

  std::ofstream outf;
  outf.exceptions(std::ifstream::failbit | std::ifstream::badbit);
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
        Ray r(origin, lower_left_corner + u*horizontal + v*vertical);

        Vec3 p = r.point_at_parameter(2.0f);
        Vec3 col = color(r, world);
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
