#pragma once

#include <SDL.h>
#include <Vector2D.hpp>

class Object
{
public:
   Object(double x, double y, double width, double height, double mass);
   ~Object();

   void fillTexture(SDL_Renderer*);
   SDL_Rect* getTextureHandle(bool update = true);

   void move(Vector2D shift);
   void applySpeed(Uint32 time); 
   
public:
   double mass;
   double x;
   double y;
   double width;
   double height;

   // vector in pixel/s
   Vector2D speed;

   SDL_Texture* texture = nullptr;
private:
   void updateHandle();

   SDL_Rect textureHandle;
};