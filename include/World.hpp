#pragma once

#include <vector>
#include <SDL.h>
#include <Object.hpp>

class World
{
public:
   World(SDL_Renderer* renderer);

   // rendering parameters
   World& setWidth(int val);
   World& setHeight(int val);
   World& setFrameRate(int val);

   // physics parameters
   World& setGravity(double val);

   void addObject(Object*);
   void start();

private:
   void applyForces();

   void checkCollisions();

private:
   std::vector<Object*> objects;
   SDL_Renderer* renderer;

   int width{};
   int height{};

   int frameRate{}; // in frames per second
   Uint32 frameTimeInterval{}; // in milliseconds

   double gravity{}; // constant g in m.s-2
};