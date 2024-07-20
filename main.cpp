#include <SDL.h>
#include <World.hpp>
#include <Object.hpp>
#include <memory>

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

constexpr int frameRate = 165; // fps

static void keepWindow()
{
   SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
}

int main(int argc, char* args[])
{
   SDL_Window* w = nullptr;
   SDL_Renderer* r = nullptr;

   SDL_Init(SDL_INIT_VIDEO);
   SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &w, &r);
   SDL_Delay(500);

   World world(r);
   world.setWidth(SCREEN_WIDTH).setHeight(SCREEN_HEIGHT).setFrameRate(frameRate)
        .setGravity(9.79);

   Circle circle{ 300, 300, 20, 5 };
   circle.speed = Vector2D{ 3, -5 };

   Circle circle2{ 100, 300, 20, 5 };
   circle2.speed = Vector2D{ 1, -5 };

   Circle circle3{ 200, 300, 20, 5 };
   circle3.speed = Vector2D{ 2, -5 };

   Rectangle fixed{ 320, 440, 500, 30, 5 };
   fixed.setFixed(true);
   fixed.color = Color::Black;

   world.addObject(&circle);
   world.addObject(&circle2);
   world.addObject(&circle3);
   world.addObject(&fixed);
   world.start();

   keepWindow();

   return 0;
}
