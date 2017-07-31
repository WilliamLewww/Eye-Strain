#pragma once
#include <vector>
#include "tile.h"

void GenerateStructureFromString(std::string data);

std::vector<Tile> GenerateBox(Vector2 position, int width, int height, int tileWidth, int tileHeight);
std::vector<Tile> GenerateBoxHollow(Vector2 position, int width, int height, int tileWidth, int tileHeight);

std::vector<Tile> DeleteTile(std::vector<Tile> tileList, Vector2 position);
std::vector<Tile> DeleteTiles(std::vector<Tile> tileList, std::vector<Vector2> positionList);

void PrintTiles(std::vector<Tile> tileList);

std::vector<StaticTile> ConvertToStatic(std::vector<Tile> tileList);