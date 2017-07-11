#pragma once
#include "tile.h"
#include <vector>

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
};

extern std::vector<StaticTile> staticTileList;