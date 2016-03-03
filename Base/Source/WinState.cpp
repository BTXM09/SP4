#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "Winstate.h"
#include "menustate.h"

CWinState CWinState::theWinState;

void CWinState::Init()
{
	theScene = new SceneManagerLevel2DforScreen(800, 600, Winscreen);
	theScene->Init();
	Select = 1;
	timer = 0.0f;
	theScene->SetSelection(Select);
}

void CWinState::Init(const int width, const int height)
{
	theScene = new SceneManagerLevel2DforScreen(width, height, Winscreen);
	theScene->Init();
	Select = 1;
	timer = 0.0f;
	theScene->SetSelection(Select);
	theScene->Sound.engine->stopAllSounds();
}

void CWinState::Cleanup()
{
	theScene->Exit();
	delete theScene;
	theScene = NULL;
}

void CWinState::Pause()
{

}

void CWinState::Resume(bool m_resume)
{

}

void CWinState::HandleEvents(CGameStateManager* theGSM)
{}

void CWinState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{}

void CWinState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{}

void CWinState::Update(CGameStateManager* theGSM)
{
}

void CWinState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	theScene->Update(m_dElapsedTime);
	if (theScene->ReturnChangeScreen() == false && theScene->ReturnScreenTransition() == false)
	{
		timer += m_dElapsedTime;
		if (Application::IsKeyPressed(VK_DOWN) && timer > 0.1f)
		{
			if (Select < 2) // Max. Number of Options
			{
				theScene->Sound.SelectSound();
				Select++;	// Move the cursor down
				//Sleep(150);
				timer = 0;
				cout << Select << endl;
			}
		}
		else if (Application::IsKeyPressed(VK_UP) && timer > 0.1f)
		{
			if (Select > 1) // Selection is not the first one.
			{
				theScene->Sound.SelectSound();
				Select--;
				//Sleep(150);
				timer = 0;
				cout << Select << endl;
			}
		}
		theScene->SetSelection(Select);
	}
	if (theScene->ReturnChangeScreen() && theScene->ReturnScreenTransition() == false)
	{
		switch (Select)
		{
		case 1:
		{
				  //check if eligible for next level
				  if (theScene->CheckEligibleForNextLevel())
				  {
					  theScene->NextLevel();
					  theGSM->ChangeState(CPlayState::Instance());
				  }
				  else
				  {
					  theScene->CheckEligibleForNextLevel();
					  theScene->ResetPlayer();
					  theGSM->ChangeState(CMenuState::Instance());
				  }
				  break;
		}
		case 2:
		{
				  theScene->CheckEligibleForNextLevel();
				  theScene->ResetPlayer();
				  theGSM->ChangeState(CMenuState::Instance());
				  break;
		}
		}
	}

	if (Application::IsKeyPressed(VK_RETURN) && timer > 0.1f)
	{
			timer = 0;
			theScene->Sound.ConfirmSound();
			theScene->SetScreenTransition(true);
			theScene->SetChangeScreen(true);
	}
}

void CWinState::Draw(CGameStateManager* theGSM)
{
	theScene->Render();
}
