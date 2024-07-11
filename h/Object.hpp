#pragma once

#include <SDL_rect.h>

class Object
{
public:
   Object(int x, int y, int width, int height, double mass);

   SDL_Rect* getView();

   double mass;

   int x;
   int y;
   int width;
   int height;

private:
   void updateView();
   SDL_Rect view;
};