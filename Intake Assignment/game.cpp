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
	//Public variables in inventory
	//should i make a world class?
	//if i make the map variables private that means i need to have a reference to the map in the farm tile and plant class? or should i just make the map variables public? Or move to worldstate?
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

	Game::Game() : player(), house(player.playerInventory()), car(player.playerInventory())
	{
	}

	bool Game::InventorysClosed()
	{
		// Check if all inventories are closed
		if (!player.playerInventory().getInvState() && !car.getCarState() && !player.playerInventory().getSeedState())
			return 1;
		return 0;
	}
	void Game::InventoryText()
	{
		// Display values
		char sunBlossom[32], moonLeaf[32], emberRoot[32], frostMint[32], berry[32];
		char vitalTonic[32], calmMind[32], dreamDraught[32], fireHeart[32], frostVeil[32];
		char seedSunBlossom[32], seedMoonLeaf[32], seedEmberRoot[32], seedFrostMint[32], seedBerry[32];
		char counterSeedSunBlossom[32], counterSeedMoonLeaf[32], counterSeedEmberRoot[32], counterSeedFrostMint[32], counterSeedBerry[32];

		// Format strings with current counts
		sprintf(sunBlossom, "Sunblossom          x%d", player.playerInventory().GetItemCount(Inventory::Item::Sunblossom));
		sprintf(moonLeaf, "Moonleaf            x%d", player.playerInventory().GetItemCount(Inventory::Item::Moonleaf));
		sprintf(emberRoot, "Emberroot           x%d", player.playerInventory().GetItemCount(Inventory::Item::Emberroot));
		sprintf(frostMint, "Frostmint           x%d", player.playerInventory().GetItemCount(Inventory::Item::Frostmint));
		sprintf(berry, "Nightshade Berry    x%d", player.playerInventory().GetItemCount(Inventory::Item::Berry));

		sprintf(vitalTonic, "Vital Tonic         x%d", player.playerInventory().GetItemCount(Inventory::Item::VitalTonic));
		sprintf(calmMind, "Calm Mind Elixir    x%d", player.playerInventory().GetItemCount(Inventory::Item::CalmMind));
		sprintf(dreamDraught, "Dream Draught       x%d", player.playerInventory().GetItemCount(Inventory::Item::DreamDraught));
		sprintf(fireHeart, "FireHeart Brew      x%d", player.playerInventory().GetItemCount(Inventory::Item::FireHeart));
		sprintf(frostVeil, "Frostveil Potion    x%d", player.playerInventory().GetItemCount(Inventory::Item::FrostVeil));

		sprintf(seedSunBlossom, "Sunblossom          x%d", player.playerInventory().GetItemCount(Inventory::Item::SeedSunblossom));
		sprintf(seedMoonLeaf, "Moonleaf            x%d", player.playerInventory().GetItemCount(Inventory::Item::SeedMoonleaf));
		sprintf(seedEmberRoot, "Emberroot           x%d", player.playerInventory().GetItemCount(Inventory::Item::SeedEmberroot));
		sprintf(seedFrostMint, "Frostmint           x%d", player.playerInventory().GetItemCount(Inventory::Item::SeedFrostmint));
		sprintf(seedBerry, "Nightshade Berry    x%d", player.playerInventory().GetItemCount(Inventory::Item::SeedBerry));

		sprintf(counterSeedSunBlossom, "x%d", player.playerInventory().GetItemCount(Inventory::Item::SeedSunblossom));
		sprintf(counterSeedMoonLeaf, "x%d", player.playerInventory().GetItemCount(Inventory::Item::SeedMoonleaf));
		sprintf(counterSeedEmberRoot, "x%d", player.playerInventory().GetItemCount(Inventory::Item::SeedEmberroot));
		sprintf(counterSeedFrostMint, "x%d", player.playerInventory().GetItemCount(Inventory::Item::SeedFrostmint));
		sprintf(counterSeedBerry, "x%d", player.playerInventory().GetItemCount(Inventory::Item::SeedBerry));

		// Display when ingredients inventory is open
		if (player.playerInventory().getInvState() && player.playerInventory().getFrame() == 0)
		{
			screen->Print(sunBlossom, 350, 236, 0x0);
			screen->Print(moonLeaf, 350, 280, 0x0);
			screen->Print(emberRoot, 350, 321, 0x0);
			screen->Print(frostMint, 350, 367, 0x0);
			screen->Print(berry, 350, 411, 0x0);
		}
		// Display when potions inventory is open
		if (player.playerInventory().getInvState() && player.playerInventory().getFrame() == 1)
		{
			screen->Print(vitalTonic, 350, 241, 0x0);
			screen->Print(calmMind, 350, 285, 0x0);
			screen->Print(dreamDraught, 350, 328, 0x0);
			screen->Print(fireHeart, 350, 373, 0x0);
			screen->Print(frostVeil, 350, 418, 0x0);
		}
		// Display when seeds inventory is open
		if (player.playerInventory().getInvState() && player.playerInventory().getFrame() == 2)
		{
			screen->Print(seedSunBlossom, 350, 236, 0x0);
			screen->Print(seedMoonLeaf, 350, 280, 0x0);
			screen->Print(seedEmberRoot, 350, 321, 0x0);
			screen->Print(seedFrostMint, 350, 367, 0x0);
			screen->Print(seedBerry, 350, 411, 0x0);
		}
		// Display when planting seeds inventory is open
		if (player.playerInventory().getSeedState() && player.playerInventory().getFrame() == 3)
		{
			screen->Print(counterSeedSunBlossom, 350 + 160, 236, 0x0);
			screen->Print(counterSeedMoonLeaf, 350 + 160, 280, 0x0);
			screen->Print(counterSeedEmberRoot, 350 + 160, 321, 0x0);
			screen->Print(counterSeedFrostMint, 350 + 160, 367, 0x0);
			screen->Print(counterSeedBerry, 350 + 160, 411, 0x0);
		}
		// Display when car shop inventory is open
		if (car.getCarState() && car.getFrame() == 4)
		{
			screen->Print(counterSeedSunBlossom, 350 + 160, 236, 0x0);
			screen->Print(counterSeedMoonLeaf, 350 + 160, 280, 0x0);
			screen->Print(counterSeedEmberRoot, 350 + 160, 321, 0x0);
			screen->Print(counterSeedFrostMint, 350 + 160, 367, 0x0);
			screen->Print(counterSeedBerry, 350 + 160, 411, 0x0);
		}
	}
	void Game::DrawInventory()
	{
		// Draw inventory
		player.playerInventory().Draw(screen);
		if(!player.playerInventory().getInvState())
			car.Draw(screen);
		InventoryText();
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
	void Game::PlantSeeds(Surface* screen, int tileNumber)
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
			if (button1 && player.playerInventory().GetItemCount(Inventory::Item::SeedSunblossom) > 0)
			{
				farmTiles[tileNumber].CreatePlant(0); // Create plant on farm tile
				player.playerInventory().AddItem(Inventory::Item::SeedSunblossom, -1);
				player.playerInventory().setSeedState(false);
				Buttons::leftPressed = false; // Reset left click state to avoid multiple plantings
			}
			// Planting Moonleaf seed
			if (button2 && player.playerInventory().GetItemCount(Inventory::Item::SeedMoonleaf) > 0)
			{
				farmTiles[tileNumber].CreatePlant(1); // Create plant on farm tile
				player.playerInventory().AddItem(Inventory::Item::SeedMoonleaf, -1);
				player.playerInventory().setSeedState(false);
				Buttons::leftPressed = false; // Reset left click state to avoid multiple plantings
			}
			// Planting Emberroot seed
			if (button3 && player.playerInventory().GetItemCount(Inventory::Item::SeedEmberroot) > 0)
			{
				farmTiles[tileNumber].CreatePlant(2); // Create plant on farm tile
				player.playerInventory().AddItem(Inventory::Item::SeedEmberroot, -1);
				player.playerInventory().setSeedState(false);
				Buttons::leftPressed = false; // Reset left click state to avoid multiple plantings
			}
			// Planting Frostmint seed
			if (button4 && player.playerInventory().GetItemCount(Inventory::Item::SeedFrostmint) > 0)
			{
				farmTiles[tileNumber].CreatePlant(3); // Create plant on farm tile
				player.playerInventory().AddItem(Inventory::Item::SeedFrostmint, -1);
				player.playerInventory().setSeedState(false);
				Buttons::leftPressed = false; // Reset left click state to avoid multiple plantings
			}
			// Planting Nightshade Berry seed
			if (button5 && player.playerInventory().GetItemCount(Inventory::Item::SeedBerry) > 0)
			{
				farmTiles[tileNumber].CreatePlant(4); // Create plant on farm tile
				player.playerInventory().AddItem(Inventory::Item::SeedBerry, -1);
				player.playerInventory().setSeedState(false);
				Buttons::leftPressed = false; // Reset left click state to avoid multiple plantings
			}
			
		}
	}
	void Game::UpdatePlants()
	{
		for (auto& x : farmTiles)
		{
			x.CollectPlant();
		}
	}
	void Game::UpdateFarmTiles()
	{
		// Tiles
		tileClicked = false;

		index = 0;
		for (auto& x : farmTiles)
		{
			if (InventorysClosed())
				x.Update();
			if (x.getClicked() && !x.getPlanted())
			{
				tileClicked = true;
				index2 = index;
				break;
			}
			index++;
		}
	}
	void Game::UpdateNextDay()
	{
		for (auto& x : farmTiles)
		{
			x.UpdatePlant();
			x.setWatered(false);
		}
		car.RemoveDays();
		car.MakeNewOrders();
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
			player.playerInventory().MainInventoryLogic(screen);
			car.CarInventory(coinCounter);
			player.playerInventory().PlantingSeedsInventory(screen, tileClicked);
			if(player.playerInventory().getSeedState())
				PlantSeeds(screen, index2);
		}
		else // Inside house
		{
			player.playerWateringCan().setState(false); // Disable watering can when house is open
			// Crafting
			if (house.getCrafting().getState())
				house.getCrafting().CraftLogic();
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
		car.UpdateOrders(coinCounter);
		Logic();
	}
	void Game::DrawUI()
	{
		// Draw day and coins
		sprintf(day, "DAY: %d", dayCounter);
		sprintf(coins, "COINS: %d", coinCounter);
		screen->Print(day, 750, 10, 0xff0000);
		screen->Print(coins, 10, 10, 0xffff00);
		if (!house.getHouseState() && InventorysClosed()) // Draw watering can only when outside and inventory is closed
			player.playerWateringCan().Draw(screen);
	}
	void Game::DrawGame()
	{
		screen->Clear(0);
		if (!house.getHouseState()) // Outside
		{
			gameMap.DrawMap(screen);

			// Tiles & Plants
			for (auto& x : farmTiles)
			{
				x.Draw(screen);
				x.DrawPlant(screen);
			}
				
			// Player
			player.Draw(screen);

			//Inventory
			DrawInventory();
			car.DrawOrders(screen);
		}
		else // Inside house
		{
			house.Draw(screen);
			if (house.getCrafting().getState() == true)
				house.getCrafting().Draw(screen);
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
				farmTiles.emplace_back(x, y, player.playerWateringCan(), player.playerInventory());
		}
		for (int x = 3; x <= 19; x++)
		{
			for (int y = 18; y <= 20; y++)
				farmTiles.emplace_back(x, y, player.playerWateringCan(), player.playerInventory());
		}
		car.MakeNewOrders();
	}

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------

	void Game::Shutdown()
	{
		farmTiles.clear();
		//delete plants?
		//orders.clear();
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------

	void Game::Tick(float deltaTime)
	{
		deltaTime /= 1000.0f; // convert to seconds.
		
		HandleInput();
		WorldState::UpdateWorldState();

		// Check for game completion
		house.GameCompleted(screen, coinCounter, gameCompleted);

		// Update and draw the world only if the game is not completed
		if (!gameCompleted)
		{
			UpdateWorld();
			DrawGame();
			if (!house.getHouseState()) // Handle player movement only when outside      !player.isinhouse
				player.HandleMovement(deltaTime);
		}
	}
};
