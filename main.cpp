#include <SDL.h>
#include <engine/WorldBuilder.hpp>

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

constexpr int defaultFrameRate = 165;

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

   WorldBuilder wb(r, SCREEN_WIDTH, SCREEN_HEIGHT, defaultFrameRate);
   wb.withGravity(9.79)
      .withCircle({ 12, 3 }, 5, 0.3, { 45, 0 })
      .withCircle({ 17, 3 }, 5, 0.3, { 11, -2 }, Color::Blue)
      .withRectangle({ 5, 1 }, 5, { 1, 17 }, { 11, -2 }, Color::Black, true)
      .withRectangle({ 20, 1 }, 5, { 1, 17 }, { 11, -2 }, Color::Black, true)
      .withRectangle({ 5, 18 }, 5, { 16, 1 }, { 11, -2 }, Color::Black, true);

   auto world = wb.buildWorld();
   world->start();

   keepWindow();

   return 0;
}
