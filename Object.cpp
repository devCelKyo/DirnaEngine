#include <Object.hpp>

Object::Object(double x, double y, double width, double height, double mass) :
   x{ x }, y{ y }, width{ width }, height{ height }, mass{ mass }, speed{Vector2D{0,0}}
{
   updateView();
}

void Object::move(Vector2D shift)
{
   x += shift.x;
   y += shift.y;
}

void Object::applySpeed(Uint32 time)
{
   double ratio = time / 1000.;
   Vector2D shift{ speed.x * ratio, speed.y * ratio };
   move(shift);
}

void Object::updateView()
{
   view.x = static_cast<int>(x);
   view.y = static_cast<int>(y);
   view.w = static_cast<int>(width);
   view.h = static_cast<int>(height);
}

SDL_Rect* Object::getView()
{
   updateView();
   return &view;
}
