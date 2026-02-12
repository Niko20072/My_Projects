#include "wateringCan.h"
namespace Tmpl8
{
	void WateringCan::WateringCanState()
		{
			if (Buttons::rPressed)
			{
				wateringCan = !wateringCan;
				Buttons::rPressed = false; //reset rPressed to avoid multiple toggles
			}
		}
}
