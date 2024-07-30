#include <SDL.h>
#include <engine/World.hpp>
#include <engine/Object.hpp>
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

   auto circle = std::make_unique<Circle>(12, 3, 0.3, 5);
   circle->speed = Vector2D{ 45, 0 };

   auto circle2 = std::make_unique<Circle>(17, 3, 0.3, 5);
   circle2->speed = Vector2D{ 11, -2 };
   circle2->color = Color::Blue;

   //Rectangle fixed{ 13, 15, 20, 1.5, 5 };
   //fixed.setFixed(true);
   //fixed.color = Color::Black;

   //Rectangle fixed2{ 3, 11, 1.5, 20, 5};
   //fixed2.setFixed(true);
   //fixed2.color = Color::Black;

   //Rectangle fixed3{ 22, 11, 1.5, 20, 5 };
   //fixed3.setFixed(true);
   //fixed3.color = Color::Black;

   //Rectangle fixed4{ 13, 5, 1.5, 1.5, 5 };
   //fixed4.setFixed(true);
   //fixed4.color = Color::Black;

   //Rectangle fixed5{ 5, 8, 1.5, 1.5, 5 };
   //fixed5.setFixed(true);
   //fixed5.color = Color::Black;

   //Rectangle fixed6{ 19, 7.5, 1.5, 1.5, 5 };
   //fixed6.setFixed(true);
   //fixed6.color = Color::Black;

   //Rectangle fixed7{ 13, 1, 20, 1.5, 5 };
   //fixed7.setFixed(true);
   //fixed7.color = Color::Black;

   world.addObject(std::move(circle));
   world.addObject(std::move(circle2));

   //world.addObject(&fixed);
   //world.addObject(&fixed2);
   //world.addObject(&fixed3);
   //world.addObject(&fixed4);
   //world.addObject(&fixed5);
   //world.addObject(&fixed6);
   //world.addObject(&fixed7);
   world.start();

   keepWindow();

   return 0;
}
