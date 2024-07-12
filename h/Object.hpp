#pragma once

#include <SDL_rect.h>
#include <Vector2D.hpp>

class Object
{
public:
   Object(double x, double y, double width, double height, double mass);

   SDL_Rect* getView();

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

private:
   void updateView();
   SDL_Rect view;
};