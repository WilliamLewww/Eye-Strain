#pragma once
#include <SDL.h>
#include <vector>
#include <algorithm>
#include "vector2.h"

void GetKeys(SDL_Event event);
void RemoveInitialPress();
extern std::vector<SDL_Keycode> keyList;
extern std::vector<SDL_Keycode> pressKeyList;

void GetButtons(SDL_Event event);
extern bool leftButtonDown, leftButtonPress;
extern bool middleMouseDown, middleMousePress;
extern bool scrollUp, scrollDown;
extern int mouseX, mouseY;

void GetController();
extern int controllerPad;
extern std::vector<int> controllerList;
extern std::vector<int> controllerPressList;

bool CheckMouseOnEntity(Vector2 position, int width, int height);