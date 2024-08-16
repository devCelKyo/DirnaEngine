#pragma once

#include <engine/World.hpp>

class WorldBuilder
{
public:
   WorldBuilder(std::unique_ptr<rendering::IDisplayer> displayer, int widthInPixels, int heightInPixels, int frameRateInFPS);

   WorldBuilder& withGravity(double value);
   
   WorldBuilder& withCircle(Vector2D coordinatesInMeters, double mass, double radius, Vector2D initialSpeed, Color color = Color::Red, bool isFixed = false);
   WorldBuilder& withRectangle(Vector2D coordinatesInMeters, double mass, Vector2D dimensions, Vector2D initialSpeed, Color color = Color::Red, bool isFixed = false);

   std::unique_ptr<World> buildWorld();

private:
   std::unique_ptr<World> world;
};