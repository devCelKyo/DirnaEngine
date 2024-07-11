#include <SDL.h>
#include <Object.hpp>

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

constexpr int frameRate = 160; // fps
constexpr double frameTimeInterval = 1000 * (1. / frameRate); // in milliseconds

static void keepWindow()
{
	SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
}

static void clear(SDL_Renderer* renderer)
{
	Uint8 r; Uint8 g; Uint8 b; Uint8 a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

int main(int argc, char* args[])
{
	SDL_Window* w = nullptr;
	SDL_Renderer* r = nullptr;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &w, &r);

	SDL_Rect rect{ 200, 200, 15, 75 };
	while (true)
	{
		clear(r);
		SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
		SDL_RenderFillRect(r, &rect);
		SDL_RenderPresent(r);

		rect.x += 5;
		if (rect.x > SCREEN_WIDTH)
			rect.x = 0;
		SDL_Delay(frameTimeInterval);
	}
	keepWindow();

	return 0;
}
