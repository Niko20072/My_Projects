#include "player.h"
#include "input.h"
#include "map.h"
#include "camera.h"
#include <iostream>

namespace Tmpl8
{
	Player::Player(Map& m, Camera& c) : map(m), camera(c), inventory(wateringCan) {}
	Inventory& Player::pInventory() 
	{ 
		return inventory; 
	}
	WateringCan& Player::pWateringCan() 
	{ 
		return wateringCan; 
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

	void Player::HandleMovement(float deltaTime)//make 1 function
	{
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
		if (movedir.sqrLentgh() > 0) // Check if the movement direction vector is not (0,0)
		{
			movedir.normalize(); // Normalize the vector so diagonal movement is not faster than horizontal/vertical
			newCameraX += movedir.x * camera.getCameraSpeed() * deltaTime;
			newCameraY += movedir.y * camera.getCameraSpeed() * deltaTime;
		}

		// Check for collision before updating camera position
		if (map.CheckCollision(newCameraX + playerX, newCameraY + playerY + pHeight / 2, newCameraX + playerX + pWidth, newCameraY + playerY + pHeight))
		{
			camera.setCameraX(newCameraX);
			camera.setCameraY(newCameraY);
		}
		//std::cout << "Camera position: X=" << camera.getCameraX() << ", Y=" << camera.getCameraY() << std::endl;

		// Player world position
		worldPlayerX = camera.getCameraX() + playerX;
		worldPlayerY = camera.getCameraY() + playerY;
		//std::cout << "Player world position: X=" << worldPlayerX << ", Y=" << worldPlayerY << std::endl;

		// Player reach area
		reachX1 = worldPlayerX - 50.0f;
		reachY1 = worldPlayerY - 25.0f;
		reachX2 = worldPlayerX + pWidth + 50.0f;
		reachY2 = worldPlayerY + pHeight + 25.0f;
	}
	void Player::Draw(Surface* screen)
	{
		// Player reach box
		//screen->Box(static_cast<int>(playerX - 50.0f), static_cast<int>(playerY - 25.0f), static_cast<int>(playerX + pWidth + 50.0f), static_cast<int>(playerY + pHeight + 25.0f), 0x00ff00);
		// Player bounding box
		//screen->Box(static_cast<int>(playerX), static_cast<int>(playerY + pHeight / 2), static_cast<int>(playerX + pWidth), static_cast<int>(playerY + pHeight), 0xff0000);
		player1.Draw(screen, playerX, playerY);
	}
}
