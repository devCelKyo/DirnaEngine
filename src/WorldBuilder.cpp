#include <engine/WorldBuilder.hpp>

WorldBuilder::WorldBuilder(std::unique_ptr<rendering::IDisplayer> displayer, int widthInPixels, int heightInPixels, int frameRateInFPS)
{
   world = std::make_unique<World>(std::move(displayer));
   world->setWidth(widthInPixels).setHeight(heightInPixels).setFrameRate(frameRateInFPS);
}

WorldBuilder& WorldBuilder::withGravity(double value)
{
   world->setGravity(value);
   return *this;
}

WorldBuilder& WorldBuilder::withCircle(Vector2D coordinatesInMeters, double mass, double radius, Vector2D initialSpeed, Color color, bool isFixed)
{
   auto circle = std::make_unique<Circle>(coordinatesInMeters.x, coordinatesInMeters.y, radius, mass);
   circle->setSpeed(initialSpeed);
   circle->color = color;
   circle->setFixed(isFixed);
   world->addObject(std::move(circle));
   return *this;
}

WorldBuilder& WorldBuilder::withRectangle(Vector2D coordinatesInMeters, double mass, Vector2D dimensions, Vector2D initialSpeed, Color color, bool isFixed)
{
   // Coordinates of the top left corner to make it easier
   double centerX = coordinatesInMeters.x + dimensions.x / 2.;
   double centerY = coordinatesInMeters.y + dimensions.y / 2.;
   auto rectangle = std::make_unique<Rectangle>(centerX, centerY, dimensions.x, dimensions.y, mass);
   rectangle->setSpeed(initialSpeed);
   rectangle->color = color;
   rectangle->setFixed(isFixed);
   world->addObject(std::move(rectangle));
   return *this;
}

std::unique_ptr<World> WorldBuilder::buildWorld()
{
   return std::move(world);
}