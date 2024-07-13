#include <World.hpp>

static void clear(SDL_Renderer* renderer)
{
   Uint8 r; Uint8 g; Uint8 b; Uint8 a;
   SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
   SDL_RenderClear(renderer);
   SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

static void drawObject(SDL_Renderer* renderer, Object* object)
{
   SDL_RenderCopy(renderer, object->texture, nullptr, object->getTextureHandle());
}

World::World(SDL_Renderer* r) : renderer{r}
{}

World& World::setWidth(int val) { width = val; return *this; }
World& World::setHeight(int val) { height = val; return *this; }
World& World::setFrameRate(int val)
{
   frameRate = val;
   frameTimeInterval = 1000 / frameRate;
   return *this;
}

void World::addObject(Object* object)
{
   SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, static_cast<int>(object->width), static_cast<int>(object->height));
   object->texture = texture;
   object->fillTexture(renderer);
   objects.push_back(object);
}

void World::start()
{  
   while (true)
   {
      clear(renderer);
      for (auto* obj : objects)
      {
         drawObject(renderer, obj);
         obj->applySpeed(frameTimeInterval);
      }
      SDL_Delay(frameTimeInterval);
      SDL_RenderPresent(renderer);
   }
}