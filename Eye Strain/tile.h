#pragma once
#include "vector2.h"
#include "geometry.h"

struct Tile {
	Vector2 position;

	int width, height;
	int color[3];

	int operator==(const Tile& tile)const {
		return (position.x == tile.position.x) && (position.y == tile.position.y);
	}

	inline Vector2 midpoint() { return Vector2(position.x + (position.x / 2), position.y + (position.y / 2)); }

	inline double top() { return position.y; }
	inline double bottom() { return position.y + height; }
	inline double left() { return position.x; }
	inline double right() { return position.x + width; }
};

void DrawTile(Tile tile);

#include "static_tile.h"
void InitializeStaticTiles();
void DrawStaticTiles();