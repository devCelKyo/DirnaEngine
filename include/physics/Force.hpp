#pragma once

#include <engine/Object.fwd.hpp>
#include <math/Geometry.hpp>
#include <vector>
#include <string>

namespace physics {

enum class ForceType
{
   Gravity,
   SupportReaction,
   Virtual
};

struct Force {
   ForceType type;
   Vector2D value; // in Newton
   
   Object* sourceObject = nullptr;
};

Force operator+(const Force& lhs, const Force& rhs);

class ForceSet {
public:
   ForceSet() = default;
   ForceSet(std::vector<Force>);

   void add(Force);

   Force getSum() const;
private:
   std::vector<Force> forces;
};

}