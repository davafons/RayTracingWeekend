#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>

#include "camera.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitablelist.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

Vec3 color(const Ray& r, HitableList world, int depth)
{
  HitRecord rec;
  if(world.hit(r, 0.001f, std::numeric_limits<float>::max(), rec))
  {
    Ray scattered;
    Vec3 attenuation;
    if(depth < 50 && rec.mat->scatter(r, rec, attenuation, scattered))
      return attenuation * color(scattered, world, depth+1);
    else
      return Vec3(0, 0, 0);
  }
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
  const int width = 300;
  const int height = 150;
  const int ns = 100;
  const int max_rgb_value = 255;

  float R = cos(M_PI/4);
  HitableList world;
  world.push_back(std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5f,
        std::make_shared<Lambertian>(Vec3(0.3f, 0.3f, 0.8f))));
  world.push_back(std::make_shared<Sphere>(Vec3(0, -100.5f, -1), 100,
        std::make_shared<Lambertian>(Vec3(0.8f, 0.8f, 0.0f))));
  world.push_back(std::make_shared<Sphere>(Vec3(1, 0, -1), 0.5f,
        std::make_shared<Metal>(Vec3(0.8f, 0.6f, 0.2f), 1.0f)));
  world.push_back(std::make_shared<Sphere>(Vec3(-1, 0, -1), 0.50f,
        std::make_shared<Dielectric>(1.5f)));
  world.push_back(std::make_shared<Sphere>(Vec3(-1, 0, -1), -0.45f,
        std::make_shared<Dielectric>(1.5f)));

  Vec3 lookfrom(3, 3, 2);
  Vec3 lookat(0, 0, -1);
  float dist_to_focus = (lookfrom - lookat).length();
  float aperture = 2.0f;
  Camera cam(lookfrom, lookat, Vec3(0, 1, 0), 20, float(width)/float(height),
      aperture, dist_to_focus);

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
        Vec3 col(0, 0, 0);
        for(int s = 0; s < ns; ++s)
        {
          float u = float(i + drand48()) / float(width);
          float v = float(j + drand48()) / float(height);
          Ray r = cam.getRay(u, v);
          Vec3 p = r.point_at_parameter(2.0f);
          col += color(r, world, 0);
        }
        col /= float(ns);
        col = Vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));
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
