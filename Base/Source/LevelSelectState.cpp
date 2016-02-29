#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "LevelShopSelectionState.h"
#include "LevelSelectState.h"
#include "DifficultySelectState.h"
#include "menustate.h"

CLevelSelectState CLevelSelectState::theLevelSelectState;

void CLevelSelectState::Init()
{
	theScene = new SceneManagerLevel2DforScreen(800, 600, LevelSelectscreen);
	theScene->Init();
	timer = 0.0f;
	Select = 1;
	theScene->SetSelection(Select);
}

void CLevelSelectState::Init(const int width, const int height)
{
	theScene = new SceneManagerLevel2DforScreen(width, height, LevelSelectscreen);
	theScene->Init();
	timer = 0.0f;
	Select = 1;
	theScene->SetSelection(Select);
}

void CLevelSelectState::Cleanup()
{
	theScene->Exit();
	delete theScene;
	theScene = NULL;
}

void CLevelSelectState::Pause()
{

}

void CLevelSelectState::Resume(bool m_resume)
{

}

void CLevelSelectState::HandleEvents(CGameStateManager* theGSM)
{}

void CLevelSelectState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{}

void CLevelSelectState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{}

void CLevelSelectState::Update(CGameStateManager* theGSM)
{
}

void CLevelSelectState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	theScene->Update(m_dElapsedTime);
	if (theScene->ReturnChangeScreen() == false && theScene->ReturnScreenTransition() == false)
	{
		timer += m_dElapsedTime;
		if (Application::IsKeyPressed(VK_DOWN)&& timer > 0.1f)
		{
			if (Select < 3)
			{
				Sound.engine->stopAllSounds();
				Sound.SelectSound();
				Select++;
				timer = 0;
				//Sleep(150);
			}
		}
		else if (Application::IsKeyPressed(VK_UP)&& timer > 0.1f)
		{
			if (Select > 1)
			{
				Sound.engine->stopAllSounds();
				Sound.SelectSound();
				Select--;
				timer = 0;
				//Sleep(150);
			}
		}
		if (Application::IsKeyPressed(VK_RETURN) && timer > 0.1f)
		{
			Sound.engine->stopAllSounds();
			Sound.ConfirmSound();
			theScene->SetScreenTransition(true);
			theScene->SetChangeScreen(true);
		}
		if (Application::IsKeyPressed(VK_BACK) && timer > 0.1f)
		{
			Sound.engine->stopAllSounds();
			Sound.BackSound();
			theScene->SetScreenTransition(true);
			theScene->SetChangeScreen(true);
			Select = -1;
		}
		theScene->SetSelection(Select);
	}

	if (theScene->ReturnChangeScreen() && theScene->ReturnScreenTransition() == false)
	{
		switch (Select)
		{
		case -1:
		{
				   theGSM->ChangeState(CDifficultySelectState::Instance());
				   break;
		}
		case 1:
		{
				  theScene->setLevel(1);
				  theGSM->ChangeState(CPlayState::Instance());
				  break;
		}
		case 2:
		{
				  theScene->setLevel(2);
				  theGSM->ChangeState(CPlayState::Instance());
				  break;
		}
		case 3:
		{
				  theScene->setLevel(3);
				  theGSM->ChangeState(CPlayState::Instance());
				  break;
		}
		}
	}
}

void CLevelSelectState::Draw(CGameStateManager* theGSM)
{
	theScene->Render();
}
