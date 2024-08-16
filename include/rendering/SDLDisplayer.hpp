#pragma once

#include <rendering/IDisplayer.hpp>
#include <SDL.h>
#include <unordered_map>

namespace rendering {

class SDLDisplayer : public IDisplayer
{
public:
   explicit SDLDisplayer(SDL_Renderer*);

   void onStartIteration() override;
   void onEndIteration() override;

   void registerObject(Object*) override;
   void drawObject(Object*) override;
   void wait(int timeInMS) override;

private:
   SDL_Renderer* renderer;
   std::unordered_map<Object*, SDL_Texture*> textures;
};

} // namespace rendering