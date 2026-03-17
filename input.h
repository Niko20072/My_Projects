#pragma once

#include <SDL_scancode.h>
#include <SDL_mouse.h>

namespace Input
{
    bool GetKey(SDL_Scancode key); // returns true if the key is currently held down
    bool GetKeyPressed(SDL_Scancode key);// returns true if the key was pressed since the last Tick
    bool GetKeyReleased(SDL_Scancode key);// returns true if the key was released since the last Tick
    bool GetMouseButton(int button); // returns true if the mouse button is currently held down
    bool GetMouseButtonPressed(int button); // returns true if the mouse button was pressed since the last Tick
    bool GetMouseButtonReleased(int button); // returns true if the mouse button was released since the last Tick
    float GetMouseX(); // returns the current x coordinate of the mouse
    float GetMouseY(); // returns the current y coordinate of the mouse
	void onMouseMove(int x, int y); // call this function when the mouse moves to update the mouse coordinates
    void onKeyDown(SDL_Scancode key);
    void onKeyUp(SDL_Scancode key);
    void onMouseButtonDown(int button);
    void onMouseButtonUp(int button);
	void SetMouseCoordinates(float x, float y);
    void Update();
};
