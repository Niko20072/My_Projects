#include "wateringCan.h"
namespace Tmpl8
{
	namespace WateringCan
	{
		bool wateringCan = false;
		void WateringCanState()
		{
			if (Buttons::rPressed)
			{
				wateringCan = !wateringCan;
				Buttons::rPressed = false; //reset rPressed to avoid multiple toggles
			}
		}
	}
}
