#include "joiner.h"

void Joiner::Initialize() {
	player.position = Vector2(10, 870);
	InitializeStaticTiles();
}

void Joiner::Draw() {
	DrawPlayer();
	DrawStaticTiles();
}

void Joiner::Update(int elapsedTime) {
	UpdatePlayer(elapsedTime);
}