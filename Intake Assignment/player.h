#pragma once
#include "surface.h"
#include "map.h"
#include <windows.h>
#include "template.h"
#include "inventory.h"
#include "wateringCan.h"
#include "worldState.h"

namespace Tmpl8
{
	class Player
	{
	public:
		Player() : wateringCan(), inventory(wateringCan) {};
		Inventory& pInventory() { return inventory; }
		WateringCan& pWateringCan() { return wateringCan; }
		bool CheckCollision(float x, float y);
		void HandleMovement(float deltaTime);
		void Draw(Surface* screen);
	private:
		WateringCan wateringCan;
		Inventory inventory; // depends on wateringCan
		Sprite player1 = Sprite(new Surface("assets/Vera.png"), 4);
	};
}