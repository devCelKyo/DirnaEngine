#include <SDL.h>
#include <World.hpp>
#include <Object.hpp>
#include <memory>

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

constexpr int frameRate = 30; // fps

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

   World world(r);
   world.setWidth(SCREEN_WIDTH).setHeight(SCREEN_HEIGHT).setFrameRate(frameRate);

   Rectangle rect{200, 200, 30, 30, 5};
   rect.speed = Vector2D{ 2, 1 };

   Circle circle{ 300, 300, 20, 5 };
   circle.speed = Vector2D{ -1, -0.5 };

   Rectangle fixed{ 320, 440, 500, 30, 5 };

   world.addObject(&rect);
   world.addObject(&circle);
   world.addObject(&fixed);
   world.start();

   keepWindow();

   return 0;
}
