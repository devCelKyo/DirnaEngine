#pragma once

constexpr double pixelsByMeter = 25;

double pixelsToMeters(int pixels);
int metersToPixels(double meters);

inline double pixelsToMeters(int pixels)
{
   return pixels / pixelsByMeter;
}

inline int metersToPixels(double meters)
{
   return static_cast<int>(meters * pixelsByMeter);
}