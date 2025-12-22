#pragma once
#include "surface.h"
#include <windows.h>
namespace Tmpl8
{
	namespace Buttons
	{
		extern float inputKeyCooldown;
		extern float inputLeftClickCooldown;
		extern float deltaTime;
		void SetDeltaTime(float dt);
		bool Key(char key);
		bool LeftClick();
	}
};