#include <Object.hpp>
#include <Units.hpp>
#include <Collisions.hpp>

Object::Object(double x, double y, double mass) :
   x{ x }, y{ y }, mass{ mass }, color{Color::Red}
{}

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

   auto shift = acceleration * (time / 1000.);
   speed += shift;
}

void Object::setFixed(bool val) { fixed = val; }

bool Object::isFixed() const { return fixed; }

double Object::getDistance2InMeters(Object* other)
{
   double xDiff = pixelsToMeters(x - other->x);
   double yDiff = pixelsToMeters(y - other->y);
   return xDiff * xDiff + yDiff * yDiff;
}

bool Object::canCollideWith(Object* other)
{
   const double distance2 = getDistance2InMeters(other);
   const double radiuses2 = getHitboxRadius2() + other->getHitboxRadius2();
   
   return distance2 <= radiuses2;
}

void Object::updateHandle()
{
   textureHandle.x = static_cast<int>(x - getTextureWidth() / 2.);
   textureHandle.y = static_cast<int>(y - getTextureHeight() / 2.);
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
   : Base(x, y, mass), width{width}, height{height}
{
   textureHandle.w = getTextureWidth();
   textureHandle.h = getTextureHeight();
   updateHandle();
}

void Rectangle::fillTexture(SDL_Renderer* renderer)
{
   auto colorStruct = getColor(color);
   SDL_SetRenderDrawColor(renderer, colorStruct.r, colorStruct.g, colorStruct.b, colorStruct.a);
   SDL_SetRenderTarget(renderer, texture);
   SDL_RenderFillRect(renderer, nullptr);
   SDL_SetRenderTarget(renderer, nullptr);
}

int Rectangle::getTextureWidth() const
{
   return static_cast<int>(width);
}

int Rectangle::getTextureHeight() const
{
   return static_cast<int>(height);
}

double Rectangle::getHitboxRadius2() const
{
   return (width / 2) * (width / 2) + (height / 2) * (height / 2);
}

void Rectangle::collideWith(Object* other)
{
   other->collideWith(this);
}

void Rectangle::collideWith(Rectangle* other)
{
   collisions::collide(this, other);
}

void Rectangle::collideWith(Circle* other)
{
   collisions::collide(this, other);
}

Circle::Circle(double x, double y, double radius, double mass)
   : Base(x, y, mass), radius{ radius }
{
   textureHandle.w = getTextureWidth();
   textureHandle.h = getTextureHeight();
   updateHandle();
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

int Circle::getTextureWidth() const
{
   return static_cast<int>(radius * 2);
}

int Circle::getTextureHeight() const
{
   return static_cast<int>(radius * 2);
}

double Circle::getHitboxRadius2() const
{
   return radius * radius;
}

void Circle::collideWith(Object* other)
{
   other->collideWith(this);
}

void Circle::collideWith(Rectangle* other)
{
   collisions::collide(other, this);
}

void Circle::collideWith(Circle* other)
{
   collisions::collide(this, other);
}
