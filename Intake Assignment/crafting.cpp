#include "crafting.h"

namespace Tmpl8
{
	namespace Crafting
	{
		Sprite crafting(new Surface("assets/crafting.png"), 3);
		bool craftingisopen = false;
		int frame = 0;
		void CraftingDraw(Surface* screen)
		{
			crafting.Draw(screen, 0, 0);

			// Display ingredient counts
			char sunBlossom[32], moonLeaf[32], emberRoot[32], frostMint[32], berry[32];
			char vitalTonic[32], calmMind[32], dreamDraught[32], fireHeart[32], frostVeil[32];

			// Format strings with current counts
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

			// Display ingredients
			if (craftingisopen)
			{
				screen->Print(sunBlossom, 291 - 5, 48, 0x0);
				screen->Print(moonLeaf, 341 - 5, 48, 0x0);
				screen->Print(emberRoot, 392 - 3, 48, 0x0);
				screen->Print(frostMint, 443 - 4, 48, 0x0);
				screen->Print(berry, 499 - 5, 48, 0x0);
			}
			// Display potions based on selected frame
			if (frame == 0 && craftingisopen)
			{
				screen->Print(vitalTonic, 329 - 4, 163, 0x0);
				screen->Print(calmMind, 676 - 4, 163, 0x0);
			}
			if (frame == 1 && craftingisopen)
			{
				screen->Print(dreamDraught, 329 - 4, 163, 0x0);
				screen->Print(fireHeart, 676 - 4, 163, 0x0);
			}
			if (frame == 2 && craftingisopen)
			{
				screen->Print(frostVeil, 329 - 4, 163, 0x0);
			}
		} 
		void ManageFrames() 
		{
			// Manage frame selection buttons
			bool button1 = GetAsyncKeyState(VK_LBUTTON) && WorldState::mouseX >= 244 && WorldState::mouseX <= 314 && WorldState::mouseY >= 516 && WorldState::mouseY <= 584;
			bool button2 = GetAsyncKeyState(VK_LBUTTON) && WorldState::mouseX >= 364 && WorldState::mouseX <= 434 && WorldState::mouseY >= 516 && WorldState::mouseY <= 584;
			bool button3 = GetAsyncKeyState(VK_LBUTTON) && WorldState::mouseX >= 485 && WorldState::mouseX <= 554 && WorldState::mouseY >= 516 && WorldState::mouseY <= 584;
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
			// Crafting logic for potions with two ingredients
			if (button && frame == Frame && ingredient1 >= 1 && ingredient2 >= 1)
			{
				ingredient1--;
				ingredient2--;
				potion++;
			}
		}
		void CraftLogic(bool button, int Frame, int& ingredient1, int& ingredient2, int& ingredient3, int& potion)
		{
			// Crafting logic for potions with three ingredients
			if (button && frame == Frame && ingredient1 >= 1 && ingredient2 >= 1 && ingredient3 >= 1)
			{
				ingredient1--;
				ingredient2--;
				ingredient3--;
				potion++;
			}
		}
		void Craft()
		{
			// Detect crafting button clicks
			bool clickedCraft1 = Buttons::leftPressed && WorldState::mouseX >= 295 && WorldState::mouseX <= 359 && WorldState::mouseY >= 111 && WorldState::mouseY <= 154;
			bool clickedCraft2 = Buttons::leftPressed && WorldState::mouseX >= 643 && WorldState::mouseX <= 704 && WorldState::mouseY >= 111 && WorldState::mouseY <= 154;

			if(clickedCraft1 || clickedCraft2)
				Buttons::leftPressed = false; // Reset left click state to avoid multiple clicks

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
		void ManageCrafring()
		{
			bool clickedOnTable = Buttons::leftPressed && WorldState::mouseX >= 103 && WorldState::mouseX <= 294 && WorldState::mouseY >= 331 && WorldState::mouseY <= 476;

			// Open crafting interface when clicking on crafting table inside house
			if (clickedOnTable && House::houseisopen && House::frame == 0)
			{
				Buttons::leftPressed = false; // Reset left click state to avoid multiple clicks
				craftingisopen = true;
				frame = 0;
				crafting.SetFrame(frame);
			}
			// Close crafting interface when pressing Q
			if (Buttons::qPressed && craftingisopen)
			{
				Buttons::qPressed = false; // Reset Q key state to avoid multiple toggles
				craftingisopen = false;
			}
		}
		void Draw(Surface* screen)
		{
			// Draw crafting interface
			if (craftingisopen)
			{
				ManageFrames();
				CraftingDraw(screen);
			}
		}
	}
};