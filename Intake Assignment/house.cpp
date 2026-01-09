#include "house.h"


namespace Tmpl8
{
	namespace House
	{
		Sprite house(new Surface("assets/bed.png"), 3);
		bool houseisopen = false;
		int frame = 0;
		bool clickedYes = 0;
		bool clickedNo = 0;
		void ShowHouse(Surface* screen, bool qPressed, float reachX1, float reachX2, float reachY1, float reachY2, float worldX, float worldY)
		{
			bool houseInReach = reachX2 >= 196 && reachX1 <= 233 && reachY2 >= 183 && reachY1 <= 232;
			bool clicekdOnDoor = worldX >= 196 && worldX <= 233 && worldY >= 183 && worldY <= 234;
			if (GetAsyncKeyState(VK_LBUTTON) && houseInReach && clicekdOnDoor)
			{
				houseisopen = true;
				frame = 0;
				house.SetFrame(frame);
			}	
			if (qPressed && Crafting::craftingisopen == false)
				houseisopen = false;
			if (houseisopen)
				house.Draw(screen, 0, 0);
		}
		void DayUpdate(bool &leftPressed, int &dayCounter, int mouseX, int mouseY)
		{
			bool clickedOnBed = leftPressed && mouseX >= 511 && mouseX <= 742 && mouseY >= 320 && mouseY <= 565;
			clickedYes = leftPressed && mouseX >= 235 && mouseX <= 389 && mouseY >= 310 && mouseY <= 385;
			clickedNo = leftPressed && mouseX >= 405 && mouseX <= 557 && mouseY >= 310 && mouseY <= 383;
			if (clickedOnBed && !Crafting::craftingisopen && frame == 0)
			{
				frame = 1;
				house.SetFrame(frame);
				leftPressed = false;
				
			}
			if (clickedYes && frame == 1)
			{
				frame = 2;
				house.SetFrame(frame);
				leftPressed = false;
				
			}
			if (frame == 2 && leftPressed)
			{
				dayCounter++;
				frame = 0;
				house.SetFrame(frame);
				leftPressed = false;
			}
			if (clickedNo && frame == 1)
			{
				frame = 0;
				house.SetFrame(frame);
				leftPressed = false;
			}
				
				
		}
		void ClickedNightstand(Surface* screen, bool leftPressed, int& coinCounter, int mouseX, int mouseY)
		{
			bool clickedOnNightstand = leftPressed && mouseX >= 386 && mouseX <= 497 && mouseY >= 351 && mouseY <= 454;
			if (clickedOnNightstand && !Crafting::craftingisopen && frame == 0)
			{
				screen->Print("You found 10 coins!", 300, 200, 0xffff00);
			}
				
		}
	}
};