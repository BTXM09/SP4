#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "GameStateManager.h"
#include "playstate.h"
#include "menustate.h"
#include "LuaUsage.h"
#include "SceneManager2DforScreen.h"

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}

	static bool IsKeyPressed(unsigned short key);
	static void GetMousePos(double&, double&);
	bool GetMouseUpdate();
	bool GetKeyboardUpdate();
	/*static void GetWindowWidth(int&);
	static void GetWindowHeight(int&);*/
	
	void CheckInit();

	void Init();
	void Run();
	void Exit();

	//Declare variables to store the last and current mouse position
	static double mouse_last_x, mouse_last_y, mouse_current_x, mouse_current_y, mouse_diff_x, mouse_diff_y;
	int Button_Left, Button_Middle, Button_Right;
	static double camera_yaw, camera_pitch;

private:
	Application();
	~Application();

	// Declare the window width and height as constant integer
	const static int m_window_deadzone = 100;
	int m_window_width;
	int m_window_height;
	//const static int m_window_width = 800;
	//const static int m_window_height = 600;
	//Declare a window object
	StopWatch m_timer;
	double m_dElapsedTime;
	double m_dAccumulatedTime_ThreadOne;
	double m_dAccumulatedTime_ThreadTwo;

	// Game State Management
	CGameStateManager* theGSM;
	LuaUsage* theAppLua;
};

#endif