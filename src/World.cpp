#include <engine/World.hpp>

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

void World::addObject(std::unique_ptr<Object> object)
{
   SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, object->getTextureWidth(), object->getTextureHeight());
   object->texture = texture;
   object->fillTexture(renderer);
   objects.push_back(std::move(object));
}

void World::start()
{  
   while (true)
   {
      clear(renderer);
      applyForces();
      for (auto& obj : objects)
      {
         drawObject(renderer, obj.get());
      }

      int ticks = 50;

      double timeFactor = 1;
      double tickTime = frameTimeInterval / (1000 * (double)ticks);
      tickTime *= timeFactor;

      for (int i = 0; i < ticks; ++i)
      {
         for (auto& obj : objects)
         {
            obj->applyAcceleration(tickTime);
            obj->applySpeed(tickTime);
         }
         checkCollisions();
      }

      SDL_Delay(frameTimeInterval);
      SDL_RenderPresent(renderer);
   }
}

void World::applyForces()
{
   for (auto& obj : objects)
   {
      Vector2D sumForceValue;
      for (const auto& force : obj->forces)
      {
         sumForceValue += force.value;
      }
      Vector2D acceleration = (1. / obj->mass) * sumForceValue;
      obj->setAcceleration(acceleration);
   }
}

void World::checkCollisions()
{
   size_t n = objects.size();
   for (int objIndex1 = 0; objIndex1 < n; ++objIndex1)
   {
      for (int objIndex2 = objIndex1 + 1; objIndex2 < n; ++objIndex2)
      {
         auto* obj1 = objects[objIndex1].get();
         auto* obj2 = objects[objIndex2].get();
         
         bool haveCollided = false;
         if (obj1->canCollideWith(obj2))
         {
            haveCollided = obj1->collideWith(obj2);
         }

         if (!haveCollided)
         {
            // Remove "support reaction" forces between obj1 and obj2 
         }
      }
   }
}
