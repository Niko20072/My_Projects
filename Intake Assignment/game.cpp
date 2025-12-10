#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include "template.h"
#include "map.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include "farmtile.h"
#include <cassert>
#include "inventory.h"

namespace Tmpl8
{
	static Sprite player(new Surface("assets/vera2.png"), 4);

	int playerX = 648 / 2 + 46, playerY = 512 / 2 + 22; //player position

	Map gameMap;
	Inventory playerInventory(10, 10);

	std::vector<FarmTile> farmTiles;

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
	}

	FarmTile farmTile(3, 7);
	FarmTile farmTile2(4, 7);

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
		/*
		for (int x = 2; x <= 3; x++)
		{
			farmTiles.emplace_back(x, 7);
		}*/
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
	int frame_counter = 0;
	int invFrame = 0;
	void Game::Tick(float deltaTime)
	{

		screen->Clear(0);

		frame_counter++;//to limit key press speed
		if(frame_counter>=100)
			frame_counter = 100;

		// Get mouse coordinates
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

		// Transform screen coordinates -> world coordinates
		int worldX = Map::cameraX + mouseX;
		int worldY = Map::cameraY + mouseY;
		//std::cout << "World X: " << worldX << ", Y: " << worldY << std::endl;

		int worldPlayerX = Map::cameraX + playerX;
		int worldPlayerY = Map::cameraY + playerY;

		//std::cout << "Player world position: X=" << worldPlayerX << ", Y=" << worldPlayerY << std::endl;

		int newCameraX = Map::cameraX;
		int newCameraY = Map::cameraY;

		//Drawing stuff
		gameMap.DrawMap(screen);

		// Check left click and if the mouse is on the desired tile
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			for (int i = 3; i <= 4; i++)
			{
				// Tile rectangle
				int tileWorldX = i * Map::TileSize; // x of the farm tile
				int tileWorldY = 7 * Map::TileSize; // y of the farm tile

				if (worldX >= tileWorldX && worldX < tileWorldX + Map::TileSize && worldY >= tileWorldY && worldY < tileWorldY + Map::TileSize)
				{
					std::cout << "Clicked on farm tile!\n";
					if(i==3)
						farmTile.SetFrame(1);
					if(i==4)
						farmTile2.SetFrame(1);
				}
			}
		}

		farmTile.Draw(screen);
		farmTile2.Draw(screen);
		player.Draw(screen, playerX, playerY);
		
		// Open inventory on 'E' key press
		
		if (GetAsyncKeyState('E') && frame_counter>=15)
		{
			if (Inventory::carisopen == true)
				Inventory::carisopen = false;
			frame_counter = 0;
			Inventory::isopen = !Inventory::isopen;
			invFrame = 0;
			playerInventory.SetFrame(invFrame);
		}
		
		if (Inventory::isopen == true)
		{
			if (GetAsyncKeyState(VK_LBUTTON) && mouseX >= 390 && mouseX <= 421 && mouseY >= 470 && mouseY <= 508)
			{
				if (invFrame == 1 && frame_counter >= 15)
					invFrame = 0, frame_counter = 0, playerInventory.SetFrame(invFrame);
				if (invFrame == 0 && frame_counter >= 15)
					invFrame = 1, frame_counter = 0, playerInventory.SetFrame(invFrame);
			}
			playerInventory.InventoryIsOpen(screen);
		}

		// Show "House" text on left click in house area
		if (GetAsyncKeyState(VK_LBUTTON))
			if (worldX >= 196 && worldX <= 233 && worldY >= 183 && worldY <= 232)
			{
				screen->Print("House", 280, 280, 0x0);
			}

		// Open car inventory on left click in car area
		if (GetAsyncKeyState(VK_LBUTTON) && worldX >= 528 && worldX <= 686 && worldY >= 175 && worldY <= 220 && frame_counter >= 15 && worldPlayerX>=448 && worldPlayerX<=688 && worldPlayerY >=86 && worldPlayerY<=176)
		{
			if(Inventory::isopen == true)
				Inventory::isopen = false;
			frame_counter = 0;
			Inventory::carisopen = !Inventory::carisopen;
			invFrame = 2;
			playerInventory.SetFrame(invFrame);
		}
		if (Inventory::carisopen == true)
		{
			if (GetAsyncKeyState(VK_LBUTTON) && mouseX >= 390 && mouseX <= 421 && mouseY >= 470 && mouseY <= 508)
			{
				if (invFrame == 2 && frame_counter >= 15)
					invFrame = 3, frame_counter = 0, playerInventory.SetFrame(invFrame), std::cout<<"da1";
				if (invFrame == 3 && frame_counter >= 15)
					invFrame = 2, frame_counter = 0, playerInventory.SetFrame(invFrame), std::cout << "da3";
			}
			playerInventory.InventoryIsOpen(screen);
			if (!(worldPlayerX >= 448 && worldPlayerX <= 688 && worldPlayerY >= 86 && worldPlayerY <= 176))
				Inventory::carisopen = false;
			if(GetAsyncKeyState('E'))
				Inventory::carisopen = false;
		}

		// Move camera based on WASD keys
		if (GetAsyncKeyState('A')) newCameraX -= 6, player.SetFrame(0);
		if (GetAsyncKeyState('D')) newCameraX += 6, player.SetFrame(1);
		if (GetAsyncKeyState('W')) newCameraY -= 6, player.SetFrame(3);
		if (GetAsyncKeyState('S')) newCameraY += 6, player.SetFrame(2);

		// Check for collision before updating camera position
		if (CheckCollision(newCameraX + playerX, newCameraY + playerY) == true)
			Map::cameraX = newCameraX, Map::cameraY = newCameraY;

		Sleep(16); //simulate ~60fps
	}
};
