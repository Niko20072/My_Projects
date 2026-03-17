#include "house.h"
#include "input.h"
#include "Windows.h"
#include "player.h"

namespace Tmpl8
{
	House::House(Player& pl) : player(pl), inventory(player.pInventory()), crafting(inventory) {};
	bool House::IsOpen()
	{
		return houseisopen;
	}
	int House::getFrame()
	{
		return frame;
	}
	int House::MainScreenOpen()
	{
		if(IsOpen() && frame == 0 && !nightstandisopen)
			return 1;
		return 0;
	}
	void House::HouseLogic(float mouseWorldX, float mouseWorldY)
	{
		// Check if player clicked on house door and is in reach
		bool houseInReach = player.getReachX2() >= 196 && player.getReachX1() <= 233 && player.getReachY2() >= 183 && player.getReachY1() <= 232;
		bool hoverOnDoor = mouseWorldX >= 196 && mouseWorldX <= 233 && mouseWorldY >= 183 && mouseWorldY <= 234;

		// Open house if left mouse button is clicked while in reach of door
		if (Input::GetMouseButtonPressed(1) && houseInReach && hoverOnDoor)
		{
			houseisopen = true;
			frame = 0;
			house.SetFrame(frame);
		}

		// Close house if Q is pressed and crafting menu is not open
		if (Input::GetKeyPressed(SDL_SCANCODE_Q) && !crafting.CraftingIsOpen() && !bedisopen && !nightstandisopen)
			houseisopen = false;
	}
	void House::Craftinglogic()
	{
		bool clickedOnTable = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 103 && Input::GetMouseX() <= 294 && Input::GetMouseY() >= 331 && Input::GetMouseY() <= 476;

		// Open crafting interface when clicking on crafting table inside house
		if (clickedOnTable && houseisopen && frame == 0) //fix this
		{
			crafting.setState(true);
			frame = 0;
			crafting.setFrame(frame);
		}
		// Close crafting interface when pressing Q
		if (Input::GetKeyPressed(SDL_SCANCODE_Q) && crafting.CraftingIsOpen())
			crafting.setState(false);
	}
	bool House::ConfirmedToSleep()
	{
		// Check if player clicked yes or no buttons
		clickedYes = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 235 && Input::GetMouseX() <= 389 && Input::GetMouseY() >= 310 && Input::GetMouseY() <= 385;
		clickedNo = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 405 && Input::GetMouseX() <= 557 && Input::GetMouseY() >= 310 && Input::GetMouseY() <= 383;
		if (bedisopen && clickedYes && frame == 1) // Player confirmed to sleep
			return true;
		return false;
	}
	void House::BedLogic(int& dayCounter)
	{
		// Check if player clicked on bed
		bool clickedOnBed = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 511 && Input::GetMouseX() <= 742 && Input::GetMouseY() >= 320 && Input::GetMouseY() <= 565;
		
		// Open bed menu if clicked on bed
		if (clickedOnBed && !crafting.CraftingIsOpen() && !nightstandisopen && frame == 0)
		{
			bedisopen = true;
			frame = 1;
		}

		// Handle bed menu interactions
		if (bedisopen)
		{
			if (clickedYes && frame == 1) // Player confirmed to sleep
			{
				frame = 2;
				dayCounter++;
			}
			else if ((frame == 2 && Input::GetMouseButtonPressed(1)) || (clickedNo && frame == 1) || Input::GetKeyPressed(SDL_SCANCODE_Q)) // Player clicked to exit day passed view or declined to sleep
			{
				bedisopen = false;
				frame = 0;
			}
		}
		
		// Frame 0: Normal house view
		// Frame 1: Sleep confirmation view
		// Frame 2: Day passed view

		house.SetFrame(frame);
	}
	void House::NightstandLogic()
	{
		// Check if player clicked on nightstand
		bool clickedOnNightstand = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 386 && Input::GetMouseX() <= 497 && Input::GetMouseY() >= 351 && Input::GetMouseY() <= 445;
		if (clickedOnNightstand && !crafting.CraftingIsOpen() && !bedisopen && frame == 0)
		{
			nightstandisopen = true;
			frame = 0;
			nightstand.SetFrame(frame);
		}
		// Close nightstand if Q is pressed and crafting menu is not open
		if (Input::GetKeyPressed(SDL_SCANCODE_Q) && !crafting.CraftingIsOpen() && !bedisopen)
			nightstandisopen = false;
	}
	void House::DrawHover(Surface* screen)
	{
		bool hoverNightstand = Input::GetMouseX() >= 386 && Input::GetMouseX() <= 497 && Input::GetMouseY() >= 351 && Input::GetMouseY() <= 445;
		bool hoverBed = Input::GetMouseX() >= 511 && Input::GetMouseX() <= 742 && Input::GetMouseY() >= 320 && Input::GetMouseY() <= 565;
		bool hoverTable = Input::GetMouseX() >= 103 && Input::GetMouseX() <= 294 && Input::GetMouseY() >= 331 && Input::GetMouseY() <= 476;
		if (hoverNightstand)
			nightstand_hover.Draw(screen, 0, 0);
		if (hoverBed)
			bed_hover.Draw(screen, 0, 0);
		if (hoverTable)
			table_hover.Draw(screen, 0, 0);
	}
	void House::Draw(Surface* screen)
	{
		// Draw house if it is open
		if (houseisopen)
		{
			house.Draw(screen, 0, 0);
			if(MainScreenOpen())
				DrawHover(screen);
		}
		// Draw nightstand if it is open
		if (nightstandisopen)
			nightstand.Draw(screen, 0, 0);
	}
	void House::GameCompleted(Surface* screen, int coinCounter, bool& gameCompleted) 
	{
		// Check if player clicked on send money button
		bool sendMoney = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 336 && Input::GetMouseX() <= 468 && Input::GetMouseY() >= 446 && Input::GetMouseY() <= 498; //say youre gonna improve this later

		// Complete game if send money button is clicked, nightstand is open, and player has enough coins
		if (sendMoney && nightstandisopen && coinCounter >= 2000 && !gameCompleted)
		{
			gameCompleted = true;
			gameframe = 0;
		}

		// Draw game end screen
		if (gameCompleted)
		{
			if (Input::GetMouseButtonPressed(1))
			{
				gameframe++;
				gameendscreen.SetFrame(gameframe);
			}
			if (gameframe <= 6)
				gameendscreen.Draw(screen, 0, 0);
		}
		if (House::gameframe > 6)
			exit(0);
	}
}