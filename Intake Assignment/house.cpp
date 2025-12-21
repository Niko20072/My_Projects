#include "house.h"
namespace Tmpl8
{
	namespace House
	{
		Sprite house(new Surface("assets/house1.png"), 1);
		Sprite crafting(new Surface("assets/crafting.png"), 3);

		float inputCooldown = 0.0f;
		bool houseisopen = false;
		bool craftingisopen = false;

		void ShowHouse(Surface* screen, float reachX1, float reachX2, float reachY1, float reachY2, int worldX, int worldY)
		{
			bool houseInReach = reachX2 >= 196 && reachX1 <= 233 && reachY2 >= 183 && reachY1 <= 232;
			bool clicekdOnDoor = worldX >= 196 && worldX <= 233 && worldY >= 183 && worldY <= 234;
			if (GetAsyncKeyState(VK_LBUTTON) && houseInReach && clicekdOnDoor && inputCooldown <= 0.0f)
			{
				inputCooldown = 0.2f; // 200 ms
				houseisopen = true;
			}
			if (GetAsyncKeyState('Q') && craftingisopen==false && inputCooldown <= 0.0f)
				houseisopen = false;
			if (houseisopen)
			{
				house.Draw(screen, 0, 0);
			}
		}
		void ShowCrafting(Surface* screen, int mouseX, int mouseY)
		{
			bool clickedOnTable = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 32 && mouseX <= 241 && mouseY >= 243 && mouseY <= 427;
			if (clickedOnTable && inputCooldown <= 0.0f)
			{
				inputCooldown = 0.2f; // 200 ms
				craftingisopen = true;
			}
			if (GetAsyncKeyState('Q'))
			{
				craftingisopen = false;
				inputCooldown = 0.2f; // 200 ms
			}
			if (craftingisopen)
			{
				crafting.Draw(screen, 0, 0);
			}

		}
		void DayUpdate(int &dayCounter, int mouseX, int mouseY)
		{
			bool clickedOnBed = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 483 && mouseX <= 772 && mouseY >= 256 && mouseY <= 534;
			if (clickedOnBed && inputCooldown <= 0.0f)
			{
				inputCooldown = 0.2f; // 200 ms
				dayCounter++;
			}
				
		}
		void Update(Surface* screen, float deltaTime)
		{
			inputCooldown -= deltaTime;//to limit key press speed
			if (inputCooldown <= 0.0f)
				inputCooldown = 0.0f;
		}
	}
};