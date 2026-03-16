#pragma once
#include "orders.h"
#include "surface.h"	

namespace Tmpl8
{
	class Inventory;
	class Player;
	class Car
	{
	public:
		Car(Inventory& inv, Player& plyr) : inventory(inv), player(plyr) {};
		int CarInvIsOpen();
		int getFrame();
		bool CheckIfAnySeedButtonPressed();
		void UpdateOrderDays();
		void CarInventoryLogic(int& coinCounter, float mouseWorldX, float mouseWorldY);
		void BuySeeds(int& coinCounter); // Buying seeds logic
		void Draw(Surface* screen);
		void MakeNewOrders();
		void UpdateOrders(int& coinCounter);
		void DrawOrders(Surface* screen);
	private:
		Inventory& inventory;
		Player& player;
		bool carisopen = false; // Car inventory open state
		int frame = 4;
		int daysUntilOrderReset = 0;
		Sprite carinventory = Sprite(new Surface("assets/inv.png"), 6);
		std::vector<Order> orders;
		// Buying seeds buttons
		bool button1 = false, button2 = false, button3 = false, button4 = false, button5 = false;
		void DrawCarText(Surface* screen);
	};
}
