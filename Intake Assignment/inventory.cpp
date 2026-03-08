#include "inventory.h"
#include "wateringCan.h"
#include "worldState.h"
#include "input.h"

namespace Tmpl8//sterge
{
	//maybe states (kinda fixed it without states)
	enum class State
	{
		Closed,
		Inventory,
		Seeds
	};

	State m_State = State::Closed;

	void SetState(State newState)
	{
		m_State = newState;
	}

	void Inventory::update()
	{
		switch (m_State)
		{
		case State::Closed:
			// Update closed state..
			if (Input::GetKeyPressed(SDL_SCANCODE_E))
			{
				SetState(State::Inventory);
				break;
			}
		case State::Inventory:
			// Update inventory state..
			if (Input::GetKeyPressed(SDL_SCANCODE_E))
			{
				SetState(State::Closed);
			}
			break;
		case State::Seeds:
			// Update seeds state....
			break;
		};
	}
		//namespace to class de ce
		int Inventory::getFrame()
		{
			return frame;
		}
		int Inventory::MainInvIsOpen()
		{
			return inventoryisopen;
		}
		int Inventory::SeedInvIsOpen()
		{
			return seedsisopen;
		}
		void Inventory::setSeedState(bool state)
		{
			seedsisopen = state;
		}

		int Inventory::AddItem(Item item, int quantity)
		{
			items[item] += quantity; // Add quantity to the specified item in the inventory
			return items[item];
		}
		int Inventory::SetItemTo(Item item, int quantity)
		{
			items[item] = quantity; // Set the specified item to the given quantity in the inventory
			return items[item];
		}
		int Inventory::GetItemCount(Item item)
		{
			return items[item];
		}

		//make text bigger
		void Inventory::InventoryText(Surface*screen)
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

			// Display when ingredients inventory is open
			if (MainInvIsOpen() && frame == 0)
			{
				screen->PrintScaled(sunBlossom, 350-20, 236, 2, 2, 0x0);
				screen->PrintScaled(moonLeaf, 350-20, 277, 2, 2, 0x0);
				screen->PrintScaled(emberRoot, 350 - 20, 319, 2, 2, 0x0);
				screen->PrintScaled(frostMint, 350 - 20, 365, 2, 2, 0x0);
				screen->PrintScaled(berry, 350 - 20-14, 409, 2, 2, 0x0);
			}
			// Display when potions inventory is open
			if (MainInvIsOpen() && frame == 1)
			{
				screen->PrintScaled(vitalTonic, 350 - 30, 239, 2, 2, 0x0);
				screen->PrintScaled(calmMind, 350 - 30, 282, 2, 2, 0x0);
				screen->PrintScaled(dreamDraught, 350 - 30, 326, 2, 2, 0x0);
				screen->PrintScaled(fireHeart, 350 - 30, 369, 2, 2, 0x0);
				screen->PrintScaled(frostVeil, 350 - 30, 417, 2, 2, 0x0);
			}
			// Display when seeds inventory is open
			if (MainInvIsOpen() && frame == 2)
			{
				screen->PrintScaled(seedSunBlossom, 350 - 20, 236, 2, 2, 0x0);
				screen->PrintScaled(seedMoonLeaf, 350 - 20, 277, 2, 2, 0x0);
				screen->PrintScaled(seedEmberRoot, 350 - 20, 319, 2, 2, 0x0);
				screen->PrintScaled(seedFrostMint, 350 - 20, 365, 2, 2, 0x0);
				screen->PrintScaled(seedBerry, 350 - 20 - 14, 409, 2, 2, 0x0);
			}
			// Display when planting seeds inventory is open
			if (SeedInvIsOpen() && frame == 3)
			{
				screen->PrintScaled(counterSeedSunBlossom, 350 + 160, 236, 2, 2, 0x0);
				screen->PrintScaled(counterSeedMoonLeaf, 350 + 160, 278, 2, 2, 0x0);
				screen->PrintScaled(counterSeedEmberRoot, 350 + 160, 321, 2, 2, 0x0);
				screen->PrintScaled(counterSeedFrostMint, 350 + 160, 364, 2, 2, 0x0);
				screen->PrintScaled(counterSeedBerry, 350 + 160, 405, 2, 2, 0x0);
			}
			
		}
		void Inventory::MainInventoryLogic(Surface* screen)
		{
			// Detect clicks
			bool clickedOutsideInv = Input::GetMouseButtonPressed(1) && !(WorldState::mouseX >= 207 && WorldState::mouseX <= 579 && WorldState::mouseY >= 78 && WorldState::mouseY <= 519);
			bool clickedOnPlantButton = Input::GetMouseButtonPressed(1) && WorldState::mouseX >= 323 && WorldState::mouseX <= 366 && WorldState::mouseY >= 471 && WorldState::mouseY <= 510;
			bool clickedOnPotionButton = Input::GetMouseButtonPressed(1) && WorldState::mouseX >= 375 && WorldState::mouseX <= 510 && WorldState::mouseY >= 471 && WorldState::mouseY <= 510;
			bool clickedOnSeedButton = Input::GetMouseButtonPressed(1) && WorldState::mouseX >= 430 && WorldState::mouseX <= 475 && WorldState::mouseY >= 471 && WorldState::mouseY <= 510;

			//Toggle normal inventory
			if (Input::GetKeyPressed(SDL_SCANCODE_E)) //add state maybe
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
			inventory.SetFrame(frame);

		}
		void Inventory::SeedInventoryLogic(Surface* screen, bool tileClicekd)
		{
			// Detect clicks
			bool clickedOutsideInv = Input::GetMouseButtonPressed(1) && !(WorldState::mouseX >= 207 && WorldState::mouseX <= 579 && WorldState::mouseY >= 78 && WorldState::mouseY <= 519);
			bool moved = Input::GetKeyPressed(SDL_SCANCODE_W) || Input::GetKeyPressed(SDL_SCANCODE_A) || Input::GetKeyPressed(SDL_SCANCODE_S) || Input::GetKeyPressed(SDL_SCANCODE_D);

			//Toggle seed inventory
			if (tileClicekd && !seedsisopen && !wateringCan.getState())
			{
				inventoryisopen = false;
				seedsisopen = true;
				frame = 3;
			}

			//Click seed inventory
			if (seedsisopen)
				if (clickedOutsideInv || Input::GetKeyPressed(SDL_SCANCODE_Q) || Input::GetKeyPressed(SDL_SCANCODE_E) || moved)
					seedsisopen = false;
			inventory.SetFrame(frame);
		}
		void Inventory::Draw(Surface* screen)
		{
			if (inventoryisopen || seedsisopen)
			{
				inventory.Draw(screen, 140, 20);
				InventoryText(screen);
			}
				
		}
		
		/*
		bool Inventory::VerifyRandomPotionOrder(int type, int quantity)
		{
			if (type == 0 && GetItemCount(Item::VitalTonic) >= quantity)
			{
				return true;
			}
			else if(type == 1 && GetItemCount(Item::CalmMind) >= quantity)
			{
				return true;
			}
			else if(type == 2 && GetItemCount(Item::DreamDraught) >= quantity)
			{
				return true;
			}
			else if(type == 3 && GetItemCount(Item::FireHeart) >= quantity)
			{
				return true;
			}
			else if(type == 4 && GetItemCount(Item::FrostVeil) >= quantity)
			{
				return true;
			}
			return false; // Return false for invalid potion type
		}
		void Inventory::RandomPotionOrder(int type, int quantity)
		{
			if(type == 0)
			{
				AddItem(Item::VitalTonic, -quantity);
			}
			else if(type == 1)
			{
				AddItem(Item::CalmMind, -quantity);
			}
			else if(type == 2)
			{
				AddItem(Item::DreamDraught, -quantity);
			}
			else if(type == 3)
			{
				AddItem(Item::FireHeart, -quantity);
			}
			else if(type == 4)
			{
				AddItem(Item::FrostVeil, -quantity);
			}
		}*/

		

		
}