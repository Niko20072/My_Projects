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
	void Crafting::CraftVitalTonic()
	{
		if(inventory.GetItemCount(Inventory::Item::Sunblossom) >= 1 && inventory.GetItemCount(Inventory::Item::Emberroot) >= 1)
		{
			tutorialCraft = true; // Set tutorial state to potion crafted
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
	//new
	/*
	void Crafting::CraftLogic(bool button, int Frame, int ingredient1, int ingredient2, int potion)
	{
		// Crafting logic for potions with two ingredients
		if (Input::GetMouseButtonPressed(1) && button && frame == Frame && ingredient1 >= 1 && ingredient2 >= 1)
		{
			inventory.AddItem(static_cast<Inventory::Item>(potion));
			inventory.AddItem(static_cast<Inventory::Item>(ingredient1), -1);
			inventory.AddItem(static_cast<Inventory::Item>(ingredient2), -1);
		}
	}
	void Crafting::CraftLogic(bool button, int Frame, int ingredient1, int ingredient2, int ingredient3, int potion)
	{
		// Crafting logic for potions with three ingredients
		if (Input::GetMouseButtonPressed(1) && button && frame == Frame && ingredient1 >= 1 && ingredient2 >= 1 && ingredient3 >= 1)
		{
			inventory.AddItem(static_cast<Inventory::Item>(potion));
			inventory.AddItem(static_cast<Inventory::Item>(ingredient1), -1);
			inventory.AddItem(static_cast<Inventory::Item>(ingredient2), -1);
			inventory.AddItem(static_cast<Inventory::Item>(ingredient3), -1);
		}
	}
	void Crafting::CraftLogic()
	{
		// Detect crafting button clicks
		bool clickedCraft1 = WorldState::mouseX >= 295 && WorldState::mouseX <= 359 && WorldState::mouseY >= 111 && WorldState::mouseY <= 154;
		bool clickedCraft2 =  WorldState::mouseX >= 643 && WorldState::mouseX <= 704 && WorldState::mouseY >= 111 && WorldState::mouseY <= 154;

		///crafting vital tonic
		CraftLogic(clickedCraft1, 0, static_cast<int>(inventory.GetItemCount(Inventory::Item::Sunblossom)), static_cast<int>(Inventory::Item::Emberroot), static_cast<int>(Inventory::Item::VitalTonic));
		///crafting calm mind elixir
		CraftLogic(clickedCraft2, 0, static_cast<int>(Inventory::Item::Moonleaf), static_cast<int>(Inventory::Item::Frostmint), static_cast<int>(Inventory::Item::CalmMind));
		///crafting dream draught
		CraftLogic(clickedCraft1, 1, static_cast<int>(Inventory::Item::Moonleaf), static_cast<int>(Inventory::Item::Berry), static_cast<int>(Inventory::Item::DreamDraught));
		///crafting fireheart brew
		CraftLogic(clickedCraft2, 1, static_cast<int>(Inventory::Item::Emberroot), static_cast<int>(Inventory::Item::Sunblossom), static_cast<int>(Inventory::Item::Berry), static_cast<int>(Inventory::Item::FireHeart));
		//crafting frostveil potion
		CraftLogic(clickedCraft1, 2, static_cast<int>(Inventory::Item::Frostmint), static_cast<int>(Inventory::Item::Moonleaf), static_cast<int>(Inventory::Item::Berry), static_cast<int>(Inventory::Item::FrostVeil));
	}
	//new*/
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
		screen->PrintScaled(sunBlossom, 291 - 11, 48, 2, 2, 0x0);
		screen->PrintScaled(moonLeaf, 341 - 12, 48, 2, 2, 0x0);
		screen->PrintScaled(emberRoot, 392 - 9, 48, 2, 2, 0x0);
		screen->PrintScaled(frostMint, 443 - 10, 48, 2, 2, 0x0);
		screen->PrintScaled(berry, 499 - 11, 48, 2, 2, 0x0);

		// Display potions based on selected frame
		if (frame == 0)
		{
			screen->PrintScaled(vitalTonic, 329 - 13, 163, 2, 2, 0x0);
			screen->PrintScaled(calmMind, 676 - 13, 163, 2, 2, 0x0);
		}
		if (frame == 1)
		{
			screen->PrintScaled(dreamDraught, 329 - 13, 163, 2, 2, 0x0);
			screen->PrintScaled(fireHeart, 676 - 13, 163, 2, 2, 0x0);
		}
		if (frame == 2)
		{
			screen->PrintScaled(frostVeil, 329 - 13, 163, 2, 2, 0x0);
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