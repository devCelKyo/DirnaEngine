#pragma once

#include <rendering/IDisplayer.hpp>

namespace rendering {

class SDLDisplayer : public IDisplayer
{
public:
   void onStartIteration() override;
   void onEndIteration() override;

   void drawObject(Object*) override;
   void wait(int timeInMS) override;
};

} // namespace rendering