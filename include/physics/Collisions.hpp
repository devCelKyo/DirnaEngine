#pragma once
#include <engine/Object.hpp>

namespace collisions {
void collide(Rectangle*, Rectangle*);
void collide(Rectangle*, Circle*);
void collide(Circle*, Circle*);
} // namespace collisions
