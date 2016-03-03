#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "highscorestate.h"
#include "optionstate.h"
//#include "playstate.h"
#include "LevelShopSelectionState.h"
#include "gamestate.h"
#include "menustate.h"
#include "instructionstate.h"

CMenuState CMenuState::theMenuState;

void CMenuState::Init()
{
	theScene = new SceneManagerLevel2DforScreen(800, 600, Menuscreen);
	theScene->Init();
	Select = 1;
	timer = 0.0f;
	theScene->SetSelection(Select);
}

void CMenuState::Init(const int width, const int height)
{
	theScene = new SceneManagerLevel2DforScreen(width, height, Menuscreen);
	theScene->Init();
	Select = 1;
	timer = 0.0f;
	theScene->SetSelection(Select);
	theScene->Sound.volume = theScene->tempsound;
	theScene->Sound.mainMenuBGM();
}

void CMenuState::Cleanup()
{
	theScene->Exit();
	delete theScene;
	theScene = NULL;
}

void CMenuState::Pause()
{
}

void CMenuState::Resume(bool m_resume)
{
}

void CMenuState::HandleEvents(CGameStateManager* theGSM)
{
}

void CMenuState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
}

void CMenuState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{
}

void CMenuState::Update(CGameStateManager* theGSM)
{
	
}

void CMenuState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	theScene->Update(m_dElapsedTime);
	
	if (theScene->ReturnChangeScreen() == false && theScene->ReturnScreenTransition() == false)
	{
		timer += m_dElapsedTime;
		if (Application::IsKeyPressed(VK_DOWN) && timer > 0.1f)
		{
			if (Select < 5) // Max. Number of Options
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
				//Sound.engine->stopAllSounds();
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
				  theGSM->ChangeState(CLevelShopSelectionState::Instance());
				  break;
		}
		case 2:
		{
				  theGSM->ChangeState(CInstructionState::Instance());
				  break;
		}
		case 3:
		{
				  theGSM->ChangeState(CHighscoreState::Instance());
				  break;
		}
		case 4:
		{
				  theGSM->ChangeState(COptionState::Instance());
				  break; 
		}
		}
	}

	if (Application::IsKeyPressed(VK_RETURN) && timer > 0.1f)
	{
		if (Select != 5)
		{
			timer = 0;
			//Sound.engine->stopAllSounds();
			theScene->Sound.ConfirmSound();
			theScene->SetScreenTransition(true);
			theScene->SetChangeScreen(true);
		}
		if (Select == 5)
		{
			timer = 0;
			theGSM->Quit();
		}
		timer = 0.0f;
	}

	
}

void CMenuState::Draw(CGameStateManager* theGSM)
{
	theScene->Render();
}
