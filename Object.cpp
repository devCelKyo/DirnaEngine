#include <Object.hpp>

Object::Object(int x, int y, int width, int height, double mass) :
   x{ x }, y{ y }, width{ width }, height{ height }, mass{ mass }
{
   view = SDL_Rect{ x, y, width, height };
}

void Object::updateView()
{
   view.x = x;
   view.y = y;
   view.w = width;
   view.h = height;
}

SDL_Rect* Object::getView()
{
   updateView();
   return &view;
}
