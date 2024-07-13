#pragma once

#include <SDL.h>
#include <Vector2D.hpp>

class Object
{
public:
   Object(double x, double y, double width, double height, double mass);
   virtual ~Object();

   virtual void fillTexture(SDL_Renderer*) = 0;
   SDL_Rect* getTextureHandle(bool update = true);

   void move(Vector2D shift);
   void applySpeed(Uint32 time); 

   void setFixed(bool val);
   bool isFixed() const;
   
public:
   double mass;
   double x;
   double y;
   double width;
   double height;

   bool fixed{false};

   // vector in meters/s
   Vector2D speed;

   SDL_Texture* texture = nullptr;
private:
   void updateHandle();

   SDL_Rect textureHandle;
};

class Rectangle : public Object
{
   using Base = Object;
public:
   Rectangle(double x, double y, double width, double height, double mass);

   void fillTexture(SDL_Renderer*) override;
};

class Circle : public Object
{
   using Base = Object;
public:
   Circle(double x, double y, double radius, double mass);

   void fillTexture(SDL_Renderer*) override;
   double getRadius() const;
};