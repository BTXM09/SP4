#include "Application.h"

//Include GLEW
/*#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>
*/

//Include the standard C++ headers
#include <stdio.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif
#endif

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
double Application::mouse_last_x = 0.0, Application::mouse_last_y = 0.0, 
	   Application::mouse_current_x = 0.0, Application::mouse_current_y = 0.0,
	   Application::mouse_diff_x = 0.0, Application::mouse_diff_y = 0.0;
double Application::camera_yaw = 0.0, Application::camera_pitch = 0.0;
int WindowHeight, WindowWidth;

/********************************************************************************
 Define an error callback
 ********************************************************************************/
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

/********************************************************************************
 Define the key input callback
 ********************************************************************************/
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

/********************************************************************************
 Callback function when the window is resized
 ********************************************************************************/
void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

/********************************************************************************
 Get keyboard's key states
 ********************************************************************************/
bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

/********************************************************************************
Get mouse position
********************************************************************************/
void Application::GetMousePos(double& x, double& y)
{
	glfwGetCursorPos(m_window, &x, &y);
	y = (WindowHeight - y);
	/*x = x / WindowWidth;
	 / WindowHeight;*/
}

/********************************************************************************
 Get mouse updates
 ********************************************************************************/
bool Application::GetMouseUpdate()
{
	
    glfwGetCursorPos(m_window, &mouse_current_x, &mouse_current_y);

	// Calculate the difference in positions
	mouse_diff_x = mouse_current_x - mouse_last_x;
	mouse_diff_y = mouse_current_y - mouse_last_y;

	//Calculate the yaw and pitch
	camera_yaw = (float) mouse_diff_x * 0.0174555555555556f;// * 3.142f / 180.0f;
	camera_pitch = mouse_diff_y * 0.0174555555555556f;// 3.142f / 180.0f );

	// Do a wraparound if the mouse cursor has gone out of the deadzone
	/*if ((mouse_current_x < m_window_deadzone) || (mouse_current_x > m_window_width-m_window_deadzone))
	{
		mouse_current_x = m_window_width >> 1;
		glfwSetCursorPos(m_window, mouse_current_x, mouse_current_y);
	}
	if ((mouse_current_y < m_window_deadzone) || (mouse_current_y > m_window_height-m_window_deadzone))
	{
		mouse_current_y = m_window_height >> 1;
		glfwSetCursorPos(m_window, mouse_current_x, mouse_current_y);
	}*/

	// Store the current position as the last position
	mouse_last_x = mouse_current_x;
	mouse_last_y = mouse_current_y;

	// Get the mouse button status
	Button_Left   = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
	Button_Middle = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_MIDDLE);
	Button_Right  = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT);



	// Update the GSM
	theGSM->HandleEvents( mouse_current_x, mouse_current_x, Button_Left, Button_Middle, Button_Right);

	// Get the mouse button status
//	if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
//		scene->UpdateWeaponStatus(scene->WA_FIRE);

    return false;
}

/********************************************************************************
 Get keyboard updates
 ********************************************************************************/
bool Application::GetKeyboardUpdate()//Controls can be changed
{
	if (IsKeyPressed(VK_ESCAPE))
	{
		theGSM->Quit();
	}

	if (IsKeyPressed('A'))
	{
		theGSM->HandleEvents('a');
	}
	else
	{
		theGSM->HandleEvents('a', false);
	}
	if (IsKeyPressed('D'))
	{
		theGSM->HandleEvents('d');
	}
	else
	{
		theGSM->HandleEvents('d', false);
	}
	if (IsKeyPressed('W'))
	{
		theGSM->HandleEvents('w');
	}
	else
	{
		theGSM->HandleEvents('w', false);
	}
	if (IsKeyPressed('S'))
	{
		theGSM->HandleEvents('s');
	}
	else
	{
		theGSM->HandleEvents('s', false);
	}
	// Jump
	if (IsKeyPressed(' '))
	{
		theGSM->HandleEvents(' ');
	}
	// Rotate camera
	if (IsKeyPressed(VK_LEFT))
	{
		theGSM->HandleEvents(VK_LEFT);
	}
	else
	{
		theGSM->HandleEvents(VK_LEFT, false);
	}
	if (IsKeyPressed(VK_RIGHT))
	{
		theGSM->HandleEvents(VK_RIGHT);
	}
	else
	{
		theGSM->HandleEvents(VK_RIGHT, false);
	}
	
	if (IsKeyPressed(VK_UP))
	{
		theGSM->HandleEvents(VK_UP);
	}
	else
	{
		theGSM->HandleEvents(VK_UP, false);
	}
	if (IsKeyPressed(VK_DOWN))
	{
		theGSM->HandleEvents(VK_DOWN);
	}
	else
	{
		theGSM->HandleEvents(VK_DOWN, false);
	}
	return true;
}

/********************************************************************************
 Constructor
 ********************************************************************************/
Application::Application()
	: theGSM(NULL),
	theAppLua(NULL)
{
}

/********************************************************************************
 Destructor
 ********************************************************************************/
Application::~Application()
{
	if (theAppLua)
	{
		delete theAppLua;
		theAppLua = NULL;
	}
	if (theGSM)
	{
		delete theGSM;
		theGSM = NULL;
	}
	_CrtDumpMemoryLeaks();
}

/********************************************************************************
 Initialise this program
 ********************************************************************************/
void Application::CheckInit()
{
	LuaUsage* Checker = new LuaUsage();
	Save* LuaSave = new Save();
	if (Checker->LuaUsageCheckit("Application"))
	{
		LuaSave->SaveEveryThing(0);
	}
	if (Checker->LuaUsageCheckit("Button"))
	{
		LuaSave->SaveEveryThing(1);
	}
	if (Checker->LuaUsageCheckit("Item"))
	{
		LuaSave->SaveEveryThing(2);
	}
	if (Checker->LuaUsageCheckit("Level"))
	{
		LuaSave->SaveEveryThing(3);
	}
	if (Checker->LuaUsageCheckit("LeveltoSave"))
	{
		LuaSave->SaveEveryThing(4);
	}
	if (Checker->LuaUsageCheckit("Player"))
	{
		LuaSave->SaveEveryThing(5);
	}
	if (Checker->LuaUsageCheckit("Sound"))
	{
		LuaSave->SaveEveryThing(6);
	}
	if (Checker->LuaUsageCheckit("Sprite"))
	{
		LuaSave->SaveEveryThing(7);
	}
	delete LuaSave;
	delete Checker;
}

void Application::Init()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //Does not allow scaleable window
	
	CheckInit();

	theAppLua = new LuaUsage();
	theAppLua->LuaUsageInit("Application");
	m_window_height = theAppLua->get<float>("WindowSize.ScreenSize.ScreenHeight");
	m_window_width = theAppLua->get<float>("WindowSize.ScreenSize.ScreenWidth");
	theAppLua->LuaUsageClose();


	WindowHeight = m_window_height;
	WindowWidth = m_window_width;
	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(m_window_width, m_window_height, "Y2S2_Framework", NULL, NULL);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

	// Hide the cursor
	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Set these 2 variables to zero
	m_dElapsedTime = 0.0;
	m_dAccumulatedTime_ThreadOne = 0.0;
	m_dAccumulatedTime_ThreadTwo = 0.0;
	
	// Initialise the GSM
	theGSM = new CGameStateManager();
	theGSM->Init("DM2240 with Game State Management", m_window_width, m_window_height);
	theGSM->ChangeState(CMenuState::Instance());
}

/********************************************************************************
 Run this program
 ********************************************************************************/
void Application::Run()
{
	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (theGSM->Running() && !glfwWindowShouldClose(m_window))
	{
		// Get the elapsed time
		m_dElapsedTime = m_timer.getElapsedTime();
		m_dAccumulatedTime_ThreadOne += m_dElapsedTime;
		m_dAccumulatedTime_ThreadTwo += m_dElapsedTime;
		if (m_dAccumulatedTime_ThreadOne > 0.03)
		{
			// Get inputs
			GetMouseUpdate();
			GetKeyboardUpdate();

			// Update the GSM
			theGSM->HandleEvents();
			theGSM->Update(m_dElapsedTime);

			m_dAccumulatedTime_ThreadOne = 0.0;
		}
		if (m_dAccumulatedTime_ThreadTwo > 1.0)
		{
			//UpdateAI();
			m_dAccumulatedTime_ThreadTwo = 0.0;
		}
		// Render the scene
		theGSM->Draw();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed

	// Clean up the GSM
	theGSM->Cleanup();
}

/********************************************************************************
 Exit this program
 ********************************************************************************/
void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();

	//std::cout << _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
}

