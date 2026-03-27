#include "crafting.h"
#include "input.h"
#include "inventory.h"

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
		if (craftingisopen)
		{
			bool button1 = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 244 && Input::GetMouseX() <= 314 && Input::GetMouseY() >= 516 && Input::GetMouseY() <= 584;
			bool button2 = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 364 && Input::GetMouseX() <= 434 && Input::GetMouseY() >= 516 && Input::GetMouseY() <= 584;
			bool button3 = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 485 && Input::GetMouseX() <= 554 && Input::GetMouseY() >= 516 && Input::GetMouseY() <= 584;
			if (button1)
				frame = 0;
			if (button2)
				frame = 1;
			if (button3)
				frame = 2;
			crafting.SetFrame(frame);
		}
	}
	void Crafting::CraftVitalTonic()
	{
		if(inventory.GetItemCount(Inventory::Item::Sunblossom) >= 1 && inventory.GetItemCount(Inventory::Item::Emberroot) >= 1)
		{
			tutorialCraft = true; // Set tutorial state to potion crafted
			inventory.AddItem(Inventory::Item::VitalTonic);
			inventory.AddItem(Inventory::Item::Sunblossom, -1);
			inventory.AddItem(Inventory::Item::Emberroot, -1);
		}
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
		bool clickedCraft1 = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 295 && Input::GetMouseX() <= 359 && Input::GetMouseY() >= 111 && Input::GetMouseY() <= 154;
		bool clickedCraft2 = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 643 && Input::GetMouseX() <= 704 && Input::GetMouseY() >= 111 && Input::GetMouseY() <= 154;

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
	void Crafting::CraftingDraw(Surface* screen)
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
		screen->PrintScaled(sunBlossom, 280, 48, 2, 2, 0x0);
		screen->PrintScaled(moonLeaf, 329, 48, 2, 2, 0x0);
		screen->PrintScaled(emberRoot, 383, 48, 2, 2, 0x0);
		screen->PrintScaled(frostMint, 433, 48, 2, 2, 0x0);
		screen->PrintScaled(berry, 488, 48, 2, 2, 0x0);

		// Display potions based on selected frame
		if (frame == 0)
		{
			screen->PrintScaled(vitalTonic, 316, 163, 2, 2, 0x0);
			screen->PrintScaled(calmMind, 663, 163, 2, 2, 0x0);
		}
		if (frame == 1)
		{
			screen->PrintScaled(dreamDraught, 316, 163, 2, 2, 0x0);
			screen->PrintScaled(fireHeart, 663, 163, 2, 2, 0x0);
		}
		if (frame == 2)
		{
			screen->PrintScaled(frostVeil, 316, 163, 2, 2, 0x0);
		}
	}
	void Crafting::Draw(Surface* screen)
	{
		if (craftingisopen)
			CraftingDraw(screen);
	}
}