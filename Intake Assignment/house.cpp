#include "house.h"


namespace Tmpl8
{
	int House::IsOpen()
	{
		return houseisopen;
	}
	int House::getFrame()
	{
		return frame;
	}
	void House::HouseLogic()
	{
		// Check if player clicked on house door and is in reach
		bool houseInReach = WorldState::reachX2 >= 196 && WorldState::reachX1 <= 233 && WorldState::reachY2 >= 183 && WorldState::reachY1 <= 232;
		bool clicekdOnDoor = WorldState::worldX >= 196 && WorldState::worldX <= 233 && WorldState::worldY >= 183 && WorldState::worldY <= 234;

		// Open house if left mouse button is clicked while in reach of door
		if (Buttons::leftPressed && houseInReach && clicekdOnDoor)
		{
			Buttons::leftPressed = false;
			houseisopen = true;
			frame = 0;
			house.SetFrame(frame);
		}

		// Close house if Q is pressed and crafting menu is not open
		if (Buttons::qPressed && !crafting.CraftingIsOpen() && !bedisopen && !nightstandisopen)
			houseisopen = false;
	}
	void House::Craftinglogic()
	{
		bool clickedOnTable = Buttons::leftPressed && WorldState::mouseX >= 103 && WorldState::mouseX <= 294 && WorldState::mouseY >= 331 && WorldState::mouseY <= 476;

		// Open crafting interface when clicking on crafting table inside house
		if (clickedOnTable && houseisopen && frame == 0) //fix this
		{
			Buttons::leftPressed = false; // Reset left click state to avoid multiple clicks
			crafting.setState(true);
			frame = 0;
			crafting.setFrame(frame);
		}
		// Close crafting interface when pressing Q
		if (Buttons::qPressed && crafting.CraftingIsOpen())
		{
			Buttons::qPressed = false; // Reset Q key state to avoid multiple toggles
			crafting.setState(false);
		}
	}
	bool House::ConfirmedToSleep()
	{
		// Check if player clicked on bed, yes or no buttons
		clickedYes = Buttons::leftPressed && WorldState::mouseX >= 235 && WorldState::mouseX <= 389 && WorldState::mouseY >= 310 && WorldState::mouseY <= 385;
		clickedNo = Buttons::leftPressed && WorldState::mouseX >= 405 && WorldState::mouseX <= 557 && WorldState::mouseY >= 310 && WorldState::mouseY <= 383;
		if (bedisopen && clickedYes && frame == 1) // Player confirmed to sleep
		{
			return true;
		}
		return false;
	}
	void House::BedLogic(int& dayCounter)
	{
		// Check if player clicked on bed
		bool clickedOnBed = Buttons::leftPressed && WorldState::mouseX >= 511 && WorldState::mouseX <= 742 && WorldState::mouseY >= 320 && WorldState::mouseY <= 565;
		
		// Open bed menu if clicked on bed
		if (clickedOnBed && !crafting.CraftingIsOpen() && !nightstandisopen && frame == 0)
		{
			bedisopen = true;
			frame = 1;
			house.SetFrame(frame);
			Buttons::leftPressed = false; // Reset left click state to avoid multiple clicks
		}
		// Frame 0: Normal house view
		// Frame 1: Sleep confirmation view
		// Frame 2: Day passed view

		// Handle bed menu interactions
		if (bedisopen)
		{
			if (ConfirmedToSleep()) // Player confirmed to sleep
			{
				frame = 2;
				dayCounter++;
			}
			else if ((frame == 2 && Buttons::leftPressed) || (clickedNo && frame == 1) || (Buttons::qPressed && crafting.CraftingIsOpen() == false)) // Player clicked to exit day passed view or declined to sleep || Close bed menu if Q is pressed
			{
				bedisopen = false;
				frame = 0;
			}
		}
		house.SetFrame(frame);
	}
	void House::NightstandLogic(Surface* screen, int coinCounter)
	{
		// Check if player clicked on nightstand
		bool clickedOnNightstand = Buttons::leftPressed && WorldState::mouseX >= 386 && WorldState::mouseX <= 497 && WorldState::mouseY >= 351 && WorldState::mouseY <= 454;
		if (clickedOnNightstand && !crafting.CraftingIsOpen() && !bedisopen && frame == 0)
		{
			nightstandisopen = true;
			Buttons::leftPressed = false; // Reset left click state to avoid multiple clicks
			frame = 0;
			nightstand.SetFrame(frame);
		}
		// Close nightstand if Q is pressed and crafting menu is not open
		if (Buttons::qPressed && !crafting.CraftingIsOpen() && !bedisopen)
			nightstandisopen = false;
	}
	void House::Draw(Surface* screen)
	{
		// Draw house if it is open
		if (houseisopen)
			house.Draw(screen, 0, 0);
		// Draw nightstand if it is open
		if (nightstandisopen)
			nightstand.Draw(screen, 0, 0);
	}
	void House::GameCompleted(Surface* screen, int coinCounter, bool& gameCompleted) //make endscreen class
	{
		// Check if player clicked on send money button
		bool sendMoney = Buttons::leftPressed && WorldState::mouseX >= 336 && WorldState::mouseX <= 468 && WorldState::mouseY >= 446 && WorldState::mouseY <= 498;

		// Complete game if send money button is clicked, nightstand is open, and player has enough coins
		if (sendMoney && nightstandisopen && coinCounter >= 2000 && !gameCompleted)
		{
			gameCompleted = true;
			Buttons::leftPressed = false; // Reset left click state to avoid multiple clicks
			gameframe = 0;
		}

		// Draw game end screen
		if (gameCompleted)
		{
			if (Buttons::leftPressed)
			{
				gameframe++;
				Buttons::leftPressed = false; // Reset left click state to avoid multiple clicks
				gameendscreen.SetFrame(gameframe);
			}
			if (gameframe <= 6)
				gameendscreen.Draw(screen, 0, 0);
		}
		if (House::gameframe > 6)
			exit(0);
	}
}