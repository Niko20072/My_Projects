#include "game.h"

///do to list:
//sterge tile clicked?
//muta chestiile in subprograme
//sterge includurile useless
//verifica ca toate variabilele sa fie folosite
//fa mai logic
//fa lista de comenzi sa se reseteze la 7 zile
//!!!!!!!!!!!!!!pt plante improve: totul e prea conectat si sunt destul de sigura ca trebuie modificat in asa fel incat toate sa fie mai independente
//fa sa nu poti deschide seed inventory daca stropitoarea e clickuita
//make endint at 1000$
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
	void Game::DrawUI()
	{
		// Draw day and coins
		sprintf(day, "DAY: %d", dayCounter);
		sprintf(coins, "COINS: %d", coinCounter);
		screen->Print(day, 750, 10, 0xff0000);
		screen->Print(coins, 10, 10, 0xffff00);
		if (WateringCan::wateringCan)
			screen->Print("Watering Can Equipped", 340, 585, 0x00ff00);
	}
	void Game::DrawGame()
	{
		// Draw farm tiles
		for (auto& x : FarmTile::farmTiles)
		{
			x.Draw(screen);
		}
		for (auto& x : Plant::plants)
		{
			if (!x.harvested)
				x.Draw(screen);
		}
		///move this to inventory draw function !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! maybe?
		if (Inventory::carisopen && Inventory::frame == 5)
		{
			for (auto& x : Order::orders)
			{
				x.Draw(screen);
			}
		}
		DrawUI();
	}
	void Game::HandleInput()
	{
		// -----------------------------------------------------------
		// Get mouse coordinates
		// -----------------------------------------------------------

		POINT mousePos;

		if (GetCursorPos(&mousePos))
		{
			HWND hwnd = GetActiveWindow();
			ScreenToClient(hwnd, &mousePos);
			WorldState::mouseX = mousePos.x;
			WorldState::mouseY = mousePos.y;
			// Mouse coordinates on screen
			//std::cout << "Mouse X: " << mouseX << ", Y: " << mouseY << std::endl;
		}
		// -----------------------------------------------------------
		// Buttons
		// -----------------------------------------------------------

		Buttons::SetValues(WorldState::mouseX, WorldState::mouseY);
		qPressed = Buttons::KeyQ();
		ePressed = Buttons::KeyE();
		rPressed = Buttons::KeyR();
		leftClickPressed = Buttons::LeftClick();
	}
	void Game::HandleMovement(float deltaTime)
	{
		// -----------------------------------------------------------
		// Movement and collision
		// -----------------------------------------------------------
		
		// New camera position
		float newCameraX = Map::cameraX;
		float newCameraY = Map::cameraY;

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
		if (CheckCollision(newCameraX + WorldState::playerX, newCameraY + WorldState::playerY) == true)
		{
			Map::cameraX = newCameraX;
			Map::cameraY = newCameraY;
		}
	}
	void Game::UpdatePlants()
	{
		for (auto& x : Plant::plants)
		{
			x.Grown();
		}
	}
	void Game::UpdateOrders()
	{
		if (Inventory::carisopen && Inventory::frame == 5)
		{
			for (auto& x : Order::orders)
			{
				x.Logic(screen, leftClickPressed, WorldState::mouseX, WorldState::mouseY, coinCounter);
			}
		}
		//check if all orders are completed
		if (Order::daysUntilReset == 0) ///or CheckAllCompleted()
		{
			//generate new orders
			Order::daysUntilReset = 5;
			Order::orders.clear();
			srand(time(0));
			for (int i = 0; i <= 5; i++)
				Order::orders.emplace_back(i);
		}
	}
	void Game::UpdateFarmTiles()
	{

	}
	void Game::UpdateWorld()
	{
		UpdateFarmTiles();
		UpdatePlants();
		UpdateOrders();
		WateringCan::Water(rPressed);
		for (auto& x : FarmTile::farmTiles) // reset clicked state
		{
			x.clicked = false;
		}
	}
	/* //not used anymore
	bool Game::CheckAllCompleted()
	{
		for (auto order : orders)
		{
			if (order.completed == false)
				return false;
		}
		return true;
	}*/
	
	
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
			Order::orders.emplace_back(i);
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------

	void Game::Shutdown()
	{
		FarmTile::farmTiles.clear();
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	
	void Game::Tick(float deltaTime)
	{
		deltaTime /= 1000.0f; // convert to seconds.
		screen->Clear(0);
		HandleInput();
		WorldState::UpdateWorldState();
		

		// Check for game completion
		House::GameCompleted(screen, leftClickPressed, qPressed, coinCounter, WorldState::mouseX, WorldState::mouseY, gameCompleted);
		
		if (!gameCompleted)
		{
			// -----------------------------------------------------------
			// Drawing stuff
			// -----------------------------------------------------------

			// Show House when left click in house area
			House::ShowHouse(screen, qPressed, WorldState::reachX1, WorldState::reachX2, WorldState::reachY1, WorldState::reachY2, WorldState::worldX, WorldState::worldY);

			// Crafting
			Crafting::ShowCrafting(screen, leftClickPressed, qPressed, WorldState::mouseX, WorldState::mouseY);
			if (Crafting::craftingisopen == true)
				Crafting::Craft(leftClickPressed, WorldState::mouseX, WorldState::mouseY);

			// Main game view
			if (!House::houseisopen)
			{
				gameMap.DrawMap(screen);

				// Tiles
				tileClicked = false;
				
				index = 0;
				for (auto& x : FarmTile::farmTiles)
				{
					index++;
					if (Inventory::InventorysClosed())
						x.Update(leftClickPressed, x.farmTileX, x.farmTileY, WorldState::worldX, WorldState::worldY, WorldState::reachX1, WorldState::reachX2, WorldState::reachY1, WorldState::reachY2);
					if (x.clicked && !x.isClicked)
					{
						tileClicked = true;
						plantX = x.farmTileX;
						plantY = x.farmTileY;
						index2 = index - 1;
						break;
					}
				}

				UpdateWorld();
				DrawGame();

				//Player range
				//screen->Box(worldPlayerX - Map::cameraX, worldPlayerY - Map::cameraY, worldPlayerX + 46 - Map::cameraX, worldPlayerY + 94 - Map::cameraY, 0xff0000);
				screen->Box(WorldState::reachX1 - Map::cameraX, WorldState::reachY1 - Map::cameraY, WorldState::reachX2 - Map::cameraX, WorldState::reachY2 - Map::cameraY, 0x00ff00);

				//drawing stuff on screen
				player.Draw(screen, WorldState::playerX, WorldState::playerY);
				Inventory::MainInventory(screen, leftClickPressed, ePressed, qPressed, WorldState::mouseX, WorldState::mouseY);
				Inventory::CarInventory(screen, coinCounter, ePressed, qPressed, leftClickPressed, WorldState::mouseX, WorldState::mouseY, WorldState::worldX, WorldState::worldY, WorldState::reachX1, WorldState::reachY1, WorldState::reachX2, WorldState::reachY2);
				Inventory::SeedsInventory(screen, ePressed, qPressed, leftClickPressed, WorldState::mouseX, WorldState::mouseY, WorldState::worldX, WorldState::worldY, plantX, plantY, tileClicked, index2);
				Inventory::DrawOnScreen(screen, deltaTime);

				HandleMovement(deltaTime);

			}
			else // Inside house
			{
				House::DayUpdate(leftClickPressed, qPressed, dayCounter, WorldState::mouseX, WorldState::mouseY);
				House::ClickedNightstand(screen, leftClickPressed, qPressed, coinCounter, WorldState::mouseX, WorldState::mouseY);
			}
			//DrawUI();
		}
	}
};
