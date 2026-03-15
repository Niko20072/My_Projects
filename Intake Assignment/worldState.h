#pragma once
namespace Tmpl8
{
	namespace WorldState
	{
		constexpr int playerX = 648 / 2 + 48, playerY = 512 / 2 + 22; //player position
		constexpr float cameraSpeed = 360.0f;
		extern float mouseX, mouseY;
		extern float playerColisionX1, playerColisionY1, playerColisionX2, playerColisionY2; //player collision box (rectangle around player)

		// Transform screen coordinates -> world coordinates -> mouse screen position
		extern float mouseWorldX;
		extern float mouseWorldY;
		//std::cout << "World X: " << worldX << ", Y: " << worldY << std::endl;

		extern float cameraX;
		extern float cameraY;

		// Player world position
		extern float worldPlayerX;
		extern float worldPlayerY ;
		//std::cout << "Player world position: X=" << worldPlayerX << ", Y=" << worldPlayerY << std::endl;

		// Player reach area
		extern float reachX1;
		extern float reachY1;
		extern float reachX2;
		extern float reachY2;

		extern const int mapTileSize; //remove

		void UpdateWorldState();
	}
}