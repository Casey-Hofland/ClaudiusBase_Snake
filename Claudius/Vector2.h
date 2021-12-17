#pragma once

struct Vector2
{
	// Variables
	float x {}; 
	float y {};

	// Constructors
	Vector2() = default;
	constexpr Vector2(float x, float y) noexcept;

	// (Binary) Arithmatic operators
	constexpr Vector2 operator+() const noexcept { return { +x, +y }; }
	constexpr Vector2 operator-() const noexcept { return { -x, -y }; }
	
	Vector2& operator+=(const Vector2& rhs) noexcept;					// compound assignment (does not need to be a member, but often is, to modify the private members)
	friend Vector2 operator+(Vector2 lhs, const Vector2& rhs) noexcept;	// friends defined inside class body are inline and are hidden from non-ADL lookup

	Vector2& operator-=(const Vector2& rhs) noexcept;
	friend Vector2 operator-(Vector2 lhs, const Vector2& rhs) noexcept;

	Vector2& operator*=(const Vector2& rhs) noexcept;
	Vector2& operator*=(const float& rhs) noexcept;						// we do not need to pass float by reference here, however we do so as to conform to the implementation pattern
	friend Vector2 operator*(Vector2 lhs, const Vector2& rhs) noexcept;
	friend Vector2 operator*(Vector2 lhs, const float& rhs) noexcept;
	friend Vector2 operator*(const float& lhs, Vector2 rhs) noexcept;

	Vector2& operator/=(const Vector2& rhs) noexcept;
	Vector2& operator/=(const float& rhs) noexcept;
	friend Vector2 operator/(Vector2 lhs, const Vector2& rhs) noexcept;
	friend Vector2 operator/(Vector2 lhs, const float& rhs) noexcept;
	friend Vector2 operator/(const float& lhs, Vector2 rhs) noexcept;	

	// Comparison Operators
	bool operator==(const Vector2& rhs) const noexcept;
	bool operator!=(const Vector2& rhs) const noexcept;

	// User-defined methods
	Vector2 perpendicular() const;
	Vector2 unit() const;

	float length() const;
	float length_squared() const;
	float dot(const Vector2& rhs) const;
	float cross(const Vector2& rhs) const;
	void normalize();

};