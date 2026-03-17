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
		Player(Map &m, Camera &c) : map(m), camera(c), wateringCan(), inventory(wateringCan) {};
		Inventory& pInventory() { return inventory; }
		WateringCan& pWateringCan() { return wateringCan; }
		void Update();
		void HandleMovement(float deltaTime);
		void Draw(Surface* screen);
		float getReachX1();
		float getReachY1();
		float getReachX2();
		float getReachY2();

	private:
		Map &map; // reference to game map
		Camera& camera; // reference to game camera
		WateringCan wateringCan;
		Inventory inventory; // depends on wateringCan
		Sprite player1 = Sprite(new Surface("assets/Vera.png"), 4);
		const int playerX = 648 / 2 + 48, playerY = 512 / 2 + 22; //player position
		float playerColisionX1 = 0, playerColisionY1 = 0, playerColisionX2 = 0, playerColisionY2 = 0; //player collision box (rectangle around player)
		//player position in world coordinates
		float worldPlayerX;
		float worldPlayerY;
		//player reach area (rectangle around player)
		float reachX1;
		float reachY1;
		float reachX2;
		float reachY2;

	};
}