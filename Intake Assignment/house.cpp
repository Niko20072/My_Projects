#include "house.h"
#include "inventory.h"
namespace Tmpl8
{
	namespace House
	{
		Sprite house(new Surface("assets/house1.png"), 1);
		Sprite crafting(new Surface("assets/crafting2.png"), 3);

		bool houseisopen = false;
		bool craftingisopen = false;
		int frame = 0;

		void ManageFrames(int mouseX, int mouseY)
		{
			bool button1 = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 244 && mouseX <= 314 && mouseY >= 516 && mouseY <= 584;
			bool button2 = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 364 && mouseX <= 434 && mouseY >= 516 && mouseY <= 584;
			bool button3 = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 485 && mouseX <= 554 && mouseY >= 516 && mouseY <= 584;
			if (button1)
				frame = 0;
			if (button2)
				frame = 1;
			if (button3)
				frame = 2;
			crafting.SetFrame(frame);

		}
		void CraftLogic(bool button, int Frame, int &ingredient1, int &ingredient2, int &potion)
		{
			if (button && frame == Frame && ingredient1 >= 1 && ingredient2 >= 1)
			{
				ingredient1--;
				ingredient2--;
				potion++;
			}
		}
		void CraftLogic(bool button, int Frame, int& ingredient1, int& ingredient2, int& ingredient3, int& potion)
		{
			if (button && frame == Frame && ingredient1 >= 1 && ingredient2 >= 1 && ingredient3 >= 1)
			{
				ingredient1--;
				ingredient2--;
				ingredient3--;
				potion++;
			}
		}
		void Craft(int mouseX, int mouseY)
		{
			bool clickedCraft1 = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 295 && mouseX <= 359 && mouseY >= 111 && mouseY <= 154;
			bool clickedCraft2 = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 643 && mouseX <= 704 && mouseY >= 111 && mouseY <= 154;

			///crafting vital tonic
			CraftLogic(clickedCraft1, 0, Inventory::contSunblossom, Inventory::contEmberroot, Inventory::contVitalTonic);
			///crafting calm mind elixir
			CraftLogic(clickedCraft2, 0, Inventory::contMoonleaf, Inventory::contFrostmint, Inventory::contCalmMind);
			///crafting dream draught
			CraftLogic(clickedCraft1, 1, Inventory::contFrostmint, Inventory::contBerry, Inventory::contDreamDraught);
			///crafting fireheart brew
			CraftLogic(clickedCraft2, 1, Inventory::contEmberroot, Inventory::contSunblossom, Inventory::contBerry, Inventory::contFireHeart);
			//crafting frostveil potion
			CraftLogic(clickedCraft1, 2, Inventory::contFrostmint, Inventory::contMoonleaf, Inventory::contBerry, Inventory::contFrostveil);
			
		}
		void ShowHouse(Surface* screen, bool qPressed, float reachX1, float reachX2, float reachY1, float reachY2, int worldX, int worldY)
		{
			bool houseInReach = reachX2 >= 196 && reachX1 <= 233 && reachY2 >= 183 && reachY1 <= 232;
			bool clicekdOnDoor = worldX >= 196 && worldX <= 233 && worldY >= 183 && worldY <= 234;
			if (GetAsyncKeyState(VK_LBUTTON) && houseInReach && clicekdOnDoor)
				houseisopen = true;
			if (qPressed && craftingisopen == false)
				houseisopen = false;
			if (houseisopen)
				house.Draw(screen, 0, 0);
		}
		void ShowCrafting(Surface* screen, bool qPressed, int mouseX, int mouseY)
		{
			bool clickedOnTable = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 32 && mouseX <= 241 && mouseY >= 243 && mouseY <= 427;
			if (clickedOnTable && houseisopen)
			{
				craftingisopen = true;
				frame = 0;
				crafting.SetFrame(frame);
			}
			if (qPressed && craftingisopen)
				craftingisopen = false;
			if (craftingisopen)
			{
				ManageFrames(mouseX, mouseY);
				crafting.Draw(screen, 0, 0);
			}
		}
		void DayUpdate(bool leftPressed, int &dayCounter, int mouseX, int mouseY)
		{
			bool clickedOnBed = leftPressed && mouseX >= 483 && mouseX <= 772 && mouseY >= 256 && mouseY <= 534;
			if (clickedOnBed && !craftingisopen)
				dayCounter++;
				
		}
	}
};