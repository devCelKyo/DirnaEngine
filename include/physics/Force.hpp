#pragma once

#include <math/Geometry.hpp>
#include <string>

namespace physics {

struct Force {
   std::string name;
   Vector2D value; // in Newton
};

}