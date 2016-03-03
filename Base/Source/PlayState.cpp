#include <iostream>
using namespace std;

#include "gamestate.h"
#include "GameStateManager.h"
#include "playstate.h"
#include "pausestate.h"
#include "WinState.h"
#include "LevelSelectState.h"

CPlayState CPlayState::thePlayState;

void CPlayState::Init()
{
#if GSM_DEBUG_MODE
	cout << "CPlayState::Init\n" << endl;
#endif
	counter = 0;

	#if TYPE_OF_VIEW == 3
		scene = new CSceneManager(800, 600);	// Use this for 3D gameplay
	#else
	scene = new CSceneManager2D(800, 600);	// Use this for 2D gameplay
	#endif
	scene->Init();
}

void CPlayState::Init(const int width, const int height)
{
#if GSM_DEBUG_MODE
	cout << "CPlayState::Init\n" << endl;
#endif
	counter = 0;

	#if TYPE_OF_VIEW == 3
		scene = new CSceneManager(width, height);	// Use this for 3D gameplay
	#else
	scene = new CSceneManager2D(width, height);	// Use this for 2D gameplay
	#endif
	this->Resumez = false;
	scene->Init();
}

void CPlayState::Cleanup()
{
#if GSM_DEBUG_MODE
	cout << "CPlayState::Cleanup\n" << endl;
#endif
	// Delete the scene
	scene->Exit();
	delete scene;
	scene = NULL;
}

void CPlayState::Pause()
{
#if GSM_DEBUG_MODE
	cout << "CPlayState::Pause\n" << endl;
#endif
}

void CPlayState::Resume(bool m_resume)
{
#if GSM_DEBUG_MODE

	if (m_resume)
	{
		this->Resumez = m_resume;
		scene->SetQuitfrompause(m_resume);
	}
	else
	scene->PreInit();
	cout << "CPlayState::Resume\n" << endl;
#endif
}

void CPlayState::HandleEvents(CGameStateManager* theGSM)
{
#if GSM_DEBUG_MODE
	//int m_iUserChoice = -1;
	//do {
	//	cout << "CPlayState: Choose one <0> Go to Menu State : " ;
	//	cin >> m_iUserChoice;
	//	cin.get();
	//	switch (m_iUserChoice) {
	//		case 0:
	//			theGSM->ChangeState( CMenuState::Instance() );
	//			break;
	//		default:
	//			cout << "Invalid choice!\n";
	//			m_iUserChoice = -1;
	//			break;
	//	}
	//} while (m_iUserChoice == -1);
#endif
}

void CPlayState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
#if GSM_DEBUG_MODE
	//int m_iUserChoice = -1;

	//do {
	//	cout << "CPlayState: Choose one <0> Go to Menu State : " ;
	//	cin >> m_iUserChoice;
	//	cin.get();

	//	switch (m_iUserChoice) {
	//		case 0:
	//			theGSM->ChangeState( CMenuState::Instance() );
	//			break;
	//		default:
	//			cout << "Invalid choice!\n";
	//			m_iUserChoice = -1;
	//			break;
	//	}
	//} while (m_iUserChoice == -1);
#endif
	if (key == 32)
	{
		theGSM->PushState(CPauseState::Instance());
	}
	/*if (key == 32)
	{
		theGSM->ChangeState( CMenuState::Instance() );
	}*/
	/*else
	{
		scene->UpdateAvatarStatus( key, status );
	}*/
}

void CPlayState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							  const int button_Left, const int button_Middle, const int button_Right)
{
#if GSM_DEBUG_MODE
	//int m_iUserChoice = -1;

	//do {
	//	cout << "CPlayState: Choose one <0> Go to Menu State : " ;
	//	cin >> m_iUserChoice;
	//	cin.get();

	//	switch (m_iUserChoice) {
	//		case 0:
	//			theGSM->ChangeState( CMenuState::Instance() );
	//			break;
	//		default:
	//			cout << "Invalid choice!\n";
	//			m_iUserChoice = -1;
	//			break;
	//	}
	//} while (m_iUserChoice == -1);
#endif
	static bool Left_Clicked = false;
	if (button_Left == true && !Left_Clicked)
	{
		scene->UpdateMouseStatus(scene->WA_LEFT_CLICKED);
		Left_Clicked = true;
	}
	else if (button_Left == false && Left_Clicked)
	{
		Left_Clicked = false;
	}
		
	/*else if (button_Right == true)
		scene->UpdateWeaponStatus(scene->WA_FIRE_SECONDARY);*/
}


void CPlayState::Update(CGameStateManager* theGSM)
{
#if GSM_DEBUG_MODE
	cout << "CPlayState::Update\n" << endl;
#endif
	// Update the scene
	scene->Update(0.16667);
}

void CPlayState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	// Update the scene
	scene->Update(m_dElapsedTime);
	if (scene->GetWinCondition() == 1)
	{
		theGSM->ChangeState(CWinState::Instance());
	}
	else if (scene->GetWinCondition() == -1 && scene->GetLoseCondition())
	{
		theGSM->ChangeState(CLevelSelectState::Instance());
	}
	if (this->Resumez)
	{
		theGSM->ChangeState(CMenuState::Instance());
	}
}

void CPlayState::Draw(CGameStateManager* theGSM)
{
#if GSM_DEBUG_MODE
	//cout << "CPlayState::Draw : " << counter << "\n" << endl;
#endif

	// Render the scene
	scene->Render();
}
