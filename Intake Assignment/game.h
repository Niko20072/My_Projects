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
#include "SDL_scancode.h"
#include "input.h"
#include "tutotial.h"

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
		void MouseUp(int button) { Input::onMouseButtonUp(button); }
		void MouseDown(int button) { Input::onMouseButtonDown(button); }
		void MouseMove(int x, int y) { /*implement if you want to detect mouse movement */ }
		void KeyUp(SDL_Scancode key) { Input::onKeyUp(key); }
		void KeyDown(SDL_Scancode key) { Input::onKeyDown(key); }
		
	private:
		Surface* screen;
		Map gameMap;
		Player player;
		House house;
		Car car;
		Tutorial tutorial;
		std::vector<FarmTile> farmTiles;
		int dayCounter = 0;
		int coinCounter = 250;
		char day[32], coins[32];
		bool gameCompleted = false;
		int index, index2;
		bool tileClicked = false;
		void GodMode();
		bool AllInventoriesClosed(); // Check if all inventories are closed
		void DrawInventory();
		void HoverOutsideObjects();
		//void HoverInsideObjects();
		bool CheckCollision(float x, float y);
		void HandleInput();
		void HandleMovement(float deltaTime);
		void PlantSeed(int tileNumber);
		void UpdatePlants();
		void UpdateFarmTiles();
		void ProgressToNextDay();
		void Logic();
		void UpdateWorld();
		void DrawUI();
		void DrawGame();

		//how to use mouse?
		//how to use in other files?
	};

}; // namespace Tmpl8