#pragma once
#include <cmath>

class Vector2 {
public:
	Vector2(float x = 0, float y = 0);
	void normalize();
	float calculateMagnitude();

	Vector2 Divide(float scalar);
	Vector2 Subtract(const Vector2& right_vector);
	Vector2 Multiply(float scalar);
	Vector2 Multiply(const Vector2& right_vector);
	Vector2 Add(const Vector2& right_vector);
	Vector2 operator /(float scalar);
	Vector2 operator -(const Vector2& right_vector);
	Vector2 operator *(float scalar);
	Vector2 operator *(const Vector2& right_vector);
	Vector2 operator +(const Vector2& right_vector);

	float x, y;
};