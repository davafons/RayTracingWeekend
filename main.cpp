#include <iostream>
#include <cfloat>

#include "sphere.h"
#include "hitablelist.h"
#include "camera.h"

vec3 color(const ray& r, hitable *world)
{
  hit_record rec;
  if(world->hit(r, 0.0f, FLT_MAX, rec))
    return 0.5f*vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
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
