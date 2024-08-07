#include <physics/Collisions.hpp>
#include <math/Geometry.hpp>

namespace collisions {

bool collide(Rectangle*, Rectangle*)
{
   return false;
}

bool collide(Rectangle* rectangle, Circle* circle)
{
   auto sides = geometry::getRectangleSides(*rectangle);
   for (const auto& side : sides)
   {
      Vector2D center(circle->x, circle->y);
      double distance = geometry::getDistance(center, side);
      if (distance < circle->radius)
      {
         // (1) : "Undo" the collision, if the objects are "overlapping" - which they are btw - 
         //       shift the circle following the orthogonal projection
         //       make it so distance == circle->radius
         Vector2D normalizedOrthProj = geometry::getOrthogonalProjection(center, side) * (1. / distance);
         Vector2D shift = (distance - circle->radius) * normalizedOrthProj;
         circle->move(shift);
         
         // (2) : Regular speed reflection on the collided side
         auto reflectedSpeed = reflect(circle->getSpeed(), side.u);
         circle->setSpeed(0.6 * reflectedSpeed); // Make this a drag coefficient of rectangle
         return true;
      }
   }
   return false;
}

static void addMomentum(Object* obj, Vector2D momentum)
{
   Vector2D speedToGive = momentum * (1 / obj->mass);
   obj->setSpeed(obj->getSpeed() + speedToGive);
}

static void withdrawMomentum(Object* obj, Vector2D momentum)
{
   Vector2D speedToGive = momentum * (1 / obj->mass);
   obj->setSpeed(obj->getSpeed() - speedToGive);
}

bool collide(Circle* A, Circle* B)
{
   // Vector between the two centers
   Vector2D AB = {B->x - A->x, B->y - A->y};
   double distance = AB.getNorm();
   if (distance <= 0.99 * (A->radius + B->radius)) // make sure this makes sense
   {
      Vector2D aSpeed = A->getSpeed();
      Vector2D bSpeed = B->getSpeed();
      
      double factorA_to_B = std::max(AB * aSpeed / (AB.getNorm() * aSpeed.getNorm()), 0.);
      double factorB_to_A = std::max((-1 * AB) * bSpeed / (AB.getNorm() * bSpeed.getNorm()), 0.);

      Vector2D A_MomentumToGive = factorA_to_B * A->mass * aSpeed;
      Vector2D B_MomentumToGive = factorB_to_A * B->mass * bSpeed;

      withdrawMomentum(A, A_MomentumToGive);
      withdrawMomentum(B, B_MomentumToGive);
      addMomentum(A, B_MomentumToGive);
      addMomentum(B, A_MomentumToGive);

      return true;
   }
   return false;
}

} // namespace collisions