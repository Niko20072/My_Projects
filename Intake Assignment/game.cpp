#include "game.h"

///to do list:
//sterge tile clicked?
//sterge includurile useless
//verifica ca toate variabilele sa fie folosite
//fa mai logic
//!!!!!!!!!!!!!!pt plante improve: totul e prea conectat si sunt destul de sigura ca trebuie modificat in asa fel incat toate sa fie mai independente
//make ending at 1000$???
//make stuff private


//change map
//improve buttons
//make namespace class
namespace Tmpl8
{
	//ask:
	//order logic vector
	//global variables
	//public vectors
	//should i make a world class?
	//if i make the map variables private that means i need to have a reference to the map in the farm tile and plant class? or should i just make the map variables public?
	//how many connections between classes are allowed?

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
				plants.emplace_back(plantX, plantY, 2, 0, tileNumber, player.playerInventory());
				player.playerInventory().contSeedSunblossom--;
				player.playerInventory().setSeedState(false);
				Buttons::leftPressed = false; // Reset left click state to avoid multiple plantings
			}
			// Planting Moonleaf seed
			if (button2 && player.playerInventory().contSeedMoonleaf > 0)
			{
				plants.emplace_back(plantX, plantY, 2, 3, tileNumber, player.playerInventory());
				player.playerInventory().contSeedMoonleaf--;
				player.playerInventory().setSeedState(false);
				Buttons::leftPressed = false; // Reset left click state to avoid multiple plantings
			}
			// Planting Emberroot seed
			if (button3 && player.playerInventory().contSeedEmberroot > 0)
			{
				plants.emplace_back(plantX, plantY, 3, 6, tileNumber, player.playerInventory());
				player.playerInventory().contSeedEmberroot--;
				player.playerInventory().setSeedState(false);
				Buttons::leftPressed = false; // Reset left click state to avoid multiple plantings
			}
			// Planting Frostmint seed
			if (button4 && player.playerInventory().contSeedFrostmint > 0)
			{
				plants.emplace_back(plantX, plantY, 3, 10, tileNumber, player.playerInventory());
				player.playerInventory().contSeedFrostmint--;
				player.playerInventory().setSeedState(false);
				Buttons::leftPressed = false; // Reset left click state to avoid multiple plantings
			}
			// Planting Nightshade Berry seed
			if (button5 && player.playerInventory().contSeedBerry > 0)
			{
				plants.emplace_back(plantX, plantY, 4, 14, tileNumber, player.playerInventory());
				player.playerInventory().contSeedBerry--;
				player.playerInventory().setSeedState(false);
				Buttons::leftPressed = false; // Reset left click state to avoid multiple plantings
			}
			
		}
	}
	void Game::UpdatePlants()
	{
		for (auto& x : plants)
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
			orders.clear();
			srand(time(0));
			for (int i = 0; i <= 5; i++)
				orders.emplace_back(i,player.playerInventory());
		}
	}
	void Game::UpdateOrders()
	{
		if (player.playerInventory().getCarState() && player.playerInventory().getFrame() == 5)
			for (auto& x : orders)
				x.Logic(coinCounter);
		ResetOrders();
	}
	void Game::UpdateFarmTiles()
	{
		// Tiles
		tileClicked = false;

		index = 0; // farmtile index in vector
		for (auto& x : farmTiles)
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
	void Game::UpdateNextDay()
	{
		for (auto& x : plants)
			if (x.getGrown() == false)
				x.NextDay();
		for (auto& x : farmTiles)
			x.setWatered(false);
		Order::daysUntilReset--;
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
			house.NightstandLogic(screen, coinCounter);
			if (house.ClickedNextDay()) // Player confirmed to sleep, update day and progress plants
				UpdateNextDay();
			house.BedLogic(dayCounter);
		}

		// reset farmtile clicked state
		for (auto& x : farmTiles)
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
		if (!house.getHouseState() && player.playerInventory().InventorysClosed()) // Draw watering can only when outside and inventory is closed
			player.playerWateringCan().Draw(screen);
	}
	void Game::DrawGame()
	{
		if (!house.getHouseState()) // Outside
		{
			gameMap.DrawMap(screen);

			// Tiles
			for (auto& x : farmTiles)
				x.Draw(screen);

			// Plants
			for (auto& x : plants)
				if (!x.getHarvested())
					x.Draw(screen);

			// Player
			player.Draw(screen);

			//Inventory
			player.playerInventory().Draw(screen);
			if (player.playerInventory().getCarState() && player.playerInventory().getFrame() == 5)
			{
				//Orders
				for (auto& x : orders)
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
				farmTiles.emplace_back(x, y, player.playerWateringCan());
		}
		for (int x = 3; x <= 19; x++)
		{
			for (int y = 18; y <= 20; y++)
				farmTiles.emplace_back(x, y, player.playerWateringCan());
		}
		for (int i = 0; i <= 5; i++)
			orders.emplace_back(i, player.playerInventory());
	}

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------

	void Game::Shutdown()
	{
		farmTiles.clear();
		plants.clear();
		orders.clear();
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

		// Update and draw the world only if the game is not completed
		if (!gameCompleted)
		{
			UpdateWorld();
			DrawGame();
			player.HandleMovement(deltaTime);
		}
	}
};
