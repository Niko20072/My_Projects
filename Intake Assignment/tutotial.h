#pragma once
#include <string>
#include "surface.h"
namespace Tmpl8
{
	class Inventory;
	class Car;
	class House;
	class WateringCan;
	class Player;

	class Tutorial
	{
	public:
		Tutorial(Player& pl, Car& c, House& h);
		void Update();
		void Draw(Surface* screen);
		void setPlanted(bool state) { planted = state; }
		enum class TutorialState
		{
			Move,
			OpenInventory,
			InteractInventory,
			ExitInventory,
			GoToCar,
			BuySeeds,
			CheckOrders,
			HowOrdersWork,
			ClickFarmTile,
			PlantSeed,
			WaterSeed,
			ClickHouse,
			InteractTable,
			ExplainTable,
			ExitTable,
			ClickNightstand,
			ExplainNightstand,
			ClickBed,
			ExplainBed,
			HaveFun,
			Done
		};
	private:
		TutorialState tutorialState = TutorialState::Move;
		char tutorialText[256] = "";
		char tutorialText2[256] = "";
		int box[4] = { 0,0,0,0 }; //xyxy
		bool planted = false;
		Player& player; // Reference to player
		Inventory& inventory; // Reference to Inventory
		Car& car; // Reference to Car
		House& house; // Reference to House
		WateringCan& wateringCan; // Reference to Watering Can from Inventory
	};
}