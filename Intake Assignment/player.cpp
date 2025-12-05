/*
#include "player.h"

namespace Tmpl8
{
	int playerX, playerY;
	Player::Player(int playerX,int playerY)
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
};*/