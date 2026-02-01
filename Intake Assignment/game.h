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
#include "worldState.h"

namespace Tmpl8 
{
//class Surface;
class Game
{
public:
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
	Map gameMap;
	const float cameraSpeed = 360.0f;
	int dayCounter = 0;
	int coinCounter = 200;
	char day[32], coins[32];
	bool gameCompleted = false;
	float plantX, plantY;
	int index, index2;
	bool tileClicked = false;
	bool CheckCollision(int x, int y);
	void HandleInput();
	void HandleMovement(float deltaTime);
	void UpdatePlants();
	void ResetOrders();
	void UpdateOrders();
	void UpdateFarmTiles();
	void Logic();
	void UpdateWorld();
	void DrawUI();
	void DrawGame();
};

}; // namespace Tmpl8