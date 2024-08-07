#pragma once
#include <engine/Object.hpp>

namespace collisions {
bool collide(Rectangle*, Rectangle*);
bool collide(Rectangle*, Circle*);
bool collide(Circle*, Circle*);
} // namespace collisions
