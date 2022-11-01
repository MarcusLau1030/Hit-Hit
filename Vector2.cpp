#include "Vector2.hpp"

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

void Vector2::normalize() {
	float magnitude = calculateMagnitude();
	x /= magnitude;
	y /= magnitude;
}

float Vector2::calculateMagnitude() {
	float mangnitude = sqrt(pow(x, 2) + pow(y, 2));
	return mangnitude;
}


Vector2 Vector2::Divide(float scalar) {
	return Vector2(x / scalar, y / scalar);
}

Vector2 Vector2::Subtract(const Vector2& right_vector) {
	return Vector2(x - right_vector.x, y - right_vector.y);
}

Vector2 Vector2::Multiply(float scalar) {
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::Multiply(const Vector2& right_vector) {
	return Vector2(x * right_vector.x, y * right_vector.y);
}

Vector2 Vector2::Add(const Vector2& right_vector) {
	return Vector2(x + right_vector.x, y + right_vector.y);
}

Vector2 Vector2::operator /(float scalar) {
	return Divide(scalar);
}

Vector2 Vector2::operator -(const Vector2& right_vector) {
	return Subtract(right_vector);
}

Vector2 Vector2::operator *(float scalar) {
	return Multiply(scalar);
}

Vector2 Vector2::operator *(const Vector2& right_vector) {
	return Multiply(right_vector);
}


Vector2 Vector2::operator +(const Vector2& right_vector) {
	return Add(right_vector);
}


