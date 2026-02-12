#include "game.h"

///to do list:
//sterge tile clicked?
//muta chestiile in subprograme
//sterge includurile useless
//verifica ca toate variabilele sa fie folosite
//fa mai logic
//fa lista de comenzi sa se reseteze la 7 zile
//!!!!!!!!!!!!!!pt plante improve: totul e prea conectat si sunt destul de sigura ca trebuie modificat in asa fel incat toate sa fie mai independente
//fa sa nu poti deschide seed inventory daca stropitoarea e clickuita
//make ending at 1000$???
//make stuff private


//change map
//improve buttons
//make namespace class
namespace Tmpl8
{
	/// <summary>
	/// ecapsulation and data hiding!!!!
	/// getter, setter!!!!!!!
	/// </summary>

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

	Game::Game() : player(), house(player.playerInventory())
	{
	}

	static Sprite player1(new Surface("assets/Vera.png"), 4);
	bool Game::CheckCollision(float x, float y)
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
	void Game::HandleInput()
	{
		// Mouse coordinates
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

		// Buttons
		Buttons::CheckClick();

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
			player1.SetFrame(0);
			movedir.x = -1;
		}
		if (GetAsyncKeyState('D'))
		{
			player1.SetFrame(1);
			movedir.x = 1;
		}
		if (GetAsyncKeyState('W'))
		{
			player1.SetFrame(3);
			movedir.y = -1;
		}
		if (GetAsyncKeyState('S'))
		{
			player1.SetFrame(2);
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
	void Game::PlantSeeds(Surface* screen, float plantX, float plantY, int tileNumber)
	{
		
		// Planting seeds buttons
		bool button1 = Buttons::leftPressed && WorldState::mouseX >= 458 && WorldState::mouseX <= 499 && WorldState::mouseY >= 224 && WorldState::mouseY <= 250;
		bool button2 = Buttons::leftPressed && WorldState::mouseX >= 458 && WorldState::mouseX <= 499 && WorldState::mouseY >= 267 && WorldState::mouseY <= 293;
		bool button3 = Buttons::leftPressed && WorldState::mouseX >= 458 && WorldState::mouseX <= 499 && WorldState::mouseY >= 310 && WorldState::mouseY <= 337;
		bool button4 = Buttons::leftPressed && WorldState::mouseX >= 458 && WorldState::mouseX <= 499 && WorldState::mouseY >= 355 && WorldState::mouseY <= 379;
		bool button5 = Buttons::leftPressed && WorldState::mouseX >= 458 && WorldState::mouseX <= 499 && WorldState::mouseY >= 394 && WorldState::mouseY <= 420;

		// Planting seeds if seed inventory is open
		if (player.playerInventory().getSeedState())
		{
			// Planting Sunblossom seed
			if (button1 && player.playerInventory().contSeedSunblossom > 0)
			{
				Plant::plants.emplace_back(plantX, plantY, 2, 0, tileNumber, player.playerInventory());
				player.playerInventory().contSeedSunblossom--;
				player.playerInventory().setSeedState(false);
				Buttons::leftPressed = false; // Reset left click state to avoid multiple plantings
			}
			// Planting Moonleaf seed
			if (button2 && player.playerInventory().contSeedMoonleaf > 0)
			{
				Plant::plants.emplace_back(plantX, plantY, 2, 3, tileNumber, player.playerInventory());
				player.playerInventory().contSeedMoonleaf--;
				player.playerInventory().setSeedState(false);
				Buttons::leftPressed = false; // Reset left click state to avoid multiple plantings
			}
			// Planting Emberroot seed
			if (button3 && player.playerInventory().contSeedEmberroot > 0)
			{
				Plant::plants.emplace_back(plantX, plantY, 3, 6, tileNumber, player.playerInventory());
				player.playerInventory().contSeedEmberroot--;
				player.playerInventory().setSeedState(false);
				Buttons::leftPressed = false; // Reset left click state to avoid multiple plantings
			}
			// Planting Frostmint seed
			if (button4 && player.playerInventory().contSeedFrostmint > 0)
			{
				Plant::plants.emplace_back(plantX, plantY, 3, 10, tileNumber, player.playerInventory());
				player.playerInventory().contSeedFrostmint--;
				player.playerInventory().setSeedState(false);
				Buttons::leftPressed = false; // Reset left click state to avoid multiple plantings
			}
			// Planting Nightshade Berry seed
			if (button5 && player.playerInventory().contSeedBerry > 0)
			{
				Plant::plants.emplace_back(plantX, plantY, 4, 14, tileNumber, player.playerInventory());
				player.playerInventory().contSeedBerry--;
				player.playerInventory().setSeedState(false);
				Buttons::leftPressed = false; // Reset left click state to avoid multiple plantings
			}
			
		}
	}
	void Game::UpdatePlants()
	{
		for (auto& x : Plant::plants)
		{
			x.Update();
		}
	}
	void Game::ResetOrders()
	{
		//check if all orders are completed
		if (Order::daysUntilReset == 0) ///or CheckAllCompleted()
		{
			//generate new orders
			Order::daysUntilReset = 5;
			Order::orders.clear();
			srand(time(0));
			for (int i = 0; i <= 5; i++)
				Order::orders.emplace_back(i,player.playerInventory());
		}
	}
	void Game::UpdateOrders()
	{
		if (player.playerInventory().getCarState() && player.playerInventory().getFrame() == 5)
			for (auto& x : Order::orders)
				x.Logic(coinCounter);
		ResetOrders();
	}
	void Game::UpdateFarmTiles()
	{
		// Tiles
		tileClicked = false;

		index = 0; // farmtile index in vector
		for (auto& x : FarmTile::farmTiles)
		{
			if (player.playerInventory().InventorysClosed())
				x.Update(x.getX(), x.getY());
			if (x.getClicked() && !x.getIsClicked())
			{
				tileClicked = true;
				plantX = x.getX();
				plantY = x.getY();
				index2 = index; // index where plant is being created
				break;
			}
			index++;
		}
	}
	void Game::Logic()
	{
		// House interaction
		house.HouseLogic();

		if (!house.getHouseState()) // Outside
		{
			// WateringCan
			player.playerWateringCan().WateringCanState();

			// Inventory
			player.playerInventory().MainInventory(screen);
			player.playerInventory().CarInventory(screen, coinCounter);
			player.playerInventory().SeedsInventory(screen, plantX, plantY, tileClicked);
			if(player.playerInventory().getSeedState())
				PlantSeeds(screen, plantX, plantY, index2);
		}
		else // Inside house
		{
			player.playerWateringCan().setState(false); // Disable watering can when house is open
			// Crafting
			if (house.getCrafting().getState())
				house.getCrafting().Craft();
			house.ManageCrafring();
			house.DayUpdate(dayCounter);
			house.NightstandLogic(screen, coinCounter);
		}

		// reset farmtile clicked state
		for (auto& x : FarmTile::farmTiles)
			x.setClicked(false);
	}
	void Game::UpdateWorld()
	{
		UpdateFarmTiles();
		UpdatePlants();
		UpdateOrders();
		Logic();
	}
	void Game::DrawUI()
	{
		// Draw day and coins
		sprintf(day, "DAY: %d", dayCounter);
		sprintf(coins, "COINS: %d", coinCounter);
		screen->Print(day, 750, 10, 0xff0000);
		screen->Print(coins, 10, 10, 0xffff00);
		if (player.playerWateringCan().getState())
			screen->Print("Watering Can Equipped", 340, 585, 0x00ff00);
	}
	void Game::DrawGame()
	{
		if (!house.getHouseState()) // Outside
		{
			gameMap.DrawMap(screen);

			// Tiles
			for (auto& x : FarmTile::farmTiles)
				x.Draw(screen);

			// Plants
			for (auto& x : Plant::plants)
				if (!x.getHarvested())
					x.Draw(screen);

			// Player reach box
			screen->Box(WorldState::reachX1 - Map::cameraX, WorldState::reachY1 - Map::cameraY, WorldState::reachX2 - Map::cameraX, WorldState::reachY2 - Map::cameraY, 0x00ff00);

			// Player Sprite
			player1.Draw(screen, WorldState::playerX, WorldState::playerY);

			//Inventory
			player.playerInventory().Draw(screen);
			if (player.playerInventory().getCarState() && player.playerInventory().getFrame() == 5)
			{
				//Orders
				for (auto& x : Order::orders)
					x.Draw(screen);
			}
		}
		else // Inside house
		{
			house.Draw(screen);
			if (house.getCrafting().getState() == true)
			{
				house.getCrafting().Draw(screen);
				house.getCrafting().CraftingDraw(screen);
			}
		}

		DrawUI();
	}

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------

	void Game::Init()
	{
		srand(time(0));
		//Plant::inventory = &inventory;
		for (int x = 3; x <= 23; x++)
		{
			for (int y = 7; y <= 17; y++)
				FarmTile::farmTiles.emplace_back(x, y, player.playerWateringCan());
		}
		for (int x = 3; x <= 19; x++)
		{
			for (int y = 18; y <= 20; y++)
				FarmTile::farmTiles.emplace_back(x, y, player.playerWateringCan());
		}
		for (int i = 0; i <= 5; i++)
			Order::orders.emplace_back(i, player.playerInventory());
	}

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------

	void Game::Shutdown()
	{
		FarmTile::farmTiles.clear();
		Plant::plants.clear();
		Order::orders.clear();
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
		house.GameCompleted(screen, coinCounter, gameCompleted);

		if (!gameCompleted)
		{
			UpdateWorld();
			DrawGame();
			HandleMovement(deltaTime);
		}

		//update keystate in game
	}
};
