#include <engine/World.hpp>
#include <physics/Force.hpp>


World::World(std::unique_ptr<rendering::IDisplayer> displayer) : displayer{ std::move(displayer) }
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
   displayer->registerObject(object.get());

   physics::Force gravityForce{ physics::ForceType::Gravity, {0, object->mass * gravity}, nullptr };
   object->forces.add(gravityForce);
   objects.push_back(std::move(object));
}

void World::start()
{  
   while (true)
   {
      displayer->onStartIteration();
      for (auto& obj : objects)
      {
         displayer->drawObject(obj.get());
      }

      int ticks = 50;

      double timeFactor = 1;
      double tickTime = frameTimeInterval / (1000 * (double)ticks);
      tickTime *= timeFactor;

      for (int i = 0; i < ticks; ++i)
      {
         applyForces();
         for (auto& obj : objects)
         {
            obj->applyAcceleration(tickTime);
            obj->applySpeed(tickTime);
         }
         checkCollisions();
      }

      displayer->wait(frameTimeInterval);
      displayer->onEndIteration();
   }
}

void World::applyForces()
{
   for (auto& obj : objects)
   {
      physics::Force allForces = obj->forces.getSum();
      Vector2D acceleration = (1. / obj->mass) * allForces.value;
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
            obj1->forces.erase([&](const physics::Force& force) { return (force.type == physics::ForceType::SupportReaction and force.sourceObject == obj2); });
            obj2->forces.erase([&](const physics::Force& force) { return (force.type == physics::ForceType::SupportReaction and force.sourceObject == obj1); });
         }
      }
   }
}
