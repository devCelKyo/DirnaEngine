#pragma once

#include <SDL_pixels.h>

enum class Color
{
   Blue,
   Red,
   Green,
   Black
};

SDL_Color getColor(Color);

inline SDL_Color getColor(Color color)
{
   switch (color)
   {
      case Color::Blue:
         return SDL_Color{ 0, 0, 255, 255 };
      case Color::Red:
         return SDL_Color{ 255, 0, 0, 255 };
      case Color::Green:
         return SDL_Color{ 0, 255, 0, 255 };
      case Color::Black:
         return SDL_Color{ 0, 0, 0, 255 };
      default:
         return SDL_Color{ 0, 0, 0, 255 };
   }
}