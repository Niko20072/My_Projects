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
		void ShowHouse(Surface* screen, bool qPressed, float reachX1, float reachX2, float reachY1, float reachY2, float worldX, float worldY)
		{
			// Check if player clicked on house door and is in reach
			bool houseInReach = reachX2 >= 196 && reachX1 <= 233 && reachY2 >= 183 && reachY1 <= 232;
			bool clicekdOnDoor = worldX >= 196 && worldX <= 233 && worldY >= 183 && worldY <= 234;

			// Open house if left mouse button is clicked while in reach of door
			if (GetAsyncKeyState(VK_LBUTTON) && houseInReach && clicekdOnDoor)
			{
				houseisopen = true;
				frame = 0;
				house.SetFrame(frame);
			}	

			// Close house if Q is pressed and crafting menu is not open
			if (qPressed && !Crafting::craftingisopen && !bedisopen && !nightstandisopen)
				houseisopen = false;

			// Draw house if it is open
			if (houseisopen)
				house.Draw(screen, 0, 0);
		}
		void DayUpdate(bool &leftPressed, bool& qPressed, int &dayCounter, int mouseX, int mouseY)
		{
			// Check if player clicked on bed, yes or no buttons
			bool clickedOnBed = leftPressed && mouseX >= 511 && mouseX <= 742 && mouseY >= 320 && mouseY <= 565;
			clickedYes = leftPressed && mouseX >= 235 && mouseX <= 389 && mouseY >= 310 && mouseY <= 385;
			clickedNo = leftPressed && mouseX >= 405 && mouseX <= 557 && mouseY >= 310 && mouseY <= 383;

			// Update house frame based on clicks:

			// Frame 0: Normal house view
			// Frame 1: Sleep confirmation view
			// Frame 2: Day passed view

			// Open bed menu if clicked on bed
			if (clickedOnBed && !Crafting::craftingisopen && !nightstandisopen && frame == 0)
			{
				bedisopen = true;
				frame = 1;
				leftPressed = false; // Reset left click state to avoid multiple clicks
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
					frame = 2;
					dayCounter++;
					leftPressed = false; // Reset left click state to avoid multiple clicks
				}
				else if ((frame == 2 && leftPressed) || (clickedNo && frame == 1)) // Player clicked to exit day passed view or declined to sleep
				{
					bedisopen = false;
					frame = 0;
					leftPressed = false; // Reset left click state to avoid multiple clicks
				}
				else if (qPressed && Crafting::craftingisopen == false) // Close bed menu if Q is pressed
				{
					bedisopen = false;
					frame = 0;
					qPressed = false; // Reset q click state to avoid multiple clicks
				}
			}
			house.SetFrame(frame);	
		}
		void ClickedNightstand(Surface* screen, bool &leftPressed, bool qPressed, int coinCounter, int mouseX, int mouseY)
		{
			// Check if player clicked on nightstand
			bool clickedOnNightstand = leftPressed && mouseX >= 386 && mouseX <= 497 && mouseY >= 351 && mouseY <= 454;
			
			if (clickedOnNightstand && !Crafting::craftingisopen && !bedisopen && frame == 0)
			{
				nightstandisopen = true;
				leftPressed = false; // Reset left click state to avoid multiple clicks
				frame = 0;
				nightstand.SetFrame(frame);
			}
			// Close nightstand if Q is pressed and crafting menu is not open
			if (qPressed && !Crafting::craftingisopen && !bedisopen)
				nightstandisopen = false;

			// Draw nightstand if it is open
			if (nightstandisopen)
				nightstand.Draw(screen, 0, 0);
		}
		void GameCompleted(Surface* screen, bool &leftPressed, bool qPressed, int coinCounter, int mouseX, int mouseY, bool &gameCompleted)
		{
			// Check if player clicked on send money button
			bool sendMoney = leftPressed && mouseX >= 336 && mouseX <= 468 && mouseY >= 446 && mouseY <= 498;

			// Complete game if send money button is clicked, nightstand is open, and player has enough coins
			if (sendMoney && nightstandisopen && coinCounter >= 2000 && !gameCompleted)
			{
				gameCompleted = true;
				leftPressed = false; // Reset left click state to avoid multiple clicks
				gameframe = 0;
			}

			// Draw game end screen
			if (gameCompleted)
			{
				if(leftPressed)
				{
					gameframe++;
					leftPressed = false; // Reset left click state to avoid multiple clicks
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