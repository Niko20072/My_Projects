#pragma once
#include "surface.h"
#include "template.h"
#include <windows.h>
namespace Tmpl8
{
	class Inventory
	{
	public:
		int x, y;
		int frame = 0;
		bool isopen = false;
		bool carisopen = false;
		bool seedsisopen = false;
		int frame_counter = 0;
		Sprite inventory = Sprite(new Surface("assets/Inventory.png"), 6);
		Inventory(int x, int y);
		void Draw(Surface* screen, int x, int y);
		void SetFrame(int frame);
		void  DrawInventory(Surface* screen);
		void NormalInventory(Surface* screen, int mouseX, int mouseY);
		void CarInventory(Surface* screen, int mouseX, int mouseY, int worldX, int worldY, int reachX1, int reachY1, int reachX2, int reachY2);
		void SeedsInventory(Surface* screen, int mouseX, int mouseY, int worldX, int worldY, bool tileClicekd);
		//void Update(Surface* screen, int mouseX, int mouseY, int worldX, int worldY, int worldPlayerX, int worldPlayerY);
		void DrawOnScreen(Surface* screen);
		bool InventorysClosed();
	};
};