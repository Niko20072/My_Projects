#include "input.h"
#include <bitset>
#include <iostream>
namespace //internal 
{
    std::bitset<SDL_NUM_SCANCODES> keys; // store key states here
    std::bitset<SDL_NUM_SCANCODES> held; // store key states from the previous tick here
    std::bitset<SDL_NUM_SCANCODES> pressed; // store key press events here (set to true on key down, reset to false after processing in Tick)
    std::bitset<SDL_NUM_SCANCODES> released; // store key release events here (set to true on key up, reset to false after processing in Tick)
	std::bitset<5> mouseKeys; // store mouse button states here (0: left, 1: middle, 2: right, 3: X1, 4: X2)
	std::bitset<5> mouseHeld; // store previous mouse button states here for detecting presses/releases
	std::bitset<5> mousePressed; // store previous mouse button states here for detecting presses/releases
	std::bitset<5> mouseReleased; // store previous mouse button states here for detecting presses/releases
    void SetKeyState(SDL_Scancode key, bool isDown)
    {
        keys.set(key, isDown);
    }
	float mouseX = 0.0f, mouseY = 0.0f; // store current mouse coordinates
}

namespace Input
{
    bool GetKey(SDL_Scancode key) { return held.test(key); } // returns true if the key is currently held down
    bool GetKeyPressed(SDL_Scancode key) { return pressed.test(key); } // returns true if the key was pressed since the last Tick
    bool GetKeyReleased(SDL_Scancode key) { return released.test(key); } // returns true if the key was released since the last Tick
	bool GetMouseButton(int button) { return mouseHeld.test(button - 1); } // returns true if the mouse button is currently held down
    bool GetMouseButtonPressed(int button) { return mousePressed.test(button - 1); } // returns true if the mouse button was pressed since the last Tick
    bool GetMouseButtonReleased(int button) { return mouseReleased.test(button - 1);  } // returns true if the mouse button was released since the last Tick
    float GetMouseX() { return mouseX; } // returns the current x coordinate of the mouse
    float GetMouseY() { return mouseY; } // returns the current y coordinate of the mouse
    void onMouseMove(int x, int y)
    {
        mouseX = static_cast<float>(x);
        mouseY = static_cast<float>(y);
		//std::cout << mouseX << " " << mouseY << std::endl;
	}
    void onKeyDown(SDL_Scancode key)
    {
        SetKeyState(key, true);
	}
    void onKeyUp(SDL_Scancode key)
    {
        SetKeyState(key, false);
    }
    void onMouseButtonDown(int button)
    {
        mouseKeys.set(button - 1, true);
	}
    void onMouseButtonUp(int button)
    {
        mouseKeys.set(button - 1, false);
	}
    void SetMouseCoordinates(float x, float y)
    {
        mouseX = x;
        mouseY = y;
	}
    void Update()
    {
        // Update key states
        pressed = keys & ~held; // keys that are currently down but were not down in the previous tick
        released = ~keys & held; // keys that were down in the previous tick but are not down now
        held = keys; // update prevKeys for the next tick
		// Update mouse button states
        mousePressed = mouseKeys & ~mouseHeld; // buttons that are currently down but were not down in the previous tick
        mouseReleased = ~mouseKeys & mouseHeld; // buttons that were down in the previous tick but are not down now
		mouseHeld = mouseKeys; // update prevMouseKeys for the next tick
    }
};