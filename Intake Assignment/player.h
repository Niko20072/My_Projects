/*
#pragma once
#include "surface.h"
#include "map.h"
#include <windows.h>
#include "template.h"

namespace Tmpl8
{
	class Player
	{
	public:
		Sprite player = Sprite(new Surface("assets/ball.png"), 1);
		static int playerX , playerY ; //player position
		Player();
		bool CheckCollision(int x, int y, Map& map);
		void Move(Surface* screen, Map& map);
	};
	
};*/