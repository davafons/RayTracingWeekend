#include <iostream>
#include <fstream>

#include "vec3.h"

const int width = 200;
const int height = 100;
const int max_rgb_value = 255;

void createPpm(const std::string &filename)
{
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
        vec3 col(float(i) / float(width), float(j) / float(height), 0.2f);
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
