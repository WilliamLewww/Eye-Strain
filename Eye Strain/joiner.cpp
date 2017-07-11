#include "joiner.h"

void Joiner::Initialize() {
	InitializeStaticTiles();
}

void Joiner::Draw() {
	DrawPlayer();
	DrawStaticTiles();
}

void Joiner::Update(int elapsedTime) {
	UpdatePlayer(elapsedTime);
}