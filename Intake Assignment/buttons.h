#pragma once
#include <windows.h>
#include "worldState.h"
namespace Tmpl8
{
	namespace Buttons
	{
		extern bool qPressed;
		extern bool ePressed;
		extern bool rPressed;
		extern bool leftPressed;
		bool KeyR();
		bool KeyQ();
		bool KeyE();
		bool LeftClick();
		void CheckClick();
	}
};