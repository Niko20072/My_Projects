#include "buttons.h"

namespace Tmpl8
{
	namespace Buttons
	{
		//pressed-once edge detection
		float mouseX, mouseY;
		void GetValues(float MouseX, float MouseY)//set
		{
			mouseX = MouseX;
			mouseY = MouseY;
		}
		bool KeyQ()
		{
			static bool wasDown = false;
			bool isDown = GetAsyncKeyState('Q');
			bool pressed = isDown && !wasDown;
			wasDown = isDown;
			return pressed;
		}
		bool KeyE()
		{
			static bool wasDown = false;
			bool isDown = GetAsyncKeyState('E');
			bool pressed = isDown && !wasDown;
			wasDown = isDown;
			return pressed;
		}
		bool LeftClick()
		{
			static bool wasDown = false;
			bool isDown = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 0 && mouseX <= 800 && mouseY >= 0 && mouseY <= 600;
			bool pressed = isDown && !wasDown;
			wasDown = isDown;
			return pressed;
		}
	}
};
