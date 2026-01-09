#include "house.h"


namespace Tmpl8
{
	namespace House
	{
		Sprite house(new Surface("assets/house.png"), 3);
		bool houseisopen = false;
		int frame = 0;
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
			if (qPressed && Crafting::craftingisopen == false)
				houseisopen = false;

			// Draw house if it is open
			if (houseisopen)
				house.Draw(screen, 0, 0);
		}
		void DayUpdate(bool &leftPressed, int &dayCounter, int mouseX, int mouseY)
		{
			// Check if player clicked on bed, yes or no buttons
			bool clickedOnBed = leftPressed && mouseX >= 511 && mouseX <= 742 && mouseY >= 320 && mouseY <= 565;
			clickedYes = leftPressed && mouseX >= 235 && mouseX <= 389 && mouseY >= 310 && mouseY <= 385;
			clickedNo = leftPressed && mouseX >= 405 && mouseX <= 557 && mouseY >= 310 && mouseY <= 383;

			// Update house frame based on clicks:

			// Frame 0: Normal house view
			// Frame 1: Sleep confirmation view
			// Frame 2: Day passed view

			if (clickedOnBed && !Crafting::craftingisopen && frame == 0)
			{
				frame = 1;
				leftPressed = false; // Reset left click state to avoid multiple clicks
			}
			if (clickedYes && frame == 1)
			{
				frame = 2;
				dayCounter++;
				leftPressed = false; // Reset left click state to avoid multiple clicks
			}
			if (frame == 2 && leftPressed)
			{		
				frame = 0;
				leftPressed = false; // Reset left click state to avoid multiple clicks
			}
			if (clickedNo && frame == 1)
			{
				frame = 0;
				leftPressed = false; // Reset left click state to avoid multiple clicks
			}
			house.SetFrame(frame);	
		}
		void ClickedNightstand(Surface* screen, bool leftPressed, int& coinCounter, int mouseX, int mouseY)
		{
			// Check if player clicked on nightstand
			bool clickedOnNightstand = leftPressed && mouseX >= 386 && mouseX <= 497 && mouseY >= 351 && mouseY <= 454;
			if (clickedOnNightstand && !Crafting::craftingisopen && frame == 0)
			{
				screen->Print("You found 10 coins!", 300, 200, 0xffff00);
			}
				
		}
	}
};