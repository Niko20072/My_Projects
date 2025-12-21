#pragma once
#include "surface.h"
#include "template.h"
#include <windows.h>
#include <cstdio> //printf

namespace Tmpl8
{
	class Inventory
	{
	public:
		int x, y;
		int frame = 0;
		float inputCooldown = 0.0f;
		bool isopen = false;
		bool carisopen = false;
		bool seedsisopen = false;

		static int contSunblossom;
		static int contMoonleaf;
		static int contEmberroot;
		static int contFrostmint;
		static int contBerry;

		static int contVitalTonic;
		static int contCalmMind;
		static int contDreamDraught;
		static int contFireHeart;
		static int contFrostveil;

		static int contSeedSunblossom;
		static int contSeedMoonleaf;
		static int contSeedEmberroot;
		static int contSeedFrostmint;
		static int contSeedBerry;

		Sprite inventory = Sprite(new Surface("assets/Inventory.png"), 6);
		Inventory(int x, int y);
		void Draw(Surface* screen, int x, int y);
		void SetFrame(int frame);
		void DrawInventory(Surface* screen);
		void NormalInventory(Surface* screen, int mouseX, int mouseY);
		void CarInventory(Surface* screen, int mouseX, int mouseY, float worldX, float worldY, float reachX1, float reachY1, float reachX2, float reachY2);
		void SeedsInventory(Surface* screen, int mouseX, int mouseY, float worldX, float worldY, bool tileClicekd);
		//void Update(Surface* screen, int mouseX, int mouseY, int worldX, int worldY, int worldPlayerX, int worldPlayerY);
		void DrawOnScreen(Surface* screen, float deltaTime);
		bool InventorysClosed();
	};
};