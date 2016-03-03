#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "Pausestate.h"
#include "menustate.h"

CPauseState CPauseState::thePauseState;

void CPauseState::Init()
{
	theScene = new SceneManagerLevel2DforScreen(800, 600,Pausescreen);
	theScene->Init();
	Select = 1;
	timer = 0.0f;
	theScene->SetSelection(Select);
}

void CPauseState::Init(const int width, const int height)
{
	theScene = new SceneManagerLevel2DforScreen(width, height, Pausescreen);
	theScene->Init();
	Select = 1;
	timer = 0.0f;
	theScene->SetSelection(Select);
}

void CPauseState::Cleanup()
{
	theScene->Exit();
	delete theScene;
	theScene = NULL;
}

void CPauseState::Pause()
{

}

void CPauseState::Resume(bool m_resume)
{

}

void CPauseState::HandleEvents(CGameStateManager* theGSM)
{}

void CPauseState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{}

void CPauseState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{}

void CPauseState::Update(CGameStateManager* theGSM)
{
}

void CPauseState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	theScene->Update(m_dElapsedTime);
	if (theScene->ReturnScreenTransition() == false)
	{
		timer += m_dElapsedTime;
		if (Application::IsKeyPressed(VK_DOWN) && timer > 0.1f)
		{
			if (Select < 2) // Max. Number of Options
			{
				Sound.engine->stopAllSounds();
				Sound.SelectSound();
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
				Sound.engine->stopAllSounds();
				Sound.SelectSound();
				Select--;
				//Sleep(150);
				timer = 0;
				cout << Select << endl;
			}
		}
		if (Application::IsKeyPressed(VK_RETURN) && timer > 0.1f)
		{
			Sound.engine->stopAllSounds();
			Sound.ConfirmSound();
			theScene->SetScreenTransition(true);
			theScene->SetChangeScreen(true);
		}
	}
	if (theScene->ReturnChangeScreen() && theScene->ReturnScreenTransition() == false)
	{
		switch (Select)
		{
		case 1:
		{
				  theGSM->PopState(false);
				  break;
		}
		case 2:
		{
				  theGSM->PopState(true);
				  break;
		}
		}
	}
	else
	{
			theScene->SetSelection(Select);
	}
}

void CPauseState::Draw(CGameStateManager* theGSM)
{
	theScene->Render();
}
