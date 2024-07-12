#pragma once

#include <vector>
#include <SDL.h>
#include <Object.hpp>

class World
{
public:
   World(SDL_Renderer* renderer);

   World& setWidth(int val);
   World& setHeight(int val);
   World& setFrameRate(int val);

   void addObject(Object);
   void start();

private:
   std::vector<Object> objects;
   SDL_Renderer* renderer;

   int width{};
   int height{};

   int frameRate{}; // in frames per second
   Uint32 frameTimeInterval{}; // in milliseconds
};