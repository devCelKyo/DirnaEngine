#pragma once

#include <SDL.h>
#include <engine/Object.hpp>

#include <vector>
#include <memory>

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

   void addObject(std::unique_ptr<Object>);
   void start();

private:
   void applyForces();

   void checkCollisions();

private:
   std::vector<std::unique_ptr<Object>> objects;
   SDL_Renderer* renderer;

   int width{};
   int height{};

   int frameRate{}; // in frames per second
   Uint32 frameTimeInterval{}; // in milliseconds

   double gravity{}; // constant g in m.s-2
};