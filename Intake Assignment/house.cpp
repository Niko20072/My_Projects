#include "house.h"
#include "input.h"
#include "worldstate.h"
#include "Windows.h"

namespace Tmpl8
{
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
	void House::HouseLogic()
	{
		// Check if player clicked on house door and is in reach
		bool houseInReach = WorldState::reachX2 >= 196 && WorldState::reachX1 <= 233 && WorldState::reachY2 >= 183 && WorldState::reachY1 <= 232;
		bool hoverOnDoor = WorldState::mouseWorldX >= 196 && WorldState::mouseWorldX <= 233 && WorldState::mouseWorldY >= 183 && WorldState::mouseWorldY <= 234;

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
		bool clickedOnTable = Input::GetMouseButtonPressed(1) && WorldState::mouseX >= 103 && WorldState::mouseX <= 294 && WorldState::mouseY >= 331 && WorldState::mouseY <= 476;

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
		clickedYes = Input::GetMouseButtonPressed(1) && WorldState::mouseX >= 235 && WorldState::mouseX <= 389 && WorldState::mouseY >= 310 && WorldState::mouseY <= 385;
		clickedNo = Input::GetMouseButtonPressed(1) && WorldState::mouseX >= 405 && WorldState::mouseX <= 557 && WorldState::mouseY >= 310 && WorldState::mouseY <= 383;
		if (bedisopen && clickedYes && frame == 1) // Player confirmed to sleep
			return true;
		return false;
	}
	//Fix double click problem(bed after clicking yes)
	void House::BedLogic(int& dayCounter)
	{
		// Check if player clicked on bed
		bool clickedOnBed = Input::GetMouseButtonPressed(1) && WorldState::mouseX >= 511 && WorldState::mouseX <= 742 && WorldState::mouseY >= 320 && WorldState::mouseY <= 565;
		
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
		bool clickedOnNightstand = Input::GetMouseButtonPressed(1) && WorldState::mouseX >= 386 && WorldState::mouseX <= 497 && WorldState::mouseY >= 351 && WorldState::mouseY <= 445;
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
		bool hoverNightstand = WorldState::mouseX >= 386 && WorldState::mouseX <= 497 && WorldState::mouseY >= 351 && WorldState::mouseY <= 445;
		bool hoverBed = WorldState::mouseX >= 511 && WorldState::mouseX <= 742 && WorldState::mouseY >= 320 && WorldState::mouseY <= 565;
		bool hoverTable = WorldState::mouseX >= 103 && WorldState::mouseX <= 294 && WorldState::mouseY >= 331 && WorldState::mouseY <= 476;
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
	//Fix double click problem(send money and nightstand button)
	void House::GameCompleted(Surface* screen, int coinCounter, bool& gameCompleted) 
	{
		// Check if player clicked on send money button
		bool sendMoney = Input::GetMouseButtonPressed(1) && WorldState::mouseX >= 336 && WorldState::mouseX <= 468 && WorldState::mouseY >= 446 && WorldState::mouseY <= 498;

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