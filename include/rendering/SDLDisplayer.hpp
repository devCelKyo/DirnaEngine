#pragma once

#include <rendering/IDisplayer.hpp>
#include <SDL.h>
#include <unordered_map>

namespace rendering {

struct SDLTextureBuilder
{
   SDL_Renderer* renderer;

   SDL_Texture* operator()(const Rectangle*);
   SDL_Texture* operator()(const Circle*);
};

struct TextureAndHandle
{
   SDL_Texture* texture;
   SDL_Rect rect;
};

class SDLDisplayer : public IDisplayer
{
public:
   explicit SDLDisplayer(SDL_Renderer*);
   ~SDLDisplayer();

   void onStartIteration() override;
   void onEndIteration() override;

   void registerObject(std::variant<Rectangle*, Circle*>) override;
   void drawObject(Object*) override;
   void wait(int timeInMS) override;

private:
   SDL_Renderer* renderer;
   std::unordered_map<Object*, TextureAndHandle> textures;
};

} // namespace rendering