#pragma once
#include "inventory.h"
#include "orders.h"

namespace Tmpl8
{
	class Car
	{
	public:
		Car(Inventory& inv) : inventory(inv) {};
		int getCarState();
		int getFrame();
		void RemoveDays()
		{
			daysUntilOrderReset--;
		}
		void CarInventory(int& coinCounter);
		void BuySeeds(int& coinCounter); // Buying seeds logic
		void Draw(Surface* screen);
		void MakeNewOrders();
		void UpdateOrders(int& coinCounter);
		void DrawOrders(Surface* screen);
	private:
		Inventory& inventory;
		bool carisopen = false; // Car inventory open state
		int frame = 4;
		int daysUntilOrderReset = 0;
		Sprite carinventory = Sprite(new Surface("assets/inventory.png"), 6);
		std::vector<Order> orders;
	};
}
