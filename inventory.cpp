#include "inventory.h"
#include "wateringCan.h"
#include "input.h"

namespace Tmpl8//sterge
{
	int Inventory::getFrame()
	{
		return frame;
	}
	bool Inventory::MainInvIsOpen()
	{
		return inventoryisopen;
	}
	bool Inventory::SeedInvIsOpen()
	{
		return seedsisopen;
	}
	void Inventory::setSeedState(bool state)
	{
		seedsisopen = state;
	}

	void Inventory::AddItem(Item item, int quantity)
	{
		items[item] += quantity; // Add quantity to the specified item in the inventory
	}
	void Inventory::SetItemTo(Item item, int quantity)
	{
		items[item] = quantity; // Set the specified item to the given quantity in the inventory
	}
	int Inventory::GetItemCount(Item item)
	{
		return items[item];
	}

	void Inventory::InventoryText(Surface* screen)
	{
		// Display values
		char sunBlossom[32], moonLeaf[32], emberRoot[32], frostMint[32], berry[32];
		char vitalTonic[32], calmMind[32], dreamDraught[32], fireHeart[32], frostVeil[32];
		char seedSunBlossom[32], seedMoonLeaf[32], seedEmberRoot[32], seedFrostMint[32], seedBerry[32];
		char counterSeedSunBlossom[32], counterSeedMoonLeaf[32], counterSeedEmberRoot[32], counterSeedFrostMint[32], counterSeedBerry[32];

		// Format strings with current counts
		sprintf(sunBlossom, "Sunblossom  x%d", items[Item::Sunblossom]);
		sprintf(moonLeaf, "Moonleaf  x%d", items[Item::Moonleaf]);
		sprintf(emberRoot, "Emberroot  x%d", items[Item::Emberroot]);
		sprintf(frostMint, "Frostmint  x%d", items[Item::Frostmint]);
		sprintf(berry, "Nightshade Berry x%d", items[Item::Berry]);

		sprintf(vitalTonic, "Vital Tonic x%d", items[Item::VitalTonic]);
		sprintf(calmMind, "Calm Mind Elixir x%d", items[Item::CalmMind]);
		sprintf(dreamDraught, "Dream Draught x%d", items[Item::DreamDraught]);
		sprintf(fireHeart, "FireHeart Brew x%d", items[Item::FireHeart]);
		sprintf(frostVeil, "Frostveil Potion x%d", items[Item::FrostVeil]);

		sprintf(seedSunBlossom, "Sunblossom  x%d", items[Item::SeedSunblossom]);
		sprintf(seedMoonLeaf, "Moonleaf  x%d", items[Item::SeedMoonleaf]);
		sprintf(seedEmberRoot, "Emberroot  x%d", items[Item::SeedEmberroot]);
		sprintf(seedFrostMint, "Frostmint  x%d", items[Item::SeedFrostmint]);
		sprintf(seedBerry, "Nightshade Berry x%d", items[Item::SeedBerry]);

		sprintf(counterSeedSunBlossom, "x%d", items[Item::SeedSunblossom]);
		sprintf(counterSeedMoonLeaf, "x%d", items[Item::SeedMoonleaf]);
		sprintf(counterSeedEmberRoot, "x%d", items[Item::SeedEmberroot]);
		sprintf(counterSeedFrostMint, "x%d", items[Item::SeedFrostmint]);
		sprintf(counterSeedBerry, "x%d", items[Item::SeedBerry]);

		if (MainInvIsOpen())
		{
			// Display when ingredients inventory is open
			if (frame == 0)
			{
				screen->PrintScaled(sunBlossom, 330, 236, 2, 2, 0x0);
				screen->PrintScaled(moonLeaf, 330, 277, 2, 2, 0x0);
				screen->PrintScaled(emberRoot, 330, 319, 2, 2, 0x0);
				screen->PrintScaled(frostMint, 330, 365, 2, 2, 0x0);
				screen->PrintScaled(berry, 316, 409, 2, 2, 0x0);
			}
			// Display when potions inventory is open
			else if (frame == 1)
			{
				screen->PrintScaled(vitalTonic, 320, 239, 2, 2, 0x0);
				screen->PrintScaled(calmMind, 320, 282, 2, 2, 0x0);
				screen->PrintScaled(dreamDraught, 320, 326, 2, 2, 0x0);
				screen->PrintScaled(fireHeart, 320, 369, 2, 2, 0x0);
				screen->PrintScaled(frostVeil, 320, 417, 2, 2, 0x0);
			}
			// Display when seeds inventory is open
			else if (frame == 2)
			{
				screen->PrintScaled(seedSunBlossom, 330, 236, 2, 2, 0x0);
				screen->PrintScaled(seedMoonLeaf, 330, 277, 2, 2, 0x0);
				screen->PrintScaled(seedEmberRoot, 330, 319, 2, 2, 0x0);
				screen->PrintScaled(seedFrostMint, 330, 365, 2, 2, 0x0);
				screen->PrintScaled(seedBerry, 316, 409, 2, 2, 0x0);
			}
		}
		
		// Display when planting seeds inventory is open
		if (SeedInvIsOpen() && frame == 3)
		{
			screen->PrintScaled(counterSeedSunBlossom, 510, 236, 2, 2, 0x0);
			screen->PrintScaled(counterSeedMoonLeaf, 510, 278, 2, 2, 0x0);
			screen->PrintScaled(counterSeedEmberRoot, 510, 321, 2, 2, 0x0);
			screen->PrintScaled(counterSeedFrostMint, 510, 364, 2, 2, 0x0);
			screen->PrintScaled(counterSeedBerry, 510, 405, 2, 2, 0x0);
		}

	}
	void Inventory::MainInventoryLogic()
	{
		// Detect clicks
		bool clickedOutsideInv = Input::GetMouseButtonPressed(1) && !(Input::GetMouseX() >= 207 && Input::GetMouseX() <= 579 && Input::GetMouseY() >= 78 && Input::GetMouseY() <= 519);
		bool clickedOnPlantButton = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 323 && Input::GetMouseX() <= 366 && Input::GetMouseY() >= 471 && Input::GetMouseY() <= 510;
		bool clickedOnPotionButton = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 375 && Input::GetMouseX() <= 510 && Input::GetMouseY() >= 471 && Input::GetMouseY() <= 510;
		bool clickedOnSeedButton = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 430 && Input::GetMouseX() <= 475 && Input::GetMouseY() >= 471 && Input::GetMouseY() <= 510;

		//Toggle normal inventory
		if (Input::GetKeyPressed(SDL_SCANCODE_E))
		{
			seedsisopen = false;
			inventoryisopen = !inventoryisopen;
			frame = 0;
		}

		//Click inventory
		if (inventoryisopen)
		{
			// Manage frame selection buttons
			if (clickedOnPlantButton)
				frame = 0;
			if (clickedOnPotionButton)
				frame = 1;
			if (clickedOnSeedButton)
				frame = 2;
			if (clickedOutsideInv || Input::GetKeyPressed(SDL_SCANCODE_Q))
				inventoryisopen = false;
		}
	}
	void Inventory::SeedInventoryLogic(bool tileClicekd)
	{
		// Detect clicks
		bool clickedOutsideInv = Input::GetMouseButtonPressed(1) && !(Input::GetMouseX() >= 207 && Input::GetMouseX() <= 579 && Input::GetMouseY() >= 78 && Input::GetMouseY() <= 519);
		bool moved = Input::GetKeyPressed(SDL_SCANCODE_W) || Input::GetKeyPressed(SDL_SCANCODE_A) || Input::GetKeyPressed(SDL_SCANCODE_S) || Input::GetKeyPressed(SDL_SCANCODE_D);

		//Toggle seed inventory
		if (tileClicekd && !seedsisopen && !wateringCan.getState())
		{
			seedsisopen = true;
			frame = 3;
		}

		//Click seed inventory
		if (seedsisopen)
		{
			if (clickedOutsideInv || Input::GetKeyPressed(SDL_SCANCODE_Q) || Input::GetKeyPressed(SDL_SCANCODE_E) || moved)
				seedsisopen = false;
		}
	}
	void Inventory::Draw(Surface* screen)
	{
		inventory.SetFrame(frame);
		if (inventoryisopen || seedsisopen)
		{
			inventory.Draw(screen, 140, 20);
			InventoryText(screen);
		}
	}
}