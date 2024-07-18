#include <Collisions.hpp>

namespace collisions {

void collide(Rectangle*, Rectangle*)
{}

void collide(Rectangle* rect, Circle* circ)
{
   if (rect->isFixed())
   {
      circ->speed.y = circ->speed.y * -1;
   }
}

void collide(Circle*, Circle*)
{}

} // namespace collisions