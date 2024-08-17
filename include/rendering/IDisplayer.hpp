#pragma once

#include <engine/Object.fwd.hpp>
#include <variant>

namespace rendering {

class IDisplayer {
public:
   virtual void onStartIteration() = 0;
   virtual void onEndIteration() = 0;

   virtual void registerObject(std::variant<Rectangle*, Circle*>) = 0;
   virtual void drawObject(Object*) = 0;
   virtual void wait(int timeInMS) = 0;
};

} // namespace rendering