#include <World.hpp>

static void clear(SDL_Renderer* renderer)
{
   Uint8 r; Uint8 g; Uint8 b; Uint8 a;
   SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
   SDL_RenderClear(renderer);
   SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

static void drawObject(SDL_Renderer* renderer, Object& object)
{
   auto* view = object.getView();
   
   SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
   SDL_RenderFillRect(renderer, view);
   SDL_RenderPresent(renderer);
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

void World::addObject(Object object)
{
   objects.push_back(object);
}

void World::start()
{
   while (true)
   {
      for (auto& obj : objects)
      {
         clear(renderer);
         drawObject(renderer, obj);
         obj.applySpeed(frameTimeInterval);
         SDL_Delay(frameTimeInterval);
      }
   }
}