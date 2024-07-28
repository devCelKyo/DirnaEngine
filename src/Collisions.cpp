#include <physics/Collisions.hpp>
#include <math/Geometry.hpp>

namespace collisions {

void collide(Rectangle*, Rectangle*)
{}

void collide(Rectangle* rectangle, Circle* circle)
{
   auto sides = geometry::getRectangleSides(*rectangle);
   for (const auto& side : sides)
   {
      Vector2D center(circle->x, circle->y);
      double distance = geometry::getDistance(center, side);
      if (distance <= circle->radius)
      {
         reflect(circle->speed, side.u);
         return;
      }
   }
}

void collide(Circle*, Circle*)
{}

} // namespace collisions