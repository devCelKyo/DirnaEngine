#include <Object.hpp>

Object::Object(double x, double y, double width, double height, double mass) :
   x{ x }, y{ y }, width{ width }, height{ height }, mass{ mass }, speed{Vector2D{0,0}}
{
   updateHandle();
}

Object::~Object()
{
   //SDL_DestroyTexture(texture);
   // let's figure out proper ownership first
}


void Object::fillTexture(SDL_Renderer* renderer)
{
   SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
   SDL_SetRenderTarget(renderer, texture);
   SDL_RenderFillRect(renderer, nullptr);
   SDL_SetRenderTarget(renderer, nullptr);
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

void Object::updateHandle()
{
   textureHandle.x = static_cast<int>(x);
   textureHandle.y = static_cast<int>(y);
   textureHandle.w = static_cast<int>(width);
   textureHandle.h = static_cast<int>(height);
}

SDL_Rect* Object::getTextureHandle(bool update)
{
   if (update)
   {
      updateHandle();
   }
   return &textureHandle;
}
