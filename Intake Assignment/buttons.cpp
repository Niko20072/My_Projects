#include "buttons.h"

namespace Tmpl8
{
	namespace Buttons
	{
		bool qPressed;
		bool ePressed;
		bool rPressed;
		bool leftPressed;

		//pressed-once edge detection
		bool KeyR()
		{
			static bool wasDown = false;
			bool isDown = GetAsyncKeyState('R');
			bool pressed = isDown && !wasDown;
			wasDown = isDown;
			return pressed;
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
			bool isDown = GetAsyncKeyState(VK_LBUTTON) && WorldState::mouseX >= 0 && WorldState::mouseX <= 800 && WorldState::mouseY >= 0 && WorldState::mouseY <= 600;
			bool pressed = isDown && !wasDown;
			wasDown = isDown;
			return pressed;
		}
		void CheckClick()
		{
			qPressed = Buttons::KeyQ();
			ePressed = Buttons::KeyE();
			rPressed = Buttons::KeyR();
			leftPressed = Buttons::LeftClick();
		}
	}
};
