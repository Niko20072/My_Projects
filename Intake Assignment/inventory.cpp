#include "inventory.h"

namespace Tmpl8
{
	Inventory::Inventory( int x, int y) : x(x), y(y) 
	{
	}
	void Inventory::SetFrame(int frame)
	{
		inventory.SetFrame(frame);
	}
	void Inventory::DrawInventory(Surface* screen)
	{
		inventory.Draw(screen, 140, 20);
		if (isopen && frame == 0)
		{
			screen->Print("Sunblossom          x0", 350, 236, 0x0);
			screen->Print("Moonleaf            x0", 350, 280, 0x0);
			screen->Print("Emberroot           x0", 350, 321, 0x0);
			screen->Print("Frostmint           x0", 350, 367, 0x0);
			screen->Print("Nightshade Berry    x0", 350, 411, 0x0);
		}
		if (isopen && frame == 1)
		{
			screen->Print("Vital Tonic         x0", 350, 241, 0x0);
			screen->Print("Calm Mind Elixir    x0", 350, 285, 0x0);
			screen->Print("Dream Draught       x0", 350, 328, 0x0);
			screen->Print("FireHeart Brew      x0", 350, 373, 0x0);
			screen->Print("Frostveil Potion    x0", 350, 418, 0x0);
		}
		if (isopen && frame == 2)
		{
			screen->Print("Sunblossom          x0", 350, 236, 0x0);
			screen->Print("Moonleaf            x0", 350, 280, 0x0);
			screen->Print("Emberroot           x0", 350, 321, 0x0);
			screen->Print("Frostmint           x0", 350, 367, 0x0);
			screen->Print("Nightshade Berry    x0", 350, 411, 0x0);
		}
		if (seedsisopen && frame == 3)
		{
			screen->Print("Sunblossom          x0", 350, 236, 0x0);
			screen->Print("Moonleaf            x0", 350, 280, 0x0);
			screen->Print("Emberroot           x0", 350, 321, 0x0);
			screen->Print("Frostmint           x0", 350, 367, 0x0);
			screen->Print("Nightshade Berry    x0", 350, 411, 0x0);
		}
	}	
	void Inventory::NormalInventory(Surface* screen, int mouseX, int mouseY)
	{
		bool clickedOutsideInv = GetAsyncKeyState(VK_LBUTTON) && !(mouseX >= 207 && mouseX <= 579 && mouseY >= 78 && mouseY <= 519);
		bool clickedOnPlantButton = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 323 && mouseX <= 366 && mouseY >= 471 && mouseY <= 510;
		bool clickedOnPotionButton = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 375 && mouseX <= 510 && mouseY >= 471 && mouseY <= 510;
		bool clickedOnSeedButton = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 430 && mouseX <= 475 && mouseY >= 471 && mouseY <= 510;

		//Toggle normal inventory
		if (GetAsyncKeyState('E') && inputCooldown <= 0.0f)
		{
			carisopen = false;
			seedsisopen = false;
			inputCooldown = 0.2f; // 200 ms
			isopen = !isopen;
			frame = 0;
			inventory.SetFrame(frame);
		}

		//Click inventory
		if (isopen)
		{
			if (clickedOnPlantButton)
			{
				frame = 0;
				inventory.SetFrame(frame);
			}
			if (clickedOnPotionButton) 
			{
				frame = 1;
				inventory.SetFrame(frame);
			}
			if (clickedOnSeedButton)
			{
				frame = 2;
				inventory.SetFrame(frame);
			}
			if (clickedOutsideInv)
				isopen = false;
		}

	}
	void Inventory::CarInventory(Surface* screen, int mouseX, int mouseY, float worldX, float worldY, float reachX1, float reachY1, float reachX2, float reachY2)
	{
		bool clickedOutsideInv = GetAsyncKeyState(VK_LBUTTON) && !(mouseX >= 207 && mouseX <= 579 && mouseY >= 78 && mouseY <= 519);
		bool clickedOnShopButton = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 345 && mouseX <= 389 && mouseY >= 471 && mouseY <= 510;
		bool clickedOnOrdersButton = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 399 && mouseX <= 444 && mouseY >= 471 && mouseY <= 510;
		//bool playerCloseToCar = worldPlayerX >= 448 && worldPlayerX <= 688 && worldPlayerY >= 86 && worldPlayerY <= 195;
		bool playerCloseToCar = reachX2 >= 528 && reachX1 <= 686 && reachY2 >= 175 && reachY1 <= 220;
		bool clickedOnCar = worldX >= 528 && worldX <= 686 && worldY >= 175 && worldY <= 220;
		bool moved = GetAsyncKeyState('W') || GetAsyncKeyState('A') || GetAsyncKeyState('S') || GetAsyncKeyState('D');

		//Toggle car inventory
		if (GetAsyncKeyState(VK_LBUTTON) && clickedOnCar && playerCloseToCar && inputCooldown <= 0.0f)
		{
			isopen = false;
			carisopen = false;
			inputCooldown = 0.2f; // 200 ms
			carisopen = !carisopen;
			frame = 4;
			inventory.SetFrame(frame);
		}

		//Click car inventory
		if (carisopen)
		{
			if (clickedOnShopButton)
			{
				frame = 4;
				inventory.SetFrame(frame);
			}
			if (clickedOnOrdersButton)
			{
				frame = 5;
				inventory.SetFrame(frame);
			}
			if (moved || clickedOutsideInv || GetAsyncKeyState('E'))
				carisopen = false;
		}

	}
	void Inventory::SeedsInventory(Surface* screen, int mouseX, int mouseY, float worldX, float worldY, bool tileClicekd)
	{
		bool clickedOutsideInv = GetAsyncKeyState(VK_LBUTTON) && !(mouseX >= 207 && mouseX <= 579 && mouseY >= 78 && mouseY <= 519);
		bool moved = GetAsyncKeyState('W') || GetAsyncKeyState('A') || GetAsyncKeyState('S') || GetAsyncKeyState('D');

		//Toggle seed inventory
		if (GetAsyncKeyState(VK_LBUTTON) && inputCooldown <= 0.0f && tileClicekd)
		{
			isopen = false;
			carisopen = false;
			inputCooldown = 0.2f; // 200 ms
			seedsisopen = !seedsisopen;
			frame = 3;
			inventory.SetFrame(frame);
		}

		//Click seed inventory
		if (seedsisopen)
		{
			if (clickedOutsideInv || GetAsyncKeyState('E') || moved)
				seedsisopen = false;
		}

	}
	void Inventory::DrawOnScreen(Surface* screen, float deltaTime)
	{
		inputCooldown -= deltaTime;//to limit key press speed
		if (inputCooldown <= 0.0f)
			inputCooldown = 0.0f;
		
		if (isopen || carisopen || seedsisopen)
			DrawInventory(screen);
	}
	bool Inventory::InventorysClosed()
	{
		if (!isopen && !carisopen && !seedsisopen)
			return 1;
		return 0;
	}
};