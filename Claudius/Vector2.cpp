#include "Vector2.h"
#include <cmath>

// Constructors
constexpr Vector2::Vector2(float x, float y) noexcept
	: x(x), y(y) 
{
}

// Addition Assignment
Vector2& Vector2::operator+=(const Vector2& rhs) noexcept
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

// Addition
Vector2 operator+(Vector2 lhs, const Vector2& rhs) noexcept // Passing lhs by value helps optimize chained a+b+c. Otherwise, both parameters may be const references.
{
	lhs += rhs; // reuse addition assignment
	return lhs; // return the result by value (uses move constructor)
}

// Subtraction Assignment
Vector2& Vector2::operator-=(const Vector2& rhs) noexcept
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

// Subtraction
Vector2 operator-(Vector2 lhs, const Vector2& rhs) noexcept // Passing lhs by value helps optimize chained a+b+c. Otherwise, both parameters may be const references.
{
	lhs -= rhs; // reuse subtraction assignment
	return lhs; // return the result by value (uses move constructor)
}

// Multiplication Assignment
Vector2& Vector2::operator*=(const Vector2& rhs) noexcept
{
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

Vector2& Vector2::operator*=(const float& rhs) noexcept
{
	x *= rhs;
	y *= rhs;
	return *this;
}

// Multiplication
Vector2 operator*(Vector2 lhs, const Vector2& rhs) noexcept // Passing lhs by value helps optimize chained a+b+c. Otherwise, both parameters may be const references.
{
	lhs *= rhs; // reuse multiplication assignment
	return lhs; // return the result by value (uses move constructor)
}

Vector2 operator*(Vector2 lhs, const float& rhs) noexcept
{
	lhs *= rhs;
	return lhs;
}

Vector2 operator*(const float& lhs, Vector2 rhs) noexcept
{
	rhs *= lhs;
	return rhs;
}

// Division Assignment
Vector2& Vector2::operator/=(const Vector2& rhs) noexcept
{
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

Vector2& Vector2::operator/=(const float& rhs) noexcept
{
	x /= rhs;
	y /= rhs;
	return *this;
}

// Division
Vector2 operator/(Vector2 lhs, const Vector2& rhs) noexcept // Passing lhs by value helps optimize chained a+b+c. Otherwise, both parameters may be const references.
{
	lhs /= rhs; // reuse division assignment
	return lhs; // return the result by value (uses move constructor)
}

Vector2 operator/(Vector2 lhs, const float& rhs) noexcept
{
	lhs /= rhs;
	return lhs;
}

Vector2 operator/(const float& lhs, Vector2 rhs) noexcept
{
	rhs /= lhs;
	return rhs;
}

// Comparison Operators
bool Vector2::operator==(const Vector2& rhs) const noexcept
{
	return (this->x == rhs.x && this->y == rhs.y);
}

bool Vector2::operator!=(const Vector2& rhs) const noexcept
{
	return !(*this == rhs);
}

// User-defined methods
Vector2 Vector2::perpendicular() const
{
	return Vector2(-y, x); // 90 degrees to the right
}

Vector2 Vector2::unit() const
{
	Vector2 result(*this); 
	result.normalize(); 
	return result;
}

float Vector2::length() const
{
	return sqrtf(x * x + y * y);
}

float Vector2::length_squared() const
{
	return x * x + y * y;
}

float Vector2::dot(const Vector2& rhs) const
{
	return x * rhs.x + y * rhs.y;
}

float Vector2::cross(const Vector2& rhs) const
{
	return x * rhs.y - y * rhs.x;
}

void Vector2::normalize()
{
	float len = length(); 
	if (len <= 0.0f) return;
	x /= len; 
	y /= len;
}
