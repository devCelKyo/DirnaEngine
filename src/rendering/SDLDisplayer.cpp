#include <rendering/SDLDisplayer.hpp>
#include <physics/Units.hpp>
#include <engine/Object.hpp>

namespace rendering {

SDLDisplayer::SDLDisplayer(SDL_Renderer* renderer) : renderer{ renderer }
{}

void SDLDisplayer::onStartIteration()
{
   Uint8 r; Uint8 g; Uint8 b; Uint8 a;
   SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
   SDL_RenderClear(renderer);
   SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void SDLDisplayer::onEndIteration()
{
   SDL_RenderPresent(renderer);
}

void SDLDisplayer::registerObject(std::variant<Rectangle*, Circle*> obj)
{
   SDL_Texture* texture = std::visit(SDLTextureBuilder{renderer}, obj);
   
   SDL_Rect handle;
   auto objectPtr = std::visit([&](Object* object) {return object; }, obj);

   int width = objectPtr->getWrapperWidth();
   int height = objectPtr->getWrapperHeight();
   handle.w = width;
   handle.h = height;
   handle.x = metersToPixels(objectPtr->x) - static_cast<int>(width / 2.);
   handle.y = metersToPixels(objectPtr->y) - static_cast<int>(height / 2.);
   
   TextureAndHandle th{ texture, handle};
   textures.insert({ objectPtr, th });
}

void SDLDisplayer::drawObject(Object* obj)
{
   auto pair = textures.find(obj);
   if (pair != textures.end())
   {
      SDL_Rect handle = pair->second.rect;
      handle.x = metersToPixels(obj->x) - static_cast<int>(obj->getWrapperWidth() / 2.);
      handle.y = metersToPixels(obj->y) - static_cast<int>(obj->getWrapperHeight() / 2.);
      SDL_RenderCopy(renderer, pair->second.texture, nullptr, &handle);
   }
}

void SDLDisplayer::wait(int timeInMS)
{
   SDL_Delay(timeInMS);
}

//////////////////////////
// Texture filling code //
//////////////////////////

SDL_Texture* SDLTextureBuilder::operator()(const Rectangle* rectangle)
{
   SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, metersToPixels(rectangle->width), metersToPixels(rectangle->height));
   
   auto colorStruct = getColor(rectangle->color);
   SDL_SetRenderDrawColor(renderer, colorStruct.r, colorStruct.g, colorStruct.b, colorStruct.a);
   SDL_SetRenderTarget(renderer, texture);
   SDL_RenderFillRect(renderer, nullptr);
   SDL_SetRenderTarget(renderer, nullptr);
   return texture;
}

static void SDLDrawPointCircleFourSymmetry(SDL_Renderer* renderer, int radius, int x, int y)
{
   int twoRadius = 2 * radius;
   SDL_RenderDrawPoint(renderer, x, y);
   SDL_RenderDrawPoint(renderer, twoRadius - x, y);
   SDL_RenderDrawPoint(renderer, twoRadius - x, twoRadius - y);
   SDL_RenderDrawPoint(renderer, x, twoRadius - y);
}

SDL_Texture* SDLTextureBuilder::operator()(const Circle* circle)
{
   const int pixelRadius = metersToPixels(circle->radius);
   SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pixelRadius * 2, pixelRadius * 2);

   SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
   auto colorStruct = getColor(circle->color);
   SDL_SetRenderDrawColor(renderer, colorStruct.r, colorStruct.g, colorStruct.b, colorStruct.a);
   SDL_SetRenderTarget(renderer, texture);

   Uint8 r; Uint8 g; Uint8 b; Uint8 a;
   SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
   SDL_RenderClear(renderer);
   SDL_SetRenderDrawColor(renderer, r, g, b, a);

   const int squaredRadius = pixelRadius * pixelRadius;
   for (int i = 0; i <= pixelRadius; ++i)
   {
      for (int j = 0; j <= pixelRadius; ++j)
      {
         int distX2 = static_cast<int>(std::pow(pixelRadius - i, 2));
         int distY2 = static_cast<int>(std::pow(pixelRadius - j, 2));
         if (distX2 + distY2 <= squaredRadius)
         {
            SDLDrawPointCircleFourSymmetry(renderer, pixelRadius, i, j);
         }
      }
   }
   SDL_SetRenderTarget(renderer, nullptr);
   return texture;
}

} // namespace rendering