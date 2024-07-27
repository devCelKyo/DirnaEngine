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

World& World::setGravity(double val) { gravity = val; return *this; }

void World::addObject(Object* object)
{
   SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, object->getTextureWidth(), object->getTextureHeight());
   object->texture = texture;
   object->fillTexture(renderer);
   objects.push_back(object);
}

void World::start()
{  
   while (true)
   {
      clear(renderer);
      applyForces();

      for (auto* obj : objects)
      {
         drawObject(renderer, obj);
         Uint32 time = frameTimeInterval;
         obj->applyAcceleration(time);
         obj->applySpeed(time);
      }
      checkCollisions();
      SDL_Delay(frameTimeInterval);
      SDL_RenderPresent(renderer);
   }
}

void World::applyForces()
{
   for (auto* obj : objects)
   {
      obj->acceleration.y = gravity;
   }
}

void World::checkCollisions()
{
   size_t n = objects.size();
   for (int objIndex1 = 0; objIndex1 < n; ++objIndex1)
   {
      for (int objIndex2 = objIndex1 + 1; objIndex2 < n; ++objIndex2)
      {
         auto* obj1 = objects[objIndex1];
         auto* obj2 = objects[objIndex2];
         if (obj1->canCollideWith(obj2))
         {
            obj1->collideWith(obj2);
         }
      }
   }
}
