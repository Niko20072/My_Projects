#include "buttons.h"

namespace Tmpl8
{
	namespace Buttons
	{
		//pressed-once edge detection
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
			bool isDown = GetAsyncKeyState(VK_LBUTTON);
			bool pressed = isDown && !wasDown;
			wasDown = isDown;
			return pressed;
		}
	}
};
