#include "crafting.h"

namespace Tmpl8
{
	bool Crafting::CraftingIsOpen()
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
	void Crafting::CraftVitalTonic()
	{
		if(inventory.GetItemCount(Inventory::Item::Sunblossom) >= 1 && inventory.GetItemCount(Inventory::Item::Emberroot) >= 1)
		{
			inventory.AddItem(Inventory::Item::VitalTonic);
			inventory.AddItem(Inventory::Item::Sunblossom, -1);
			inventory.AddItem(Inventory::Item::Emberroot, -1);
		}
		//else add sound maybe
	}
	void Crafting::CraftCalmMind()
	{
		if(inventory.GetItemCount(Inventory::Item::Moonleaf) >= 1 && inventory.GetItemCount(Inventory::Item::Frostmint) >= 1)
		{
			inventory.AddItem(Inventory::Item::CalmMind);
			inventory.AddItem(Inventory::Item::Moonleaf, -1);
			inventory.AddItem(Inventory::Item::Frostmint, -1);
		}
	}
	void Crafting::CraftDreamDraught()
	{
		if(inventory.GetItemCount(Inventory::Item::Moonleaf) >= 1 && inventory.GetItemCount(Inventory::Item::Berry) >= 1)
		{
			inventory.AddItem(Inventory::Item::DreamDraught);
			inventory.AddItem(Inventory::Item::Moonleaf, -1);
			inventory.AddItem(Inventory::Item::Berry, -1);
		}
	}
	void Crafting::CraftFireHeart()
	{
		if(inventory.GetItemCount(Inventory::Item::Emberroot) >= 1 && inventory.GetItemCount(Inventory::Item::Sunblossom) >= 1 && inventory.GetItemCount(Inventory::Item::Berry) >= 1)
		{
			inventory.AddItem(Inventory::Item::FireHeart);
			inventory.AddItem(Inventory::Item::Emberroot, -1);
			inventory.AddItem(Inventory::Item::Sunblossom, -1);
			inventory.AddItem(Inventory::Item::Berry, -1);
		}
	}
	void Crafting::CraftFrostVeil()
	{
		if(inventory.GetItemCount(Inventory::Item::Frostmint) >= 1 && inventory.GetItemCount(Inventory::Item::Moonleaf) >= 1 && inventory.GetItemCount(Inventory::Item::Berry) >= 1)
		{
			inventory.AddItem(Inventory::Item::FrostVeil);
			inventory.AddItem(Inventory::Item::Frostmint, -1);
			inventory.AddItem(Inventory::Item::Moonleaf, -1);
			inventory.AddItem(Inventory::Item::Berry, -1);
		}
	}
	void Crafting::CraftPotions()
	{
		// Detect crafting button clicks
		bool clickedCraft1 = Buttons::leftPressed && WorldState::mouseX >= 295 && WorldState::mouseX <= 359 && WorldState::mouseY >= 111 && WorldState::mouseY <= 154;
		bool clickedCraft2 = Buttons::leftPressed && WorldState::mouseX >= 643 && WorldState::mouseX <= 704 && WorldState::mouseY >= 111 && WorldState::mouseY <= 154;

		if (clickedCraft1 || clickedCraft2)
			Buttons::leftPressed = false; // Reset left click state to avoid multiple clicks

		if (frame == 0)
		{
			if(clickedCraft1)
				CraftVitalTonic();
			if(clickedCraft2)
				CraftCalmMind();
		}
		if(frame == 1)
		{
			if(clickedCraft1)
				CraftDreamDraught();
			if(clickedCraft2)
				CraftFireHeart();
		}
		if(frame == 2)
		{
			if(clickedCraft1)
				CraftFrostVeil();
		}
	}
	void Crafting::CraftingDraw(Surface* screen) ///chance frame!!!!!!!!!!!!!!
	{
		crafting.Draw(screen, 0, 0);

		// Display ingredient counts
		char sunBlossom[32], moonLeaf[32], emberRoot[32], frostMint[32], berry[32];
		char vitalTonic[32], calmMind[32], dreamDraught[32], fireHeart[32], frostVeil[32];

		// Format strings with current counts
		sprintf(sunBlossom, "x%d", inventory.GetItemCount(Inventory::Item::Sunblossom));
		sprintf(moonLeaf, "x%d", inventory.GetItemCount(Inventory::Item::Moonleaf));
		sprintf(emberRoot, "x%d", inventory.GetItemCount(Inventory::Item::Emberroot));
		sprintf(frostMint, "x%d", inventory.GetItemCount(Inventory::Item::Frostmint));
		sprintf(berry, "x%d", inventory.GetItemCount(Inventory::Item::Berry));

		sprintf(vitalTonic, "x%d", inventory.GetItemCount(Inventory::Item::VitalTonic));
		sprintf(calmMind, "x%d", inventory.GetItemCount(Inventory::Item::CalmMind));
		sprintf(dreamDraught, "x%d", inventory.GetItemCount(Inventory::Item::DreamDraught));
		sprintf(fireHeart, "x%d", inventory.GetItemCount(Inventory::Item::FireHeart));
		sprintf(frostVeil, "x%d", inventory.GetItemCount(Inventory::Item::FrostVeil));

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