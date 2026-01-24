#pragma once
#include "surface.h"
#include <cstdio> //printf
#include "template.h"
#include "map.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include "farmtile.h"
//#include <cassert>
#include "inventory.h"
#include "plant.h"
#include "house.h"
#include "buttons.h"
#include "orders.h"
#include "nightstand.h"
#include "wateringCan.h"

namespace Tmpl8 
{
//class Surface;
class Game
{
public:
	bool CheckCollision(int x, int y);
	bool CheckAllCompleted();
	void SetTarget(Surface* surface) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick(float deltaTime);
	void MouseUp(int button) {  /*implement if you want to detect mouse button presses  */}
	void MouseDown(int button) {  /*implement if you want to detect mouse button presses  */}
	void MouseMove(int x, int y) { /*implement if you want to detect mouse movement */} 
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }
private:
	Surface* screen;
	const int playerX = 648 / 2 + 46, playerY = 512 / 2 + 22; //player position
	const float cameraSpeed = 360.0f;
	int dayCounter = 1;
	int coinCounter = 150;
	char day[32], coins[32], weekDay[32];
	bool gameCompleted = false;
	Map gameMap;
	std::vector<Order> orders;
};

}; // namespace Tmpl8