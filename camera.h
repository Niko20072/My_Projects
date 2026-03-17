#pragma once

namespace Tmpl8
{
	class Camera
	{
	public:
		float getCameraSpeed();
		float getCameraX();
		float getCameraY();
		void setCameraX(float x) { cameraX = x; }
		void setCameraY(float y) { cameraY = y; }
	private:
		const float cameraSpeed = 360.0f;
		float cameraX = 10.0f, cameraY = 50.0f; //world coordinates (map offset)
	};
}