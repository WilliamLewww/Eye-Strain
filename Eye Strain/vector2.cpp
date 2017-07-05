#include "vector2.h"

Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::Vector2(double xArgs, double yArgs) {
	x = xArgs;
	y = yArgs;
}

Vector2 Vector2::Get() {
	return Vector2(x, y);
}

Vector2 Vector2::Abs() {
	x = abs(x);
	y = abs(y);

	return *this;
}

double Vector2::Max() {
	if (x > y) {
		return x;
	}

	return y;
}

double Vector2::Min() {
	if (x < y) {
		return x;
	}

	return y;
}

Vector2 Vector2::Normalize() {
	// | a | = sqrt((ax * ax) + (ay * ay) + (az * az))
	// x = ax / | a |
	// y = ay / | a |
	// z = az / | a |
	double magnitude = (double)abs(sqrt((x * x) + (y * y)));

	if (magnitude != 0) {
		x = x / magnitude;
		y = y / magnitude;
	}

	return *this;
}

Vector2 Vector2::operator*(Vector2 vector) {
	Vector2 newVector(x *= vector.x, y *= vector.y);
	return newVector;
}

Vector2 Vector2::operator/(Vector2 vector) {
	Vector2 newVector(x /= vector.x, y /= vector.y);
	return newVector;
}

Vector2 Vector2::operator*(double value) {
	Vector2 newVector(x *= value, y *= value);
	return newVector;
}

Vector2 Vector2::operator+(Vector2 vector) {
	return Vector2(x += vector.x, y += vector.y);
}

Vector2 Vector2::operator-(Vector2 vector) {
	return Vector2(x -= vector.x, y -= vector.y);
}

Vector2 Vector2::operator+=(Vector2 vector) {
	Vector2 newVector(x += vector.x, y += vector.y);
	return newVector;
}

Vector2 Vector2::operator-=(Vector2 vector) {
	Vector2 newVector(x -= vector.x, y -= vector.y);
	return newVector;
}

bool Vector2::operator==(Vector2 vector) {
	if (x == vector.x && y == vector.y) return true;
	return false;
}

bool Vector2::operator!=(Vector2 vector) {
	if (x != vector.x || y != vector.y) return true;
	return false;
}

std::ostream &operator<<(std::ostream &os, Vector2 const &m) {
	return os << m.x << "," << m.y;
}