#include "wateringCan.h"
namespace Tmpl8
{
	namespace WateringCan
	{
		bool wateringCan = false;
		void Water(bool& rPressed)
		{
			if (rPressed)
			{
				wateringCan = !wateringCan;
				rPressed = false; //reset rPressed to avoid multiple toggles
			}
		}
	}
}
