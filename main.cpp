#include <iostream>
#include <cfloat>

#include "sphere.h"
#include "hitablelist.h"
#include "camera.h"

vec3 random_in_unit_sphere()
{
  vec3 p;
  do
  {
    p = 2.0f*vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
  } while(p.squared_length() >= 1.0f);
  return p;
}

vec3 color(const ray& r, hitable *world)
{
  hit_record rec;
  if(world->hit(r, 0.001f, FLT_MAX, rec))
  {
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    return 0.5f*color(ray(rec.p, target-rec.p), world);
  }
  else
  {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0f);
    return (1.0f-t)*vec3(1.0f, 1.0f, 1.0f) + t*vec3(0.5f, 0.7f, 1.0f);
  }
}

int main()
{
  int nx = 600;
  int ny = 300;
  int ns = 100;

  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  hitable *list[2];
  list[0] = new sphere(vec3(0, 0, -1), 0.5f);
  list[1] = new sphere(vec3(0, -100.5f, -1), 100);
  hitable *world = new hitable_list(list, 2);

  camera cam;

  for(int j = ny-1; j >= 0; --j) {
    for(int i = 0; i < nx; ++i) {
      vec3 col(0, 0, 0);
      for(int s = 0; s < ns; ++s)
      {
        float u = float(i + drand48()) / float(nx);
        float v = float(j + drand48()) / float(ny);
        ray r = cam.get_ray(u, v);
        vec3 p = r.point_at_parameter(2.0f);
        col += color(r, world);
      }
      col /= float(ns);
      col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
      int ir = int(255.99f*col[0]);
      int ig = int(255.99f*col[1]);
      int ib = int(255.99f*col[2]);
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }

  delete list[0];
  delete list[1];
  delete world;
}
