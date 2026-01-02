#pragma once
#include "surface.h"
#include "template.h"
#include <windows.h>
#include <cstdio> //printf
#include <iostream>
#include "house.h"

namespace Tmpl8
{
	namespace Inventory
	{
		extern int x, y;
		extern int frame;
		extern bool isopen;
		extern bool carisopen;
		extern bool seedsisopen;

		extern int contSunblossom;
		extern int contMoonleaf;
		extern int contEmberroot;
		extern int contFrostmint;
		extern int contBerry;

		extern int contVitalTonic;
		extern int contCalmMind;
		extern int contDreamDraught;
		extern int contFireHeart;
		extern int contFrostveil;

		extern int contSeedSunblossom;
		extern int contSeedMoonleaf;
		extern int contSeedEmberroot;
		extern int contSeedFrostmint;
		extern int contSeedBerry;

		extern Sprite inventory;

		void Draw(Surface* screen, int x, int y);
		void SetFrame(int frame);
		void DrawInventory(Surface* screen);
		void BuySeeds(Surface* screen, bool leftPressed, int& coinCounter, int mouseX, int mouseY);
		void PlantSeeds(Surface* screen, bool leftPressed, int mouseX, int mouseY);
		void NormalInventory(Surface* screen, bool ePressed, int mouseX, int mouseY);
		void CarInventory(Surface* screen, bool ePressed, bool &leftPressed, int mouseX, int mouseY, float worldX, float worldY, float reachX1, float reachY1, float reachX2, float reachY2);
		void SeedsInventory(Surface* screen, bool ePressed, bool &leftPressed, int mouseX, int mouseY, float worldX, float worldY, bool tileClicekd);
		//void Update(Surface* screen, int mouseX, int mouseY, int worldX, int worldY, int worldPlayerX, int worldPlayerY);
		void DrawOnScreen(Surface* screen, float deltaTime);
		bool InventorysClosed();
	}
};