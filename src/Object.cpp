#include <engine/Object.hpp>
#include <physics/Units.hpp>
#include <physics/Collisions.hpp>

Object::Object(double x, double y, double mass) :
   x{ x }, y{ y }, mass{ mass }, color{Color::Red}
{}

Object::~Object()
{}

void Object::move(Vector2D shift)
{
   x += shift.x;
   y += shift.y;
}

void Object::applySpeed(double time)
{
   if (isFixed())
      return;

   auto shift = speed * time;
   move(shift);
}

void Object::applyAcceleration(double time)
{
   if (isFixed())
      return;

   auto shift = acceleration * time;
   speed += shift;
}

void Object::setFixed(bool val) { fixed = val; }

bool Object::isFixed() const { return fixed; }

Vector2D Object::getSpeed() const
{
   return speed;
}

// TODO make it a World parameter
constexpr double minimalSpeed = 0.000001;

void Object::setSpeed(Vector2D val)
{
   speed.x = std::abs(val.x) >= minimalSpeed ? val.x : 0;
   speed.y = std::abs(val.y) >= minimalSpeed ? val.y : 0;
}

Vector2D Object::getAcceleration() const
{
   return acceleration;
}

void Object::setAcceleration(Vector2D val)
{
   acceleration = val;
}

double Object::getDistanceInMeters(Object* other)
{
   double xDiff = x - other->x;
   double yDiff = y - other->y;
   return std::sqrt(xDiff * xDiff + yDiff * yDiff);
}

bool Object::canCollideWith(Object* other)
{
   const double distance2 = getDistanceInMeters(other);
   const double radiuses2 = getHitboxRadius() + other->getHitboxRadius();
   
   return distance2 <= radiuses2;
}

Rectangle::Rectangle(double x, double y, double width, double height, double mass)
   : Base(x, y, mass), width{width}, height{height}
{}

int Rectangle::getWrapperWidth() const
{
   return metersToPixels(width);
}

int Rectangle::getWrapperHeight() const
{
   return metersToPixels(height);
}

double Rectangle::getHitboxRadius() const
{
   return std::sqrt((width / 2) * (width / 2) + (height / 2) * (height / 2));
}

bool Rectangle::collideWith(Object* other)
{
   return other->collideWith(this);
}

bool Rectangle::collideWith(Rectangle* other)
{
   return collisions::collide(this, other);
}

bool Rectangle::collideWith(Circle* other)
{
   return collisions::collide(this, other);
}

Circle::Circle(double x, double y, double radius, double mass)
   : Base(x, y, mass), radius{ radius }
{}

int Circle::getWrapperWidth() const
{
   return metersToPixels(radius * 2);
}

int Circle::getWrapperHeight() const
{
   return metersToPixels(radius * 2);
}

double Circle::getHitboxRadius() const
{
   return radius;
}

bool Circle::collideWith(Object* other)
{
   return other->collideWith(this);
}

bool Circle::collideWith(Rectangle* other)
{
   return collisions::collide(other, this);
}

bool Circle::collideWith(Circle* other)
{
   return collisions::collide(this, other);
}
