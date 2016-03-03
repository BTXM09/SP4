#pragma once

#include "gamestate.h"
#include "application.h"

class CHighscoreState : public CGameState
{
public:
	void Init();
	void Init(const int width, const int height);
	void Cleanup();

	void Pause();
	void Resume(bool m_resume);

	void HandleEvents(CGameStateManager* theGSM);
	void HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status = true);
	void HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
		const int button_Left, const int button_Middle, const int button_Right);
	void Update(CGameStateManager* theGSM);
	void Update(CGameStateManager* theGSM, const double m_dElapsedTime);
	void Draw(CGameStateManager* theGSM);

	static CHighscoreState* Instance() {
		return &theHighscoreState;
	}

	CSoundManager Sound;

protected:
	CHighscoreState() { }

private:
	static CHighscoreState theHighscoreState;
	SceneManagerLevel2DforScreen* theScene;
	int Select;
	int SelectLevel;
	double timer;
};
