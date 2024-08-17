#pragma once

#include <engine/Object.hpp>
#include <rendering/IDisplayer.hpp>

#include <vector>
#include <memory>

class World
{
public:
   World(std::unique_ptr<rendering::IDisplayer> displayer);

   // rendering parameters
   World& setWidth(int val);
   World& setHeight(int val);
   World& setFrameRate(int val);

   rendering::IDisplayer* getDisplayer() const;

   // physics parameters
   World& setGravity(double val);

   void addObject(std::unique_ptr<Object>);
public:
   void start();
private:
   void applyForces();

   void checkCollisions();

private:
   std::unique_ptr<rendering::IDisplayer> displayer;

   std::vector<std::unique_ptr<Object>> objects;

   int width{};
   int height{};

   int frameRate{}; // in frames per second
   Uint32 frameTimeInterval{}; // in milliseconds

   double gravity{}; // constant g in m.s-2
};