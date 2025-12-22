#include "buttons.h"

namespace Tmpl8
{
	namespace Buttons
	{
		float inputKeyCooldown = 0.0f;
		float inputLeftClickCooldown = 0.0f;
		float deltaTime;

		void SetDeltaTime(float dt) 
		{
			deltaTime = dt; 
			inputKeyCooldown -= deltaTime;//to limit key press speed
			if (inputKeyCooldown <= 0.0f)
				inputKeyCooldown = 0.0f;

			inputLeftClickCooldown -= deltaTime;//to limit key press speed
			if (inputLeftClickCooldown <= 0.0f)
				inputLeftClickCooldown = 0.0f;
		}

		bool Key(char key)
		{
			if (GetAsyncKeyState(key) && inputKeyCooldown <= 0.0f)
			{
				inputKeyCooldown = 0.2f; // 200 ms
				return true;
			}
			return false;
		}
		bool LeftClick()
		{
			if (GetAsyncKeyState(VK_LBUTTON) && inputLeftClickCooldown <= 0.0f)
			{
				inputLeftClickCooldown = 0.2f; // 200 ms
				return true;
			}
			return false;
		}
	}
};
