#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include "template.h"
#include "map.h"
#include <windows.h>

namespace Tmpl8
{
	

	static Sprite player(new Surface("assets/ball.png"), 1);
	
	int playerX = 200, playerY = 200; //player position

	Map gameMap;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);

		gameMap.DrawMap(screen);
		player.Draw(screen, playerX, playerY);

		int newCameraX = Map::cameraX;
		int newCameraY = Map::cameraY;

		if (GetAsyncKeyState('A')) newCameraX -= 4;
		if (GetAsyncKeyState('D')) newCameraX += 4;
		if (GetAsyncKeyState('W')) newCameraY -= 4;
		if (GetAsyncKeyState('S')) newCameraY += 4;
		Map::cameraX = newCameraX, Map::cameraY = newCameraY;
		Sleep(16); //simulate ~60fps
	}
};