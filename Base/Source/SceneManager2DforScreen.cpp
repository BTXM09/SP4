#include "SceneManager2DforScreen.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>
#include "Strategy_Kill.h"

SceneManagerLevel2DforScreen::SceneManagerLevel2DforScreen()
: m_player(NULL)
, m_save(NULL)
, m_shop(NULL)
, m_particle(NULL)
, m_particle2(NULL)
, m_button(NULL)
, theButtonHolder(NULL)
, tempsound(0)
/*
: m_cMinimap(NULL)
, m_cMap(NULL)
, tileOffset_x(0)
, tileOffset_y(0)
, m_cRearMap(NULL)
, rearWallOffset_x(0)
, rearWallOffset_y(0)
, rearWallTileOffset_x(0)
, rearWallTileOffset_y(0)
, rearWallFineOffset_x(0)
, rearWallFineOffset_y(0)
, theEnemy(NULL)
*/
{
}

SceneManagerLevel2DforScreen::SceneManagerLevel2DforScreen(const int m_window_width, const int m_window_height, const int m_screenvalue)
: m_player(NULL)
, m_save(NULL)
, m_shop(NULL)
, m_particle(NULL)
, m_particle2(NULL)
, m_button(NULL)
, theButtonHolder(NULL)
, tempsound(0)
{
	this->m_screenvalue = m_screenvalue;
	this->m_windowWidth = m_window_width;
	this->m_windowHeight = m_window_height;
}

SceneManagerLevel2DforScreen::~SceneManagerLevel2DforScreen()
{
	for (vector<Button*>::iterator it = theButtonHolder.begin(); it != theButtonHolder.end(); ++it)
	{
		Button* button = (Button*)*it;
		if (button != NULL)
		{
			delete button;
			button = NULL;
		}
		delete button;
	}
	if (m_shop)
	{
		delete m_shop;
		m_shop = NULL;
	}
	if (m_player)
	{
		delete m_player;
		m_player = NULL;
	}
	if (m_loading)
	{
		delete m_loading;
		m_loading = NULL;
	}

	if (m_save)
	{
		delete m_save;
		m_save = NULL;
	}

	for (vector<AllLevelDetails*>::iterator it = theLevelDetailsHolder.begin(); it != theLevelDetailsHolder.end(); ++it)
	{
		AllLevelDetails* leveldetails = (AllLevelDetails*)*it;
		if (leveldetails != NULL)
		{
			delete leveldetails;
			leveldetails = NULL;
		}
	}
}

void SceneManagerLevel2DforScreen::PreInit()
{
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Switch on culling
	glEnable(GL_CULL_FACE);

	// Render mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Activate blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Generate and bind vertex array
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Load the shaders
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Fog.fragmentshader");

	// Get a handle for our uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	//m_parameters[U_MODEL] = glGetUniformLocation(m_programID, "M");
	//m_parameters[U_VIEW] = glGetUniformLocation(m_programID, "V");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	m_parameters[U_TEXT_ALPHA] = glGetUniformLocation(m_programID, "truetextColor");
	m_parameters[U_TEXT_ALPHA_ENABLED] = glGetUniformLocation(m_programID, "truetextEnabled");
	// Use our shader
	glUseProgram(m_programID);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
}

void SceneManagerLevel2DforScreen::Init()
{
	PreInit();

	// Initialise the camera
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));

	// Create the meshes
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Test3.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);


	meshList[GEO_MENU] = MeshBuilder::Generate2DMesh("GEO_MENU", Color(1, 1, 1, 0.0f), 0, 0, 800, 600);
	meshList[GEO_MENU]->textureID = LoadTGA("Image//MainMenu.tga");
	meshList[GEO_HIGHSCORE] = MeshBuilder::Generate2DMesh("GEO_HIGHSCORE", Color(1, 1, 1), 0, 0, 800, 600);
	meshList[GEO_HIGHSCORE]->textureID = LoadTGA("Image//Highscore.tga");
	meshList[GEO_VOL_MUTE] = MeshBuilder::Generate2DMesh("GEO_VOL_MUTE", Color(1, 1, 1), 0, 0, 800, 600);
	meshList[GEO_VOL_MUTE]->textureID = LoadTGA("Image//OptionsVolumeSoundOff.tga");
	meshList[GEO_VOL] = MeshBuilder::Generate2DMesh("GEO_VOL", Color(1, 1, 1), 0, 0, 800, 600);
	meshList[GEO_VOL]->textureID = LoadTGA("Image//OptionsVolumeSoundOn.tga");
	meshList[GEO_SOUND_MUTE] = MeshBuilder::Generate2DMesh("GEO_SOUND_MUTE", Color(1, 1, 1), 0, 0, 800, 600);
	meshList[GEO_SOUND_MUTE]->textureID = LoadTGA("Image//OptionsSoundOff.tga");
	meshList[GEO_SOUND] = MeshBuilder::Generate2DMesh("GEO_SOUND", Color(1, 1, 1), 0, 0, 800, 600);
	meshList[GEO_SOUND]->textureID = LoadTGA("Image//OptionsSoundOn.tga");
	meshList[GEO_INSTRUCTION] = MeshBuilder::Generate2DMesh("GEO_INSTRUCTIONS", Color(1, 1, 1), 0, 0, 800, 600);
	meshList[GEO_INSTRUCTION]->textureID = LoadTGA("Image//Instructions.tga");
	meshList[GEO_PAUSE] = MeshBuilder::Generate2DMesh("GEO_PAUSE", Color(1, 1, 1), 0, 0, 800, 600);
	meshList[GEO_PAUSE]->textureID = LoadTGA("Image//Pause.tga");
	meshList[GEO_SHOP] = MeshBuilder::Generate2DMesh("GEO_SHOP", Color(1, 1, 1), 0, 0, 800, 600);
	meshList[GEO_SHOP]->textureID = LoadTGA("Image//Shop.tga");
	meshList[GEO_WIN] = MeshBuilder::Generate2DMesh("GEO_WIN", Color(1, 1, 1), 0, 0, 800, 600);
	meshList[GEO_WIN]->textureID = LoadTGA("Image//Win.tga");
	meshList[GEO_LEVELSHOPSELECT] = MeshBuilder::Generate2DMesh("GEO_LEVELSHOPSELECT", Color(1, 1, 1), 0, 0, 800, 600);
	meshList[GEO_LEVELSHOPSELECT]->textureID = LoadTGA("Image//LevelShopSelect.tga");

	meshList[GEO_LEVELSELECT] = MeshBuilder::Generate2DMesh("GEO_LEVELSELECT", Color(1, 1, 1), 0, 0, 800, 600);
	meshList[GEO_LEVELSELECT]->textureID = LoadTGA("Image//LevelSelect.tga");

	meshList[GEO_SELECT] = MeshBuilder::Generate2DMesh("GEO_SELECT", Color(1, 1, 1), 0, 0, 75, 55);
	meshList[GEO_SELECT]->textureID = LoadTGA("Image//Select.tga");

	meshList[GEO_DIFFICULTYSELECT] = MeshBuilder::Generate2DMesh("GEO_DIFFICULTYSELECT", Color(1, 1, 1), 0, 0, 800, 600);
	meshList[GEO_DIFFICULTYSELECT]->textureID = LoadTGA("Image//DiffTemp.tga");

	meshList[GEO_VOL_BAR] = MeshBuilder::GenerateQuad("volume bar", Color(1, 0, 0), 20);

	meshList[GEO_MENU_PLAY] = MeshBuilder::Generate2DMesh("GEO_MENU_PLAY", Color(1, 1, 1), 0, 0, 96, 34);
	meshList[GEO_MENU_PLAY]->textureID = LoadTGA("Image//ButtonMesh/Playbutton.tga");
	meshList[GEO_MENU_INSTRUCTION] = MeshBuilder::Generate2DMesh("GEO_MENU_INSTRUCTION", Color(1, 1, 1), 0, 0, 265, 34);
	meshList[GEO_MENU_INSTRUCTION]->textureID = LoadTGA("Image//ButtonMesh/Instructionbutton.tga");
	meshList[GEO_MENU_HIGHSCORE] = MeshBuilder::Generate2DMesh("GEO_MENU_HIGHSCORE", Color(1, 1, 1), 0, 0, 202, 34);
	meshList[GEO_MENU_HIGHSCORE]->textureID = LoadTGA("Image//ButtonMesh/Highscorebutton.tga");
	meshList[GEO_MENU_OPTION] = MeshBuilder::Generate2DMesh("GEO_MENU_OPTION", Color(1, 1, 1), 0, 0, 157, 34);
	meshList[GEO_MENU_OPTION]->textureID = LoadTGA("Image//ButtonMesh/Optionbutton.tga");
	meshList[GEO_MENU_EXIT] = MeshBuilder::Generate2DMesh("GEO_MENU_EXIT", Color(1, 1, 1), 0, 0, 83, 34);
	meshList[GEO_MENU_EXIT]->textureID = LoadTGA("Image//ButtonMesh/Exitbutton.tga");

	meshList[GEO_LEVELSHOPSELECT_LEVELSELECT] = MeshBuilder::Generate2DMesh("GEO_LEVELSHOPSELECT_LEVELSELECT", Color(1, 1, 1), 0, 0, 263, 34);
	meshList[GEO_LEVELSHOPSELECT_LEVELSELECT]->textureID = LoadTGA("Image//ButtonMesh/LevelSelectbutton.tga");
	meshList[GEO_LEVELSHOPSELECT_SHOP] = MeshBuilder::Generate2DMesh("GEO_LEVELSHOPSELECT_SHOP", Color(1, 1, 1), 0, 0, 94, 34);
	meshList[GEO_LEVELSHOPSELECT_SHOP]->textureID = LoadTGA("Image//ButtonMesh/Shopbutton.tga");
	meshList[GEO_LEVELSHOPSELECT_CONTINUELEVEL] = MeshBuilder::Generate2DMesh("GEO_LEVELSHOPSELECT_CONTINUELEVEL", Color(1, 1, 1), 0, 0, 311, 34);
	meshList[GEO_LEVELSHOPSELECT_CONTINUELEVEL]->textureID = LoadTGA("Image//ButtonMesh/ContinueLevelbutton.tga");


	meshList[GEO_WIN_NEXTLEVEL] = MeshBuilder::Generate2DMesh("GEO_WIN_NEXTLEVEL", Color(1, 1, 1), 0, 0, 225, 34);
	meshList[GEO_WIN_NEXTLEVEL]->textureID = LoadTGA("Image//ButtonMesh/NextLevelbutton.tga");

	meshList[GEO_LEVELSELECT_LEVEL1] = MeshBuilder::Generate2DMesh("GEO_LEVELSELECT_LEVEL1", Color(1, 1, 1), 0, 0, 140, 34);
	meshList[GEO_LEVELSELECT_LEVEL1]->textureID = LoadTGA("Image//ButtonMesh/Level1button.tga");
	meshList[GEO_LEVELSELECT_LEVEL2] = MeshBuilder::Generate2DMesh("GEO_LEVELSELECT_LEVEL2", Color(1, 1, 1), 0, 0, 140, 34);
	meshList[GEO_LEVELSELECT_LEVEL2]->textureID = LoadTGA("Image//ButtonMesh/Level2button.tga");
	meshList[GEO_LEVELSELECT_LEVEL3] = MeshBuilder::Generate2DMesh("GEO_LEVELSELECT_LEVEL3", Color(1, 1, 1), 0, 0, 140, 34);
	meshList[GEO_LEVELSELECT_LEVEL3]->textureID = LoadTGA("Image//ButtonMesh/Level3button.tga");
	meshList[GEO_LEVELSELECT_LEVEL4] = MeshBuilder::Generate2DMesh("GEO_LEVELSELECT_LEVEL4", Color(1, 1, 1), 0, 0, 140, 34);
	meshList[GEO_LEVELSELECT_LEVEL4]->textureID = LoadTGA("Image//ButtonMesh/Level4button.tga");

	meshList[GEO_DIFFICULTY_EASY] = MeshBuilder::Generate2DMesh("GEO_DIFFICULTY_EASY", Color(1, 1, 1), 0, 0, 95, 34);
	meshList[GEO_DIFFICULTY_EASY]->textureID = LoadTGA("Image//ButtonMesh/Easybutton.tga");
	meshList[GEO_DIFFICULTY_NORMAL] = MeshBuilder::Generate2DMesh("GEO_DIFFICULTY_NORMAL", Color(1, 1, 1), 0, 0, 147, 34);
	meshList[GEO_DIFFICULTY_NORMAL]->textureID = LoadTGA("Image//ButtonMesh/Normalbutton.tga");
	meshList[GEO_DIFFICULTY_HARD] = MeshBuilder::Generate2DMesh("GEO_DIFFICULTY_HARD", Color(1, 1, 1), 0, 0, 98, 34);
	meshList[GEO_DIFFICULTY_HARD]->textureID = LoadTGA("Image//ButtonMesh/Hardbutton.tga");

	meshList[GEO_HIGHSCORE_TUTORIAL] = MeshBuilder::Generate2DMesh("GEO_HIGHSCORE_TUTORIAL", Color(1, 1, 1), 0, 0, 184, 34);
	meshList[GEO_HIGHSCORE_TUTORIAL]->textureID = LoadTGA("Image//ButtonMesh/Tutorial.tga");
	meshList[GEO_HIGHSCORE_EASY] = MeshBuilder::Generate2DMesh("GEO_HIGHSCORE_EASY", Color(1, 1, 1), 0, 0, 95, 34);
	meshList[GEO_HIGHSCORE_EASY]->textureID = LoadTGA("Image//ButtonMesh/Easybutton.tga");
	meshList[GEO_HIGHSCORE_NORMAL] = MeshBuilder::Generate2DMesh("GEO_HIGHSCORE_NORMAL", Color(1, 1, 1), 0, 0, 147, 34);
	meshList[GEO_HIGHSCORE_NORMAL]->textureID = LoadTGA("Image//ButtonMesh/Normalbutton.tga");
	meshList[GEO_HIGHSCORE_HARD] = MeshBuilder::Generate2DMesh("GEO_HIGHSCORE_HARD", Color(1, 1, 1), 0, 0, 98, 34);
	meshList[GEO_HIGHSCORE_HARD]->textureID = LoadTGA("Image//ButtonMesh/Hardbutton.tga");

	meshList[GEO_HIGHSCORE_LEVEL1] = MeshBuilder::Generate2DMesh("GEO_HIGHSCORE_LEVEL1", Color(1, 1, 1), 0, 0, 140, 34);
	meshList[GEO_HIGHSCORE_LEVEL1]->textureID = LoadTGA("Image//ButtonMesh/Level1button.tga");
	meshList[GEO_HIGHSCORE_LEVEL2] = MeshBuilder::Generate2DMesh("GEO_HIGHSCORE_LEVEL2", Color(1, 1, 1), 0, 0, 140, 34);
	meshList[GEO_HIGHSCORE_LEVEL2]->textureID = LoadTGA("Image//ButtonMesh/Level2button.tga");
	meshList[GEO_HIGHSCORE_LEVEL3] = MeshBuilder::Generate2DMesh("GEO_HIGHSCORE_LEVEL3", Color(1, 1, 1), 0, 0, 140, 34);
	meshList[GEO_HIGHSCORE_LEVEL3]->textureID = LoadTGA("Image//ButtonMesh/Level3button.tga");
	meshList[GEO_HIGHSCORE_LEVEL4] = MeshBuilder::Generate2DMesh("GEO_HIGHSCORE_LEVEL4", Color(1, 1, 1), 0, 0, 140, 34);
	meshList[GEO_HIGHSCORE_LEVEL4]->textureID = LoadTGA("Image//ButtonMesh/Level4button.tga");

	meshList[GEO_PAUSE_RESUME] = MeshBuilder::Generate2DMesh("GEO_PAUSE_RESUME", Color(1, 1, 1), 0, 0, 138, 34);
	meshList[GEO_PAUSE_RESUME]->textureID = LoadTGA("Image//ButtonMesh/Resumebutton.tga");
	meshList[GEO_PAUSE_QUITTOMENU] = MeshBuilder::Generate2DMesh("GEO_PAUSE_QUITTOMENU", Color(1, 1, 1), 0, 0, 263, 34);
	meshList[GEO_PAUSE_QUITTOMENU]->textureID = LoadTGA("Image//ButtonMesh/QuitToMenubutton.tga");

	meshList[GEO_BOMB] = MeshBuilder::Generate2DMesh("GEO_BOMB", Color(1, 1, 1), 0, 0, 34, 34);
	meshList[GEO_BOMB]->textureID = LoadTGA("Image//Bomb.tga");
	meshList[GEO_BRIDGE] = MeshBuilder::Generate2DMesh("GEO_BRIDGE", Color(1, 1, 1), 0, 0, 34, 34);
	meshList[GEO_BRIDGE]->textureID = LoadTGA("Image//Bridge.tga");

	meshList[GEO_BACKTOEXIT] = MeshBuilder::Generate2DMesh("GEO_BACKTOEXIT", Color(1, 1, 1), 0, 0, 376, 34);
	meshList[GEO_BACKTOEXIT]->textureID = LoadTGA("Image//ButtonMesh/PressBackToExit.tga");

	if (m_screenvalue == Winscreen)
	{
		m_SpriteAnimationLoad = new LuaUsage();
		m_SpriteAnimationLoad->LuaUsageInit("Sprite");
		confettiRightside = false;
		m_particle = new Particle();
		m_particle2 = new Particle();

		SetParticleStyle(m_particle, PARTICLE_STYLE::DROPDOWN);
		SetParticleStyle(m_particle2, PARTICLE_STYLE::DROPDOWN);
		//SetParticleStyle(m_particle, PARTICLE_STYLE::CONFETTI);
		//SetParticleStyle(m_particle2, PARTICLE_STYLE::CONFETTI);

		Math::InitRNG();
		for (int i = 0; i < m_particle->GetSize(); i++)
		{
			SetSpriteAnimation(m_particle, i);
		}

		for (int i = 0; i < m_particle2->GetSize(); i++)
		{
			SetSpriteAnimation(m_particle2, i);
		}
		m_SpriteAnimationLoad->LuaUsageClose();

		m_SpriteAnimationLoad->LuaUsageInit("LeveltoSave");
		m_maxlevel = m_SpriteAnimationLoad->get<int>("AmountOfLevel");
		m_maxdiff = m_SpriteAnimationLoad->get<int>("AmountOfDiff");
		m_maxleveltutorial = m_SpriteAnimationLoad->get<int>("AmountOfTutorialDiff");
		m_SpriteAnimationLoad->LuaUsageClose();

		string Start = "Level.";
		for (int i = 0; i < m_maxdiff; ++i)
		{
			string Diff = "";
			switch (i)
			{
			case 0:
			{
					  Diff = Start + "Tutorial.";
					  for (int j = 0; j < m_maxleveltutorial; ++j)
					  {
						  string Level = Diff + "Level" + to_string((j + 1)) + ".";
						  AllLevelDetails* m_levelofdetail = new AllLevelDetails();
						  m_levelofdetail->AllLevelDetailsInit(Level);
						  theLevelDetailsHolder.push_back(m_levelofdetail);
					  }
					  break;
			}
			case 1:
			{
					  Diff = Start + "Easy.";
					  break;
			}
			case 2:
			{
					  Diff = Start + "Normal.";
					  break;
			}
			case 3:
			{
					  Diff = Start + "Hard.";
					  break;
			}
			}
			if (i > 0)
			{
				for (int j = 0; j < m_maxlevel; ++j)
				{
					string Level = Diff + "Level" + to_string((j + 1)) + ".";
					AllLevelDetails* m_levelofdetail = new AllLevelDetails();
					m_levelofdetail->AllLevelDetailsInit(Level);
					theLevelDetailsHolder.push_back(m_levelofdetail);
				}
			}
		}
		CreateButton("NextLevel");
		CreateButton("QuitToMenu");
	}
	if (m_screenvalue == Menuscreen)
	{
		CreateButton("Play");
		CreateButton("Instruction");
		CreateButton("Highscore");
		CreateButton("Option");
		CreateButton("Exit");
	}
	if (m_screenvalue == LevelShopSelectionscreen)
	{
		CreateButton("LevelSelect");
		CreateButton("Shop");
		CreateButton("ContinueLevel");
	}
	if (m_screenvalue == DifficultySelectscreen)
	{
		CreateButton("DifficultyTutorial");
		CreateButton("DifficultyEasy");
		CreateButton("DifficultyNormal");
		CreateButton("DifficultyHard");
	}
	if (m_screenvalue == LevelSelectscreen)
	{
		CreateButton("Level1");
		CreateButton("Level2");
		CreateButton("Level3");
		CreateButton("Level4");
	}
	if (m_screenvalue == Pausescreen)
	{
		CreateButton("Resume");
		CreateButton("QuitToMenu");
	}
	if (m_screenvalue == Highscorescreen)
	{
		CreateButton("HighscoreTutorial");
		CreateButton("HighscoreEasy");
		CreateButton("HighscoreNormal");
		CreateButton("HighscoreHard");
		CreateButton("HighscoreLevel1");
		CreateButton("HighscoreLevel2");
		CreateButton("HighscoreLevel3");
		CreateButton("HighscoreLevel4");
	}

	m_select = -1;
	theLevelButtonSelection = -1;
	m_alpha = 0.0f;
	m_ChangeScreen = false;
	m_ScreenTransition = true;
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	m_save = new Save();
	rotateAngle = 0;

	m_loading = new LuaUsage();
	m_loading->LuaUsageInit("Sound");
	tempsound = m_loading->get<float>("Volume");
	m_loading->LuaUsageClose();

	m_player = new Player();
	m_player->PlayerInit("Player");
	m_shop = new Shop();
	m_shop->PlayerInit(m_player);
	m_shop->ItemInit();

	//if (m_screenvalue == Highscorescreen)
		//AddHighscore();
}

void SceneManagerLevel2DforScreen::ReadHighscoreTextFiles()
{
	if (getHSDifficulty() == 1)
	{
		theScore.ReadTextFile("Scores//TutorialHighscore.txt");
	}
	if (getHSDifficulty() == 2)
	{
		if (getHSLevel() == 1)
			theScore.ReadTextFile("Scores//EasyHighscore1.txt");
		if (getHSLevel() == 2)
			theScore.ReadTextFile("Scores//EasyHighscore2.txt");
		if (getHSLevel() == 3)
			theScore.ReadTextFile("Scores//EasyHighscore3.txt");
		if (getHSLevel() == 4)
			theScore.ReadTextFile("Scores//EasyHighscore4.txt");
	}
	if (getHSDifficulty() == 3)
	{
		if (getHSLevel() == 1)
			theScore.ReadTextFile("Scores//NormalHighscore1.txt");
		if (getHSLevel() == 2)
			theScore.ReadTextFile("Scores//NormalHighscore2.txt");
		if (getHSLevel() == 3)
			theScore.ReadTextFile("Scores//NormalHighscore3.txt");
		if (getHSLevel() == 4)
			theScore.ReadTextFile("Scores//NormalHighscore4.txt");
	}
	if (getHSDifficulty() == 4)
	{
		if (getHSLevel() == 1)
			theScore.ReadTextFile("Scores//HardHighscore1.txt");
		if (getHSLevel() == 2)
			theScore.ReadTextFile("Scores//HardHighscore2.txt");
		if (getHSLevel() == 3)
			theScore.ReadTextFile("Scores//HardHighscore3.txt");
		if (getHSLevel() == 4)
			theScore.ReadTextFile("Scores//HardHighscore4.txt");
	}
}

void SceneManagerLevel2DforScreen::GetHighscore()
{
	const int MAX_SCORES = 5;
	for (int i = 0; i < MAX_SCORES; i++)
	{
		ReadHighscoreTextFiles();
	}
}
void SceneManagerLevel2DforScreen::CreateButton(string name)
{
	m_button = new Button();
	m_button->ButtonInit(name);
	theButtonHolder.push_back(m_button);
}
bool SceneManagerLevel2DforScreen::ReturnPlayerDifficultySelection(int difficultyselection)
{
	if (difficultyselection == 1)
	{
		return true;
	}
	else
	{
		if (m_shop->theItemHolder[difficultyselection - 2]->GetBought() == true)
		{
			switch (difficultyselection)
			{
			case 2:
			{
					  if (m_player->GetEasyLevelUnlocked())
						  return true;
					  else
						  return false;
					  break;
			}
			case 3:
			{
					  if (m_player->GetNormalLevelUnlocked())
						  return true;
					  else
						  return false;
					  break;
			}
			case 4:
			{
					  if (m_player->GetHardLevelUnlocked())
						  return true;
					  else
						  return false;
					  break;
			}
			}
		}
		else
			return false;
	}
	return false;
}
bool SceneManagerLevel2DforScreen::CheckEligibleForNextLevel()
{

	if (this->m_player->GetLevelToDifficultyStartAt() == m_maxdiff)
	{
		if (this->m_player->GetLevelToStartAt() < m_maxlevel)
			return true;
		else
			return false;
	}
	else
	{
		switch (this->m_player->GetLevelToDifficultyStartAt())
		{
		case 1:
		{
				  if ((this->m_player->GetLevelToStartAt()) < m_maxleveltutorial)
				  {
					  return true;
				  }
				  if ((this->m_player->GetEasyLevelUnlocked()) == true && this->m_shop->theItemHolder[this->m_player->GetLevelToDifficultyStartAt() - 1]->GetBought() == true)
				  {
					  return true;
				  }
				  else if ((this->m_player->GetEasyLevelUnlocked() == false) || (this->m_shop->theItemHolder[this->m_player->GetLevelToDifficultyStartAt() - 1]->GetBought() == false))
				  {
					  if (this->theLevelDetailsHolder[0]->GetCleared())
						  this->m_player->SetEasyLevelUnlocked(true);
					  return false;
				  }
				  break;
		}
		case 2:
		{
				  if ((this->m_player->GetLevelToStartAt()) < m_maxlevel)
				  {
					  return true;
				  }
				  if ((this->m_player->GetNormalLevelUnlocked()) == true && this->m_shop->theItemHolder[this->m_player->GetLevelToDifficultyStartAt()-1]->GetBought() == true)
				  {
					  return true;
				  }
				  else if ((this->m_player->GetNormalLevelUnlocked() == false) || (this->m_shop->theItemHolder[this->m_player->GetLevelToDifficultyStartAt() - 1]->GetBought() == false))
				  {
					  if (this->theLevelDetailsHolder[((this->m_player->GetLevelToDifficultyStartAt() - 2) * 4) + 1]->GetCleared() &&
						  this->theLevelDetailsHolder[((this->m_player->GetLevelToDifficultyStartAt() - 2) * 4) + 2]->GetCleared()&&
						  this->theLevelDetailsHolder[((this->m_player->GetLevelToDifficultyStartAt() - 2) * 4) + 3]->GetCleared()&&
						  this->theLevelDetailsHolder[((this->m_player->GetLevelToDifficultyStartAt() - 2) * 4) + 4]->GetCleared())
					  this->m_player->SetNormalLevelUnlocked(true);
					  return false;
				  }
				  break;
		}
		case 3:
		{
				  if ((this->m_player->GetLevelToStartAt()) < m_maxlevel)
				  {
					  return true;
				  }
				  if ((this->m_player->GetHardLevelUnlocked()) == true && this->m_shop->theItemHolder[this->m_player->GetLevelToDifficultyStartAt() - 1]->GetBought() == true)
				  {
					  return true;
				  }
				  else if ((this->m_player->GetHardLevelUnlocked() == false) || (this->m_shop->theItemHolder[this->m_player->GetLevelToDifficultyStartAt() - 1]->GetBought() == false))
				  {
					  if (this->theLevelDetailsHolder[((this->m_player->GetLevelToDifficultyStartAt() - 2) * 4) + 1]->GetCleared() &&
						  this->theLevelDetailsHolder[((this->m_player->GetLevelToDifficultyStartAt() - 2) * 4) + 2]->GetCleared() &&
						  this->theLevelDetailsHolder[((this->m_player->GetLevelToDifficultyStartAt() - 2) * 4) + 3]->GetCleared() &&
						  this->theLevelDetailsHolder[((this->m_player->GetLevelToDifficultyStartAt() - 2) * 4) + 4]->GetCleared())
					  this->m_player->SetHardLevelUnlocked(true);
					  return false;
				  }
				  break;
		}
		}
	}
}
void SceneManagerLevel2DforScreen::NextLevel()
{
	if (this->m_player->GetLevelToDifficultyStartAt() == 1)
	{
		this->m_player->SetLevelToDifficultyStartAt((this->m_player->GetLevelToDifficultyStartAt() + 1));
		this->m_player->SetLevelToStartAt(1);
	}
	else
	{
		if ((this->m_player->GetLevelToStartAt()) == m_maxlevel)
		{
			this->m_player->SetLevelToDifficultyStartAt((this->m_player->GetLevelToDifficultyStartAt() + 1));
			this->m_player->SetLevelToStartAt(1);
		}
		else
			this->m_player->SetLevelToStartAt((this->m_player->GetLevelToStartAt() + 1));
	}
}

void SceneManagerLevel2DforScreen::ResetPlayer()
{
	this->m_player->SetLevelToDifficultyStartAt(NULL);
	this->m_player->SetLevelToStartAt(NULL);
	this->m_player->SetLevelStopAt(NULL, NULL);
}

void SceneManagerLevel2DforScreen::SetLevelDifficulty(int LevelDifficulty)
{
	this->m_player->SetLevelToDifficultyStartAt(LevelDifficulty);
}
void SceneManagerLevel2DforScreen::SetLevelNumber(int LevelNumber)
{
	if (this->m_player->GetLevelToDifficultyStartAt() == 1)
		this->m_player->SetLevelToStartAt(1);
	else
		this->m_player->SetLevelToStartAt(LevelNumber);
}

void SceneManagerLevel2DforScreen::SetContinuedLevel()
{
	this->m_player->SetLevelToDifficultyStartAt(m_player->GetLevelDifficultyStopAt());
	this->m_player->SetLevelToStartAt(m_player->GetLevelStopAt());
}
int SceneManagerLevel2DforScreen::GetLevelReferencetoContinue()
{
	return this->m_player->GetLevelStopAt();
}
void SceneManagerLevel2DforScreen::SetChangeScreen(bool m_ChangeScreen)
{
	this->m_ChangeScreen = m_ChangeScreen;
}
void SceneManagerLevel2DforScreen::SetSelection(short m_select)
{
	this->m_select = m_select;
}
void SceneManagerLevel2DforScreen::SetScreenTransition(bool m_ScreenTransition)
{
	this->m_ScreenTransition = m_ScreenTransition;
}
bool SceneManagerLevel2DforScreen::ReturnScreenTransition()
{
	return this->m_ScreenTransition;
}
bool SceneManagerLevel2DforScreen::ReturnChangeScreen()
{
	return this->m_ChangeScreen;
}

void SceneManagerLevel2DforScreen::SetShopSelect(int shopSelect)
{
	this->m_shop->Buy(shopSelect);
}

void SceneManagerLevel2DforScreen::SetShopSelectItem(int shopSelectItem)
{
	this->m_shop->BuyItem(shopSelectItem);
}

void SceneManagerLevel2DforScreen::SetParticleStyle(Particle *ParticleVector, int ParticleStyle)
{

	if (ParticleStyle == PARTICLE_STYLE::DROPDOWN)
		ParticleVector->ParticleInit(10, 0, m_windowHeight, PARTICLE_STYLE::DROPDOWN);
	else if (ParticleStyle == PARTICLE_STYLE::CONFETTI && confettiRightside == false)
	{
		ParticleVector->ParticleInit(10, m_windowWidth * 0.125, m_windowHeight* 0.5, PARTICLE_STYLE::CONFETTI);
		confettiRightside = true;
	}
	else if (ParticleStyle == PARTICLE_STYLE::CONFETTI && confettiRightside)
	{
		ParticleVector->ParticleInit(10, m_windowWidth * 0.875, m_windowHeight* 0.5, PARTICLE_STYLE::CONFETTI);
		ParticleVector->SetConfettiRightSide(confettiRightside);
	}

}

void SceneManagerLevel2DforScreen::SetSpriteAnimation(Particle *ParticleVector, int SAIndex)
{
	meshList[GEO_SPRITE_ANIMATION] = MeshBuilder::GenerateSpriteAnimation("star", Color(), m_SpriteAnimationLoad->get<int>("StarRow"), m_SpriteAnimationLoad->get<int>("StarCol"));
	meshList[GEO_SPRITE_ANIMATION]->textureID = LoadTGA("Image//StarSprite.tga");
	m_spriteAnimation = dynamic_cast<SpriteAnimation*>(meshList[GEO_SPRITE_ANIMATION]);
	m_spriteAnimation->m_anim = new Animation();
	if (m_spriteAnimation)
	{
		m_spriteAnimation->m_anim->Set(0, 18, 0, Math::RandFloatMinMax((m_SpriteAnimationLoad->get<float>("StarMinTime")), (m_SpriteAnimationLoad->get<float>("StarMaxTime"))));
		if (ParticleVector->Getparticlestyle() == PARTICLE_STYLE::DROPDOWN)
		{
			m_spriteAnimation->x = m_spriteAnimation->x + Math::RandIntMinMax(m_windowWidth*0.125, m_windowWidth - m_windowWidth*0.125);//64;
			m_spriteAnimation->y = ParticleVector->GetY() + Math::RandIntMinMax(m_windowWidth*0.125, m_windowWidth*0.25);
			m_spriteAnimation->speed = Math::RandIntMinMax(m_windowWidth*0.125, m_windowWidth);
			m_spriteAnimation->index = SAIndex;
			ParticleVector->SpritePushBack(m_spriteAnimation, 0, 0);
		}
		else if (ParticleVector->Getparticlestyle() == PARTICLE_STYLE::CONFETTI)
		{
			m_spriteAnimation->x = ParticleVector->GetX();
			m_spriteAnimation->y = ParticleVector->GetY();
			m_spriteAnimation->speed = Math::RandIntMinMax(m_windowWidth*0.125, m_windowWidth);
			m_spriteAnimation->index = SAIndex;
			ParticleVector->SpritePushBack(m_spriteAnimation, m_spriteAnimation->y + Math::RandIntMinMax(0, m_windowWidth*0.125 + m_windowWidth*0.25), m_windowWidth*0.5);
		}
	}
}

void SceneManagerLevel2DforScreen::setHSDifficulty(int theDifficulty)
{
	this->theDifficulty = theDifficulty;
}
void SceneManagerLevel2DforScreen::setHSLevel(int theLevel)
{
	this->theLevel = theLevel;
}

int SceneManagerLevel2DforScreen::getHSDifficulty()
{
	return this->theDifficulty;
}
int SceneManagerLevel2DforScreen::getHSLevel()
{
	return this->theLevel;
}

void SceneManagerLevel2DforScreen::setDifficultyButton(bool theDifficultyButton)
{
	this->theDifficultyButton = theDifficultyButton;
}
bool SceneManagerLevel2DforScreen::getDifficultyButton()
{
	return this->theDifficultyButton;
}
void SceneManagerLevel2DforScreen::setLevelButton(bool theLevelButton)
{
	this->theLevelButton = theLevelButton;
}
bool SceneManagerLevel2DforScreen::getLevelButton()
{
	return this->theLevelButton;
}
void SceneManagerLevel2DforScreen::setHighscoreDisplay(bool DisplayHighscore)
{
	this->DisplayHighscore = DisplayHighscore;
}
bool SceneManagerLevel2DforScreen::getHighscoreDisplay()
{
	return this->DisplayHighscore;
}

void SceneManagerLevel2DforScreen::setLevelButtonSelection(int theLevelButtonSelection)
{
	this->theLevelButtonSelection = theLevelButtonSelection;
}
int SceneManagerLevel2DforScreen::getLevelButtonSelection()
{
	return this->theLevelButtonSelection;
}

void SceneManagerLevel2DforScreen::Update(double dt)
{
	//cout << m_player->GetAmtOfClearedLevelEasy() << " " << m_player->GetAmtOfClearedLevelNormal() << " " << m_player->GetAmtOfClearedLevelHard();
	if (Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (int i = 0; i < theButtonHolder.size(); ++i)
	{
		theButtonHolder[i]->update(dt);
	}

	if (m_screenvalue == Winscreen)
	{
		m_particle->Update(dt);
		m_particle2->Update(dt);
	}

	if (m_ScreenTransition && m_ChangeScreen)
	{
		m_alpha -= 0.04f;
		if (m_alpha < 0)
			m_ScreenTransition = false;
	}
	else if (m_ScreenTransition)
	{
		m_alpha += 0.04f;
		if (m_alpha >= 1.0f)
			m_ScreenTransition = false;
	}


	rotateAngle -= (float)Application::camera_yaw;// += (float)(10 * dt);

	//cout << Sound.volume << endl;

	camera.Update(dt);
	/*

	// Update the hero
	if(Application::IsKeyPressed('W'))
	this->theHero->MoveUpDown( true, 1.0f );
	if(Application::IsKeyPressed('S'))
	this->theHero->MoveUpDown( false, 1.0f );
	if(Application::IsKeyPressed('A'))
	this->theHero->MoveLeftRight( true, 1.0f );
	if(Application::IsKeyPressed('D'))
	this->theHero->MoveLeftRight( false, 1.0f );
	if(Application::IsKeyPressed(' '))
	this->theHero->SetToJumpUpwards(true);
	theHero->HeroUpdate(m_cMap);
	*/


	fps = (float)(1.f / dt);
}

/********************************************************************************
 Update Camera position
 ********************************************************************************/
void SceneManagerLevel2DforScreen::UpdateCameraStatus(const unsigned char key, const bool status)
{
	//camera.UpdateStatus(key, status);

	// Update avatar position
}

/********************************************************************************
 Update Weapon status
 ********************************************************************************/
void SceneManagerLevel2DforScreen::UpdateMouseStatus(const unsigned char key)
{
}

/********************************************************************************
 Render text onto the screen
 ********************************************************************************/
void SceneManagerLevel2DforScreen::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, bool enablealpha)
{
	if (!mesh || mesh->textureID <= 0)
		return;

	Mtx44 ortho;
	ortho.SetToOrtho(0, 800, 0, 600, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	if (enablealpha == true)
	{
		glUniform1i(m_parameters[U_TEXT_ALPHA_ENABLED], 1);
		glUniform4fv(m_parameters[U_TEXT_ALPHA], 1, &color.r);
	}
	else
	{
		glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
		glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	}

	//glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	//glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	//	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation((i*0.5f) + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
}

/********************************************************************************
 Render 2D Mesh
 ********************************************************************************/
void SceneManagerLevel2DforScreen::Render2DMesh(Mesh *mesh, bool enableLight, bool enablealpha, float size, int x, int y, bool rotate, bool flip)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 800, 0, 600, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate((float)x, (float)y, 0);
	modelStack.Scale((float)size, (float)size, (float)size);
	if (rotate)
		modelStack.Rotate(rotateAngle, 0, 0, 1);

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		if (enablealpha == false)
		{
			glUniform1i(m_parameters[U_TEXT_ALPHA_ENABLED], 0);
		}
		else
		{
			glUniform1i(m_parameters[U_TEXT_ALPHA_ENABLED], 1);
		}
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
}
/********************************************************************************
 Render this scene
 ********************************************************************************/
void SceneManagerLevel2DforScreen::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	switch (m_screenvalue)
	{
	case Menuscreen:
	{
					   RenderMainMenu();
					   break;
	}
	case Instructionscreen:
	{
							  RenderInstructions();
							  break;
	}
	case Highscorescreen:
	{
							RenderHighscore();
							break;
	}
	case Optionscreen:
	{
						 RenderOption();
						 break;
	}
	case LevelShopSelectionscreen:
	{
									 RenderLevelShopSelect();
									 break;
	}
	case Shopscreen:
	{
					   RenderShop();
					   break;
	}
	case LevelSelectscreen:
	{
							  RenderLevelSelect();
							  break;
	}
	case Pausescreen:
	{
						RenderPause();
						break;
	}
	case Winscreen:
	{
					  RenderWin();
					  break;
	}
	case DifficultySelectscreen:
	{
								   RenderDifficulty();
								   break;
	}
	}
}


/********************************************************************************
Render Mainmenu Screen
********************************************************************************/
void SceneManagerLevel2DforScreen::RenderMainMenu()
{
	modelStack.PushMatrix();
	Render2DMesh(meshList[GEO_MENU], false, true);
	Render2DMesh(meshList[GEO_MENU_PLAY], false, true, 1, theButtonHolder[0]->getTempPosition().x, theButtonHolder[0]->getTempPosition().y);
	Render2DMesh(meshList[GEO_MENU_INSTRUCTION], false, true, 1, theButtonHolder[1]->getTempPosition().x, theButtonHolder[1]->getTempPosition().y);
	Render2DMesh(meshList[GEO_MENU_HIGHSCORE], false, true, 1, theButtonHolder[2]->getTempPosition().x, theButtonHolder[2]->getTempPosition().y);
	Render2DMesh(meshList[GEO_MENU_OPTION], false, true, 1, theButtonHolder[3]->getTempPosition().x, theButtonHolder[3]->getTempPosition().y);
	Render2DMesh(meshList[GEO_MENU_EXIT], false, true, 1, theButtonHolder[4]->getTempPosition().x, theButtonHolder[4]->getTempPosition().y);
	if (m_select >= 0)
		Render2DMesh(meshList[GEO_SELECT], false, true, 1, theButtonHolder[m_select - 1]->getPosition().x - theButtonHolder[m_select - 1]->getOffset().x, theButtonHolder[m_select - 1]->getPosition().y - theButtonHolder[m_select - 1]->getOffset().y);
	modelStack.PopMatrix();

	RenderTextOnScreen(meshList[GEO_TEXT], "", Color(1, 1, 1, m_alpha), 30, 0, 6, true);
}


/********************************************************************************
Render Instructions Screen
********************************************************************************/
void SceneManagerLevel2DforScreen::RenderInstructions()
{
	modelStack.PushMatrix();
	Render2DMesh(meshList[GEO_INSTRUCTION], false, true);
	RenderTextOnScreen(meshList[GEO_TEXT], "", Color(1, 1, 1, m_alpha), 30, 0, 6, true);
	modelStack.PopMatrix();
}


/********************************************************************************
Render Highscore Screen
********************************************************************************/
void SceneManagerLevel2DforScreen::RenderHighscore()
{
	modelStack.PushMatrix();
	Render2DMesh(meshList[GEO_HIGHSCORE], false, true);
	if (getDifficultyButton() == true)
	{
		Render2DMesh(meshList[GEO_HIGHSCORE_TUTORIAL], false, true, 1, theButtonHolder[0]->getTempPosition().x, theButtonHolder[0]->getTempPosition().y);		// Tutorial Select
		Render2DMesh(meshList[GEO_HIGHSCORE_EASY], false, true, 1, theButtonHolder[1]->getTempPosition().x, theButtonHolder[1]->getTempPosition().y);		// Easy Select
		Render2DMesh(meshList[GEO_HIGHSCORE_NORMAL], false, true, 1, theButtonHolder[2]->getTempPosition().x, theButtonHolder[2]->getTempPosition().y);		// Normal Select
		Render2DMesh(meshList[GEO_HIGHSCORE_HARD], false, true, 1, theButtonHolder[3]->getTempPosition().x, theButtonHolder[3]->getTempPosition().y);		// Hard Select

		if (m_select >= 0)
			Render2DMesh(meshList[GEO_SELECT], false, true, 1, theButtonHolder[m_select - 1]->getPosition().x - theButtonHolder[m_select - 1]->getOffset().x, theButtonHolder[m_select - 1]->getPosition().y - theButtonHolder[m_select - 1]->getOffset().y);
	}
	else if (getLevelButton() == true)
	{
		Render2DMesh(meshList[GEO_HIGHSCORE_LEVEL1], false, true, 1, theButtonHolder[4]->getTempPosition().x, theButtonHolder[4]->getTempPosition().y);
		Render2DMesh(meshList[GEO_HIGHSCORE_LEVEL2], false, true, 1, theButtonHolder[5]->getTempPosition().x, theButtonHolder[5]->getTempPosition().y);
		Render2DMesh(meshList[GEO_HIGHSCORE_LEVEL3], false, true, 1, theButtonHolder[6]->getTempPosition().x, theButtonHolder[6]->getTempPosition().y);
		Render2DMesh(meshList[GEO_HIGHSCORE_LEVEL4], false, true, 1, theButtonHolder[7]->getTempPosition().x, theButtonHolder[7]->getTempPosition().y);

		if (theLevelButtonSelection >= 0)
			Render2DMesh(meshList[GEO_SELECT], false, true, 1, theButtonHolder[theLevelButtonSelection + 3]->getPosition().x - theButtonHolder[theLevelButtonSelection + 3]->getOffset().x, theButtonHolder[theLevelButtonSelection + 3]->getPosition().y - theButtonHolder[theLevelButtonSelection + 3]->getOffset().y);
	}
	else if (getHighscoreDisplay() == true)
	{
		GetHighscore();
		std::ostringstream ss;
		const int size = 5;
		for (int i = 0; i < size; i++)
		{
		ss.str(std::string());
		ss << i + 1 << ". " << theScore.GetAllHighscores(i);
		RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 0, 1, m_alpha), 60, 300, 300 - (i * 40), true);
		}
	}
	modelStack.PopMatrix();
	Render2DMesh(meshList[GEO_BACKTOEXIT], false, true, 1, 100, 50);
	RenderTextOnScreen(meshList[GEO_TEXT], "", Color(1, 1, 1, m_alpha), 30, 0, 6, true);
	
}


/********************************************************************************
Render Option Screen
********************************************************************************/
void SceneManagerLevel2DforScreen::RenderOption()
{
	modelStack.PushMatrix();
	Render2DMesh(meshList[GEO_SOUND], false, true);

	if (SoundSelect && !muted)
	{
		Render2DMesh(meshList[GEO_SOUND], false, true);
	}
	else if (SoundSelect && muted)
	{
		Render2DMesh(meshList[GEO_SOUND_MUTE], false, true);
	}
	else if (VolumeSelect && !muted)
	{
		Render2DMesh(meshList[GEO_VOL], false, true);
	}
	else if (VolumeSelect && muted)
	{
		Render2DMesh(meshList[GEO_VOL_MUTE], false, true);
	}

	/*std::ostringstream ssVol;
	ssVol << tempsound;
	RenderTextOnScreen(meshList[GEO_TEXT], ssVol.str(), Color(1, 0, 0), 80, 450, 180, true);*/

	RenderTextOnScreen(meshList[GEO_TEXT], "", Color(1, 1, 1, m_alpha), 30, 0, 6, true);

	for (int i = 0; i < (int)(tempsound * 10); i++)
	{
		Render2DMesh(meshList[GEO_VOL_BAR], false, true, 1, 440 + i * 30, 215);
	}
	Render2DMesh(meshList[GEO_BACKTOEXIT], false, true, 1, 100, 50);
	RenderTextOnScreen(meshList[GEO_TEXT], "", Color(1, 1, 1, m_alpha), 30, 0, 6, true);
	modelStack.PopMatrix();
}


/********************************************************************************
Render LevelShopSelect Screen
********************************************************************************/
void SceneManagerLevel2DforScreen::RenderLevelShopSelect()
{
	modelStack.PushMatrix();
	Render2DMesh(meshList[GEO_LEVELSHOPSELECT], false, true);
	Render2DMesh(meshList[GEO_LEVELSHOPSELECT_LEVELSELECT], false, true, 1, theButtonHolder[0]->getTempPosition().x, theButtonHolder[0]->getTempPosition().y);
	Render2DMesh(meshList[GEO_LEVELSHOPSELECT_SHOP], false, true, 1, theButtonHolder[1]->getTempPosition().x, theButtonHolder[1]->getTempPosition().y);
	Render2DMesh(meshList[GEO_LEVELSHOPSELECT_CONTINUELEVEL], false, true, 1, theButtonHolder[2]->getTempPosition().x, theButtonHolder[2]->getTempPosition().y);
	if (m_select >= 0)
		Render2DMesh(meshList[GEO_SELECT], false, true, 1, theButtonHolder[m_select - 1]->getPosition().x - theButtonHolder[m_select - 1]->getOffset().x, theButtonHolder[m_select - 1]->getPosition().y - theButtonHolder[m_select - 1]->getOffset().y);
	modelStack.PopMatrix();

	if (m_select == 3)
	{
		if (m_player->GetLevelStopAt() == 0)
			RenderTextOnScreen(meshList[GEO_TEXT], "There is No Level to continue", Color(1, 0, 0), 30, 200, 110, true);
		else
		{
			string Diff = "";
			switch (m_player->GetLevelDifficultyStopAt())
			{
			case 1:
			{ Diff = "Easy"; break; }
			case 2:
			{Diff = "Normal"; break; }
			case 3:
			{Diff = "Hard"; break; }
			}
			RenderTextOnScreen(meshList[GEO_TEXT], "Continue Level?", Color(1, 0, 0), 30, theButtonHolder[2]->getPosition().x, 170, true);
			string StringDiff = "Difficulty:" + Diff;
			RenderTextOnScreen(meshList[GEO_TEXT], StringDiff, Color(1, 0, 0), 30, theButtonHolder[2]->getPosition().x, 140, true);
			string StringLevel = "Level:" + to_string(m_player->GetLevelStopAt());
			RenderTextOnScreen(meshList[GEO_TEXT], StringLevel, Color(1, 0, 0), 30, theButtonHolder[2]->getPosition().x, 110, true);
		}
			
	}
	Render2DMesh(meshList[GEO_BACKTOEXIT], false, true, 1, 100, 50);
	RenderTextOnScreen(meshList[GEO_TEXT], "", Color(1, 1, 1, m_alpha), 30, 0, 6, true);
}


/********************************************************************************
Render Shop Screen
********************************************************************************/
void SceneManagerLevel2DforScreen::RenderShop()
{
	modelStack.PushMatrix();
	Render2DMesh(meshList[GEO_SHOP], false, true);
	modelStack.PopMatrix();

	string notUnlocked = "Level is still locked";
	string Insufficient = "Insufficient Funds to purchase";

	switch (m_select)
	{
		case 1:
		{
			modelStack.PushMatrix();
			Render2DMesh(meshList[GEO_SELECT], false, true, 1, 70, 401 - m_select * 76);
			if (!m_shop->GetplayerEasyModeUnlocked())
			{
				RenderTextOnScreen(meshList[GEO_TEXT], notUnlocked, Color(1, 0, 0), 30, 200, 110, true);
			}
			else if (!m_shop->theItemHolder[m_select - 1]->GetBought() && m_shop->GetPlayerMoney() < m_shop->theItemHolder[m_select - 1]->GetPrice())
			{
				RenderTextOnScreen(meshList[GEO_TEXT], Insufficient, Color(1, 0, 0), 30, 200, 110, true);
			}
			modelStack.PopMatrix();
			break;
		}
		case 2:
		{
			modelStack.PushMatrix();
			Render2DMesh(meshList[GEO_SELECT], false, true, 1, 70, 401 - m_select * 76);
			if (!m_shop->GetplayerNormalModeUnlocked())
			{
				RenderTextOnScreen(meshList[GEO_TEXT], notUnlocked, Color(1, 0, 0), 30, 200, 110, true);
			}
			else if (!m_shop->theItemHolder[m_select - 1]->GetBought() && m_shop->GetPlayerMoney() < m_shop->theItemHolder[m_select - 1]->GetPrice())
			{
				RenderTextOnScreen(meshList[GEO_TEXT], Insufficient, Color(1, 0, 0), 30, 200, 110, true);
			}
			modelStack.PopMatrix();
			break;
		}
		case 3:
		{
			modelStack.PushMatrix();
			Render2DMesh(meshList[GEO_SELECT], false, true, 1, 70, 401 - m_select * 76);
			if (!m_shop->GetplayerHardModeUnlocked())
			{
				RenderTextOnScreen(meshList[GEO_TEXT], notUnlocked, Color(1, 0, 0), 30, 200, 110, true);
			}
			else if (!m_shop->theItemHolder[m_select - 1]->GetBought() && m_shop->GetPlayerMoney() < m_shop->theItemHolder[m_select - 1]->GetPrice())
			{
				RenderTextOnScreen(meshList[GEO_TEXT], Insufficient, Color(1, 0, 0), 30, 200, 110, true);
			}
			modelStack.PopMatrix();
			break;
		}
		case 4:
		{
			modelStack.PushMatrix();
			Render2DMesh(meshList[GEO_SELECT], false, true, 1, 420, 629 - m_select * 76);
			if (!m_shop->theItemHolder[m_select - 1]->GetBought() && m_shop->GetPlayerGold() < m_shop->theItemHolder[m_select - 1]->GetPrice())
			{
				RenderTextOnScreen(meshList[GEO_TEXT], Insufficient, Color(1, 0, 0), 30, 200, 110, true);
			}
			modelStack.PopMatrix();
			break;
		}
		case 5:
		{
			modelStack.PushMatrix();
			Render2DMesh(meshList[GEO_SELECT], false, true, 1, 420, 629 - m_select * 76);
			if (!m_shop->theItemHolder[m_select - 1]->GetBought() && m_shop->GetPlayerGold() < m_shop->theItemHolder[m_select - 1]->GetPrice())
			{
				RenderTextOnScreen(meshList[GEO_TEXT], Insufficient, Color(1, 0, 0), 30, 200, 110, true);
			}
			modelStack.PopMatrix();
			break;
		}
	}

	RenderTextOnScreen(meshList[GEO_TEXT], "Levels", Color(0, 0, 1), 50, 150, 400, true);
	RenderTextOnScreen(meshList[GEO_TEXT], "Items", Color(0, 0, 1), 50, 500, 400, true);
	Render2DMesh(meshList[GEO_BOMB], false, false, 1, 550, 470);
	Render2DMesh(meshList[GEO_BRIDGE], false, false, 1, 620, 470);

	for (int i = 0; i < m_shop->theItemHolder.size(); i++)
	{
		if (i <= 2)
		{
			modelStack.PushMatrix();
			string Naming = "Name: " + m_shop->theItemHolder[i]->GetName();
			RenderTextOnScreen(meshList[GEO_TEXT], Naming, Color(0, 0, 0), 30, 150, (330 - i * 75), true);
			string pricing = "Cost: " + std::to_string(m_shop->theItemHolder[i]->GetPrice());
			RenderTextOnScreen(meshList[GEO_TEXT], pricing, Color(0, 0, 0), 30, 150, (310 - i * 75), true);
			if (m_shop->theItemHolder[i]->GetBought())
				RenderTextOnScreen(meshList[GEO_TEXT], "Bought", Color(0, 1, 0), 30, 150, (290 - i * 75), true);
			else
				RenderTextOnScreen(meshList[GEO_TEXT], "Not Bought", Color(1, 0, 0), 30, 150, (290 - i * 75), true);
			modelStack.PopMatrix();
		}
		else if (i == 3)
		{
			modelStack.PushMatrix();
			string Naming = "Name: " + m_shop->theItemHolder[i]->GetName();
			RenderTextOnScreen(meshList[GEO_TEXT], Naming, Color(0, 0, 0), 30, 500, (555 - i * 75), true);
			string pricing = "Cost: " + std::to_string(m_shop->theItemHolder[i]->GetPrice());
			RenderTextOnScreen(meshList[GEO_TEXT], pricing, Color(0, 0, 0), 30, 500, (535 - i * 75), true);
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(m_shop->GetPlayerBomb()), Color(0, 0, 0), 30, 580, 450, true);
			modelStack.PopMatrix();
		}
		else if (i == 4)
		{
			modelStack.PushMatrix();
			string Naming = "Name: " + m_shop->theItemHolder[i]->GetName();
			RenderTextOnScreen(meshList[GEO_TEXT], Naming, Color(0, 0, 0), 30, 500, (555 - i * 75), true);
			string pricing = "Cost: " + std::to_string(m_shop->theItemHolder[i]->GetPrice());
			RenderTextOnScreen(meshList[GEO_TEXT], pricing, Color(0, 0, 0), 30, 500, (535 - i * 75), true);
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(m_shop->GetPlayerBridge()), Color(0, 0, 0), 30, 660, 450, true);
			modelStack.PopMatrix();
		}

	}
	string currentAmt = "Keys: " + std::to_string(m_shop->GetPlayerMoney());
	string currentGold = "Gold: " + std::to_string(m_shop->GetPlayerGold());
	RenderTextOnScreen(meshList[GEO_TEXT], currentAmt, Color(0, 0, 1), 30, 100, 510, true);
	RenderTextOnScreen(meshList[GEO_TEXT], currentGold, Color(0, 0, 1), 30, 100, 480, true);
	Render2DMesh(meshList[GEO_BACKTOEXIT], false, true, 1, 100, 50);
	RenderTextOnScreen(meshList[GEO_TEXT], "", Color(1, 1, 1, m_alpha), 30, 0, 6, true);
}


/********************************************************************************
Render LevelSelect Screen
********************************************************************************/
void SceneManagerLevel2DforScreen::RenderLevelSelect()
{
	modelStack.PushMatrix();
	Render2DMesh(meshList[GEO_LEVELSHOPSELECT], false, true);
	Render2DMesh(meshList[GEO_LEVELSELECT_LEVEL1], false, true, 1, theButtonHolder[0]->getTempPosition().x, theButtonHolder[0]->getTempPosition().y);
	if (m_player->GetLevelToDifficultyStartAt() != 1)
	{
		Render2DMesh(meshList[GEO_LEVELSELECT_LEVEL2], false, true, 1, theButtonHolder[1]->getTempPosition().x, theButtonHolder[1]->getTempPosition().y);
		Render2DMesh(meshList[GEO_LEVELSELECT_LEVEL3], false, true, 1, theButtonHolder[2]->getTempPosition().x, theButtonHolder[2]->getTempPosition().y);
		Render2DMesh(meshList[GEO_LEVELSELECT_LEVEL4], false, true, 1, theButtonHolder[3]->getTempPosition().x, theButtonHolder[3]->getTempPosition().y);
	}
	if (m_select >= 0 && m_player->GetLevelToDifficultyStartAt() != 1)
		Render2DMesh(meshList[GEO_SELECT], false, true, 1, theButtonHolder[m_select - 1]->getPosition().x - theButtonHolder[m_select - 1]->getOffset().x, theButtonHolder[m_select - 1]->getPosition().y - theButtonHolder[m_select - 1]->getOffset().y);
	if (m_select >= 0)
		Render2DMesh(meshList[GEO_SELECT], false, true, 1, theButtonHolder[0]->getPosition().x - theButtonHolder[0]->getOffset().x, theButtonHolder[0]->getPosition().y - theButtonHolder[0]->getOffset().y);
	modelStack.PopMatrix();
	Render2DMesh(meshList[GEO_BACKTOEXIT], false, true, 1, 100, 50);
	RenderTextOnScreen(meshList[GEO_TEXT], "", Color(1, 1, 1, m_alpha), 30, 0, 6, true);
}


/********************************************************************************
Render Pause Screen
********************************************************************************/
void SceneManagerLevel2DforScreen::RenderPause()
{
	modelStack.PushMatrix();
	Render2DMesh(meshList[GEO_PAUSE], false, true);
	Render2DMesh(meshList[GEO_PAUSE_RESUME], false, true, 1, theButtonHolder[0]->getTempPosition().x, theButtonHolder[0]->getTempPosition().y);
	Render2DMesh(meshList[GEO_PAUSE_QUITTOMENU], false, true, 1, theButtonHolder[1]->getTempPosition().x, theButtonHolder[1]->getTempPosition().y);
	if (m_select >= 0)
		Render2DMesh(meshList[GEO_SELECT], false, true, 1, theButtonHolder[m_select - 1]->getPosition().x - theButtonHolder[m_select - 1]->getOffset().x, theButtonHolder[m_select - 1]->getPosition().y - theButtonHolder[m_select - 1]->getOffset().y);
	modelStack.PopMatrix();
	RenderTextOnScreen(meshList[GEO_TEXT], "", Color(1, 1, 1, m_alpha), 30, 0, 6, true);
}


/********************************************************************************
Render Win Screen
********************************************************************************/
void SceneManagerLevel2DforScreen::RenderWin()
{
	modelStack.PushMatrix();
	Render2DMesh(meshList[GEO_WIN], false, true);
	Render2DMesh(meshList[GEO_WIN_NEXTLEVEL], false, true, 1, theButtonHolder[0]->getTempPosition().x, theButtonHolder[0]->getTempPosition().y);
	Render2DMesh(meshList[GEO_PAUSE_QUITTOMENU], false, true, 1, theButtonHolder[1]->getTempPosition().x, theButtonHolder[1]->getTempPosition().y);
	if (m_select >= 0)
		Render2DMesh(meshList[GEO_SELECT], false, true, 1, theButtonHolder[m_select - 1]->getPosition().x - theButtonHolder[m_select - 1]->getOffset().x, theButtonHolder[m_select - 1]->getPosition().y - theButtonHolder[m_select - 1]->getOffset().y);
	modelStack.PopMatrix();

	for (int i = 0; i < m_particle->GetSize(); i++)
	{
		modelStack.PushMatrix();
		Render2DMesh(m_particle->theSpriteHolder[i], false, true, 50, m_particle->theSpriteHolder[i]->x, m_particle->theSpriteHolder[i]->y);
		Render2DMesh(m_particle2->theSpriteHolder[i], false, true, 50, m_particle2->theSpriteHolder[i]->x, m_particle2->theSpriteHolder[i]->y);
		modelStack.PopMatrix();
	}

	RenderTextOnScreen(meshList[GEO_TEXT], "", Color(1, 1, 1, m_alpha), 30, 0, 6, true);
}


/********************************************************************************
Render Difficulty Screen
********************************************************************************/
void SceneManagerLevel2DforScreen::RenderDifficulty()
{
	modelStack.PushMatrix();
	Render2DMesh(meshList[GEO_DIFFICULTYSELECT], false, true);
	Render2DMesh(meshList[GEO_HIGHSCORE_TUTORIAL], false, true, 1, theButtonHolder[0]->getTempPosition().x, theButtonHolder[0]->getTempPosition().y);
	Render2DMesh(meshList[GEO_DIFFICULTY_EASY], false, true, 1, theButtonHolder[1]->getTempPosition().x, theButtonHolder[1]->getTempPosition().y);
	Render2DMesh(meshList[GEO_DIFFICULTY_NORMAL], false, true, 1, theButtonHolder[2]->getTempPosition().x, theButtonHolder[2]->getTempPosition().y);
	Render2DMesh(meshList[GEO_DIFFICULTY_HARD], false, true, 1, theButtonHolder[3]->getTempPosition().x, theButtonHolder[3]->getTempPosition().y);
	if (m_select >= 0)
		Render2DMesh(meshList[GEO_SELECT], false, true, 1, theButtonHolder[m_select - 1]->getPosition().x - theButtonHolder[m_select - 1]->getOffset().x, theButtonHolder[m_select - 1]->getPosition().y - theButtonHolder[m_select - 1]->getOffset().y);
	switch (m_select)
	{
	case 2:
	{
			  if (!m_player->GetEasyLevelUnlocked())
				  RenderTextOnScreen(meshList[GEO_TEXT], "It is not Unlocked yet!", Color(1, 0, 0), 30, 200, 110, true);
			  else if (m_player->GetEasyLevelUnlocked() && !m_shop->theItemHolder[0]->GetBought())
				  RenderTextOnScreen(meshList[GEO_TEXT], "It is not Bought yet!", Color(1, 0, 0), 30, 200, 110, true);
			  break;
	}
	case 3:
	{
			  if (!m_player->GetNormalLevelUnlocked())
				  RenderTextOnScreen(meshList[GEO_TEXT], "It is not Unlocked yet!", Color(1, 0, 0), 30, 200, 110, true);
			  else if (m_player->GetNormalLevelUnlocked() && !m_shop->theItemHolder[1]->GetBought())
				  RenderTextOnScreen(meshList[GEO_TEXT], "It is not Bought yet!", Color(1, 0, 0), 30, 200, 110, true);
			  break;
	}
	case 4:
	{
			  if (!m_player->GetHardLevelUnlocked())
				  RenderTextOnScreen(meshList[GEO_TEXT], "It is not Unlocked yet!", Color(1, 0, 0), 30, 200, 110, true);
			  else if (m_player->GetHardLevelUnlocked() && !m_shop->theItemHolder[2]->GetBought())
				  RenderTextOnScreen(meshList[GEO_TEXT], "It is not Bought yet!", Color(1, 0, 0), 30, 200, 110, true);
			  break;
	}
	}
	modelStack.PopMatrix();
	Render2DMesh(meshList[GEO_BACKTOEXIT], false, true, 1, 100, 50);
	RenderTextOnScreen(meshList[GEO_TEXT], "", Color(1, 1, 1, m_alpha), 30, 0, 6, true);
}


/********************************************************************************
 Exit this scene
 ********************************************************************************/
void SceneManagerLevel2DforScreen::Exit()
{
	if (m_screenvalue == Optionscreen)
		m_save->SaveMusic(tempsound);


	m_save->SaveShop(m_shop);
	m_shop->Set(m_player);
	m_save->SavePlayer(m_player);
	if (m_screenvalue == Winscreen)
	{
		if (m_SpriteAnimationLoad)
		{
			delete m_SpriteAnimationLoad;
			m_SpriteAnimationLoad = NULL;
		}
		if (m_particle)
		{
			delete m_particle;
			m_particle = NULL;
		}
		if (m_particle2)
		{
			delete m_particle2;
			m_particle2 = NULL;
		}
		for (int i = 0; i < NUM_GEOMETRY; ++i)
		{
			if (meshList[i] && i != GEO_SPRITE_ANIMATION)
				delete meshList[i];
		}
	}
	else
	{
		for (int i = 0; i < NUM_GEOMETRY; ++i)
		{
			if (meshList[i])
				delete meshList[i];
		}
	}
	// Cleanup VBO

	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);

}


/*

void SceneManagerLevel2DforScreen::RenderTileMap()
{
int m = 0;
for (int i = 0; i < m_cMap->GetNumOfTiles_Height(); i++)
{
for (int k = 0; k < m_cMap->GetNumOfTiles_Width() + 1; k++)
{
m = tileOffset_x + k;
// If we have reached the right side of the Map, then do not display the extra column of tiles.
if ((tileOffset_x + k) >= m_cMap->getNumOfTiles_MapWidth())
break;
if (m_cMap->theScreenMap[i][m] == 1)
{
Render2DMesh(meshList[GEO_TILEGROUND], false, 1, k*m_cMap->GetTileSize() - theHero->GetMapFineOffset_x(), 575 - i*m_cMap->GetTileSize());
}
else if (m_cMap->theScreenMap[i][m] == 2)
{
Render2DMesh(meshList[GEO_TILETREE], false, 1, k*m_cMap->GetTileSize() - theHero->GetMapFineOffset_x(), 575 - i*m_cMap->GetTileSize());
}
else if (m_cMap->theScreenMap[i][m] == 10)
{
Render2DMesh(meshList[GEO_TILE_KILLZONE], false, 1, k*m_cMap->GetTileSize() - theHero->GetMapFineOffset_x(), 575 - i*m_cMap->GetTileSize());
}
else if (m_cMap->theScreenMap[i][m] == 11)
{
Render2DMesh(meshList[GEO_TILE_SAFEZONE], false, 1, k*m_cMap->GetTileSize() - theHero->GetMapFineOffset_x(), 575 - i*m_cMap->GetTileSize());
}
}
}

if (theHero->GetAnimationInvert() == false)
{
if (theHero->GetAnimationCounter() == 0)
Render2DMesh(meshList[GEO_TILEHERO_FRAME0], false, 1, theHero->GetPos_x(), theHero->GetPos_y());
else if (theHero->GetAnimationCounter() == 1)
Render2DMesh(meshList[GEO_TILEHERO_FRAME1], false, 1, theHero->GetPos_x(), theHero->GetPos_y());
else if (theHero->GetAnimationCounter() == 2)
Render2DMesh(meshList[GEO_TILEHERO_FRAME2], false, 1, theHero->GetPos_x(), theHero->GetPos_y());
else if (theHero->GetAnimationCounter() == 3)
Render2DMesh(meshList[GEO_TILEHERO_FRAME3], false, 1, theHero->GetPos_x(), theHero->GetPos_y());
else
Render2DMesh(meshList[GEO_TILEHERO_FRAME0], false, 1, theHero->GetPos_x(), theHero->GetPos_y());
}
else
{
if (theHero->GetAnimationCounter() == 0)
Render2DMesh(meshList[GEO_TILEHERO_FRAME0], false, 1, theHero->GetPos_x(), theHero->GetPos_y(), false, true);
else if (theHero->GetAnimationCounter() == 1)
Render2DMesh(meshList[GEO_TILEHERO_FRAME1], false, 1, theHero->GetPos_x(), theHero->GetPos_y(), false, true);
else if (theHero->GetAnimationCounter() == 2)
Render2DMesh(meshList[GEO_TILEHERO_FRAME2], false, 1, theHero->GetPos_x(), theHero->GetPos_y(), false, true);
else if (theHero->GetAnimationCounter() == 3)
Render2DMesh(meshList[GEO_TILEHERO_FRAME3], false, 1, theHero->GetPos_x(), theHero->GetPos_y(), false, true);
else
Render2DMesh(meshList[GEO_TILEHERO_FRAME0], false, 1, theHero->GetPos_x(), theHero->GetPos_y(), false, true);
}

// Render the enemy
int theEnemy_x = theEnemy->GetPos_x() - theHero->GetMapFineOffset_x();
int theEnemy_y = theEnemy->GetPos_y();
if (((theEnemy_x >= 0) && (theEnemy_x<800)) &&
((theEnemy_y >= 0) && (theEnemy_y<600)))
{
Render2DMesh(meshList[GEO_TILEENEMY_FRAME0], false, 1, theEnemy_x, theEnemy_y);
}
}


void SceneManagerLevel2DforScreen::RenderRearTileMap()
{
rearWallOffset_x = (int)(theHero->GetMapOffset_x() / 2);
rearWallOffset_y = 0;
rearWallTileOffset_y = 0;
rearWallTileOffset_x = (int)(rearWallOffset_x / m_cRearMap->GetTileSize());
if (rearWallTileOffset_x + m_cRearMap->GetNumOfTiles_Width() > m_cRearMap->getNumOfTiles_MapWidth())
rearWallTileOffset_x = m_cRearMap->getNumOfTiles_MapWidth() - m_cRearMap->GetNumOfTiles_Width();
rearWallFineOffset_x = rearWallOffset_x % m_cRearMap->GetTileSize();

int m = 0;
for (int i = 0; i < m_cRearMap->GetNumOfTiles_Height(); i++)
{
for (int k = 0; k < m_cRearMap->GetNumOfTiles_Width() + 1; k++)
{
m = rearWallTileOffset_x + k;
// If we have reached the right side of the Map, then do not display the extra column of tiles.
if ((rearWallTileOffset_x + k) >= m_cRearMap->getNumOfTiles_MapWidth())
break;
if (m_cRearMap->theScreenMap[i][m] == 3)
{
Render2DMesh(meshList[GEO_TILESTRUCTURE], false, 1, k*m_cRearMap->GetTileSize() - rearWallFineOffset_x, 575 - i*m_cRearMap->GetTileSize());
}
}
}
}


void SceneManagerLevel2DforScreen::RenderGoodies()
{
// Render the goodies
for (int i = 0; i<10; i++)
{
Render2DMesh(theArrayOfGoodies[i]->GetMesh(), false, 1, theArrayOfGoodies[i]->GetPos_x(), theArrayOfGoodies[i]->GetPos_y());
}
}
*/