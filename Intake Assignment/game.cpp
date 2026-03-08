#include "game.h"

///to do list:
//sterge tile clicked?
//sterge includurile useless
//verifica ca toate variabilele sa fie folosite
//fa mai logic
//make stuff private


//change map
//improve buttons
//make namespace class

//change crafting frame
//change tiles hover box
//add hovering for all obsects

namespace Tmpl8
{
	//ask:
	//should i make a world class?
	//how many connections between classes are allowed?
	//schiba hover. gen pune sa se puna pe ecran patratul cand mouseul e in zona. e mai easy
	//fa s pot pierde daca nu mai ai potiuni sau iteme sa poti crafta potiunile
	//deltatime = the time between frames

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

	//add state
	//learn aabb cuz its important
	//modify crafting recepie 18 feb update on discord


	//to do:
	//add forward declaration of classes in game.h
	//add turotial class with switch statements and like frame?
	//fix all errors (holy errors btw)
	//make plants


	Game::Game() : player(gameMap), house(player.pInventory()), car(player.pInventory()), tutorial(player.pInventory(), car, house, player.pWateringCan())
	{
	}

	void Game::GodMode()
	{
		if(Input::GetKeyPressed(SDL_SCANCODE_G))
		{
			player.pInventory().SetItemTo(Inventory::Item::VitalTonic, 99);
			player.pInventory().SetItemTo(Inventory::Item::CalmMind, 99);
			player.pInventory().SetItemTo(Inventory::Item::DreamDraught, 99);
			player.pInventory().SetItemTo(Inventory::Item::FireHeart, 99);
			player.pInventory().SetItemTo(Inventory::Item::FrostVeil, 99);
			player.pInventory().SetItemTo(Inventory::Item::Sunblossom, 99);
			player.pInventory().SetItemTo(Inventory::Item::Moonleaf, 99);
			player.pInventory().SetItemTo(Inventory::Item::Emberroot, 99);
			player.pInventory().SetItemTo(Inventory::Item::Frostmint, 99);
			player.pInventory().SetItemTo(Inventory::Item::Berry, 99);
			player.pInventory().SetItemTo(Inventory::Item::SeedSunblossom, 99);
			player.pInventory().SetItemTo(Inventory::Item::SeedMoonleaf, 99);
			player.pInventory().SetItemTo(Inventory::Item::SeedEmberroot, 99);
			player.pInventory().SetItemTo(Inventory::Item::SeedFrostmint, 99);
			player.pInventory().SetItemTo(Inventory::Item::SeedBerry, 99);
			coinCounter = 9999;
		}
	}
	bool Game::AllInventoriesClosed()
	{
		// Check if all inventories are closed
		if (!player.pInventory().MainInvIsOpen() && !car.CarInvIsOpen() && !player.pInventory().SeedInvIsOpen())
			return 1;
		return 0;
	}
	void Game::DrawInventory()
	{
		// Draw inventory
		player.pInventory().Draw(screen);
		if(!player.pInventory().MainInvIsOpen())
			car.Draw(screen);
		//InventoryText();
	}
	void Game::HoverOutsideObjects()
	{
		Sprite car_hover = Sprite(new Surface("assets/car_hover2.png"), 1);
		Sprite door_hover = Sprite(new Surface("assets/door_hover2.png"), 1);
		bool carHover = WorldState::mouseWorldX >= 528 && WorldState::mouseWorldX <= 686 && WorldState::mouseWorldY >= 175 && WorldState::mouseWorldY <= 220;
		bool doorHover = WorldState::mouseWorldX >= 196 && WorldState::mouseWorldX <= 233 && WorldState::mouseWorldY >= 183 && WorldState::mouseWorldY <= 234;
		if (carHover)
			car_hover.Draw(screen, static_cast<int>(503 - WorldState::cameraX), static_cast<int>(152 - WorldState::cameraY)); //fixed conversion from float to int warning
		if (doorHover)
			door_hover.Draw(screen, static_cast<int>(192 - WorldState::cameraX), static_cast<int>(179 - WorldState::cameraY));
	}
	/*void Game::HoverInsideObjects()
	{
		
		bool craftingTableHover = WorldState::mouseX >= 103 && WorldState::mouseX <= 294 && WorldState::mouseY >= 331 && WorldState::mouseY <= 476;
		bool bedHover = WorldState::mouseX >= 511 && WorldState::mouseX <= 742 && WorldState::mouseY >= 320 && WorldState::mouseY <= 565;
		bool nightstandHover = WorldState::mouseX >= 386 && WorldState::mouseX <= 497 && WorldState::mouseY >= 351 && WorldState::mouseY <= 454;
		if (craftingTableHover)
			screen->Box(103, 331, 294, 476, 0xffff00);
		if (bedHover)
			screen->Box(511, 320, 742, 565, 0xffff00);
		if (nightstandHover)
			screen->Box(386, 351, 497, 454, 0xffff00);
	}//not used?*/
	void Game::HandleInput()
	{
		Input::Update(); // Update input states

		// Mouse coordinates
		POINT mousePos;

		if (GetCursorPos(&mousePos))
		{
			HWND hwnd = GetActiveWindow();
			ScreenToClient(hwnd, &mousePos);
			WorldState::mouseX = static_cast<float>(mousePos.x); //fixed conversion from long to float warning
			WorldState::mouseY = static_cast<float>(mousePos.y);
			// Mouse coordinates on screen
			//std::cout << "Mouse X: " << WorldState::mouseX << ", Y: " << WorldState::mouseY << std::endl;
		}
	}
	void Game::PlantSeed(int tileNumber)
	{
		
		// Planting seeds buttons
		bool button1 = Input::GetMouseButtonPressed(1) && WorldState::mouseX >= 458 && WorldState::mouseX <= 499 && WorldState::mouseY >= 224 && WorldState::mouseY <= 250;
		bool button2 = Input::GetMouseButtonPressed(1) && WorldState::mouseX >= 458 && WorldState::mouseX <= 499 && WorldState::mouseY >= 267 && WorldState::mouseY <= 293;
		bool button3 = Input::GetMouseButtonPressed(1) && WorldState::mouseX >= 458 && WorldState::mouseX <= 499 && WorldState::mouseY >= 310 && WorldState::mouseY <= 337;
		bool button4 = Input::GetMouseButtonPressed(1) && WorldState::mouseX >= 458 && WorldState::mouseX <= 499 && WorldState::mouseY >= 355 && WorldState::mouseY <= 379;
		bool button5 = Input::GetMouseButtonPressed(1) && WorldState::mouseX >= 458 && WorldState::mouseX <= 499 && WorldState::mouseY >= 394 && WorldState::mouseY <= 420;

		// Planting seeds if seed inventory is open
		if (player.pInventory().SeedInvIsOpen())
		{
			// Planting Sunblossom seed
			if (button1 && player.pInventory().GetItemCount(Inventory::Item::SeedSunblossom) > 0)
			{
				tutorial.setPlanted(true); // Set tutorial state to seed planted
				farmTiles[tileNumber].CreatePlant(0); // Create plant on farm tile
				player.pInventory().AddItem(Inventory::Item::SeedSunblossom, -1);
				player.pInventory().setSeedState(false);
			}
			// Planting Moonleaf seed
			if (button2 && player.pInventory().GetItemCount(Inventory::Item::SeedMoonleaf) > 0)
			{
				tutorial.setPlanted(true); // Set tutorial state to seed planted
				farmTiles[tileNumber].CreatePlant(1); // Create plant on farm tile
				player.pInventory().AddItem(Inventory::Item::SeedMoonleaf, -1);
				player.pInventory().setSeedState(false);
			}
			// Planting Emberroot seed
			if (button3 && player.pInventory().GetItemCount(Inventory::Item::SeedEmberroot) > 0)
			{
				tutorial.setPlanted(true); // Set tutorial state to seed planted
				farmTiles[tileNumber].CreatePlant(2); // Create plant on farm tile
				player.pInventory().AddItem(Inventory::Item::SeedEmberroot, -1);
				player.pInventory().setSeedState(false);
			}
			// Planting Frostmint seed
			if (button4 && player.pInventory().GetItemCount(Inventory::Item::SeedFrostmint) > 0)
			{
				tutorial.setPlanted(true); // Set tutorial state to seed planted
				farmTiles[tileNumber].CreatePlant(3); // Create plant on farm tile
				player.pInventory().AddItem(Inventory::Item::SeedFrostmint, -1);
				player.pInventory().setSeedState(false);
			}
			// Planting Nightshade Berry seed
			if (button5 && player.pInventory().GetItemCount(Inventory::Item::SeedBerry) > 0)
			{
				tutorial.setPlanted(true); // Set tutorial state to seed planted
				farmTiles[tileNumber].CreatePlant(4); // Create plant on farm tile
				player.pInventory().AddItem(Inventory::Item::SeedBerry, -1);
				player.pInventory().setSeedState(false);
			}
			
		}
	}
	void Game::UpdatePlants()
	{
		for (auto& x : farmTiles)
			x.CollectPlant();
	}
	void Game::UpdateFarmTiles()
	{
		// Tiles
		tileClicked = false;

		index = 0;
		for (auto& x : farmTiles)
		{
			if (AllInventoriesClosed())
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
	void Game::ProgressToNextDay()
	{
		for (auto& x : farmTiles)
		{
			x.UpdatePlant();
			x.setWatered(false);
		}
		car.UpdateOrderDays();
		car.MakeNewOrders();
	}
	void Game::Logic()
	{
		//check if godmode is activated
		GodMode();

		// House interaction
		house.HouseLogic();

		if (!house.IsOpen()) // Outside
		{
			// WateringCan
			player.pWateringCan().WateringCanLogic();
			if (!AllInventoriesClosed())
				player.pWateringCan().setState(false);

			// Inventory
			if (player.pInventory().SeedInvIsOpen()) //check this before update to avoid double click bug
				PlantSeed(index2);
			player.pInventory().MainInventoryLogic(screen);
			car.CarInventoryLogic(coinCounter);
			player.pInventory().SeedInventoryLogic(screen, tileClicked);
			
		}
		else // Inside house
		{
			player.pWateringCan().setState(false); // Disable watering can when house is open

			// Crafting
			house.Craftinglogic();
			if (house.hCrafting().CraftingIsOpen())
				house.hCrafting().CraftPotions();

			// House Interactions
			house.NightstandLogic(coinCounter);
			house.BedLogic(dayCounter);
			if (house.ConfirmedToSleep()) // Player confirmed to sleep, update day and progress plants
				ProgressToNextDay();
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
		tutorial.Update();
	}
	void Game::DrawUI()
	{
		// Draw day and coins
		sprintf(day, "DAY: %d", dayCounter);
		sprintf(coins, "COINS: %d", coinCounter);
		screen->PrintScaled(day, 710, 10, 2, 2, 0x0389afc);
		screen->PrintScaled(coins, 10, 10, 2, 2, 0xffff00);
		if (!house.IsOpen() && AllInventoriesClosed()) // Draw watering can only when outside and inventory is closed
			player.pWateringCan().Draw(screen);
		tutorial.Draw(screen);

	}
	void Game::DrawGame()
	{
		screen->Clear(0);
		if (!house.IsOpen()) // Outside
		{
			gameMap.Draw(screen);
			if(AllInventoriesClosed())
				HoverOutsideObjects();

			// Tiles & Plants
			for (auto& x : farmTiles)
			{
				x.Draw(screen);
				if (AllInventoriesClosed())
					x.DrawHover(screen);
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
			if (house.hCrafting().CraftingIsOpen())
				house.hCrafting().Draw(screen);
		}
		DrawUI();
		
	}

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------

	void Game::Init()
	{
		srand(static_cast<unsigned int>(time(0))); //fixed conversion from time_t to unsigned int warning
		for (int x = 3; x <= 23; x++)
		{
			for (int y = 7; y <= 17; y++)
				farmTiles.emplace_back(x, y, player.pWateringCan(), player.pInventory());
		}
		for (int x = 3; x <= 19; x++)
		{
			for (int y = 18; y <= 20; y++)
				farmTiles.emplace_back(x, y, player.pWateringCan(), player.pInventory());
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

		// Update and draw the world
		UpdateWorld();
		DrawGame();

		// Handle player movement only when outside
		if (!house.IsOpen())
			player.HandleMovement(deltaTime);

		// Check for game completion
		house.GameCompleted(screen, coinCounter, gameCompleted);
	}
};
