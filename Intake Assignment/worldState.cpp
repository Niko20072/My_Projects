#include "worldState.h"
namespace Tmpl8
{
	namespace WorldState
	{
		const int playerX = 648 / 2 + 46, playerY = 512 / 2 + 22; //player position
		float mouseX = 0, mouseY = 0;
		float worldX, worldY, worldPlayerX, worldPlayerY, reachX1, reachY1, reachX2, reachY2;
		void UpdateWorldState()
		{
			// Transform screen coordinates -> world coordinates -> mouse screen position
			worldX = Map::cameraX + mouseX;
			worldY = Map::cameraY + mouseY;
			//std::cout << "World X: " << worldX << ", Y: " << worldY << std::endl;

			// Player world position
			worldPlayerX = Map::cameraX + playerX;
			worldPlayerY = Map::cameraY + playerY;
			//std::cout << "Player world position: X=" << worldPlayerX << ", Y=" << worldPlayerY << std::endl;

			// Player reach area
			reachX1 = worldPlayerX - 50.0f;
			reachY1 = worldPlayerY - 25.0f;
			reachX2 = worldPlayerX + 46.0f + 50.0f;
			reachY2 = worldPlayerY + 94.0f + 25.0f;
		}
	}
}