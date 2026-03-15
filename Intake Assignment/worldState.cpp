#include "worldState.h"
#include "map.h"
namespace Tmpl8
{
	namespace WorldState
	{
		
		float worldPlayerX, worldPlayerY; //player position in world coordinates
		float reachX1, reachY1, reachX2, reachY2; //player reach area (rectangle around player)
		float cameraX = 10.0f, cameraY = 50.0f; //world coordinates (map offset)
		
		float mouseX = 0, mouseY = 0; //mouse position on screen
		float mouseWorldX, mouseWorldY; //mouse position in world coordinates
		const int mapTileSize = Map::TileSize;
		void UpdateWorldState()
		{
			// Transform screen coordinates -> world coordinates -> mouse screen position
			mouseWorldX = cameraX + mouseX;
			mouseWorldY = cameraY + mouseY;
			//std::cout << "World X: " << worldX << ", Y: " << worldY << std::endl;

			// Player world position
			worldPlayerX = cameraX + playerX;
			worldPlayerY = cameraY + playerY;
			//std::cout << "Player world position: X=" << worldPlayerX << ", Y=" << worldPlayerY << std::endl;

			// Player reach area
			reachX1 = worldPlayerX - 50.0f;
			reachY1 = worldPlayerY - 25.0f;
			reachX2 = worldPlayerX + 46.0f + 50.0f;
			reachY2 = worldPlayerY + 94.0f + 25.0f;
		}
	}
}