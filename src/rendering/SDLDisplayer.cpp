#include <rendering/SDLDisplayer.hpp>
#include <engine/Object.hpp>

namespace rendering {

SDLDisplayer::SDLDisplayer(SDL_Renderer* renderer) : renderer{ renderer }
{}

void SDLDisplayer::onStartIteration()
{
   Uint8 r; Uint8 g; Uint8 b; Uint8 a;
   SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
   SDL_RenderClear(renderer);
   SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void SDLDisplayer::onEndIteration()
{
   SDL_RenderPresent(renderer);
}

void SDLDisplayer::registerObject(Object* obj)
{
   SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, obj->getTextureWidth(), obj->getTextureHeight());
   obj->texture = texture;
   obj->fillTexture(renderer);
}

void SDLDisplayer::drawObject(Object* obj)
{
   SDL_RenderCopy(renderer, obj->texture, nullptr, obj->getTextureHandle());
}

void SDLDisplayer::wait(int timeInMS)
{
   SDL_Delay(timeInMS);
}

} // namespace rendering