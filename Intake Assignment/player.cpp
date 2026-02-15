#include "player.h"

namespace Tmpl8
{
	bool Player::CheckCollision(float x, float y)
	{
		//sprit corners
		int left = x;
		int top = y;
		int right = left + 46;
		int bottom = top + 22;

		/*
		//check all corners for collision
		if (gameMap.IsBlocked(left, top)) return false;
		if (gameMap.IsBlocked(right, top)) return false;
		if (gameMap.IsBlocked(left, bottom)) return false;
		if (gameMap.IsBlocked(right, bottom)) return false;*/

		return true; //no collision
	}
	void Player::HandleMovement(float deltaTime)
	{
		// -----------------------------------------------------------
		// Movement and collision
		// -----------------------------------------------------------

		// New camera position
		float newCameraX = Map::cameraX;
		float newCameraY = Map::cameraY;

		// Move camera based on WASD keys
		vec2 movedir = 0.0f;

		if (GetAsyncKeyState('A'))
		{
			player1.SetFrame(0);
			movedir.x = -1;
		}
		if (GetAsyncKeyState('D'))
		{
			player1.SetFrame(1);
			movedir.x = 1;
		}
		if (GetAsyncKeyState('W'))
		{
			player1.SetFrame(3);
			movedir.y = -1;
		}
		if (GetAsyncKeyState('S'))
		{
			player1.SetFrame(2);
			movedir.y = 1;
		}
		if (movedir.sqrLentgh() > 0)
		{
			movedir.normalize();
			newCameraX += movedir.x * WorldState::cameraSpeed * deltaTime;
			newCameraY += movedir.y * WorldState::cameraSpeed * deltaTime;
		}

		// Check for collision before updating camera position
		if (CheckCollision(newCameraX + WorldState::playerX, newCameraY + WorldState::playerY) == true)
		{
			Map::cameraX = newCameraX;
			Map::cameraY = newCameraY;
		}
	}
	void Player::Draw(Surface* screen)
	{
		// Player reach box
		screen->Box(WorldState::reachX1 - Map::cameraX, WorldState::reachY1 - Map::cameraY, WorldState::reachX2 - Map::cameraX, WorldState::reachY2 - Map::cameraY, 0x00ff00);
		// Player sprite
		player1.Draw(screen, WorldState::playerX, WorldState::playerY);
	}
}
