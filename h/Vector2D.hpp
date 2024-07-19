#pragma once

#include <cmath>

class Vector2D
{
public:
   Vector2D();
   Vector2D(double x, double y);
   Vector2D(const Vector2D& a, const Vector2D& b); // vector AB 

   double getNorm() const;
   double getNorm2() const;
   
   friend Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);
   friend Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs);

   friend Vector2D operator*(const Vector2D& lhs, const double rhs);
   friend Vector2D operator*(const double lhs, const Vector2D& rhs);
   friend double operator*(const Vector2D& lhs, const Vector2D& rhs); // dot product

   friend Vector2D& operator+=(Vector2D& lhs, const Vector2D& rhs);

public:
   double x{};
   double y{};
};

inline Vector2D::Vector2D() : x{0}, y{0}
{}

inline Vector2D::Vector2D(double x, double y) : x{x}, y{y}
{}

inline Vector2D::Vector2D(const Vector2D& a, const Vector2D& b) : x{ b.x - a.x }, y{ b.y - a.y }
{}


inline double Vector2D::getNorm() const
{
   return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

inline double Vector2D::getNorm2() const
{
   return std::pow(x, 2) + std::pow(y, 2);
}

inline Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs)
{
   return Vector2D(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector2D& operator+=(Vector2D& lhs, const Vector2D& rhs)
{
   lhs = lhs + rhs;
   return lhs;
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

inline double operator*(const Vector2D& lhs, const Vector2D& rhs)
{
   return lhs.x * rhs.x + lhs.y + rhs.y;
}


