#pragma once

#include <SDL.h>
#include <Vector2D.hpp>
#include <Colors.hpp>
#include <optional>

#include <Object.fwd.hpp>

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
   void applySpeed(Uint32 time); 
   void applyAcceleration(Uint32 time); 

   void setFixed(bool val);
   bool isFixed() const;

   double getDistance2InMeters(Object* other);

   // Hitbox circle is a Shape-specific circular hitbox used to quickly evaluate if a collision can occur between two objects
   // Returns squared value to avoid sqrt
   virtual double getHitboxRadius2() const = 0;
   bool canCollideWith(Object*);

   virtual void collideWith(Object*) = 0;
   virtual void collideWith(Rectangle*) = 0;
   virtual void collideWith(Circle*) = 0;
   
public:
   double mass;
   double x;
   double y;

   bool fixed{false};

   // should be set before filling texture for now
   Color color;

   // vector in meters/s
   Vector2D speed;
   // vector in meters/s-2
   Vector2D acceleration;

   SDL_Texture* texture = nullptr;
protected:
   void updateHandle();

   SDL_Rect textureHandle{};
};

class Rectangle : public Object
{
   using Base = Object;
public:
   Rectangle(double x, double y, double width, double height, double mass);

   void fillTexture(SDL_Renderer*) override;
   int getTextureWidth() const override;
   int getTextureHeight() const override;

   double getHitboxRadius2() const override;

   void collideWith(Object*) override;
   void collideWith(Rectangle*) override;
   void collideWith(Circle*) override;

public:
   double width{};
   double height{};

private:
   std::optional<double> cachedRadius2;
};

class Circle : public Object
{
   using Base = Object;
public:
   Circle(double x, double y, double radius, double mass);

   void fillTexture(SDL_Renderer*) override;
   int getTextureWidth() const override;
   int getTextureHeight() const override;

   double getHitboxRadius2() const override;

   void collideWith(Object*) override;
   void collideWith(Rectangle*) override;
   void collideWith(Circle*) override;

public:
   double radius{};

private:
   std::optional<double> cachedRadius2;
};