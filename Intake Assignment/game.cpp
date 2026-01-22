#include "game.h"

///do to list:
//sterge tile clicked?
//muta chestiile in subprograme
//sterge includurile useless
//verifica ca toate variabilele sa fie folosite
//fa mai logic
//!!!!!!!!!!!!!!pt plante improve: totul e prea conectat si sunt destul de sigura ca trebuie modificat in asa fel incat toate sa fie mai independente
namespace Tmpl8
{
	/// <summary>
	/// ecapsulation and data hiding!!!!
	/// getter, setter!!!!!!!
	/// </summary>
	static Sprite player(new Surface("assets/Vera.png"), 4);

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

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	bool Game::CheckCollision(int x, int y)
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
	bool Game::CheckAllCompleted()
	{
		for (auto order : orders)
		{
			if (order.completed == false)
				return false;
		}
		return true;
	}

	void Game::Init()
	{
		srand(time(0));
		for (int x = 3; x <= 23; x++)
		{
			for(int y = 7; y <= 17; y++)
				FarmTile::farmTiles.emplace_back(x, y);
		}
		for (int x = 3; x <= 19; x++)
		{
			for (int y = 18; y <= 20; y++)
				FarmTile::farmTiles.emplace_back(x, y);
		}
		for(int i = 0; i <= 5; i++)
			orders.emplace_back(i);
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
	float plantX, plantY;
	int index,index2;
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
			// Mouse coordinates on screen
			std::cout << "Mouse X: " << mouseX << ", Y: " << mouseY << std::endl;
		}
		// -----------------------------------------------------------
		// Buttons
		// -----------------------------------------------------------

		Buttons::GetValues(mouseX, mouseY);
		bool qPressed = Buttons::KeyQ();
		bool ePressed = Buttons::KeyE();
		bool leftClickPressed = Buttons::LeftClick();

		// -----------------------------------------------------------
		// Variables
		// -----------------------------------------------------------
		
		// Transform screen coordinates -> world coordinates -> mouse screen position
		float worldX = Map::cameraX + mouseX;
		float worldY = Map::cameraY + mouseY;
		//std::cout << "World X: " << worldX << ", Y: " << worldY << std::endl;

		// Player world position
		float worldPlayerX = Map::cameraX + playerX;
		float worldPlayerY = Map::cameraY + playerY;
		//std::cout << "Player world position: X=" << worldPlayerX << ", Y=" << worldPlayerY << std::endl;

		// New camera position
		float newCameraX = Map::cameraX;
		float newCameraY = Map::cameraY;

		// Player reach area
		float reachX1 = worldPlayerX - 50.0f;
		float reachY1 = worldPlayerY - 25.0f;
		float reachX2 = worldPlayerX + 46.0f + 50.0f;
		float reachY2 = worldPlayerY + 94.0f + 25.0f;

		// Check for game completion
		House::GameCompleted(screen, leftClickPressed, qPressed, coinCounter, mouseX, mouseY, gameCompleted);
		
		if (!gameCompleted)
		{
			// -----------------------------------------------------------
			// Drawing stuff
			// -----------------------------------------------------------

			// Show House when left click in house area
			House::ShowHouse(screen, qPressed, reachX1, reachX2, reachY1, reachY2, worldX, worldY);

			// Crafting
			Crafting::ShowCrafting(screen, leftClickPressed, qPressed, mouseX, mouseY);
			if (Crafting::craftingisopen == true)
				Crafting::Craft(leftClickPressed, mouseX, mouseY);

			// Main game view
			if (!House::houseisopen)
			{
				gameMap.DrawMap(screen);

				// Tiles
				bool tileClicked = false;
				
				int index = 0;
				for (auto& x : FarmTile::farmTiles)
				{
					index++;
					if (Inventory::InventorysClosed())
						x.Update(leftClickPressed, x.farmTileX, x.farmTileY, worldX, worldY, reachX1, reachX2, reachY1, reachY2);
					if (x.clicked && !x.isClicked)
					{
						tileClicked = true;
						plantX = x.farmTileX;
						plantY = x.farmTileY;
						index2 = index - 1;
						break;
					}
				}
	
				// Draw farm tiles
				for (auto& x : FarmTile::farmTiles)
				{
					x.Draw(screen);
				}

				// Draw plants
				for (auto& x : Plant::plants)
				{
					x.Grown();
					if(!x.harvested)
						x.Draw(screen);
				}

				for (auto& x : FarmTile::farmTiles) // reset clicked state
				{
					x.clicked = false;
				}
				//check if all orders are completed
				if (CheckAllCompleted())
				{
					//generate new orders
					orders.clear();
					srand(time(0));
					for (int i = 0; i <= 5; i++)
						orders.emplace_back(i);
				}

				//Player range
				//screen->Box(worldPlayerX - Map::cameraX, worldPlayerY - Map::cameraY, worldPlayerX + 46 - Map::cameraX, worldPlayerY + 94 - Map::cameraY, 0xff0000);
				screen->Box(reachX1 - Map::cameraX, reachY1 - Map::cameraY, reachX2 - Map::cameraX, reachY2 - Map::cameraY, 0x00ff00);

				//drawing stuff on screen
				player.Draw(screen, playerX, playerY);
				Inventory::NormalInventory(screen, leftClickPressed, ePressed, qPressed, mouseX, mouseY);
				Inventory::CarInventory(screen, coinCounter, ePressed, qPressed, leftClickPressed, mouseX, mouseY, worldX, worldY, reachX1, reachY1, reachX2, reachY2);
				Inventory::SeedsInventory(screen, ePressed, qPressed, leftClickPressed, mouseX, mouseY, worldX, worldY, plantX, plantY, tileClicked, index2);
				Inventory::DrawOnScreen(screen, deltaTime);

				///move this to inventory draw function !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! maybe?
				if (Inventory::carisopen && Inventory::frame == 5)
				{
					for (auto& x : orders)
					{
						x.Logic(screen, leftClickPressed, mouseX, mouseY, coinCounter);
						x.Draw(screen);
					}
				}

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
					newCameraX += movedir.x * cameraSpeed * deltaTime;
					newCameraY += movedir.y * cameraSpeed * deltaTime;
				}

				// Check for collision before updating camera position
				if (CheckCollision(newCameraX + playerX, newCameraY + playerY) == true)
				{
					Map::cameraX = newCameraX;
					Map::cameraY = newCameraY;
				}

			}
			else // Inside house
			{
				House::DayUpdate(leftClickPressed, qPressed, dayCounter, mouseX, mouseY);
				House::ClickedNightstand(screen, leftClickPressed, qPressed, coinCounter, mouseX, mouseY);
			}

			// Draw day and coins
			sprintf(day, "DAY: %d", dayCounter);
			sprintf(coins, "COINS: %d", coinCounter);
			screen->Print(day, 750, 10, 0xff0000);
			screen->Print(coins, 10, 10, 0xffff00);
		}
	}
};
