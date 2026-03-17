#include "buttons.h"

namespace Tmpl8
{
	namespace Buttons
	{
        bool qPressed = false;
        bool ePressed = false;
        bool rPressed = false;
        bool leftPressed = false;

        static bool qWasDown = false;
        static bool eWasDown = false;
        static bool rWasDown = false;
        static bool mouseWasDown = false;

        void Update()
        {
            // Q
            bool qIsDown = (GetAsyncKeyState('Q') & 0x8000) != 0;
            qPressed = qIsDown && !qWasDown;
            qWasDown = qIsDown;

            // E
            bool eIsDown = (GetAsyncKeyState('E') & 0x8000) != 0;
            ePressed = eIsDown && !eWasDown;
            eWasDown = eIsDown;

            // R
            bool rIsDown = (GetAsyncKeyState('R') & 0x8000) != 0;
            rPressed = rIsDown && !rWasDown;
            rWasDown = rIsDown;

            // Left click
            bool mouseIsDown = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
            leftPressed = mouseIsDown && !mouseWasDown;
            mouseWasDown = mouseIsDown;
        }
	}
};
