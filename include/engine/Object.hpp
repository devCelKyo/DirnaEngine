#pragma once

#include <SDL.h>
#include <math/Vector2D.hpp>
#include <misc/Colors.hpp>
#include <optional>

#include <engine/Object.fwd.hpp>

#include <physics/Force.hpp>

class Object
{
public:
   Object(double x, double y, double mass);
   virtual ~Object();

   void move(Vector2D shift);
   void applySpeed(double time); 
   void applyAcceleration(double time); 

   void setFixed(bool val);
   bool isFixed() const;
   
   Vector2D getSpeed() const;
   void setSpeed(Vector2D val);

   Vector2D getAcceleration() const;
   void setAcceleration(Vector2D val);

   virtual int getWrapperWidth() const = 0;
   virtual int getWrapperHeight() const = 0;

   double getDistanceInMeters(Object* other);
   // Hitbox circle is a Shape-specific circular hitbox used to quickly evaluate if a collision can occur between two objects
   // Returns squared value to avoid having to evaluate sqrt
   virtual double getHitboxRadius() const = 0;
   bool canCollideWith(Object*);

   virtual bool collideWith(Object*) = 0;
   virtual bool collideWith(Rectangle*) = 0;
   virtual bool collideWith(Circle*) = 0;
   
public:
   double mass;
   double x; // in meters
   double y; // in meters

   bool fixed{false};

   Color color;

   physics::ForceSet forces;

private:
   // vector in meters/s
   Vector2D speed;
   // vector in meters/s-2
   Vector2D acceleration;
};

class Rectangle : public Object
{
   using Base = Object;
public:
   Rectangle(double x, double y, double width, double height, double mass);

   int getWrapperWidth() const override;
   int getWrapperHeight() const override;

   double getHitboxRadius() const override;

   bool collideWith(Object*) override;
   bool collideWith(Rectangle*) override;
   bool collideWith(Circle*) override;

public:
   double width{}; // in meters
   double height{}; // in meters
};

class Circle : public Object
{
   using Base = Object;
public:
   Circle(double x, double y, double radius, double mass);

   int getWrapperWidth() const override;
   int getWrapperHeight() const override;

   double getHitboxRadius() const override;

   bool collideWith(Object*) override;
   bool collideWith(Rectangle*) override;
   bool collideWith(Circle*) override;

public:
   double radius{}; // in meters
};