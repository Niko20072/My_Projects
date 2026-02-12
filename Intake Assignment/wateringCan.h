#pragma once
#include "buttons.h"
namespace Tmpl8
{
	class WateringCan
	{
	public:
		int getState() { return wateringCan; }
		void setState(bool state) { wateringCan = state; }
		void WateringCanState();
	private:
		bool wateringCan = false;
	};
}