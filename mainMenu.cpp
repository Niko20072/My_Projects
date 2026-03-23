#include "mainMenu.h"
#include "input.h"
#include "Windows.h"
namespace Tmpl8
{
	void MainMenu::Draw(Surface* screen)
	{
		main.Draw(screen, 0, 0);
	}
	void MainMenu::ManageFrames()
	{
		// Advance to the next frame of the cutscene
		if (Input::GetMouseButtonPressed(1))
		{
			cutSceneFrame++;
			cutScene.SetFrame(cutSceneFrame);
		}
	}
	void MainMenu::DrawCutScene(Surface* screen)
	{
		if (cutSceneFrame < 16)
			cutScene.Draw(screen, 0, 0);
	}
	void MainMenu::Logic(bool &gameStarted)
	{
		// Check if any button is pressed
		bool button1 = Input::GetMouseX() >= 313 && Input::GetMouseX() <= 499 && Input::GetMouseY() >= 274 && Input::GetMouseY() <= 349;
		bool button2 = Input::GetMouseX() >= 313 && Input::GetMouseX() <= 499 && Input::GetMouseY() >= 371 && Input::GetMouseY() <= 447;
		if (button1)
		{
			frame = 1;
			if(Input::GetMouseButtonPressed(1)) // Click play -> game starts
				gameStarted = true;
		}
		else if (button2)
		{
			frame = 2;
			if (Input::GetMouseButtonPressed(1)) // Click exit -> exit game
				exit(0);
		}
		else
			frame = 0;
		main.SetFrame(frame);	
	}
	void MainMenu::CutSceneLogic(bool& cutScenePlayed)
	{
		// Check if the cutscene is over
		if (cutSceneFrame >= 16 || Input::GetKeyPressed(SDL_SCANCODE_X))
			cutScenePlayed = true;
		else
			ManageFrames();
	}
}