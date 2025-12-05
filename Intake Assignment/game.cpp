#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include "template.h"
#include "map.h"
#include <windows.h>

namespace Tmpl8
{
	

	static Sprite player(new Surface("assets/ball.png"), 1);
	
	int playerX = 648/2+50, playerY = 512/2+50; //player position

	Map gameMap;

	bool CheckCollision(int x, int y)
	{
		//sprit corners
		int left = x;
		int top = y;
		int right = left + 50;
		int bottom = top + 50;

		//check all corners for collision
		if (gameMap.IsBlocked(left, top)) return false;      
		if (gameMap.IsBlocked(right, top)) return false;     
		if (gameMap.IsBlocked(left, bottom)) return false;   
		if (gameMap.IsBlocked(right, bottom)) return false;  

		return true; //no collision
	}
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

		if (GetAsyncKeyState('A')) newCameraX -= 5;
		if (GetAsyncKeyState('D')) newCameraX += 5;
		if (GetAsyncKeyState('W')) newCameraY -= 5;
		if (GetAsyncKeyState('S')) newCameraY += 5;
		if(CheckCollision(newCameraX+playerX, newCameraY+playerY) == true)
		Map::cameraX = newCameraX, Map::cameraY = newCameraY;
		Sleep(16); //simulate ~60fps
	}
};