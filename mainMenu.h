#pragma once
#include "surface.h"

namespace Tmpl8
{
	class MainMenu
	{
	public:
		void Logic(bool &gameStarted); // Menu logic
		void CutSceneLogic(bool& cutScenePlayed); // Cutscene logic
		void Draw(Surface* screen); // Draw menu
		void DrawCutScene(Surface* screen); // Draw cutscene
	private:
		Sprite main = Sprite(new Surface("assets/image/mainMenu.png"),3);
		Sprite cutScene = Sprite(new Surface("assets/image/startgame.png"), 16);
		int frame = 0;
		int cutSceneFrame = 0;
		void ManageFrames();// Handle input to advance cutscene frames
	};
}