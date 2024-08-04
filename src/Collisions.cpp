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

static void addMomentum(Object* obj, Vector2D momentum)
{
   Vector2D speedToGive = momentum * (1 / obj->mass);
   obj->speed += speedToGive;
}

static void withdrawMomentum(Object* obj, Vector2D momentum)
{
   Vector2D speedToGive = momentum * (1 / obj->mass);
   obj->speed += -1 * speedToGive;
}

void collide(Circle* A, Circle* B)
{
   // Vector between the two centers
   Vector2D AB = {B->x - A->x, B->y - A->y};
   double distance = AB.getNorm();
   if (distance <= 0.97 * (A->radius + B->radius))
   {
      double factorA_to_B = std::abs(AB * A->speed / (AB.getNorm() * A->speed.getNorm()));
      double factorB_to_A = std::abs((-1 * AB) * B->speed / (AB.getNorm() * B->speed.getNorm()));

      Vector2D A_MomentumToGive = factorA_to_B * A->mass * A->speed;
      Vector2D B_MomentumToGive = factorB_to_A * B->mass * B->speed;

      withdrawMomentum(A, A_MomentumToGive);
      withdrawMomentum(B, B_MomentumToGive);
      addMomentum(A, B_MomentumToGive);
      addMomentum(B, A_MomentumToGive);
   }
}

} // namespace collisions