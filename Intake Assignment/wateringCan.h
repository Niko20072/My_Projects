#pragma once
#include "buttons.h"
namespace Tmpl8
{
	class WateringCan
	{
	public:
		int getState() { return wateringCanState; }
		void setState(bool state) { wateringCanState = state; }
		void WateringCanState();
		void Draw(Surface* screen);
	private:
		bool wateringCanState = false;
		Sprite wateringCan = Sprite(new Surface("assets/Wateringcan.png"), 2);
	};
}