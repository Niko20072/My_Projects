#include "crafting.h"

namespace Tmpl8
{
	namespace Crafting
	{
		Sprite crafting(new Surface("assets/crafting2.png"), 3);
		bool craftingisopen = false;
		int frame = 0;
		void CraftingDraw(Surface* screen)
		{
			crafting.Draw(screen, 0, 0);
			char sunBlossom[32], moonLeaf[32], emberRoot[32], frostMint[32], berry[32];
			char vitalTonic[32], calmMind[32], dreamDraught[32], fireHeart[32], frostVeil[32];

			sprintf(sunBlossom, "x%d", Inventory::contSunblossom);
			sprintf(moonLeaf, "x%d", Inventory::contMoonleaf);
			sprintf(emberRoot, "x%d", Inventory::contEmberroot);
			sprintf(frostMint, "x%d", Inventory::contFrostmint);
			sprintf(berry, "x%d", Inventory::contBerry);

			sprintf(vitalTonic, "x%d", Inventory::contVitalTonic);
			sprintf(calmMind, "x%d", Inventory::contCalmMind);
			sprintf(dreamDraught, "x%d", Inventory::contDreamDraught);
			sprintf(fireHeart, "x%d", Inventory::contFireHeart);
			sprintf(frostVeil, "x%d", Inventory::contFrostveil);

			if (frame == 0 && craftingisopen)
			{
				screen->Print(emberRoot, 171, 275, 0x0);
				screen->Print(sunBlossom, 282 - 4, 275, 0x0);
				screen->Print(moonLeaf, 520 - 4, 275, 0x0);
				screen->Print(frostMint, 620 - 4, 275, 0x0);
				screen->Print(vitalTonic, 329 - 4, 163, 0x0);
				screen->Print(calmMind, 676 - 4, 163, 0x0);
			}
			if (frame == 1 && craftingisopen)
			{
				screen->Print(moonLeaf, 175 - 4, 275, 0x0);
				screen->Print(berry, 272 - 4, 275, 0x0);
				screen->Print(emberRoot, 478 - 4, 275, 0x0);
				screen->Print(sunBlossom, 567 - 4, 275, 0x0);
				screen->Print(berry, 665 - 4, 275, 0x0);
				screen->Print(dreamDraught, 329 - 4, 163, 0x0);
				screen->Print(fireHeart, 676 - 4, 163, 0x0);
			}
			if (frame == 2 && craftingisopen)
			{
				screen->Print(frostMint, 139 - 4, 275, 0x0);
				screen->Print(moonLeaf, 225 - 4, 275, 0x0);
				screen->Print(berry, 315 - 4, 275, 0x0);
				screen->Print(frostVeil, 329 - 4, 163, 0x0);
			}
		}
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
		void CraftLogic(bool button, int Frame, int& ingredient1, int& ingredient2, int& potion)
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
		void Craft(bool leftPressed, int mouseX, int mouseY)
		{
			bool clickedCraft1 = leftPressed && mouseX >= 295 && mouseX <= 359 && mouseY >= 111 && mouseY <= 154;
			bool clickedCraft2 = leftPressed && mouseX >= 643 && mouseX <= 704 && mouseY >= 111 && mouseY <= 154;

			///crafting vital tonic
			CraftLogic(clickedCraft1, 0, Inventory::contSunblossom, Inventory::contEmberroot, Inventory::contVitalTonic);
			///crafting calm mind elixir
			CraftLogic(clickedCraft2, 0, Inventory::contMoonleaf, Inventory::contFrostmint, Inventory::contCalmMind);
			///crafting dream draught
			CraftLogic(clickedCraft1, 1, Inventory::contMoonleaf, Inventory::contBerry, Inventory::contDreamDraught);
			///crafting fireheart brew
			CraftLogic(clickedCraft2, 1, Inventory::contEmberroot, Inventory::contSunblossom, Inventory::contBerry, Inventory::contFireHeart);
			//crafting frostveil potion
			CraftLogic(clickedCraft1, 2, Inventory::contFrostmint, Inventory::contMoonleaf, Inventory::contBerry, Inventory::contFrostveil);

		}
		void ShowCrafting(Surface* screen, bool qPressed, int mouseX, int mouseY)
		{
			bool clickedOnTable = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 32 && mouseX <= 241 && mouseY >= 243 && mouseY <= 427;
			if (clickedOnTable && House::houseisopen)
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
				CraftingDraw(screen);
			}
		}
	}
};