#include "player.h"
#include "input.h"
#include "worldState.h"
#include "map.h"

namespace Tmpl8
{
	void Player::HandleMovement(float deltaTime)
	{
		// -----------------------------------------------------------
		// Movement and collision
		// -----------------------------------------------------------

		// New camera position
		float newCameraX = WorldState::cameraX;
		float newCameraY = WorldState::cameraY;

		// Move camera based on WASD keys
		vec2 movedir = 0.0f;

		if (Input::GetKey(SDL_SCANCODE_A))
		{
			player1.SetFrame(0);
			movedir.x = -1;
		}
		if (Input::GetKey(SDL_SCANCODE_D))
		{
			player1.SetFrame(1);
			movedir.x = 1;
		}
		if (Input::GetKey(SDL_SCANCODE_W))
		{
			player1.SetFrame(3);
			movedir.y = -1;
		}
		if (Input::GetKey(SDL_SCANCODE_S))
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
		if (map.CheckCollision(newCameraX + WorldState::playerX, newCameraY + WorldState::playerY, newCameraX + WorldState::playerX + 48, newCameraY + WorldState::playerY + 94) == true)
		{
			WorldState::cameraX = newCameraX;
			WorldState::cameraY = newCameraY;
		}
	}
	void Player::Draw(Surface* screen)
	{
		// Player reach box
		//screen->Box(WorldState::reachX1 - WorldState::cameraX, WorldState::reachY1 - WorldState::cameraY, WorldState::reachX2 - WorldState::cameraX, WorldState::reachY2 - WorldState::cameraY, 0x00ff00);
		screen->Box(WorldState::playerColisionX1 - WorldState::cameraX, WorldState::playerColisionY1 - WorldState::cameraY, WorldState::playerColisionX2 - WorldState::cameraX, WorldState::playerColisionY2 - WorldState::cameraY, 0xff0000);
		player1.Draw(screen, WorldState::playerX, WorldState::playerY);
	}
}
