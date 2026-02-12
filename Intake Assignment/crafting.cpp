#include "crafting.h"

namespace Tmpl8
{
	bool Crafting::getState()
	{
		return craftingisopen;
	}
	void Crafting::setState(bool state)
	{
		craftingisopen = state;
	}
	int Crafting::getFrame()
	{
		return frame;
	}
	void Crafting::setFrame(int state)
	{
		frame = state;
	}
	void Crafting::ManageFrames()
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
	void Crafting::CraftLogic(bool button, int Frame, int& ingredient1, int& ingredient2, int& potion)
	{
		// Crafting logic for potions with two ingredients
		if (button && frame == Frame && ingredient1 >= 1 && ingredient2 >= 1)
		{
			ingredient1--;
			ingredient2--;
			potion++;
		}
	}
	void Crafting::CraftLogic(bool button, int Frame, int& ingredient1, int& ingredient2, int& ingredient3, int& potion)
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
	void Crafting::Craft()
	{
		// Detect crafting button clicks
		bool clickedCraft1 = Buttons::leftPressed && WorldState::mouseX >= 295 && WorldState::mouseX <= 359 && WorldState::mouseY >= 111 && WorldState::mouseY <= 154;
		bool clickedCraft2 = Buttons::leftPressed && WorldState::mouseX >= 643 && WorldState::mouseX <= 704 && WorldState::mouseY >= 111 && WorldState::mouseY <= 154;

		if (clickedCraft1 || clickedCraft2)
			Buttons::leftPressed = false; // Reset left click state to avoid multiple clicks

		///crafting vital tonic
		CraftLogic(clickedCraft1, 0, inventory.contSunblossom, inventory.contEmberroot, inventory.contVitalTonic);
		///crafting calm mind elixir
		CraftLogic(clickedCraft2, 0, inventory.contMoonleaf, inventory.contFrostmint, inventory.contCalmMind);
		///crafting dream draught
		CraftLogic(clickedCraft1, 1, inventory.contMoonleaf, inventory.contBerry, inventory.contDreamDraught);
		///crafting fireheart brew
		CraftLogic(clickedCraft2, 1, inventory.contEmberroot, inventory.contSunblossom, inventory.contBerry, inventory.contFireHeart);
		//crafting frostveil potion
		CraftLogic(clickedCraft1, 2, inventory.contFrostmint, inventory.contMoonleaf, inventory.contBerry, inventory.contFrostveil);

	}
	void Crafting::CraftingDraw(Surface* screen) ///chance frame!!!!!!!!!!!!!!
	{
		crafting.Draw(screen, 0, 0);

		// Display ingredient counts
		char sunBlossom[32], moonLeaf[32], emberRoot[32], frostMint[32], berry[32];
		char vitalTonic[32], calmMind[32], dreamDraught[32], fireHeart[32], frostVeil[32];

		// Format strings with current counts
		sprintf(sunBlossom, "x%d", inventory.getContSunblossom());
		sprintf(moonLeaf, "x%d", inventory.getContMoonleaf());
		sprintf(emberRoot, "x%d", inventory.getContEmberroot());
		sprintf(frostMint, "x%d", inventory.getContFrostmint());
		sprintf(berry, "x%d", inventory.getContBerry());

		sprintf(vitalTonic, "x%d", inventory.getContVitalTonic());
		sprintf(calmMind, "x%d", inventory.getContCalmMind());
		sprintf(dreamDraught, "x%d", inventory.getContDreamDraught());
		sprintf(fireHeart, "x%d", inventory.getContFireHeart());
		sprintf(frostVeil, "x%d", inventory.getContFrostveil());

		// Display ingredients
		screen->Print(sunBlossom, 291 - 5, 48, 0x0);
		screen->Print(moonLeaf, 341 - 5, 48, 0x0);
		screen->Print(emberRoot, 392 - 3, 48, 0x0);
		screen->Print(frostMint, 443 - 4, 48, 0x0);
		screen->Print(berry, 499 - 5, 48, 0x0);

		// Display potions based on selected frame
		if (frame == 0)
		{
			screen->Print(vitalTonic, 329 - 4, 163, 0x0);
			screen->Print(calmMind, 676 - 4, 163, 0x0);
		}
		if (frame == 1)
		{
			screen->Print(dreamDraught, 329 - 4, 163, 0x0);
			screen->Print(fireHeart, 676 - 4, 163, 0x0);
		}
		if (frame == 2)
		{
			screen->Print(frostVeil, 329 - 4, 163, 0x0);
		}
	}
	void Crafting::Draw(Surface* screen)
	{
		// Draw crafting interface
		if (craftingisopen)
		{
			ManageFrames();
			CraftingDraw(screen);
		}
	}
}