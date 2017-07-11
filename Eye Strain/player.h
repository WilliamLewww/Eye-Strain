#pragma once
#include "vector2.h"
#include "geometry.h"
#include "input.h"

struct Player {
	Vector2 position = Vector2(500, 500);
	int width = 5, height = 5;
	double velocityX, velocityY;

	double jumpSpeed = 0.05;

	bool onGround;

	inline Vector2 midpoint() { return Vector2(position.x + (position.x / 2), position.y + (position.y / 2)); }

	inline double top() { return position.y; }
	inline double bottom() { return position.y + height; }
	inline double left() { return position.x; }
	inline double right() { return position.x + width; }
};
extern Player player;

void UpdatePlayer(int elapsedTime);
void DrawPlayer();