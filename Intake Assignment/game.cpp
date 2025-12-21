#include "game.h"
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

namespace Tmpl8
{
	static Sprite player(new Surface("assets/Vera.png"), 4);
	

	const int playerX = 648 / 2 + 46, playerY = 512 / 2 + 22; //player position
	int dayCounter = 1;
	int coinCounter = 10;
	char day[32], coins[32];

	int contSunblossom = 0;
	int contMoonleaf = 0;
	int contEmberroot = 0;
	int contFrostmint = 0;
	int contBerry = 0;

	Map gameMap;
	Inventory playerInventory(10, 10);
	std::vector<FarmTile> farmTiles;
	std::vector<Plant> plants;

	/*
	// Convert farm tile (x,y) to index in farmTiles vector
	int farmTileToIndex(int x, int y)
	{
		assert(x < Map::MapWidth);
		assert(y < Map::MapHeight);
		return  x + y * Map::MapWidth;
	}

	// Get reference to farm tile at (x,y)
	FarmTile& getFarmTile(int x, int y)
	{
		int idx = farmTileToIndex(x, y);
		assert(idx < farmTiles.size());
		return farmTiles[idx];
	}*/

	bool CheckCollision(int x, int y)
	{
		//sprit corners
		int left = x;
		int top = y;
		int right = left + 46;
		int bottom = top + 22;

		//check all corners for collision
		if (gameMap.IsBlocked(left, top)) return false;
		if (gameMap.IsBlocked(right, top)) return false;
		if (gameMap.IsBlocked(left, bottom)) return false;
		if (gameMap.IsBlocked(right, bottom)) return false;

		return true; //no collision
	}

	/*
	
	Sprite WetFarmTile (new Surface("assets/FarmLand_Tile.png"), 1);

	int farmTiles[] = { NULL };
	int size = 0;

	void MakeFarmTile()
	{
		
		for (int y = 7; y <= 31; y++)
		{
			for (int x = 2; x <= 29; x++)
			{
				farmTiles[size++] = x * Map::TileSize;
				farmTiles[size++] = y * Map::TileSize;
			}
		}
		for (int x = 4; x <= 29; x++)
		{
			farmTiles[size++] = x * Map::TileSize;
			farmTiles[size++] = 31 * Map::TileSize;
		}
		for (int y = 7; y <= 27; y++)
		{
			for (int x = 30; x <= 33; x++)
			{
				farmTiles[size++] = x * Map::TileSize;
				farmTiles[size++] = y * Map::TileSize;
			}
		}
	}
	

	void DrawFarmTile(Surface* screen)
	{
		int size2 = 0;
		while (size2 <= size)
		{
			WetFarmTile.Draw(screen, (farmTiles[size2] - Map::cameraX), (farmTiles[size2 + 1]) - Map::cameraY);
			size2 += 2;
		}
	}*/


	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	
	void Game::Init()
	{
		for (int x = 3; x <= 23; x++)
		{
			for(int y = 7; y <= 17; y++)
				farmTiles.emplace_back(x, y);
		}
		for (int x = 3; x <= 19; x++)
		{
			for (int y = 18; y <= 20; y++)
				farmTiles.emplace_back(x, y);
		}
		//plants.emplace_back("Moonleaf");
	}

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------

	void Game::Shutdown()
	{
		
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------

	void Game::Tick(float deltaTime)
	{
		deltaTime /= 1000.0f; // convert to seconds.
		//std::cout << deltaTime << std::endl;
		screen->Clear(0);
		
		// -----------------------------------------------------------
		// Get mouse coordinates
		// -----------------------------------------------------------
		
		POINT mousePos;
		int mouseX = 0, mouseY = 0;
		if (GetCursorPos(&mousePos))
		{
			HWND hwnd = GetActiveWindow();
			ScreenToClient(hwnd, &mousePos);
			mouseX = mousePos.x;
			mouseY = mousePos.y;
			std::cout << "Mouse X: " << mouseX << ", Y: " << mouseY << std::endl;
		}

		// -----------------------------------------------------------
		// Variables
		// -----------------------------------------------------------
		
		// Transform screen coordinates -> world coordinates
		float worldX = Map::cameraX + mouseX;
		float worldY = Map::cameraY + mouseY;
		//std::cout << "World X: " << worldX << ", Y: " << worldY << std::endl;

		float worldPlayerX = Map::cameraX + playerX;
		float worldPlayerY = Map::cameraY + playerY;

		//std::cout << "Player world position: X=" << worldPlayerX << ", Y=" << worldPlayerY << std::endl;

		float newCameraX = Map::cameraX;
		float newCameraY = Map::cameraY;

		float reachX1 = worldPlayerX - 50.0f;
		float reachY1 = worldPlayerY - 25.0f;
		float reachX2 = worldPlayerX + 46.0f + 50.0f;
		float reachY2 = worldPlayerY + 94.0f + 25.0f;

		// -----------------------------------------------------------
		// Drawing stuff
		// -----------------------------------------------------------

		// Show House when left click in house area
		House::ShowHouse(screen, reachX1, reachX2, reachY1, reachY2, worldX, worldY);
		House::Update(screen, deltaTime);
		House::ShowCrafting(screen, mouseX, mouseY);
		if (House::craftingisopen == true)
		{
			playerInventory.NormalInventory(screen, mouseX, mouseY);
			playerInventory.DrawOnScreen(screen, deltaTime);
		}
			
		House::DayUpdate(dayCounter, mouseX, mouseY);

		//days and coins
		sprintf(day, "DAY: %d", dayCounter);
		sprintf(coins, "COINS: %d", coinCounter);
		screen->Print(day, 750, 10, 0xff0000);
		screen->Print(coins, 10, 10, 0xffff00);


		if (House::houseisopen == false)
		{
			gameMap.DrawMap(screen);

			// Tiles
			bool tileClicked = false;
			for (auto& x : farmTiles)
			{
				if (playerInventory.InventorysClosed())
					x.Update(x.farmTileX, x.farmTileY, worldX, worldY, reachX1, reachX2, reachY1, reachY2, tileClicked);
			}

			for (auto& x : farmTiles)
			{
				x.Draw(screen);
			}

			//Player range
			screen->Box(worldPlayerX - Map::cameraX, worldPlayerY - Map::cameraY, worldPlayerX + 46 - Map::cameraX, worldPlayerY + 94 - Map::cameraY, 0xff0000);
			screen->Box(reachX1 - Map::cameraX, reachY1 - Map::cameraY, reachX2 - Map::cameraX, reachY2 - Map::cameraY, 0x00ff00);

			//drawing
			player.Draw(screen, playerX, playerY);
			playerInventory.NormalInventory(screen, mouseX, mouseY);
			playerInventory.CarInventory(screen, mouseX, mouseY, worldX, worldY, reachX1, reachY1, reachX2, reachY2);
			playerInventory.SeedsInventory(screen, mouseX, mouseY, worldX, worldY, tileClicked);
			playerInventory.DrawOnScreen(screen, deltaTime);

			// -----------------------------------------------------------
			// Movement and collision
			// -----------------------------------------------------------

			// Move camera based on WASD keys
			vec2 movedir = 0.0f;

			if (GetAsyncKeyState('A'))
			{
				player.SetFrame(0);
				movedir.x = -1;
			}
			if (GetAsyncKeyState('D'))
			{
				player.SetFrame(1);
				movedir.x = 1;
			}
			if (GetAsyncKeyState('W'))
			{
				player.SetFrame(3);
				movedir.y = -1;
			}
			if (GetAsyncKeyState('S'))
			{
				player.SetFrame(2);
				movedir.y = 1;
			}
			if (movedir.sqrLentgh() > 0)
			{
				movedir.normalize();
				newCameraX += movedir.x * 360.0f * deltaTime;
				newCameraY += movedir.y * 360.0f * deltaTime;
			}

			// Check for collision before updating camera position
			if (CheckCollision(newCameraX + playerX, newCameraY + playerY) == true)
			{
				Map::cameraX = newCameraX;
				Map::cameraY = newCameraY;
			}

		}
		//Sleep(16); //simulate ~60fps
	}
};
