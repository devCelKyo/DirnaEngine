#pragma once

#include <engine/Object.fwd.hpp>
#include <math/Vector2D.hpp>
#include <vector>
#include <string>

namespace physics {

enum class ForceType
{
   Gravity,
   SupportReaction,
   Virtual
};

struct Force 
{
   ForceType type;
   Vector2D value; // in Newton
   
   Object* sourceObject = nullptr;
};

Force operator+(const Force& lhs, const Force& rhs);

class ForceSet 
{
public:
   ForceSet() = default;
   ForceSet(std::vector<Force>);

   void add(Force);

   Force getSum() const;
   Force getSumByType(ForceType) const;

   const std::vector<Force>& getForces() const;
private:
   std::vector<Force> forces;
};

}