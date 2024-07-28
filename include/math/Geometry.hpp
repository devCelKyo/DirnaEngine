#pragma once

#include <math/Vector2D.hpp>
#include <array>
#include <engine/Object.hpp>

namespace geometry {

struct Segment
{
   Vector2D a; // base point
   Vector2D u; // segment vector
};

std::array<Segment, 4> getRectangleSides(const Rectangle& rectangle);

double getDistance(const Vector2D& point, const Segment& segment);

} // namespace geometry