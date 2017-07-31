#include "structure.h"

void GenerateStructureFromString(std::string data) {

}

std::vector<Tile> GenerateBox(Vector2 position, int width, int height, int tileWidth, int tileHeight) {
	std::vector<Tile> tempTileList;

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			tempTileList.push_back(Tile(Vector2(position.x + (x * tileWidth), position.y + (y * tileHeight))));
		}
	}

	return tempTileList;
}

std::vector<Tile> GenerateBoxHollow(Vector2 position, int width, int height, int tileWidth, int tileHeight) {
	std::vector<Tile> tempTileList;

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
				tempTileList.push_back(Tile(Vector2(position.x + (x * tileWidth), position.y + (y * tileHeight))));
			}
		}
	}

	return tempTileList;
}

std::vector<Tile> DeleteTile(std::vector<Tile> tileList, Vector2 position) {
	std::vector<Tile> tempTileList = tileList;
	std::remove(tempTileList.begin(), tempTileList.end(), Tile(position));

	return tempTileList;
}

std::vector<Tile> DeleteTiles(std::vector<Tile> tileList, std::vector<Vector2> positionList) {
	std::vector<Tile> tempTileList = tileList;
	for (Vector2 position : positionList) { std::remove(tempTileList.begin(), tempTileList.end(), Tile(position)); }

	return tempTileList;
}

void PrintTiles(std::vector<Tile> tileList) {
	int counter = 0;
	for (Tile tile : tileList) {
		std::cout << "[" << tile.position << "]";

		if (counter == 5) {
			std::cout << "" << std::endl;
			counter = 0;
		}

		counter++;
	}
}

std::vector<StaticTile> ConvertToStatic(std::vector<Tile> tileList) {
	std::vector<StaticTile> tempTileList;
	for (Tile tile : tileList) { tempTileList.push_back(StaticTile(tile.position)); }

	return tempTileList;
}