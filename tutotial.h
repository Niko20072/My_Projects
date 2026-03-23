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
		//---Setters---
		void setPlanted(bool state) { planted = state; }
		//--Main functions---
		void Update(); // Update state
		void Draw(Surface* screen); // Draw tutorial text
	private:
		Player& player; // Reference to player
		Inventory& inventory; // Reference to Inventory
		Car& car; // Reference to Car
		House& house; // Reference to House
		WateringCan& wateringCan; // Reference to Watering can from Inventory
		TutorialState tutorialState = TutorialState::Move;
		char tutorialText[256] = "";
		char tutorialText2[256] = "";
		int box[4] = { 0,0,0,0 }; //Tutorial text black background (xyxy)
		bool planted = false;
	};
}