#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "menustate.h"
#include "highscorestate.h"

CHighscoreState CHighscoreState::theHighscoreState;

void CHighscoreState::Init()
{
	theScene = new SceneManagerLevel2DforScreen(800, 600, Highscorescreen);
	theScene->Init();
	Select = 1;
	SelectLevel = 1;
	timer = 0.0f;
	theScene->SetSelection(Select);
	theScene->setLevelButtonSelection(SelectLevel);
	theScene->setDifficultyButton(true);
}

void CHighscoreState::Init(const int width, const int height)
{
	theScene = new SceneManagerLevel2DforScreen(width, height, Highscorescreen);
	theScene->Init();
	Select = 1;
	SelectLevel = 1;
	timer = 0.0f;
	theScene->SetSelection(Select);
	theScene->setLevelButtonSelection(SelectLevel);
	theScene->setDifficultyButton(true);
}

void CHighscoreState::Cleanup()
{
	theScene->Exit();
	delete theScene;
	theScene = NULL;
}

void CHighscoreState::Pause()
{
}

void CHighscoreState::Resume(bool m_resume)
{
}

void CHighscoreState::HandleEvents(CGameStateManager* theGSM)
{
}

void CHighscoreState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
}

void CHighscoreState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{
}

void CHighscoreState::Update(CGameStateManager* theGSM)
{
}

void CHighscoreState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	bool quit = false;
	theScene->Update(m_dElapsedTime);

	if (theScene->getDifficultyButton() == true)
	{
		theScene->SetChangeScreen(false);
		if (theScene->ReturnChangeScreen() == false && theScene->ReturnScreenTransition() == false)
		{
			timer += m_dElapsedTime;
			if (Application::IsKeyPressed(VK_DOWN) && timer > 0.1f)
			{
				if (Select < 4)
				{
					Sound.engine->stopAllSounds();
					Sound.SelectSound();
					Select++;
					//Sleep(150);
					timer = 0;
				}
			}
			else if (Application::IsKeyPressed(VK_UP) && timer > 0.1f)
			{
				if (Select > 1)
				{
					Sound.engine->stopAllSounds();
					Sound.SelectSound();
					Select--;
					//Sleep(150);
					timer = 0;
				}
			}
			if (Application::IsKeyPressed(VK_RETURN) && timer > 0.1f)
			{
				timer = 0;
				Sound.engine->stopAllSounds();
				Sound.ConfirmSound();
				theScene->SetChangeScreen(true);
			}

			if (Application::IsKeyPressed(VK_BACK) && timer > 0.1f)
			{
				timer = 0;
				Sound.engine->stopAllSounds();
				Sound.BackSound();
				Select = -1;
				if ((theScene->getDifficultyButton() == false))
					theScene->SetScreenTransition(true);

				theScene->SetChangeScreen(true);
			}
		}
		if (theScene->ReturnChangeScreen() && theScene->ReturnScreenTransition() == false)
		{
			switch (Select)
			{
			case -1:
			{
					   quit = true;
					   break;
			}
			case 1:
			{
					  theScene->setHSDifficulty(Select);
					  theScene->setDifficultyButton(false);
					  theScene->setLevelButton(false);
					  theScene->setHighscoreDisplay(true);
					  Select = 1;
					  break;
			}
			case 2:
			{
					  theScene->setHSDifficulty(Select);
					  theScene->setDifficultyButton(false);
					  theScene->setLevelButton(true);
					  theScene->setHighscoreDisplay(false);
					  Select = 1;
					  break;
			}
			case 3:
			{
					  theScene->setHSDifficulty(Select);
					  theScene->setDifficultyButton(false);
					  theScene->setLevelButton(true);
					  theScene->setHighscoreDisplay(false);
					  Select = 1;
					  break;
			}
			case 4:
			{
					  theScene->setHSDifficulty(Select);
					  theScene->setDifficultyButton(false);
					  theScene->setLevelButton(true);
					  theScene->setHighscoreDisplay(false);
					  Select = 1;
					  break;
			}
			}

			if (quit == true)
			{
				theGSM->ChangeState(CMenuState::Instance());
			}
		}
		else
		{
			theScene->SetSelection(Select);
		}
	}

	else if (theScene->getLevelButton() == true)
	{
		theScene->SetChangeScreen(false);
		if (theScene->ReturnChangeScreen() == false && theScene->ReturnScreenTransition() == false)
		{
			timer += m_dElapsedTime;
			if (Application::IsKeyPressed(VK_DOWN) && timer > 0.1f)
			{
				if (SelectLevel < 4)
				{
					Sound.engine->stopAllSounds();
					Sound.SelectSound();
					SelectLevel++;
					//Sleep(150);
					timer = 0;
					cout << SelectLevel << endl;
				}
			}
			else if (Application::IsKeyPressed(VK_UP) && timer > 0.1f)
			{
				if (SelectLevel > 1)
				{
					Sound.engine->stopAllSounds();
					Sound.SelectSound();
					SelectLevel--;
					//Sleep(150);
					cout << SelectLevel << endl;
					timer = 0;
				}
			}
			if (Application::IsKeyPressed(VK_RETURN) && timer > 0.1f)
			{
				timer = 0;
				Sound.engine->stopAllSounds();
				Sound.ConfirmSound();
				theScene->SetChangeScreen(true);
			}

			if (Application::IsKeyPressed(VK_BACK) && timer > 0.1f)
			{
				timer = 0;
				Sound.engine->stopAllSounds();
				Sound.BackSound();
				SelectLevel = -1;
				if ((theScene->getLevelButton() == false))
					theScene->SetScreenTransition(true);
				theScene->SetChangeScreen(true);
			}
		}
		if (theScene->ReturnChangeScreen() && theScene->ReturnScreenTransition() == false)
		{
			switch (SelectLevel)
			{
			case -1:
			{
					   theScene->setDifficultyButton(true);
					   theScene->setLevelButton(false);
					   SelectLevel = 1;
					   break;
			}
			case 1:
			{
					  theScene->setHSLevel(SelectLevel);
					  theScene->setDifficultyButton(false);
					  theScene->setLevelButton(false);
					  theScene->setHighscoreDisplay(true);
					  SelectLevel = 1;
					  break;
			}
			case 2:
			{
					  theScene->setHSLevel(SelectLevel);
					  theScene->setDifficultyButton(false);
					  theScene->setLevelButton(false);
					  theScene->setHighscoreDisplay(true);
					  SelectLevel = 1;
					  break;
			}
			case 3:
			{
					  theScene->setHSLevel(SelectLevel);
					  theScene->setDifficultyButton(false);
					  theScene->setLevelButton(false);
					  theScene->setHighscoreDisplay(true);
					  SelectLevel = 1;
					  break;
			}
			case 4:
			{
					  theScene->setHSLevel(SelectLevel);
					  theScene->setDifficultyButton(false);
					  theScene->setLevelButton(false);
					  theScene->setHighscoreDisplay(true);
					  SelectLevel = 1;
					  break;
			}
			}
		}
		else
		{
			theScene->setLevelButtonSelection(SelectLevel);
		}
	}

	else if (theScene->getHighscoreDisplay() == true)
	{
		theScene->SetChangeScreen(false);
		if (theScene->ReturnChangeScreen() == false && theScene->ReturnScreenTransition() == false)
		{
			timer += m_dElapsedTime;
			if (Application::IsKeyPressed(VK_BACK) && timer > 0.1f)
			{
				timer = 0;
				Sound.engine->stopAllSounds();
				Sound.BackSound();
				if ((theScene->getHighscoreDisplay() == false))
					theScene->SetScreenTransition(true);

				theScene->SetChangeScreen(true);
			}
		}

		if (theScene->ReturnChangeScreen() && theScene->ReturnScreenTransition() == false)
		{
			if (theScene->getHSDifficulty() > 1)
			{
				theScene->setDifficultyButton(false);
				theScene->setLevelButton(true);
				theScene->setHighscoreDisplay(false);
			}
			else
			{
				theScene->setDifficultyButton(true);
				theScene->setLevelButton(false);
				theScene->setHighscoreDisplay(false);
			}
		}
	}
}

void CHighscoreState::Draw(CGameStateManager* theGSM)
{
	theScene->Render();
}
