#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include "template.h"
#include "map.h"
#include <windows.h>
#include <iostream>
#include "farmtile.h"

namespace Tmpl8
{
	static Sprite player(new Surface("assets/player3.png"), 4);
	
	///change sprite size 50 -> ??? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	int playerX = 648 / 2 + 50, playerY = 512 / 2 + 50; //player position

	Map gameMap;

	bool CheckCollision(int x, int y)
	{
		//sprit corners
		int left = x;
		int top = y;
		int right = left + 50;
		int bottom = top + 50;

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
		//MakeFarmTile();
		
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
	
	FarmTile farmTile(2 * Map::TileSize, 7 * Map::TileSize);
	FarmTile farmTile2(3 * Map::TileSize, 7 * Map::TileSize);

	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		int newCameraX = Map::cameraX;
		int newCameraY = Map::cameraY;

		// Get mouse coordinates
		POINT mousePos;
		int mouseX = 0, mouseY = 0;
		if (GetCursorPos(&mousePos))
		{
			HWND hwnd = GetActiveWindow();
			ScreenToClient(hwnd, &mousePos);
			mouseX = mousePos.x;
			mouseY = mousePos.y;
			//std::cout << "Mouse X: " << mouseX << ", Y: " << mouseY << std::endl;
		}

		// Transform screen coordinates -> world coordinates
		int worldX = Map::cameraX + mouseX;
		int worldY = Map::cameraY + mouseY;

		// Tile under the mouse
		int tileX = worldX / Map::TileSize;
		int tileY = worldY / Map::TileSize;

		//Drawing stuff
		gameMap.DrawMap(screen);

		// Check left click and if the mouse is on the desired tile
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			// Tile rectangle
			int tileWorldX = 2 * Map::TileSize; // x of the farm tile
			int tileWorldY = 7 * Map::TileSize; // y of the farm tile

			if (worldX >= tileWorldX && worldX < tileWorldX + Map::TileSize && worldY >= tileWorldY && worldY < tileWorldY + Map::TileSize)
			{
				std::cout << "Clicked on farm tile!\n";
				farmTile.SetFrame(1);
			}
		}
		farmTile.Draw(screen);
		farmTile2.SetFrame(1);
		farmTile2.Draw(screen);
		//FarmTile farmTile(screen);
		player.Draw(screen, playerX, playerY);


		// Move camera based on WASD keys
		if (GetAsyncKeyState('A')) newCameraX -= 5, player.SetFrame(0);
		if (GetAsyncKeyState('D')) newCameraX += 5, player.SetFrame(1);
		if (GetAsyncKeyState('W')) newCameraY -= 5;
		if (GetAsyncKeyState('S')) newCameraY += 5;

		// Check for collision before updating camera position
		if (CheckCollision(newCameraX + playerX, newCameraY + playerY) == true)
			Map::cameraX = newCameraX, Map::cameraY = newCameraY;

		int worldPlayerX = Map::cameraX + playerX;
		int worldPlayerY = Map::cameraY + playerY;

		//std::cout << "Player world position: X=" << worldPlayerX << ", Y=" << worldPlayerY << std::endl;

		
		Sleep(16); //simulate ~60fps
	}
};
