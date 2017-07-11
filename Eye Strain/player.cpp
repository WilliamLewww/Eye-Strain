#include "player.h"

bool CheckCollision(Tile tile);
void HandleCollision(Tile tile);
bool CheckCollisionBottom(Tile tile);

Player player;

std::vector<Tile> groundTileList;
bool jumpPress = false;
void UpdatePlayer(int elapsedTime) {
	float deltaTimeS = (float)(elapsedTime) / 1000;

	player.position.x += player.velocityX;
	player.position.y += player.velocityY;
	player.velocityX = 0;

	switch (controllerPad) {
		case 2: case 3: case 4: 
			if (std::find(controllerList.begin(), controllerList.end(), SDL_CONTROLLER_BUTTON_X) != controllerList.end()) { player.velocityX = player.runSpeed * deltaTimeS; }
			else { player.velocityX = player.speed * deltaTimeS; }

			break;
		case 6: case 7: case 8: 
			if (std::find(controllerList.begin(), controllerList.end(), SDL_CONTROLLER_BUTTON_X) != controllerList.end()) { player.velocityX = -player.runSpeed * deltaTimeS; }
			else { player.velocityX = -player.speed * deltaTimeS; }

			break;
	}

	if (std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_LEFT) == keyList.end()) {
		if (std::find(keyList.begin(), keyList.end(), SDLK_LCTRL) != keyList.end()) { player.velocityX = player.runSpeed * deltaTimeS; } else { player.velocityX = player.speed * deltaTimeS; }
	}
	if (std::find(keyList.begin(), keyList.end(), SDLK_LEFT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) == keyList.end()) {
		if (std::find(keyList.begin(), keyList.end(), SDLK_LCTRL) != keyList.end()) { player.velocityX = -player.runSpeed * deltaTimeS; } else { player.velocityX = -player.speed * deltaTimeS; }
	}

	if (player.onGround == true) {
		if (jumpPress == false) {
			if (std::find(keyList.begin(), keyList.end(), SDLK_SPACE) != keyList.end() || std::find(controllerList.begin(), controllerList.end(), SDL_CONTROLLER_BUTTON_A) != controllerList.end()) {
				player.velocityY = -player.jumpSpeed; player.onGround = false; jumpPress = true;
			}
		}
	}
	else {
		player.velocityY += 0.25 * deltaTimeS;
	}

	if (std::find(keyList.begin(), keyList.end(), SDLK_SPACE) == keyList.end() && std::find(controllerList.begin(), controllerList.end(), SDL_CONTROLLER_BUTTON_A) == controllerList.end()) {
		if (player.velocityY < 0 && player.onGround == false) player.velocityY += 0.25 * deltaTimeS;
		if (player.onGround == true) jumpPress = false;
	}

	for (auto &tile : staticTileList) {
		if (CheckCollision(tile.tile) == true) { HandleCollision(tile.tile); }
	}

	std::vector<Tile> tempGroundTileList;
	for (auto &tile : groundTileList) {
		if (CheckCollision(tile) == false) {
			tempGroundTileList.push_back(tile);
		}
	}

	for (auto &tile : tempGroundTileList) {
		groundTileList.erase(std::remove(groundTileList.begin(), groundTileList.end(), tile), groundTileList.end());
	}
	tempGroundTileList.clear();

	if (groundTileList.size() == 0) player.onGround = false;
}

bool CheckCollision(Tile tile) {
	if (player.left() <= tile.right() &&
		player.right() >= tile.left() &&
		player.top() <= tile.bottom() &&
		player.bottom() >= tile.top()) {
		return true;
	}

	return false;
}

bool CheckCollisionBottom(Tile tile) {
	if (player.top() <= tile.bottom() && player.top() >= tile.bottom() - 5 && player.left() <= tile.right() - 3 && player.right() >= tile.left() + 3) return true;
	return false;
}

void HandleCollision(Tile tile) {
	double overlapX, overlapY;
	if (player.midpoint().x > tile.midpoint().x) overlapX = tile.right() - player.left();
	else overlapX = -(player.right() - tile.left());
	if (player.midpoint().y > tile.midpoint().y) overlapY = tile.bottom() - player.top();
	else overlapY = -(player.bottom() - tile.top());

	if (overlapX != 0 && overlapY != 0) {
		if (abs(overlapY) < abs(overlapX)) {
			if (overlapY < 0) {
				if (player.velocityY > 0) {
					player.onGround = true;
					player.position.y += overlapY; player.velocityY = 0;
					if (std::find(groundTileList.begin(), groundTileList.end(), tile) == groundTileList.end()) groundTileList.push_back(tile);
				}
			}
			else {
				if (player.velocityY < 0) {
					if (CheckCollisionBottom(tile)) { player.position.y += overlapY; player.velocityY = 0; }
				}
			}
		}
		else {
			player.position.x += overlapX; player.velocityX = 0;
		}
	}
}


void DrawPlayer() {
	DrawRect(player.position, player.width, player.height);
}