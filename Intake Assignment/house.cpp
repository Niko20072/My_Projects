#include "house.h"
namespace Tmpl8
{
	namespace House
	{
		Sprite house(new Surface("assets/house1.png"), 1);
		Sprite crafting(new Surface("assets/crafting2.png"), 3);

		float inputCooldown = 0.0f;
		bool houseisopen = false;
		bool craftingisopen = false;

		void ManageFrames(int mouseX, int mouseY)
		{
			bool button1 = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 244 && mouseX <= 314 && mouseY >= 516 && mouseY <= 584;
			bool button2 = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 364 && mouseX <= 434 && mouseY >= 516 && mouseY <= 584;
			bool button3 = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 485 && mouseX <= 554 && mouseY >= 516 && mouseY <= 584;
			if (button1)
				crafting.SetFrame(0);
			if (button2)
				crafting.SetFrame(1);
			if (button3)
				crafting.SetFrame(2);

		}
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
			if (clickedOnTable && houseisopen && inputCooldown <= 0.0f)
			{
				inputCooldown = 0.2f; // 200 ms
				craftingisopen = true;
				crafting.SetFrame(0);
			}
			if (GetAsyncKeyState('Q'))
			{
				craftingisopen = false;
				inputCooldown = 0.2f; // 200 ms
			}
			if (craftingisopen)
			{
				ManageFrames(mouseX, mouseY);
				crafting.Draw(screen, 0, 0);
			}

		}
		void DayUpdate(int &dayCounter, int mouseX, int mouseY)
		{
			bool clickedOnBed = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 483 && mouseX <= 772 && mouseY >= 256 && mouseY <= 534;
			if (clickedOnBed && !craftingisopen && inputCooldown <= 0.0f)
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