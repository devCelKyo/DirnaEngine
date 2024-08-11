#include <physics/Force.hpp>

namespace physics {

Force operator+(const Force& lhs, const Force& rhs)
{
   Force sum;
   sum.sourceObject = nullptr;
   sum.type = ForceType::Virtual;
   sum.value = lhs.value + rhs.value;
   
   return sum;
}

ForceSet::ForceSet(std::vector<Force> forces) : forces{forces}
{}

void ForceSet::add(Force force)
{
   forces.push_back(force);
}

Force ForceSet::getSum() const
{
   Force sum;
   for (const auto& force : forces)
   {
      sum = sum + force;
   }
   return sum;
}

Force ForceSet::getSumByType(ForceType type) const
{
   Force sum;
   for (const auto& force : forces)
   {
      sum = force.type == type ? sum + force : sum;
   }
   return sum;
}

std::vector<Force>& ForceSet::getForces()
{
   return forces;
}

} // namespace physics