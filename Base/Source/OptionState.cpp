#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "optionstate.h"
#include "menustate.h"

COptionState COptionState::theOptionState;

void COptionState::Init()
{
	theScene = new SceneManagerLevel2DforScreen(800, 600,Optionscreen);
	theScene->Init();
}

void COptionState::Init(const int width, const int height)
{
	theScene = new SceneManagerLevel2DforScreen(width, height, Optionscreen);
	theScene->Init();
	Select = 1;

	//Sound.mainMenuBGM();
	Sound.volume = theScene->tempsound;
}

void COptionState::Cleanup()
{
	theScene->Exit();
	delete theScene;
	theScene = NULL;
}

void COptionState::Pause()
{

}

void COptionState::Resume(bool m_resume)
{

}

void COptionState::HandleEvents(CGameStateManager* theGSM)
{}

void COptionState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{}

void COptionState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{}

void COptionState::Update(CGameStateManager* theGSM)
{
}

void COptionState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	theScene->Update(m_dElapsedTime);
	if (theScene->ReturnScreenTransition() == false)
	{
		if (Application::IsKeyPressed(VK_BACK))
		{
			//Sound.engine->stopAllSounds();
			Sound.BackSound();
			theScene->SetScreenTransition(true);
			theScene->SetChangeScreen(true);
		}

		if (Application::IsKeyPressed(VK_DOWN))
		{
			if (Select < 2) // Max. Number of Options
			{
				Sound.SelectSound();
				Select++;	// Move the cursor down
				Sleep(150);
				cout << Select << endl;
			}
		}
		if (Application::IsKeyPressed(VK_UP))
		{
			if (Select >= 1) // Selection is not the first one.
			{
				Sound.SelectSound();
				Select--;
				Sleep(150);
				cout << Select << endl;
			}
		}
	}

	if (theScene->ReturnChangeScreen() && theScene->ReturnScreenTransition() == false)
	{
		theGSM->ChangeState(CMenuState::Instance());
	}

	

	if (Select == 1) // Sound
	{
		theScene->SoundSelect = true;
		theScene->VolumeSelect = false;
		Sound.muteSound();
	}
	else if (Select == 2) // Volume
	{

		theScene->SoundSelect = false;
		theScene->VolumeSelect = true;
		Sound.adjustVol();
	}

	theScene->tempsound = Sound.volume;

	if (theScene->tempsound == 0)
	{
		theScene->muted = true;
	}
	else
	{
		theScene->muted = false;
	}

	if (Application::IsKeyPressed(VK_BACK))
	{
		theGSM->ChangeState(CMenuState::Instance());
	}
}

void COptionState::Draw(CGameStateManager* theGSM)
{
	theScene->Render();
}
