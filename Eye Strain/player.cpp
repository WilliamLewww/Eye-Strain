#include "player.h"

Player player;

void UpdatePlayer(int elapsedTime) {
	float deltaTimeS = (float)(elapsedTime) / 1000;

	player.position.x += player.velocityX;
	player.position.y += player.velocityY;
	player.velocityX = 0;

	switch (controllerPad) {
		case 2: case 3: case 4: player.velocityX = 50 * deltaTimeS; break;
		case 6: case 7: case 8: player.velocityX = -50 * deltaTimeS; break;
	}
}


void DrawPlayer() {
	DrawRect(player.position, player.width, player.height);
}