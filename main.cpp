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
  if(world.hit(r, 0.01f, std::numeric_limits<float>::max(), rec))
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
  const int width = 600;
  const int height = 300;
  const int ns = 20;
  const int max_rgb_value = 255;

  HitableList world;

  world.push_back(std::make_shared<Sphere>(Vec3(0, -1000, 0), 1000,
        std::make_shared<Lambertian>(Vec3(0.5f, 0.5f, 0.5f))));

  for(int a = -11; a < 11; ++a)
  {
    for(int b = -11; b < 11; ++b)
    {
      float choose_mat = drand48();
      Vec3 center(a + 0.9f * drand48(), 0.2f, b + 0.9f * drand48());
      if((center - Vec3(4, 0.2f, 0)).length() > 0.9f)
      {
        if(choose_mat < 0.8f) // Diffuse
          world.push_back(std::make_shared<Sphere>(center, 0.2f,
                  std::make_shared<Lambertian>(Vec3(drand48()*drand48(),
                      drand48()*drand48(), drand48()*drand48()))));
        else if (choose_mat < 0.95f) // Metal
          world.push_back(std::make_shared<Sphere>(center, 0.2f,
                std::make_shared<Metal>(Vec3(0.5f*(1 + drand48()), 0.5f*(1 +
                      drand48()), 0.5f*(1 + drand48())), 0.5f*drand48())));
        else // Glass
          world.push_back(std::make_shared<Sphere>(center, 0.2f,
                std::make_shared<Dielectric>(1.5f)));
      }
    }
  }

  world.push_back(std::make_shared<Sphere>(Vec3(0, 1, 0), 1.0f,
        std::make_shared<Dielectric>(1.5f)));
  world.push_back(std::make_shared<Sphere>(Vec3(-4, 1, 0), 1.0f,
      std::make_shared<Lambertian>(Vec3(0.4f, 0.2f, 0.1f))));
  world.push_back(std::make_shared<Sphere>(Vec3(4, 1, 0), 1.0f,
        std::make_shared<Metal>(Vec3(0.7f, 0.6f, 0.5f), 0.0f)));

  std::cout << "-- World created" << std::endl;

  Vec3 lookfrom(13, 2, 3);
  Vec3 lookat(0, 0, 0);
  float dist_to_focus = 7.0f;
  float aperture = 0.00f;
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
      std::cout << j << std::endl;
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
