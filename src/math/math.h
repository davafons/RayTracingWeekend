#include <cmath>

#include "vec3.h"

class Math {
public:
  static constexpr double PI = std::atan(1) * 4;
  static double drand48() { return double(rand()) / RAND_MAX; }
};
