#include "player.h"
#include "input.h"
#include "map.h"
#include "camera.h"

namespace Tmpl8
{
	void Player::Update()//make 1 function
	{
		// Player world position
		worldPlayerX = camera.getCameraX() + playerX;
		worldPlayerY = camera.getCameraY() + playerY;
		//std::cout << "Player world position: X=" << worldPlayerX << ", Y=" << worldPlayerY << std::endl;

		// Player reach area
		reachX1 = worldPlayerX - 50.0f;
		reachY1 = worldPlayerY - 25.0f;
		reachX2 = worldPlayerX + 46.0f + 50.0f;
		reachY2 = worldPlayerY + 94.0f + 25.0f;

		playerColisionX1 = worldPlayerX;
		playerColisionY1 = worldPlayerY;
		playerColisionX2 = worldPlayerX + 46.0f;
		playerColisionY2 = worldPlayerY + 94.0f;

		//handle movement here

		//std::cout << "Player world position: X=" << worldPlayerX << ", Y=" << worldPlayerY << std::endl;
	}
	void Player::HandleMovement(float deltaTime)//make 1 function
	{
		// -----------------------------------------------------------
		// Movement and collision
		// -----------------------------------------------------------

		// New camera position
		float newCameraX = camera.getCameraX();
		float newCameraY = camera.getCameraY();

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
			newCameraX += movedir.x * camera.getCameraSpeed() * deltaTime;
			newCameraY += movedir.y * camera.getCameraSpeed() * deltaTime;
		}

		// Check for collision before updating camera position
		if (map.CheckCollision(newCameraX + playerX, newCameraY + playerY, newCameraX + playerX + 48, newCameraY + playerY + 94) == true)
		{
			camera.setCameraX(newCameraX);
			camera.setCameraY(newCameraY);
		}
	}
	void Player::Draw(Surface* screen)
	{
		// Player reach box
		//screen->Box(WorldState::reachX1 - camera.getCameraX(), WorldState::reachY1 - camera.getCameraY(), WorldState::reachX2 - camera.getCameraX(), WorldState::reachY2 - camera.getCameraY(), 0x00ff00);
		screen->Box(static_cast<int>(playerColisionX1 - camera.getCameraX()), static_cast<int>(playerColisionY1 - camera.getCameraY()), static_cast<int>(playerColisionX2 - camera.getCameraX()), static_cast<int>(playerColisionY2 - camera.getCameraY()), 0xff0000);
		player1.Draw(screen, playerX, playerY);
	}
	float Player::getReachX1()
	{
		return reachX1;
	}
	float Player::getReachY1()
	{
		return reachY1;
	}
	float Player::getReachX2()
	{
		return reachX2;
	}
	float Player::getReachY2()
	{
		return reachY2;
	}

}
