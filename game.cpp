#include "game.h"
#include <Audio/Device.hpp>

///to do list:
//verifica ca toate variabilele sa fie folosite
//make stuff private
//unsigned int?

namespace Tmpl8
{
	//fa sa pot pierde daca nu mai ai potiuni sau iteme sa poti crafta potiunile
	
	//add state
	//learn aabb cuz its important
	//modify crafting recepie 18 feb update on discord

	//to do:
	//add forward declaration of classes in game.h
	//fix plant sprite

	//add sound when plant is not ready
	//hotbar for seeds

	//check assets licence

	//make player class -> game has player -> inv
	//map -> house
	//namespace to class de ce

	//learn stuff from player,car(forward declaration),endscreen(default constructor?),farmtile(uniqueptr),input(bittset),inv(maps),map(why -camerax),orders(const* ceva in header,convertion to item),plant(draw poz),player(map poz), why make sprite in constructor in farmtile?

	//update:: button class, split inv and seed inv, states for inv, be able to hold the seeds so you dont need to click "plant" every time (annoying), fix collision and drawing for map (improve collision)

	//vs,git - nu pun in fisier, -> pptx format prezentare
	Game::Game() : camera(), gameMap(camera), player(gameMap, camera), house(player), car(player), tutorial(player, car, house) {};
	void Game::States()
	{
		switch (gameState)
		{
		case GameStates::MainMenu:
			if (gameStarted)
				gameState = GameStates::CutScene;
			break;
		case GameStates::CutScene:
			if (cutScenePlayed)
				gameState = GameStates::InGame;
			break;
		case GameStates::InGame:
			if(gameCompleted)
				gameState = GameStates::EndScreen;
			break;
		}
	}
	void Game::GodMode()
	{
		// Activate debug "God Mode" when G is pressed
		if(Input::GetKeyPressed(SDL_SCANCODE_G))
		{
			for (int i=0;i<static_cast<int>(Inventory::Item	::COUNT);i++)
			{
				Inventory::Item item = static_cast<Inventory::Item>(i);
				player.pInventory().SetItemTo(item, 99);
			}
			coinCounter = 9999;
		}
	}
	void Game::UpdateMouseWorldPosition()
	{
		// worldX = screenX + cameraX;
		// screenX = worldX - cameraX;
	
		// Transform screen coordinates -> world coordinates
		mouseWorldX = camera.getCameraX() + Input::GetMouseX();
		mouseWorldY = camera.getCameraY() + Input::GetMouseY();
		//std::cout << "World X: " << mouseWorldX << ", Y: " << mouseWorldY << std::endl;
	}
	bool Game::AllInventoriesClosed()
	{
		// Check if all inventories are closed
		if (!player.pInventory().MainInvIsOpen() && !car.CarInvIsOpen() && !player.pInventory().SeedInvIsOpen())
			return true;
		return false;
	}
	void Game::HoverOutsideObjects()
	{
		bool carHover = mouseWorldX >= 528 && mouseWorldX <= 686 && mouseWorldY >= 175 && mouseWorldY <= 220;
		bool doorHover = mouseWorldX >= 196 && mouseWorldX <= 233 && mouseWorldY >= 183 && mouseWorldY <= 234;
		if (carHover)
			car_hover.Draw(screen, static_cast<int>(503 - camera.getCameraX()), static_cast<int>(152 - camera.getCameraY())); //fixed conversion from float to int warning
		if (doorHover)
			door_hover.Draw(screen, static_cast<int>(192 - camera.getCameraX()), static_cast<int>(179 - camera.getCameraY()));
	}
	void Game::PlantSeed(FarmTile &farmtile)
	{
		// Planting seeds buttons
		bool button1 = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 458 && Input::GetMouseX() <= 499 && Input::GetMouseY() >= 224 && Input::GetMouseY() <= 250;
		bool button2 = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 458 && Input::GetMouseX() <= 499 && Input::GetMouseY() >= 267 && Input::GetMouseY() <= 293;
		bool button3 = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 458 && Input::GetMouseX() <= 499 && Input::GetMouseY() >= 310 && Input::GetMouseY() <= 337;
		bool button4 = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 458 && Input::GetMouseX() <= 499 && Input::GetMouseY() >= 355 && Input::GetMouseY() <= 379;
		bool button5 = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 458 && Input::GetMouseX() <= 499 && Input::GetMouseY() >= 394 && Input::GetMouseY() <= 420;
		bool planted = false;
		// Planting Sunblossom seed
		if (button1 && player.pInventory().GetItemCount(Inventory::Item::SeedSunblossom) > 0)
		{
			planted = true;
			farmtile.CreatePlant(0); // Create plant on farm tile
			player.pInventory().AddItem(Inventory::Item::SeedSunblossom, -1);
		}
		// Planting Moonleaf seed
		if (button2 && player.pInventory().GetItemCount(Inventory::Item::SeedMoonleaf) > 0)
		{
			planted = true;
			farmtile.CreatePlant(1); // Create plant on farm tile
			player.pInventory().AddItem(Inventory::Item::SeedMoonleaf, -1);
		}
		// Planting Emberroot seed
		if (button3 && player.pInventory().GetItemCount(Inventory::Item::SeedEmberroot) > 0)
		{
			planted = true;
			farmtile.CreatePlant(2); // Create plant on farm tile
			player.pInventory().AddItem(Inventory::Item::SeedEmberroot, -1);
		}
		// Planting Frostmint seed
		if (button4 && player.pInventory().GetItemCount(Inventory::Item::SeedFrostmint) > 0)
		{
			planted = true;
			farmtile.CreatePlant(3); // Create plant on farm tile
			player.pInventory().AddItem(Inventory::Item::SeedFrostmint, -1);
		}
		// Planting Nightshade Berry seed
		if (button5 && player.pInventory().GetItemCount(Inventory::Item::SeedBerry) > 0)
		{
			planted = true;
			farmtile.CreatePlant(4); // Create plant on farm tile
			player.pInventory().AddItem(Inventory::Item::SeedBerry, -1);
		}
		if (planted)
		{
			tutorial.setPlanted(true); // Set tutorial state to seed planted
			player.pInventory().setSeedState(false);
			selectedTile = nullptr;
		}
	}
	void Game::CollectPlants(float deltaTime)
	{
		for (auto& farmtile : farmTiles)
			farmtile.CollectPlant(deltaTime);
	}
	void Game::UpdateFarmTiles()
	{
		tileClicked = false;
		
		for (auto& farmtile : farmTiles)
		{
			if (AllInventoriesClosed())
				farmtile.Update(mouseWorldX, mouseWorldY);
			if (farmtile.isClicked() && !farmtile.isPlanted())
			{
				tileClicked = true;
				selectedTile = &farmtile;
			}
		}
	}
	void Game::ResetFarmTilesClick()
	{
		for (auto& farmtile : farmTiles)
			farmtile.setClicked(false);
	}
	void Game::ProgressToNextDay()
	{
		// ---Plants---
		for (auto& farmtile : farmTiles)
		{
			farmtile.UpdatePlant();
			farmtile.setWatered(false);
		}

		// ---Orders---
		car.UpdateOrderDays();
		car.MakeNewOrders();
	}
	void Game::Logic(float deltaTime)
	{
		GodMode(); // Check if godmode is activated (press G)
		house.HouseLogic(mouseWorldX, mouseWorldY); // House interaction

		if (!house.IsOpen()) // Outside
		{
			//---FarmTiles & Plants---
			UpdateFarmTiles();
			CollectPlants(deltaTime);

			// ---Inventory---
			player.pInventory().MainInventoryLogic();
			car.CarInventoryLogic(coinCounter, mouseWorldX, mouseWorldY);
			if (player.pInventory().SeedInvIsOpen()) // do this before inventory seed logic to avoid double click
				PlantSeed(*selectedTile);
			player.pInventory().SeedInventoryLogic(tileClicked);
			

			// ---WateringCan---
			player.pWateringCan().WateringCanLogic();
			if (!AllInventoriesClosed())
				player.pWateringCan().setState(false);
			
			// ---Orders---
			car.UpdateOrders(coinCounter);
		}
		else // Inside house
		{
			// ---WateringCan---
			player.pWateringCan().setState(false); // Disable watering can when house is open

			// ---Crafting---
			house.Craftinglogic();
			house.hCrafting().ManageFrames();
			if (house.hCrafting().CraftingIsOpen())
				house.hCrafting().CraftPotions();

			// ---Nightstand & Bed---
			house.NightstandLogic();
			house.BedLogic(dayCounter);
			if (house.ConfirmedToSleep())
				ProgressToNextDay();
		}
	}
	void Game::DrawAudioBar()
	{
		int barWidth = static_cast<int>(volume * 3);
		if (Input::GetKey(SDL_SCANCODE_EQUALS) || Input::GetKey(SDL_SCANCODE_MINUS))
		{
			screen->Box(7, 27, 103, 48, 0x000000); // Draw background for volume bar
			screen->Bar(10, 30, 10 + barWidth, 45, 0x276CF5); // Draw volume bar
		}
	}
	void Game::Audio()
	{
		volume = Audio::Device::getMasterVolume();
		// Adjust game volume with +/- keys.
		if (Input::GetKey(SDL_SCANCODE_EQUALS) && volume <= 30)
			Audio::Device::setMasterVolume(volume + 0.1f);
		if (Input::GetKey(SDL_SCANCODE_MINUS))
			Audio::Device::setMasterVolume(volume - 0.1f);
		//std::cout << "Current Volume: " << volume << std::endl;
	}
	void Game::UpdateWorld(float deltaTime)
	{
		States();
		Audio(); 
		if (gameState == GameStates::MainMenu)
		{
			menu.Logic(gameStarted);
		}
		if(gameState == GameStates::CutScene)
		{
			menu.CutSceneLogic(cutScenePlayed);
		}
		if (gameState == GameStates::InGame)
		{
			// ---Player---
			player.HandleMovement(deltaTime);

			// ---Mouse World Coordinates---
			UpdateMouseWorldPosition();

			// ---Check Game Completed---
			house.CheckGameCompleted(coinCounter, gameCompleted);

			// ---FarmTiles---
			ResetFarmTilesClick();

			// ---Core Logic---
			Logic(deltaTime);

			// ---Tutorial---
			tutorial.Update();
		}
		if (gameState == GameStates::EndScreen)
		{
			endScreen.ManageFrames();
		}
	}
	void Game::DrawUI()
	{
		// Draw day and coins
		tutorial.Draw(screen);
		sprintf(day, "DAY: %d", dayCounter);
		sprintf(coins, "COINS: %d", coinCounter);
		screen->PrintScaled(day, 710, 10, 2, 2, 0x0389afc);
		screen->PrintScaled(coins, 10, 10, 2, 2, 0xffff00);
	}
	void Game::DrawGame()
	{
		screen->Clear(0xb0905d); //83924c  b0905d
		if (gameState == GameStates::MainMenu)
		{
			menu.Draw(screen);
		}
		if(gameState == GameStates::CutScene)
		{
			menu.DrawCutScene(screen);
		}
		if (gameState == GameStates::InGame)
		{
			if (!house.IsOpen()) // Outside
			{
				gameMap.Draw(screen);
				if (AllInventoriesClosed())
					HoverOutsideObjects();

				// Tiles & Plants
				for (auto& farmtile : farmTiles)
				{
					farmtile.Draw(screen);
					if (AllInventoriesClosed())
						farmtile.DrawHover(screen, mouseWorldX, mouseWorldY);
				}
				for (auto& farmtile : farmTiles)
				{
					farmtile.DrawPlant(screen);
				}

				// Player
				player.Draw(screen);

				// Watering can
				if (AllInventoriesClosed())
					player.pWateringCan().Draw(screen);

				// Inventory
				player.pInventory().Draw(screen);
				if (!player.pInventory().MainInvIsOpen())
					car.Draw(screen);
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
		if (gameState == GameStates::EndScreen)
		{
			endScreen.DrawGameCompletedScreen(screen);
		}
		DrawAudioBar();
		
	}

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	
	void Game::Init()
	{
		std::cout<<"You can ajust the game volume with +/- keys.\nOther instructions are in the readme file.\n";

		// ---FarmTiles---
		for (int x = 3; x <= 23; x++)
		{
			for (int y = 7; y <= 17; y++)
				farmTiles.emplace_back(static_cast<float>(x), static_cast<float>(y), player, camera);
		}
		for (int x = 3; x <= 19; x++)
		{
			for (int y = 18; y <= 20; y++)
				farmTiles.emplace_back(static_cast<float>(x), static_cast<float>(y), player, camera);
		}

		// ---Orders---
		car.MakeNewOrders();

		// ---Audio---
		backgroundMusic.loadMusic("assets/audio/background.mp3");
		backgroundMusic.setLooping(true);
		backgroundMusic.setVolume(0.2f);
		backgroundMusic.play();
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
		deltaTime /= 1000.0f; // convert to seconds
		Input::Update();
		UpdateWorld(deltaTime);
		DrawGame();
	}
};