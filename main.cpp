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

   Circle circle{ 12, 3, 0.3, 5 };
   circle.speed = Vector2D{ 40, 0 };

   Circle circle2{ 17, 3, 0.3, 5 };
   circle2.speed = Vector2D{ 36, -2 };
   circle2.color = Color::Blue;

   Rectangle fixed{ 13, 15, 20, 1.5, 5 };
   fixed.setFixed(true);
   fixed.color = Color::Black;

   Rectangle fixed2{ 3, 11, 1.5, 20, 5};
   fixed2.setFixed(true);
   fixed2.color = Color::Black;

   Rectangle fixed3{ 22, 11, 1.5, 20, 5 };
   fixed3.setFixed(true);
   fixed3.color = Color::Black;

   world.addObject(&circle);
   world.addObject(&circle2);

   world.addObject(&fixed);
   world.addObject(&fixed2);
   world.addObject(&fixed3);
   world.start();

   keepWindow();

   return 0;
}
