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
#include "player.h"
#include "car.h"
#include "SDL_scancode.h"
#include "input.h"
#include "tutotial.h"
#include "camera.h"
#include "mainMenu.h"
#include "endScreen.h"

#include <Audio/Sound.hpp>

namespace Tmpl8
{
	//class Surface;
	class Game
	{
	public:
		Game();
		void States();
		void SetTarget(Surface* surface) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick(float deltaTime);
		void MouseUp(int button) { Input::onMouseButtonUp(button); }
		void MouseDown(int button) { Input::onMouseButtonDown(button); }
		void MouseMove(int x, int y) { Input::onMouseMove(x, y); }
		void KeyUp(SDL_Scancode key) { Input::onKeyUp(key); }
		void KeyDown(SDL_Scancode key) { Input::onKeyDown(key); }

	private:
		Surface* screen;
		Map gameMap;
		Camera camera;
		Player player;
		House house;
		Car car;
		Tutorial tutorial;
		MainMenu menu;
		EndGame endScreen;
		Audio::Sound backgroundMusic;
		std::vector<FarmTile> farmTiles;
		int dayCounter = 0;
		int coinCounter = 250;
		char day[32] = "", coins[32] = "";
		bool gameCompleted = false;
		bool gameStarted = false;
		bool cutScenePlayed = false;
		bool tileClicked = false;
		float mouseWorldX, mouseWorldY; //mouse position in world coordinates
		float volume;
		FarmTile* selectedTile = nullptr;
		enum class GameStates
		{
			MainMenu,
			CutScene,
			InGame,
			EndScreen
		};
		GameStates gameState = GameStates::MainMenu;
		void GodMode();
		bool AllInventoriesClosed(); // Check if all inventories are closed
		void DrawInventory();
		void HoverOutsideObjects();
		void HandleMovement(float deltaTime);
		void PlantSeed(FarmTile& farmtile);
		void UpdatePlants(float deltaTime);
		void UpdateFarmTiles();
		void ResetFarmTilesClick();
		void ProgressToNextDay();
		void Logic(float deltaTime);
		void DrawAudioBar();
		void Audio();
		void UpdateWorld(float deltaTime);
		void DrawUI();
		void DrawGame();

		//how to use mouse?
		//how to use in other files?
	};

}; // namespace Tmpl8