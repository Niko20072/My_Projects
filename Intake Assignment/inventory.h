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
		static bool isopen;
		static bool carisopen;
		static bool seedsisopen;
		static int frame_counter;
		Sprite inventory = Sprite(new Surface("assets/inv5.png"), 4);
		Inventory(int x, int y);
		void Draw(Surface* screen, int x, int y);
		void SetFrame(int frame);
		void  DrawInventory(Surface* screen);
		void ManageFrames(int fr1, int fr2);
		void NormalInventory(Surface* screen, int mouseX, int mouseY, int worldX, int worldY, int worldPlayerX, int worldPlayerY);
		void CarInventory(Surface* screen, int mouseX, int mouseY, int worldX, int worldY, int worldPlayerX, int worldPlayerY);
		void SeedsInventory(Surface* screen, int mouseX, int mouseY, int worldX, int worldY, bool tileClicekd);
		//void Update(Surface* screen, int mouseX, int mouseY, int worldX, int worldY, int worldPlayerX, int worldPlayerY);
		void DrawOnScreen(Surface* screen);
		bool InventorysClosed();
	};
};