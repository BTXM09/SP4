#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "LevelShopSelectionState.h"
#include "LevelSelectState.h"
#include "DifficultySelectState.h"
#include "ShopState.h"
#include "menustate.h"

CLevelShopSelectionState CLevelShopSelectionState::theLevelShopSelectionState;

void CLevelShopSelectionState::Init()
{
	theScene = new SceneManagerLevel2DforScreen(800, 600, LevelShopSelectionscreen);
	theScene->Init();
	timer = 0.0f;
	Select = 1;
	theScene->SetSelection(Select);
}

void CLevelShopSelectionState::Init(const int width, const int height)
{
	theScene = new SceneManagerLevel2DforScreen(width, height, LevelShopSelectionscreen);
	theScene->Init();
	timer = 0.0f;
	Select = 1;
	theScene->SetSelection(Select);
	theScene->Sound.volume = theScene->tempsound;
}

void CLevelShopSelectionState::Cleanup()
{
	theScene->Exit();
	delete theScene;
	theScene = NULL;
}

void CLevelShopSelectionState::Pause()
{

}

void CLevelShopSelectionState::Resume(bool m_resume)
{

}

void CLevelShopSelectionState::HandleEvents(CGameStateManager* theGSM)
{}

void CLevelShopSelectionState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{}

void CLevelShopSelectionState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{}

void CLevelShopSelectionState::Update(CGameStateManager* theGSM)
{
}

void CLevelShopSelectionState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	theScene->Update(m_dElapsedTime);
	if (theScene->ReturnChangeScreen() == false && theScene->ReturnScreenTransition() == false)
	{
		timer += m_dElapsedTime;
		if (Application::IsKeyPressed(VK_DOWN) && timer > 0.1f)
		{
			if (Select < 3) // Max. Number of Options
			{
				//theScene->Sound.engine->stopAllSounds();
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
		if (Application::IsKeyPressed(VK_RETURN) && timer > 0.1f)
		{
			timer = 0;
			if (Select < 3)
			{
				//Sound.engine->stopAllSounds();
				theScene->Sound.ConfirmSound();
				theScene->SetScreenTransition(true);
				theScene->SetChangeScreen(true);
			}
			else if (theScene->GetLevelReferencetoContinue() != 0 && Select == 3)
			{
				//Sound.engine->stopAllSounds();
				theScene->Sound.ConfirmSound();
				theScene->SetScreenTransition(true);
				theScene->SetChangeScreen(true);
			}
		}

		if (Application::IsKeyPressed(VK_BACK) && timer > 0.1f)
		{
			timer = 0;
			//Sound.engine->stopAllSounds();
			theScene->Sound.BackSound();
			Select = -1;
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
				   theGSM->ChangeState(CMenuState::Instance());
				   break;
		}
		case 1:
		{
				  theGSM->ChangeState(CDifficultySelectState::Instance());
				  break;
		}
		case 2:
		{
				  theGSM->ChangeState(CShopState::Instance());
				  break;
		}
		case 3:
		{
				  if (theScene->GetLevelReferencetoContinue() != 0)
				  {
					  theScene->SetContinuedLevel();
					  theGSM->ChangeState(CPlayState::Instance());
				  }
				  break;
		}
		}
	}
	else
	{
		theScene->SetSelection(Select);
	}
}

void CLevelShopSelectionState::Draw(CGameStateManager* theGSM)
{
	theScene->Render();
}
