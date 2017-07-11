#pragma once
#include "vector2.h"
#include "geometry.h"

struct Tile {
	Vector2 position;

	int width, height;
	int color[3];

	Tile() { }
	Tile(Vector2 newPosition) { position = newPosition; }

	int operator==(const Tile& tile)const {
		return (position.x == tile.position.x) && (position.y == tile.position.y);
	}

	inline Vector2 midpoint() { return Vector2(position.x + (position.x / 2), position.y + (position.y / 2)); }

	inline double top() { return position.y; }
	inline double bottom() { return position.y + height; }
	inline double left() { return position.x; }
	inline double right() { return position.x + width; }
};

struct StaticTile {
	Tile tile;
	StaticTile(Vector2 position) {
		tile.position = position;

		tile.width = 7;
		tile.height = 7;

		tile.color[0] = 150;
		tile.color[1] = 100;
		tile.color[2] = 200;
	}

	inline void changeColor(int color[3]) {
		tile.color[0] = color[0];
		tile.color[1] = color[1];
		tile.color[2] = color[2];
	}
};
extern std::vector<StaticTile> staticTileList;

#include "structure.h"

void DrawTile(Tile tile);

void InitializeStaticTiles();
void DrawStaticTiles();