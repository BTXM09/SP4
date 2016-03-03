#pragma once

#include <vector>
using namespace std;

static const short Splashscreen = 0;
static const short Menuscreen = 1;
static const short Instructionscreen = 2;
static const short Highscorescreen = 3;
static const short Optionscreen = 4;
static const short LevelShopSelectionscreen = 5;
static const short Shopscreen = 6;
static const short LevelSelectscreen = 7;
static const short Pausescreen = 8;
static const short Winscreen = 9;
static const short DifficultySelectscreen = 10;

class CGameState;

class CGameStateManager
{
public:

	CGameStateManager();


	void Init(const char* title, int width=640, int height=480, 
		      int bpp=0, bool fullscreen=false);
	void Cleanup();

	void ChangeState(CGameState* state);
	void PushState(CGameState* state);
	void PopState(bool m_resume);

	void HandleEvents();
	void HandleEvents(const unsigned char key, const bool status = true);
	void HandleEvents(const double mouse_x, const double mouse_y,
					  const int button_Left, const int button_Middle, const int button_Right);
	void Update(const double m_dElapsedTime);
	void Draw();

	bool Running() { return m_bRunning; }
	void Quit() { m_bRunning = false; }

private:
	// the stack of states
	vector<CGameState*> StackOfStates;

	int m_window_width;
	int m_window_height;

	bool m_bRunning;
	bool m_bFullscreen;
};
