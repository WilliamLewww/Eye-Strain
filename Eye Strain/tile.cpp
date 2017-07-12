#include "tile.h"

std::vector<StaticTile> staticTileList;
std::vector<StaticTile> tempStructure;
void InitializeStaticTiles() {

}

void DrawStaticTiles() {
	for (StaticTile staticTile : staticTileList) { DrawTile(staticTile.tile); }

	if (leftButtonPress) {
		for (StaticTile staticTile : staticTileList) { 
			if (mouseX >= staticTile.tile.position.x && mouseX <= staticTile.tile.position.x + staticTile.tile.width &&
				mouseY >= staticTile.tile.position.y && mouseY <= staticTile.tile.position.y + staticTile.tile.height) {
				std::cout << staticTile.tile.position << std::endl;
			}
		}
	}
}

void DrawTile(Tile tile) {
	DrawRect(tile.position, tile.width, tile.height, tile.color);
}