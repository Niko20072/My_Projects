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

#include <bitset>
#include <SDL_scancode.h>


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
		void KeyUp(SDL_Scancode key) { keys.reset(key); }
		void KeyDown(SDL_Scancode key) { keys.set(key); } //use this (bool pt mouse). muta din buttons aici (vezi ce face functia asta). uitate in template cpp (int bitset)
		bool GetKey(SDL_Scancode key) const { return held.test(key); } // returns true if the key is currently held down
		bool GetKeyPressed(SDL_Scancode key) const { return pressed.test(key); } // returns true if the key was pressed since the last Tick
		bool GetKeyReleased(SDL_Scancode key) const { return released.test(key); } // returns true if the key was released since the last Tick
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
		bool AllInventoriesClosed(); // Check if all inventories are closed
		void InventoryText();
		void DrawInventory();
		bool CheckCollision(float x, float y);
		void HandleInput();
		void HandleMovement(float deltaTime);
		void PlantSeed(Surface* screen, int tileNumber);
		void UpdatePlants();
		void UpdateFarmTiles();
		void ProgressToNextDay();
		void Logic();
		void UpdateWorld();
		void DrawUI();
		void DrawGame();
		std::bitset<SDL_NUM_SCANCODES> keys; // store key states here
		std::bitset<SDL_NUM_SCANCODES> held; // store key states from the previous tick here
		std::bitset<SDL_NUM_SCANCODES> pressed; // store key press events here (set to true on key down, reset to false after processing in Tick)
		std::bitset<SDL_NUM_SCANCODES> released; // store key release events here (set to true on key up, reset to false after processing in Tick)
	};

}; // namespace Tmpl8