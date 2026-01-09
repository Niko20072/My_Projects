#include "house.h"


namespace Tmpl8
{
	namespace House
	{
		Sprite house(new Surface("assets/house1.png"), 1);
		bool houseisopen = false;
		void ShowHouse(Surface* screen, bool qPressed, float reachX1, float reachX2, float reachY1, float reachY2, float worldX, float worldY)
		{
			bool houseInReach = reachX2 >= 196 && reachX1 <= 233 && reachY2 >= 183 && reachY1 <= 232;
			bool clicekdOnDoor = worldX >= 196 && worldX <= 233 && worldY >= 183 && worldY <= 234;
			if (GetAsyncKeyState(VK_LBUTTON) && houseInReach && clicekdOnDoor)
				houseisopen = true;
			if (qPressed && Crafting::craftingisopen == false)
				houseisopen = false;
			if (houseisopen)
				house.Draw(screen, 0, 0);
		}
		void DayUpdate(bool leftPressed, int &dayCounter, int mouseX, int mouseY)
		{
			bool clickedOnBed = leftPressed && mouseX >= 483 && mouseX <= 772 && mouseY >= 256 && mouseY <= 534;
			if (clickedOnBed && !Crafting::craftingisopen)
				dayCounter++;
				
		}
	}
};