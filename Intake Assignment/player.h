#pragma once
#include "surface.h"
#include "map.h"
#include <windows.h>
#include "template.h"
#include "inventory.h"

namespace Tmpl8
{
	class Player
	{
	public:
		Player() : wateringCan(), inventory(wateringCan) {};
		Inventory& playerInventory() { return inventory; }
		WateringCan& playerWateringCan() { return wateringCan; }
	private:
		WateringCan wateringCan;
		Inventory inventory; // depends on wateringCan
	};
}