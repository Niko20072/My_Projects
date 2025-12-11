#include "inventory.h"

namespace Tmpl8
{
	bool Inventory::isopen = false;
	bool Inventory::carisopen = false;
	bool Inventory::seedsisopen = false;
	int Inventory::frame_counter = 0;

	Inventory::Inventory( int x, int y) : x(x), y(y) 
	{
	}
	void Inventory::Draw(Surface* screen, int x, int y)
	{
		inventory.Draw(screen, x, y);
	}
	void Inventory::SetFrame(int frame)
	{
		inventory.SetFrame(frame);
	}
	void Inventory::DrawInventory(Surface* screen)
	{
		inventory.Draw(screen, 140, 20);
		screen->Print("Plant      x0", 270, 220, 0x0);
		screen->Print("Inventory Opened", 270, 240, 0x0);
		screen->Print("Inventory Opened", 270, 260, 0x0);
		screen->Print("Inventory Opened", 270, 280, 0x0);
		screen->Print("Inventory Opened", 270, 300, 0x0);
		screen->Print("Inventory Opened", 270, 320, 0x0);
		screen->Print("Inventory Opened", 270, 340, 0x0);
		screen->Print("Inventory Opened", 270, 360, 0x0);
		screen->Print("Inventory Opened", 270, 380, 0x0);
		screen->Print("Inventory Opened", 270, 400, 0x0);
	}
	void Inventory::ManageFrames(int fr1, int fr2)
	{
		if (frame == fr1 && frame_counter >= 15)
			frame = fr2, frame_counter = 0, inventory.SetFrame(frame);
		if (frame == fr2 && frame_counter >= 15)
			frame = fr1, frame_counter = 0, inventory.SetFrame(frame);
	}
	void Inventory::NormalInventory(Surface* screen, int mouseX, int mouseY, int worldX, int worldY, int worldPlayerX, int worldPlayerY)
	{
		bool clickedOutsideInv = GetAsyncKeyState(VK_LBUTTON) && !(mouseX >= 207 && mouseX <= 579 && mouseY >= 78 && mouseY <= 519);
		bool clickedOnInvButton = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 390 && mouseX <= 421 && mouseY >= 470 && mouseY <= 508;

		//Toggle normal inventory
		if (GetAsyncKeyState('E') && frame_counter >= 15)
		{
			carisopen = false;
			frame_counter = 0;
			isopen = !isopen;
			frame = 0;
			inventory.SetFrame(frame);
		}

		//Click inventory
		if (isopen)
		{
			if (GetAsyncKeyState(VK_LBUTTON) && clickedOnInvButton)
				ManageFrames(0, 1);
			if (clickedOutsideInv)
				isopen = false;
		}

	}
	void Inventory::CarInventory(Surface* screen, int mouseX, int mouseY, int worldX, int worldY, int worldPlayerX, int worldPlayerY)
	{
		bool clickedOutsideInv = GetAsyncKeyState(VK_LBUTTON) && !(mouseX >= 207 && mouseX <= 579 && mouseY >= 78 && mouseY <= 519);
		bool clickedOnInvButton = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 390 && mouseX <= 421 && mouseY >= 470 && mouseY <= 508;
		bool playerCloseToCar = worldPlayerX >= 448 && worldPlayerX <= 688 && worldPlayerY >= 86 && worldPlayerY <= 195;
		bool clickedOnCar = worldX >= 528 && worldX <= 686 && worldY >= 175 && worldY <= 220;

		//Toggle car inventory
		if (GetAsyncKeyState(VK_LBUTTON) && clickedOnCar && playerCloseToCar && frame_counter >= 15)
		{
			isopen = false;
			frame_counter = 0;
			carisopen = !carisopen;
			frame = 2;
			inventory.SetFrame(frame);
		}

		//Click car inventory
		if (carisopen)
		{
			if (GetAsyncKeyState(VK_LBUTTON) && clickedOnInvButton)
				ManageFrames(2, 3);

			if (!playerCloseToCar || clickedOutsideInv || GetAsyncKeyState('E'))
				carisopen = false;
		}

	}
	void Inventory::SeedsInventory(Surface* screen, int mouseX, int mouseY, int worldX, int worldY, bool tileClicekd)
	{
		bool clickedOutsideInv = GetAsyncKeyState(VK_LBUTTON) && !(mouseX >= 207 && mouseX <= 579 && mouseY >= 78 && mouseY <= 519);
		bool clickedOnInvButton = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 390 && mouseX <= 421 && mouseY >= 470 && mouseY <= 508;
		bool moved = GetAsyncKeyState('W') || GetAsyncKeyState('A') || GetAsyncKeyState('S') || GetAsyncKeyState('D');

		//Toggle seed inventory
		if (GetAsyncKeyState(VK_LBUTTON) && frame_counter >= 15 && tileClicekd)
		{
			isopen = false;
			carisopen = false;
			frame_counter = 0;
			seedsisopen = !seedsisopen;
		}

		//Click seed inventory
		if (seedsisopen)
		{
			inventory.SetFrame(1);
			if (clickedOutsideInv || GetAsyncKeyState('E') || moved)
				seedsisopen = false;
		}

	}
	/*void Inventory::Update(Surface* screen, int mouseX, int mouseY, int worldX, int worldY, int worldPlayerX, int worldPlayerY)
	{
		frame_counter++;//to limit key press speed

		bool clickedOutsideInv = GetAsyncKeyState(VK_LBUTTON) && !(mouseX >= 207 && mouseX <= 579 && mouseY >= 78 && mouseY <= 519);
		bool clickedOnInvButton = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 390 && mouseX <= 421 && mouseY >= 470 && mouseY <= 508;
		bool playerCloseToCar = worldPlayerX >= 448 && worldPlayerX <= 688 && worldPlayerY >= 86 && worldPlayerY <= 195;
		bool clickedOnCar = worldX >= 528 && worldX <= 686 && worldY >= 175 && worldY <= 220;

		//Toggle normal inventory
		if (GetAsyncKeyState('E') && frame_counter >= 15)
		{
			carisopen = false;
			frame_counter = 0;
			isopen = !isopen;
			frame = 0;
			inventory.SetFrame(frame);
		}

		//Click inventory
		if (isopen)
		{
			if (GetAsyncKeyState(VK_LBUTTON) && clickedOnInvButton)
				ManageFrames(0, 1);
			if (clickedOutsideInv)
				isopen = false;
		}

		//Toggle car inventory
		if (GetAsyncKeyState(VK_LBUTTON) && clickedOnCar && playerCloseToCar && frame_counter >= 15)
		{
			isopen = false;
			frame_counter = 0;
			carisopen = !carisopen;
			frame = 2;
			inventory.SetFrame(frame);
		}

		//Click car inventory
		if (carisopen)
		{
			if (GetAsyncKeyState(VK_LBUTTON) && clickedOnInvButton)
				ManageFrames(2, 3);

			if (!playerCloseToCar || clickedOutsideInv || GetAsyncKeyState('E'))
				carisopen = false;
		}
	}*/
	void Inventory::DrawOnScreen(Surface* screen)
	{
		frame_counter++;//to limit key press speed
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