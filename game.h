#pragma once
#include "surface.h"
#include <cstdio> //printf
#include "template.h"
#include "map.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include "input.h"
#include "farmtile.h"
#include "inventory.h"
#include "crafting.h"
#include "plant.h"
#include "house.h"
#include "orders.h"
#include "nightstand.h"
#include "wateringCan.h"
#include "player.h"
#include "car.h"
#include "SDL_scancode.h"
#include "tutotial.h"
#include "camera.h"
#include "mainMenu.h"
#include "endScreen.h"
#include <Audio/Sound.hpp>

namespace Tmpl8
{
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
		void MouseMove(int x, int y) { Input::onMouseMove(x, y); }
		void KeyUp(SDL_Scancode key) { Input::onKeyUp(key); }
		void KeyDown(SDL_Scancode key) { Input::onKeyDown(key); }

	private:
		Surface* screen;
		Camera camera;
		Map gameMap;
		Player player;
		House house;
		Car car;
		Tutorial tutorial;
		MainMenu menu;
		EndGame endScreen;
		Audio::Sound backgroundMusic;
		std::vector<FarmTile> farmTiles;
		FarmTile* selectedTile = nullptr;
		enum class GameStates
		{
			MainMenu,
			CutScene,
			InGame,
			EndScreen
		};
		GameStates gameState = GameStates::MainMenu;
		Sprite car_hover = Sprite(new Surface("assets/image/car_hover.png"), 1);
		Sprite door_hover = Sprite(new Surface("assets/image/door_hover.png"), 1);
		int dayCounter = 0;
		int coinCounter = 250;
		char day[32] = "", coins[32] = "";
		bool gameCompleted = false;
		bool gameStarted = false;
		bool cutScenePlayed = false;
		bool tileClicked = false;
		float mouseWorldX, mouseWorldY; //mouse position in world coordinates
		float volume;
		// --- Core ---
		void States();
		void UpdateWorld(float deltaTime);
		void Logic(float deltaTime);
		// --- Rendering ---
		void DrawUI();
		void HoverOutsideObjects();
		void DrawAudioBar();
		void DrawGame();
		// --- Gameplay  ---
		void UpdateMouseWorldPosition();
		void ResetFarmTilesClick();
		void UpdateFarmTiles();
		void CollectPlants(float deltaTime);
		void PlantSeed(FarmTile& farmtile);
		void ProgressToNextDay();
		bool AllInventoriesClosed(); // Check if all inventories are closed
		// --- Audio ---
		void Audio();
		// --- Debug ---
		void GodMode();
	};
}; // namespace Tmpl8