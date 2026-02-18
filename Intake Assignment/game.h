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
#include "crafting.h"
#include "plant.h"
#include "house.h"
#include "buttons.h"
#include "orders.h"
#include "nightstand.h"
#include "wateringCan.h"
#include "worldState.h"
#include "player.h"
#include "car.h"

namespace Tmpl8
{
	//class Surface;
	class Game
	{
	public:
		Game();
		void SetTarget(Surface* surface) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick(float deltaTime);
		void MouseUp(int button) {  /*implement if you want to detect mouse button presses  */ }
		void MouseDown(int button) {  /*implement if you want to detect mouse button presses  */ }
		void MouseMove(int x, int y) { /*implement if you want to detect mouse movement */ }
		void KeyUp(int key) { /* implement if you want to handle keys */ }
		void KeyDown(int key) { /* implement if you want to handle keys */ } //use this (bool pt mouse). muta din buttons aici (vezi ce face functia asta). uitate in template cpp (int bitset)
	private:
		Surface* screen;
		Map gameMap;
		Player player;
		House house;
		Car car;
		std::vector<FarmTile> farmTiles;
		int dayCounter = 0;
		int coinCounter = 200;
		char day[32], coins[32];
		bool gameCompleted = false;
		int index, index2;
		bool tileClicked = false;
		bool InventorysClosed(); // Check if all inventories are closed
		void InventoryText();
		void DrawInventory();
		bool CheckCollision(float x, float y);
		void HandleInput();
		void HandleMovement(float deltaTime);
		void PlantSeeds(Surface* screen, int tileNumber);
		void UpdatePlants();
		void UpdateOrders();
		void UpdateFarmTiles();
		void UpdateNextDay();
		void Logic();
		void UpdateWorld();
		void DrawUI();
		void DrawGame();
	};

}; // namespace Tmpl8