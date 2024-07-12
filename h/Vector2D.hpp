#pragma once

#include <cmath>

class Vector2D
{
public:
   Vector2D(double x, double y);

   double getNorm();
   
   friend Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);
   friend Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs);

   friend Vector2D operator*(const Vector2D& lhs, const double rhs);
   friend Vector2D operator*(const double lhs, const Vector2D& rhs);

private:
   double x;
   double y;
};

Vector2D::Vector2D(double x, double y) : x{x}, y{y}
{}

double Vector2D::getNorm()
{
   return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

inline Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs)
{
   return Vector2D(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs)
{
   return lhs + rhs * -1;
}

inline Vector2D operator*(const Vector2D& lhs, const double rhs)
{
   return Vector2D(lhs.x * rhs, lhs.y * rhs);
}

inline Vector2D operator*(const double lhs, const Vector2D& rhs)
{
   return rhs * lhs;
}


