#pragma once

#include <SDL.h>
#include <math/Vector2D.hpp>
#include <misc/Colors.hpp>
#include <optional>

#include <engine/Object.fwd.hpp>

class Object
{
public:
   Object(double x, double y, double mass);
   virtual ~Object();

   virtual void fillTexture(SDL_Renderer*) = 0;
   SDL_Rect* getTextureHandle(bool update = true);

   virtual int getTextureWidth() const = 0;
   virtual int getTextureHeight() const = 0;

   void move(Vector2D shift);
   void applySpeed(double time); 
   void applyAcceleration(double time); 

   void setFixed(bool val);
   bool isFixed() const;
   
   Vector2D getSpeed() const;
   void setSpeed(Vector2D val);

   Vector2D getAcceleration() const;
   void setAcceleration(Vector2D val);
   
   double getDistanceInMeters(Object* other);
   // Hitbox circle is a Shape-specific circular hitbox used to quickly evaluate if a collision can occur between two objects
   // Returns squared value to avoid sqrt
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

   // should be set before filling texture for now
   Color color;

   SDL_Texture* texture = nullptr;
protected:
   void updateHandle();

   SDL_Rect textureHandle{};

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

   void fillTexture(SDL_Renderer*) override;
   int getTextureWidth() const override;
   int getTextureHeight() const override;

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

   void fillTexture(SDL_Renderer*) override;
   int getTextureWidth() const override;
   int getTextureHeight() const override;

   double getHitboxRadius() const override;

   bool collideWith(Object*) override;
   bool collideWith(Rectangle*) override;
   bool collideWith(Circle*) override;

public:
   double radius{}; // in meters
};