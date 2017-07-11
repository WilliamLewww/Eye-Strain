#include "tile.h"

std::vector<StaticTile> staticTileList;
void InitializeStaticTiles() {
	std::vector<StaticTile> tempStructure = ConvertToStatic(DeleteTile(GenerateBoxHollow(Vector2(0, 861), 8, 5, 8, 8),Vector2(56, 877)));
	PrintTiles(GenerateBoxHollow(Vector2(0, 861), 8, 5, 8, 8));
	staticTileList.insert(staticTileList.end(), tempStructure.begin(), tempStructure.end());

	for (StaticTile& tile : staticTileList) {
		int random[3] = { std::rand() % 255, std::rand() % 255, std::rand() % 255 };
		tile.changeColor(random);
	}
}

void DrawStaticTiles() {
	for (StaticTile staticTile : staticTileList) { DrawTile(staticTile.tile); }
}

void DrawTile(Tile tile) {
	DrawRect(tile.position, tile.width, tile.height, tile.color);
}