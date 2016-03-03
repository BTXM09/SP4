#include "SoundManager.h"
#include "Application.h"

CSoundManager::CSoundManager(void)
{
	engine = createIrrKlangDevice();
	engine->setDefault3DSoundMinDistance(2.0f);
	engine->setDefault3DSoundMaxDistance(5.0f);
	volume = 0.0f;
	clicked = false;
	gameVol = 5;
}

CSoundManager::~CSoundManager(void)
{
	engine->drop();
} 
// Adjust Volume
void CSoundManager::adjustVol()
{
	static bool pressedLeft = false;
	if (Application::IsKeyPressed(VK_LEFT) && pressedLeft == false)
	{
		volume -= 0.1f;
		pressedLeft = true;
		if (volume <= 0)
		{
			volume = 0;
		}
	}
	else if (!Application::IsKeyPressed(VK_LEFT) && pressedLeft == true)
	{
		pressedLeft = false;
	}

	static bool pressedRight = false;
	if (Application::IsKeyPressed(VK_RIGHT) && pressedRight == false)
	{
		volume += 0.1f;
		pressedRight = true;
		if (volume >= 1)
		{
			volume = 1;
		}
	}
	else if (!Application::IsKeyPressed(VK_RIGHT) && pressedRight == true)
	{
		pressedRight = false;
	}
	
	cout << "Volume: " << volume << "\n" << endl;
	engine->setSoundVolume(volume);
}

//Mute Volume
void CSoundManager::muteSound()
{
	static bool pressedLeft = false;
	if (Application::IsKeyPressed(VK_LEFT) && pressedLeft == false && volume == 0)
	{
		volume = 0.1f;
		pressedLeft = true;
	}
	else if (!Application::IsKeyPressed(VK_LEFT) && pressedLeft == true)
	{
		pressedLeft = false;
	}

	static bool pressedRight = false;
	if (Application::IsKeyPressed(VK_RIGHT) && pressedRight == false)
	{
		volume = 0;
		pressedRight = true;
	}
	else if (!Application::IsKeyPressed(VK_RIGHT) && pressedRight == true)
	{
		pressedRight = false;
	}

	cout << "Volume: " << volume << "\n" << endl;
	engine->setSoundVolume(volume);
}

// main menu
void CSoundManager::mainMenuBGM()
{
	// play main menu music
	ISound* music = engine->play2D("../irrklang/media/Music.ogg",
		true, false, true);

	adjustVol();
}

void CSoundManager::ConfirmSound()
{
	//main menu confirming choice sound
	ISound* music = engine->play2D("../irrklang/media/confirm.wav",
		false, false, true);

	adjustVol();
}

void CSoundManager::SelectSound()
{
	//main menu selecting choice sound
	ISound* music = engine->play2D("../irrklang/media/select.wav",
		false, false, true);

	adjustVol();
}

void CSoundManager::BackSound()
{
	//main menu selecting choice sound
	ISound* music = engine->play2D("../irrklang/media/back.mp3",
		false, false, true);

	adjustVol();
}

void CSoundManager::level1BGM()
{
	//Level 1 background music
	/*ISound* music = engine->play2D(,
		true, false, true);*/

	engine->setSoundVolume(0.25f * volume);
}

void CSoundManager::level2BGM()
{
	//Level 2 background music
	/*ISound* music = engine->play2D(,
		true, false, true);*/

	engine->setSoundVolume(0.25f * volume);
}

void CSoundManager::level3BGM()
{
	//Level 3 background music
	/*ISound* music = engine->play2D(,
		true, false, true);*/

	engine->setSoundVolume(0.25f * volume);
}

void CSoundManager::level4BGM()
{
	//Level 4 background music
	/*ISound* music = engine->play2D(,
		true, false, true);*/

	engine->setSoundVolume(0.25f * volume);
}