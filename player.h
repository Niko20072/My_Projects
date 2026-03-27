#pragma once
#include "surface.h"
#include "template.h"
#include "inventory.h"
#include "wateringCan.h"


namespace Tmpl8
{
	class Map;
	class Camera;

	class Player
	{
	public:
		Player(Map &m, Camera &c);
		//---Getters---
		Inventory& pInventory();
		WateringCan& pWateringCan();
		float getReachX1();
		float getReachY1();
		float getReachX2();
		float getReachY2();
		//--Main functions---
		void HandleMovement(float deltaTime); // Move the player (camera) and update coordinates
		void Draw(Surface* screen); // Draw player (+ range + bounding box)
	private:
		Map &map; // reference to game map
		Camera& camera; // reference to game camera
		WateringCan wateringCan;
		Inventory inventory; // depends on wateringCan
		Sprite player1 = Sprite(new Surface("assets/image/Vera.png"), 4);
		//player sprite size
		const int pHeight = player1.GetHeight();
		const int pWidth = player1.GetWidth();
		//player position
		const int playerX = (ScreenWidth - player1.GetWidth()) / 2;
		const int playerY = (ScreenHeight - player1.GetHeight()) / 2;
		//player position in world coordinates
		float worldPlayerX = 0.0f;
		float worldPlayerY = 0.0f;
		//player reach area (rectangle around player)
		float reachX1 = 0.0f;
		float reachY1 = 0.0f;
		float reachX2 = 0.0f;
		float reachY2 = 0.0f;
	};
}