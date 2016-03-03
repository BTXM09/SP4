#pragma once

#include "gamestate.h"
#include "application.h"

class CLevelShopSelectionState : public CGameState
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

	static CLevelShopSelectionState* Instance() {
		return &theLevelShopSelectionState;
	}

protected:
	CLevelShopSelectionState() { }

private:
	static CLevelShopSelectionState theLevelShopSelectionState;
	SceneManagerLevel2DforScreen* theScene;
	double timer;
	int Select;
};
