#include <Object.hpp>
#include <Units.hpp>

Object::Object(double x, double y, double width, double height, double mass) :
   x{ x }, y{ y }, width{ width }, height{ height }, mass{ mass }, color{Color::Red}
{
   textureHandle.w = static_cast<int>(width);
   textureHandle.h = static_cast<int>(height);
   updateHandle();
}

Object::~Object()
{
   SDL_DestroyTexture(texture);
}

void Object::move(Vector2D shift)
{
   x += shift.x;
   y += shift.y;
}

void Object::applySpeed(Uint32 time)
{
   if (isFixed())
      return;

   auto shift = metersToPixels(speed) * (time / 1000.);
   move(shift);
}

void Object::applyAcceleration(Uint32 time)
{
   if (isFixed())
      return;

   auto shift = metersToPixels(acceleration) * (time / 1000.);
   speed += shift;
}

void Object::setFixed(bool val) { fixed = val; }

bool Object::isFixed() const { return fixed; }

void Object::updateHandle()
{
   textureHandle.x = static_cast<int>(x - width / 2.);
   textureHandle.y = static_cast<int>(y - height / 2.);
}

SDL_Rect* Object::getTextureHandle(bool update)
{
   if (update)
   {
      updateHandle();
   }
   return &textureHandle;
}

Rectangle::Rectangle(double x, double y, double width, double height, double mass)
   : Base(x, y, width, height, mass)
{
}

void Rectangle::fillTexture(SDL_Renderer* renderer)
{
   auto colorStruct = getColor(color);
   SDL_SetRenderDrawColor(renderer, colorStruct.r, colorStruct.g, colorStruct.b, colorStruct.a);
   SDL_SetRenderTarget(renderer, texture);
   SDL_RenderFillRect(renderer, nullptr);
   SDL_SetRenderTarget(renderer, nullptr);
}

Circle::Circle(double x, double y, double radius, double mass)
   : Base(x, y, radius * 2, radius * 2, mass)
{
}

static void drawPointCircleFourSymmetry(SDL_Renderer* renderer, double radius, int x, int y)
{
   int twoRadius = static_cast<int>(2 * radius);
   SDL_RenderDrawPoint(renderer, x, y);
   SDL_RenderDrawPoint(renderer, twoRadius - x, y);
   SDL_RenderDrawPoint(renderer, twoRadius - x, twoRadius - y);
   SDL_RenderDrawPoint(renderer, x, twoRadius - y);
}

void Circle::fillTexture(SDL_Renderer* renderer)
{
   SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
   SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
   SDL_SetRenderTarget(renderer, texture);

   Uint8 r; Uint8 g; Uint8 b; Uint8 a;
   SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
   SDL_RenderClear(renderer);
   SDL_SetRenderDrawColor(renderer, r, g, b, a);
   
   const double radius = getRadius();
   const double squaredRadius = radius * radius;
   for (int i = 0; i <= radius; ++i)
   {
      for (int j = 0; j <= radius; ++j)
      {
         int distX2 = static_cast<int>(std::pow(radius - i, 2));
         int distY2 = static_cast<int>(std::pow(radius - j, 2));
         if (distX2 + distY2 <= squaredRadius)
         {
            drawPointCircleFourSymmetry(renderer, radius, i, j);
         }
      }
   }
   SDL_SetRenderTarget(renderer, nullptr);
}

double Circle::getRadius() const
{
   return width / 2.;
}

