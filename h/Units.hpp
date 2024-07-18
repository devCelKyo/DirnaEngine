#pragma once

constexpr double pixelsByMeter = 25;

double pixelsToMeters(int pixels);
double pixelsToMeters(double pixels);

double metersToPixels(double meters);

Vector2D pixelsToMeters(Vector2D pixels);
Vector2D metersToPixels(Vector2D meters);

inline double pixelsToMeters(int pixels)
{
   return pixels / pixelsByMeter;
}

inline double pixelsToMeters(double pixels)
{
   return pixels / pixelsByMeter;
}

inline double metersToPixels(double meters)
{
   return meters * pixelsByMeter;
}

inline Vector2D pixelsToMeters(Vector2D pixels)
{
   return pixels * (1 / pixelsByMeter);
}

inline Vector2D metersToPixels(Vector2D meters)
{
   return meters * pixelsByMeter;
}