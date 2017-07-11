#include "tile.h"

std::vector<StaticTile> staticTileList;

void InitializeStaticTiles() {
	staticTileList.push_back(StaticTile(Vector2(500, 510)));
}

void DrawStaticTiles() {
	for (StaticTile staticTile : staticTileList) { DrawTile(staticTile.tile); }
}

void DrawTile(Tile tile) {
	DrawRect(tile.position, tile.width, tile.height, tile.color);
}