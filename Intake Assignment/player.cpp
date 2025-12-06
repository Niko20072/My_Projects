/*
#include "player.h"


namespace Tmpl8
{
	Player::Player()
	{
		playerX = 648 / 2 + 50;
		playerY = 512 / 2 + 50;
	}
	bool Player::CheckCollision(int x, int y, Map&map)
	{
		//sprit corners
		int left = x;
		int top = y;
		int right = left + 50;
		int bottom = top + 50;

		//check all corners for collision
		if (map.IsBlocked(left, top)) return false;
		if (map.IsBlocked(right, top)) return false;
		if (map.IsBlocked(left, bottom)) return false;
		if (map.IsBlocked(right, bottom)) return false;

		return true; //no collision
	}
	void Player::Move(Surface*screen, Map& map)
	{
		int newCameraX = Map::cameraX;
		int newCameraY = Map::cameraY;

		if (GetAsyncKeyState('A')) newCameraX -= 5;
		if (GetAsyncKeyState('D')) newCameraX += 5;
		if (GetAsyncKeyState('W')) newCameraY -= 5;
		if (GetAsyncKeyState('S')) newCameraY += 5;
		if (CheckCollision(newCameraX + playerX, newCameraY + playerY, map) == true)
			Map::cameraX = newCameraX, Map::cameraY = newCameraY;
	}
};*/