#include "house.h"


namespace Tmpl8
{
	namespace House
	{
		//fix exit when sleep screen is open si q pressed
		Sprite house(new Surface("assets/house.png"), 3);
		Sprite nightstand(new Surface("assets/nightstand.png"), 1);
		Sprite gameendscreen(new Surface("assets/endgame.png"), 7);
		bool houseisopen = false;
		bool nightstandisopen = false;
		bool bedisopen = false;
		int frame = 0;
		int gameframe = 0;
		bool clickedYes = 0;
		bool clickedNo = 0;
		void HouseLogic()
		{
			// Check if player clicked on house door and is in reach
			bool houseInReach = WorldState::reachX2 >= 196 && WorldState::reachX1 <= 233 && WorldState::reachY2 >= 183 && WorldState::reachY1 <= 232;
			bool clicekdOnDoor = WorldState::worldX >= 196 && WorldState::worldX <= 233 && WorldState::worldY >= 183 && WorldState::worldY <= 234;

			// Open house if left mouse button is clicked while in reach of door
			if (GetAsyncKeyState(VK_LBUTTON) && houseInReach && clicekdOnDoor)
			{
				houseisopen = true;
				frame = 0;
				house.SetFrame(frame);
			}	

			// Close house if Q is pressed and crafting menu is not open
			if (Buttons::qPressed && !Crafting::craftingisopen && !bedisopen && !nightstandisopen)
				houseisopen = false;
				
		}
		void DayUpdate(int &dayCounter)
		{
			// Check if player clicked on bed, yes or no buttons
			bool clickedOnBed = Buttons::leftPressed && WorldState::mouseX >= 511 && WorldState::mouseX <= 742 && WorldState::mouseY >= 320 && WorldState::mouseY <= 565;
			clickedYes = Buttons::leftPressed && WorldState::mouseX >= 235 && WorldState::mouseX <= 389 && WorldState::mouseY >= 310 && WorldState::mouseY <= 385;
			clickedNo = Buttons::leftPressed && WorldState::mouseX >= 405 && WorldState::mouseX <= 557 && WorldState::mouseY >= 310 && WorldState::mouseY <= 383;

			// Update house frame based on clicks:

			// Frame 0: Normal house view
			// Frame 1: Sleep confirmation view
			// Frame 2: Day passed view

			// Open bed menu if clicked on bed
			if (clickedOnBed && !Crafting::craftingisopen && !nightstandisopen && frame == 0)
			{
				bedisopen = true;
				frame = 1;
				Buttons::leftPressed = false; // Reset left click state to avoid multiple clicks
			}

			// Handle bed menu interactions
			if (bedisopen == true)
			{
				if (clickedYes && frame == 1) // Player confirmed to sleep
				{
					for (auto& x : Plant::plants)
					{
						if (x.grown == false)
							x.NextDay();
					}
					for (auto& x : FarmTile::farmTiles)
					{
						x.watered = false;
					}
					frame = 2;
					dayCounter++;
					Order::daysUntilReset--;
					Buttons::leftPressed = false; // Reset left click state to avoid multiple clicks
				}
				else if ((frame == 2 && Buttons::leftPressed) || (clickedNo && frame == 1)) // Player clicked to exit day passed view or declined to sleep
				{
					bedisopen = false;
					frame = 0;
					Buttons::leftPressed = false; // Reset left click state to avoid multiple clicks
				}
				else if (Buttons::qPressed && Crafting::craftingisopen == false) // Close bed menu if Q is pressed
				{
					bedisopen = false;
					frame = 0;
					Buttons::qPressed = false; // Reset q click state to avoid multiple clicks
				}
			}
			house.SetFrame(frame);	
		}
		void NightstandLogic(Surface* screen, int coinCounter)
		{
			// Check if player clicked on nightstand
			bool clickedOnNightstand = Buttons::leftPressed && WorldState::mouseX >= 386 && WorldState::mouseX <= 497 && WorldState::mouseY >= 351 && WorldState::mouseY <= 454;
			
			if (clickedOnNightstand && !Crafting::craftingisopen && !bedisopen && frame == 0)
			{
				nightstandisopen = true;
				Buttons::leftPressed = false; // Reset left click state to avoid multiple clicks
				frame = 0;
				nightstand.SetFrame(frame);
			}
			// Close nightstand if Q is pressed and crafting menu is not open
			if (Buttons::qPressed && !Crafting::craftingisopen && !bedisopen)
				nightstandisopen = false;
		}
		void Draw(Surface* screen)
		{
			// Draw house if it is open
			if (houseisopen)
			{
				house.Draw(screen, 0, 0);
				WateringCan::wateringCan = false; // Disable watering can when house is open
			}
			// Draw nightstand if it is open
			if (nightstandisopen)
				nightstand.Draw(screen, 0, 0);
		}
		void GameCompleted(Surface* screen, int coinCounter, bool &gameCompleted)
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
				if(Buttons::leftPressed)
				{
					gameframe++;
					Buttons::leftPressed = false; // Reset left click state to avoid multiple clicks
					gameendscreen.SetFrame(gameframe);
				}
				if(gameframe <= 6)
					gameendscreen.Draw(screen, 0, 0);	
			}
			if (House::gameframe > 6)
				exit(0);
		}
	}
};