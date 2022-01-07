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
	return std::fabsf(x - rhs.x) < std::numeric_limits<float>::epsilon()
		&& std::fabsf(y - rhs.y) < std::numeric_limits<float>::epsilon();
}

bool Vector2::operator!=(const Vector2& rhs) const noexcept
{
	return !(*this == rhs);
}

// Static functions
Vector2 Vector2::perpendicular(const Vector2& vector2) noexcept
{
	return { -vector2.y, vector2.x }; // 90 degrees to the right
}

float Vector2::length(const Vector2& vector2) noexcept
{
	return sqrtf(Vector2::length_squared(vector2));
}

float Vector2::length_squared(const Vector2& vector2) noexcept
{
	return vector2.x * vector2.x 
		+ vector2.y * vector2.y;
}

Vector2 Vector2::normalize(const Vector2& vector2) noexcept
{
	float length = Vector2::length(vector2);
	if (length <= 0.0f)
	{
		return {};
	}

	return { vector2 / length };
}
