#pragma once

#include <engine/Object.fwd.hpp>
#include <math/Geometry.hpp>
#include <string>

namespace physics {

enum class ForceType
{
   Gravity,
   SupportReaction
};

struct Force {
   ForceType type;
   Vector2D value; // in Newton
   
   Object* sourceObject = nullptr;
};

}