#include <math/Geometry.hpp>
#include <algorithm>

namespace geometry {

std::array<Segment, 4> getRectangleSides(const Rectangle& rectangle)
{
   std::array<Segment, 4> sides;
   const double x = rectangle.x;
   const double y = rectangle.y;
   const double halfWidth = rectangle.width / 2;
   const double halfHeight = rectangle.height / 2;
   Vector2D widthSideVector(rectangle.width, 0);
   Vector2D heightSideVector(0, rectangle.height);

   sides[0] = Segment{ Vector2D(x - halfWidth, y - halfHeight), widthSideVector };
   sides[1] = Segment{ Vector2D(x + halfWidth, y - halfHeight), heightSideVector };
   sides[2] = Segment{ Vector2D(x + halfWidth, y + halfHeight), -1 * widthSideVector };
   sides[3] = Segment{ Vector2D(x - halfWidth, y + halfHeight), -1 * heightSideVector };
   return sides;
}

Vector2D getOrthogonalProjection(const Vector2D& point, const Segment& segment)
{
   Vector2D AP(segment.a, point);
   double t = (AP * segment.u) / segment.u.getNorm2();
   t = std::min(std::max(0., t), 1.);
   Vector2D projectedPoint = segment.a + segment.u * t;
   Vector2D orthogonalProjectionVector(point, projectedPoint);

   return orthogonalProjectionVector;
}

double getDistance(const Vector2D& point, const Segment& segment)
{
   return getOrthogonalProjection(point, segment).getNorm();
}



} // namespace geometry