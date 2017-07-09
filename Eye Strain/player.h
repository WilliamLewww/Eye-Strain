#pragma once
#include "vector2.h"
#include "geometry.h"
#include "input.h"

struct Player {
	Vector2 position;
	int width = 5, height = 5;

	double velocityX, velocityY;
};
extern Player player;

void UpdatePlayer(int elapsedTime);
void DrawPlayer();