#pragma once
#include "map.h"
namespace Tmpl8
{
	namespace WorldState
	{
		extern const int playerX, playerY; //player position
		extern const float cameraSpeed;
		extern float mouseX, mouseY;

		// Transform screen coordinates -> world coordinates -> mouse screen position
		extern float worldX;
		extern float worldY;
		//std::cout << "World X: " << worldX << ", Y: " << worldY << std::endl;

		// Player world position
		extern float worldPlayerX;
		extern float worldPlayerY ;
		//std::cout << "Player world position: X=" << worldPlayerX << ", Y=" << worldPlayerY << std::endl;

		// Player reach area
		extern float reachX1;
		extern float reachY1;
		extern float reachX2;
		extern float reachY2;

		void UpdateWorldState();
	}
}