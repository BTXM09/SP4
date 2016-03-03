#include "SceneManager2D.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>
#include "Strategy_Kill.h"

CSceneManager2D::CSceneManager2D()
: m_player(NULL)
, m_save(NULL)
, Playfield(NULL)
, Platformer(NULL)
, CurrentLayout(NULL)
, switchStage(false)
, KeysCollected(0)
, tempsound(0.5)
, m_Load(NULL)
, m_cLevel(NULL)
, theLevelDetailsHolder(NULL)
, m_LevelDetails(NULL)
, MoveChar(true)
, ShowStart(false)
, ShowMove(false)
, ShowMonster(false)
, ShowExit(false)
, Sign1Exited(false)
, Sign2Exited(false)
, Sign3Exited(false)
, Sign4Exited(false)
, Sign5Exited(false)
, player_Health(0)
, damage_Buffer(5.f)
{
}

CSceneManager2D::CSceneManager2D(const int m_window_width, const int m_window_height)
: m_player(NULL)
, m_save(NULL)
, Playfield(NULL)
, Platformer(NULL)
, CurrentLayout(NULL)
, switchStage(false)
, KeysCollected(0)
, tempsound(0.5)
, m_Load(NULL)
, m_cLevel(NULL)
, theLevelDetailsHolder(NULL)
, m_LevelDetails(NULL)
, MoveChar(true)
, ShowStart(false)
, ShowMove(false)
, ShowMonster(false)
, ShowExit(false)
, Sign1Exited(false)
, Sign2Exited(false)
, Sign3Exited(false)
, Sign4Exited(false)
, Sign5Exited(false)
, player_Health(0)
, damage_Buffer(5.f)
{
	this->m_windowWidth = m_window_width;
	this->m_windowHeight = m_window_height;
}

CSceneManager2D::~CSceneManager2D()
{
	if (m_player)
	{
		delete m_player;
		m_player = NULL;
	}
	
	if (m_save)
	{
		delete m_save;
		m_save = NULL;
	}

	if (Playfield)
	{
		delete Playfield;
		Playfield = NULL;
	}

	if (Platformer)
	{
		delete Platformer;
		Platformer = NULL;
	}

	if (m_Load)
	{
		delete m_Load;
		m_Load = NULL;
	}

	if (m_cLevel)
	{
		delete m_cLevel;
		m_cLevel = NULL;
	}
	if (m_LevelDetails)
	{
		delete m_LevelDetails;
		m_LevelDetails = NULL;
	}

	if (AIList.size() > 0)
	{
		for (int a = 0; a < AIList.size(); a++)
		{
			delete AIList[a];
		}
		AIList.clear();
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

void CSceneManager2D::PreInit()
{
	// Black background
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

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

void CSceneManager2D::Init()
{
	PreInit();

	// Initialise the camera
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));

	// Create the meshes
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	meshList[GEO_TILEENEMY_FRAME0] = MeshBuilder::Generate2DMesh("GEO_TILEENEMY_FRAME0", Color(1, 1, 1), 0, 0, 50, 50);
	meshList[GEO_TILEENEMY_FRAME0]->textureID = LoadTGA("Image//tile20_enemy.tga");

	meshList[GEO_BACKGROUND]= MeshBuilder::Generate2DMesh("GEO_BACKGROUND", Color(1, 1, 1), 0, 0, 800, 600);
	meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//Background.tga");

	meshList[GEO_MENU] = MeshBuilder::Generate2DMesh("GEO_MENU", Color(1, 1, 1), 0, 0, 800, 600);
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

	meshList[GEO_SELECT] = MeshBuilder::Generate2DMesh("GEO_SELECT", Color(1, 1, 1), 0, 0, 75, 55);
	meshList[GEO_SELECT]->textureID = LoadTGA("Image//Select.tga");

	meshList[GEO_KEYSCOLLECTED] = MeshBuilder::Generate2DMesh("GEO_KEYSCOLLECTED", Color(1, 1, 1), 0, 0, 200, 100);
	meshList[GEO_KEYSCOLLECTED]->textureID = LoadTGA("Image//KeysCollected.tga");
	meshList[GEO_MOVESLEFT] = MeshBuilder::Generate2DMesh("GEO_MOVESLEFT", Color(1, 1, 1), 0, 0, 200, 100);
	meshList[GEO_MOVESLEFT]->textureID = LoadTGA("Image//MovesLeft.tga");
	meshList[GEO_BOMBSLEFT] = MeshBuilder::Generate2DMesh("GEO_BOMBSLEFT", Color(1, 1, 1), 0, 0, 200, 100);
	meshList[GEO_BOMBSLEFT]->textureID = LoadTGA("Image//BombsLeft.tga");
	meshList[GEO_BRIDGESLEFT] = MeshBuilder::Generate2DMesh("GEO_BRIDGESLEFT", Color(1, 1, 1), 0, 0, 200, 100);
	meshList[GEO_BRIDGESLEFT]->textureID = LoadTGA("Image//BridgesLeft.tga");
	meshList[GEO_HEALTHLEFT] = MeshBuilder::Generate2DMesh("GEO_HEALTHLEFT", Color(1, 1, 1), 0, 0, 200, 100);
	meshList[GEO_HEALTHLEFT]->textureID = LoadTGA("Image//HealthLeft.tga");

	meshList[GEO_MOVELOSESIGN] = MeshBuilder::Generate2DMesh("GEO_CHARACTER", Color(1, 1, 1), 0, 0, 400, 200);
	meshList[GEO_MOVELOSESIGN]->textureID = LoadTGA("Image//MovesLoseSign.tga");
	meshList[GEO_HEALTHLOSESIGN] = MeshBuilder::Generate2DMesh("GEO_CHARACTER", Color(1, 1, 1), 0, 0, 400, 200);
	meshList[GEO_HEALTHLOSESIGN]->textureID = LoadTGA("Image//HealthLoseSign.tga");

	meshList[GEO_CHARACTER] = MeshBuilder::Generate2DMesh("GEO_CHARACTER", Color(1, 1, 1), 0, 0, 50, 50);
	meshList[GEO_CHARACTER]->textureID = LoadTGA("Image//Temp.tga");
	meshList[GEO_FLOORING] = MeshBuilder::Generate2DMesh("GEO_FLOORING", Color(1, 1, 1), 0, 0, 50, 50);
	meshList[GEO_FLOORING]->textureID = LoadTGA("Image//Floor.tga");
	meshList[GEO_ROCK] = MeshBuilder::Generate2DMesh("GEO_ROCK", Color(1, 1, 1), 0, 0, 50, 50);
	meshList[GEO_ROCK]->textureID = LoadTGA("Image//Rock.tga");
	meshList[GEO_TRAP] = MeshBuilder::Generate2DMesh("GEO_TRAP", Color(1, 1, 1), 0, 0, 50, 50);
	meshList[GEO_TRAP]->textureID = LoadTGA("Image//Trap.tga");
	meshList[GEO_SNAKE] = MeshBuilder::Generate2DMesh("GEO_SNAKE", Color(1, 1, 1), 0, 0, 50, 50);
	meshList[GEO_SNAKE]->textureID = LoadTGA("Image//Snake.tga");
	meshList[GEO_MONSTER] = MeshBuilder::Generate2DMesh("GEO_MONSTER", Color(1, 1, 1), 0, 0, 50, 50);
	meshList[GEO_MONSTER]->textureID = LoadTGA("Image//Monster.tga");
	meshList[GEO_WALL] = MeshBuilder::Generate2DMesh("GEO_WALL", Color(1, 1, 1), 0, 0, 50, 50);
	meshList[GEO_WALL]->textureID = LoadTGA("Image//Wall.tga");
	meshList[GEO_KEY] = MeshBuilder::Generate2DMesh("GEO_KEY", Color(1, 1, 1), 0, 0, 50, 50);
	meshList[GEO_KEY]->textureID = LoadTGA("Image//Key.tga");
	meshList[GEO_FEET] = MeshBuilder::Generate2DMesh("GEO_FEET", Color(1, 1, 1), 0, 0, 50, 50);
	meshList[GEO_FEET]->textureID = LoadTGA("Image//Feet.tga");
	meshList[GEO_EXIT] = MeshBuilder::Generate2DMesh("GEO_EXIT", Color(1, 1, 1), 0, 0, 50, 50);
	meshList[GEO_EXIT]->textureID = LoadTGA("Image//Exit.tga");
	
	meshList[GEO_BOMBED] = MeshBuilder::Generate2DMesh("GEO_BOMBED", Color(1, 1, 1), 0, 0, 50, 50);
	meshList[GEO_BOMBED]->textureID = LoadTGA("Image//Rock_Bombed.tga");
	
	meshList[GEO_BRIDGED] = MeshBuilder::Generate2DMesh("GEO_BRIDGED", Color(1, 1, 1), 0, 0, 50, 50);
	meshList[GEO_BRIDGED]->textureID = LoadTGA("Image//Bridge.tga");

	meshList[GEO_SIGN] = MeshBuilder::Generate2DMesh("GEO_SIGN", Color(1, 1, 1), 0, 0, 50, 50);
	meshList[GEO_SIGN]->textureID = LoadTGA("Image//Sign.tga");
	meshList[GEO_SIGN1] = MeshBuilder::Generate2DMesh("GEO_SIGN1", Color(1, 1, 1), 0, 0, 260, 230);
	meshList[GEO_SIGN1]->textureID = LoadTGA("Image//Sign1.tga");
	meshList[GEO_SIGN2] = MeshBuilder::Generate2DMesh("GEO_SIGN2", Color(1, 1, 1), 0, 0, 260, 230);
	meshList[GEO_SIGN2]->textureID = LoadTGA("Image//Sign2.tga");
	meshList[GEO_SIGN3] = MeshBuilder::Generate2DMesh("GEO_SIGN3", Color(1, 1, 1), 0, 0, 260, 230);
	meshList[GEO_SIGN3]->textureID = LoadTGA("Image//Sign3.tga");
	meshList[GEO_SIGN4] = MeshBuilder::Generate2DMesh("GEO_SIGN4", Color(1, 1, 1), 0, 0, 260, 230);
	meshList[GEO_SIGN4]->textureID = LoadTGA("Image//Sign4.tga");
	meshList[GEO_SIGN5] = MeshBuilder::Generate2DMesh("GEO_SIGN5", Color(1, 1, 1), 0, 0, 260, 230);
	meshList[GEO_SIGN5]->textureID = LoadTGA("Image//Sign5.tga");
	meshList[GEO_SIGN6] = MeshBuilder::Generate2DMesh("GEO_SIGN6", Color(1, 1, 1), 0, 0, 260, 230);
	meshList[GEO_SIGN6]->textureID = LoadTGA("Image//Sign6.tga");


	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	m_Quitfrompause = false;
	m_WinCondition = 0;
	m_save = new Save();
	m_player = new Player();
	m_player->PlayerInit("Player");
	
	KeysCollected = 0;
	m_LevelDetails = new LevelDetails();
	m_LevelDetails->LevelDetailsInit(m_player->GetLevelToDifficultyStartAt(), m_player->GetLevelToStartAt(), "Level");
	NoOfMoves = m_LevelDetails->GetAmountOfMoves();

	m_Load = new LuaUsage();
	m_Load->LuaUsageInit("LeveltoSave");
	m_maxlevel = m_Load->get<int>("AmountOfLevel");
	m_maxdiff = m_Load->get<int>("AmountOfDiff");
	m_maxleveltutorial = m_Load->get<int>("AmountOfTutorialDiff");
	m_Load->LuaUsageClose();
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

	//level loader
	m_cLevel = new LevelLoader();
	m_cLevel->Init((m_LevelDetails->GetNumberOfGridY() + 1) * m_LevelDetails->GetLengthYOfAGrid(), m_LevelDetails->GetNumberOfGridX() * m_LevelDetails->GetLengthXOfAGrid(), m_LevelDetails->GetNumberOfGridY() + 1, m_LevelDetails->GetNumberOfGridX());
	m_cLevel->LevelLoaded(m_LevelDetails->GetNameOfLevelFile());

	//initailise grid system
	Playfield = new GridSystem();
	// in this order: position of the whole grid system, size of grid x, size of grid y, number of grid x, number of grid y 
	Playfield->Init(Vector3(m_LevelDetails->GetPositionXOfGrid(), m_LevelDetails->GetPositionYOfGrid(), 0), m_LevelDetails->GetLengthXOfAGrid(), m_LevelDetails->GetLengthYOfAGrid(), m_LevelDetails->GetNumberOfGridY(), m_LevelDetails->GetNumberOfGridX());

	Playfield->PlayerGridSetUp(m_LevelDetails->GetPlayerPositionX(), m_LevelDetails->GetPlayerPositionY());

	Playfield->SetMap(m_cLevel->screenMap);

	cAI * AI = new cAI();
	AI->init();
	AI->setPos(8, 1);
	AI->setDifficulty(m_player->GetLevelToDifficultyStartAt());
	AI->setWaypoint(3, 8);
	AI->setWaypoint(3, 3);
	AI->setWaypoint(8, 3);
	AI->setWaypoint(8, 8);
	AIList.push_back(AI);

	Playfield->AIGridSetUp(AIList);
	/*for (int a = 0; a < 11; a++)
	{
		for (int b = 0; b < 10; b++)
		{
			cout << m_cLevel->screenMap[a][b];
		}
		cout << endl;
	}*/
	//direction and offset
	direction = 0.f;
	offset = Vector3(0, 0, 0);

	timeBuffer = 0.f;

	Platformer = new GridSystem();
	Platformer->Init(Vector3(m_LevelDetails->GetPositionXOfGrid(), m_LevelDetails->GetPositionYOfGrid(), 0), m_LevelDetails->GetLengthXOfAGrid(), m_LevelDetails->GetLengthYOfAGrid(), 6, 10);
	Platformer->GridDropInit(KeysCollected);
	Platformer->PlayerGridSetUp(4, 8);

	player_Health = 3;
	m_losed = false;

	CurrentLayout = Playfield;

}

void CSceneManager2D::SetQuitfrompause(bool m_Quitfrompause)
{
	KeysCollected = 0;
	this->m_Quitfrompause = m_Quitfrompause;
	this->m_player->SetLevelStopAt(m_LevelDetails->GetLevelinDifficultyReference(),m_LevelDetails->GetDifficultyReference());
}

void CSceneManager2D::ReadHighscoreText()
{
	// Uncomment tihs for tutorial
	
	if (m_player->GetLevelToDifficultyStartAt() == 1)
	{
	theScore.ReadTextFile("Scores//TutorialHighscore.txt");
	}
	if (m_player->GetLevelToDifficultyStartAt() == 2)
	{
		if (m_player->GetLevelToStartAt() == 1)
			theScore.ReadTextFile("Scores//EasyHighscore1.txt");
		if (m_player->GetLevelToStartAt() == 2)
			theScore.ReadTextFile("Scores//EasyHighscore2.txt");
		if (m_player->GetLevelToStartAt() == 3)
			theScore.ReadTextFile("Scores//EasyHighscore3.txt");
		if (m_player->GetLevelToStartAt() == 4)
			theScore.ReadTextFile("Scores//EasyHighscore4.txt");
	}
	if (m_player->GetLevelToDifficultyStartAt() == 3)
	{
		if (m_player->GetLevelToStartAt() == 1)
			theScore.ReadTextFile("Scores//NormalHighscore1.txt");
		if (m_player->GetLevelToStartAt() == 2)
			theScore.ReadTextFile("Scores//NormalHighscore2.txt");
		if (m_player->GetLevelToStartAt() == 3)
			theScore.ReadTextFile("Scores//NormalHighscore3.txt");
		if (m_player->GetLevelToStartAt() == 4)
			theScore.ReadTextFile("Scores//NormalHighscore4.txt");
	}
	if (m_player->GetLevelToDifficultyStartAt() == 4)
	{
		if (m_player->GetLevelToStartAt() == 1)
			theScore.ReadTextFile("Scores//HardHighscore1.txt");
		if (m_player->GetLevelToStartAt() == 2)
			theScore.ReadTextFile("Scores//HardHighscore2.txt");
		if (m_player->GetLevelToStartAt() == 3)
			theScore.ReadTextFile("Scores//HardHighscore3.txt");
		if (m_player->GetLevelToStartAt() == 4)
			theScore.ReadTextFile("Scores//HardHighscore4.txt");
	}
}

void CSceneManager2D::WriteHighscoreText()
{
	//Uncomment this for Tutorial
	if (m_player->GetLevelToDifficultyStartAt() == 1)
	{
		theScore.WriteTextFile("Scores//TutorialHighscore.txt");
	}
	if (m_player->GetLevelToDifficultyStartAt() == 2)
	{
		if (m_player->GetLevelToStartAt() == 1)
			theScore.WriteTextFile("Scores//EasyHighscore1.txt");
		if (m_player->GetLevelToStartAt() == 2)
			theScore.WriteTextFile("Scores//EasyHighscore2.txt");
		if (m_player->GetLevelToStartAt() == 3)
			theScore.WriteTextFile("Scores//EasyHighscore3.txt");
		if (m_player->GetLevelToStartAt() == 4)
			theScore.WriteTextFile("Scores//EasyHighscore4.txt");
	}
	if (m_player->GetLevelToDifficultyStartAt() == 3)
	{
		if (m_player->GetLevelToStartAt() == 1)
			theScore.WriteTextFile("Scores//NormalHighscore1.txt");
		if (m_player->GetLevelToStartAt() == 2)
			theScore.WriteTextFile("Scores//NormalHighscore2.txt");
		if (m_player->GetLevelToStartAt() == 3)
			theScore.WriteTextFile("Scores//NormalHighscore3.txt");
		if (m_player->GetLevelToStartAt() == 4)
			theScore.WriteTextFile("Scores//NormalHighscore4.txt");
	}
	if (m_player->GetLevelToDifficultyStartAt() == 4)
	{
		if (m_player->GetLevelToStartAt() == 1)
			theScore.WriteTextFile("Scores//HardHighscore1.txt");
		if (m_player->GetLevelToStartAt() == 2)
			theScore.WriteTextFile("Scores//HardHighscore2.txt");
		if (m_player->GetLevelToStartAt() == 3)
			theScore.WriteTextFile("Scores//HardHighscore3.txt");
		if (m_player->GetLevelToStartAt() == 4)
			theScore.WriteTextFile("Scores//HardHighscore4.txt");
	}
}

void CSceneManager2D::AddHighscore()
{
	const int MAX_SCORES = 5;

	for (int i = 0; i < 1; i++)
	{
		ReadHighscoreText();
		PrevScore.addScore(theScore.GetAllHighscores(i)); // Store all the highscores from the text file to PrevScore
		theScore.setPlayer(PrevScore); // set the previous scores into the player current score
	}

	for (int i = 0; i < MAX_SCORES; i++)
	{
		if (PrevScore.getScore() < PlayerScore.getScore()) // if the scores stored in the prev score is less than the player's newscore
		{
			theScore.UpdateHighscore(PlayerScore); // take in the player score
		}

		if (PrevScore.getScore() > PlayerScore.getScore()) // if the scores stored in prev score is more than player's newscore
		{
			theScore.UpdateHighscore(PlayerScore); // take in the player score anyway to check if it's bigger than the other variables
		}	

		if (PrevScore.getScore() == PlayerScore.getScore()) // if the scores stored in prev score is more than player's newscore
		{
			theScore.UpdateHighscore(PlayerScore); // take in the player score anyway to check if it's bigger than the other variables
		}
	}

	WriteHighscoreText();
}

void CSceneManager2D::SetScoreToGold(int ScoreToGold)
{
	this->ScoreToGold = ScoreToGold; // let the variable be the inputed score
	this->ScoreToGold = this->ScoreToGold + NoOfMoves; // multiply that inputed score with the no of moves
	this->ScoreToGold = this->ScoreToGold + (KeysCollected * 10); // add the no of key collected and multiply each key with 10
	this->ScoreToGold = this->ScoreToGold + this->player_Health;

}

int CSceneManager2D::GetScoreToGold()
{
	return this->ScoreToGold;
}
bool CSceneManager2D::GetLoseCondition()
{
	return this->m_losed;
}
int CSceneManager2D::GetWinCondition()
{
	return this->m_WinCondition;
}

void CSceneManager2D::Update(double dt)
{
	if(Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	int TempKeyCollectedCalc = 0;
	int count = 0;
	if (ShowStart == true || ShowKey == true || ShowMove == true || ShowMonster == true || ShowExit == true)
	{
		MoveChar = false;
	}

	if (CurrentLayout == Playfield)
	{
		/*****************************************************************/
		//Playfield stuff
		if (player_Health <= 0 || NoOfMoves <= 0)
		{
			m_WinCondition = -1;
			if (Application::IsKeyPressed(VK_RETURN))
			{
				m_losed = true;
			}
		}

		if (m_WinCondition != 1)
		{
			if (player_Health <= 0 || NoOfMoves <= 0)
			{
				m_WinCondition = -1;
				if (Application::IsKeyPressed(VK_RETURN))
				{
					m_losed = true;
				}
			}
		}

		if (m_WinCondition != -1)
		{
			for (int a = 0; a < CurrentLayout->GetGridsVec().size(); a++)
			{

				

			
				this->m_WinCondition = CurrentLayout->CheckCollisionType(Grid::GridType::EXIT, count);

			
				if (Sign1Exited == false)
					this->ShowStart = CurrentLayout->CheckCollisionType(Grid::GridType::INTROSIGN, count);

			
				if (Sign2Exited == false)
					this->ShowMove = CurrentLayout->CheckCollisionType(Grid::GridType::MOVESIGN, count);

				
				if (Sign3Exited == false)
					this->ShowKey = CurrentLayout->CheckCollisionType(Grid::GridType::KEYSIGN, count);

			
				if (Sign4Exited == false)
					this->ShowMonster = CurrentLayout->CheckCollisionType(Grid::GridType::MONSTERSIGN, count);

				
				if (Sign5Exited == false)
					this->ShowExit = CurrentLayout->CheckCollisionType(Grid::GridType::EXITSIGN, count);
			}

			if (Application::IsKeyPressed('X'))
			{
				MoveChar = true;
				if (ShowStart == true)
				{
					Sign1Exited = true;
					ShowStart = false;
				}
				if (ShowMove == true)
				{
					Sign2Exited = true;
					ShowMove = false;
				}
				if (ShowKey == true)
				{
					Sign3Exited = true;
					ShowKey = false;
				}
				if (ShowMonster == true)
				{
					Sign4Exited = true;
					ShowMonster = false;
				}
				if (ShowExit == true)
				{
					Sign5Exited = true;
					ShowExit = false;
				}
			}
			if (damage_Buffer <= 0.f)
			{
				for (int a = 0; a < CurrentLayout->GetAIGrids().size(); a++)
				{
					if (CurrentLayout->GetPlayerGrid() == CurrentLayout->GetAIGrids()[a])
					{
						player_Health--;
						damage_Buffer = 5.0f;
						cout << "player health" << player_Health << endl;
					}
				}
			}
			else
				damage_Buffer -= 0.1f;
		}

		if (m_WinCondition == 1)
		{
			if (m_player->GetLevelToDifficultyStartAt() == 1)
			{
				if (m_player->GetLevelToStartAt() == 1)
					SetScoreToGold(10);
				if (m_player->GetLevelToStartAt() == 2)
					SetScoreToGold(20);
				if (m_player->GetLevelToStartAt() == 3)
					SetScoreToGold(30);
				if (m_player->GetLevelToStartAt() == 4)
					SetScoreToGold(40);
			}
			if (m_player->GetLevelToDifficultyStartAt() == 2)
			{
				if (m_player->GetLevelToStartAt() == 1)
					SetScoreToGold(50);
				if (m_player->GetLevelToStartAt() == 2)
					SetScoreToGold(60);
				if (m_player->GetLevelToStartAt() == 3)
					SetScoreToGold(70);
				if (m_player->GetLevelToStartAt() == 4)
					SetScoreToGold(80);
			}
			if (m_player->GetLevelToDifficultyStartAt() == 3)
			{
				if (m_player->GetLevelToStartAt() == 1)
					SetScoreToGold(90);
				if (m_player->GetLevelToStartAt() == 2)
					SetScoreToGold(100);
				if (m_player->GetLevelToStartAt() == 3)
					SetScoreToGold(110);
				if (m_player->GetLevelToStartAt() == 4)
					SetScoreToGold(120);
			}
			PlayerScore.addScore(GetScoreToGold());
			AddHighscore();
		}



	

		//playfield
		if (NoOfMoves <= 0)
		{
			MoveChar = false;
			NoOfMoves = 0;
		}

		if (MoveChar == true)
		{
			if (timeBuffer > 5.f)
			{
				char key = 'z';
				if (Application::IsKeyPressed('W'))
				{
					key = 'w';
				}
				else if (Application::IsKeyPressed('S'))
				{
					key = 's';
				}
				else if (Application::IsKeyPressed('A'))
				{
					key = 'a';
				}
				else if (Application::IsKeyPressed('D'))
				{
					key = 'd';
				}
				if (CurrentLayout->PlayerGridUpdate(key))
				{
					timeBuffer = 0.f;
					NoOfMoves--;
					switchStage = false;
				}
			}
			timeBuffer += 1.f;
		}
		/*****************************************************************/
		CurrentLayout->AIGridUpdate();
		cout << "keycollected::     " << CurrentLayout->CheckCollisionType(Grid::GridType::KEY, count) << endl;
		cout << "switchStage::     " << switchStage << endl;

		if (CurrentLayout->CheckCollisionType(Grid::GridType::KEY, count) && !switchStage)
		{


			CurrentLayout = Platformer;
			CurrentLayout->ResetGridDrop(4, 8, KeysCollected);
			switchStage = true;
		}
	}
	else
	{
		/*****************************************************************/
		//platformer stuff
		{
			char key = 'z';
			if (Application::IsKeyPressed('W'))
			{
				key = 'w';
			}
			else if (Application::IsKeyPressed('S'))
			{
				key = 's';
			}
			else if (Application::IsKeyPressed('A'))
			{
				key = 'a';
			}
			else if (Application::IsKeyPressed('D'))
			{
				key = 'd';
			}
			else if (Application::IsKeyPressed('P'))
			{
				key = 'p';
			}

			CurrentLayout->PlayerGridDropUpdate(key);
			CurrentLayout->PlayerGridDropStateChange(key);

			//cout << Platformer->GetPlayerGrid()->GetDirection() << endl;
			CurrentLayout->GridDropUpdate(KeysCollected);

			if (CurrentLayout->CheckCollisionType(Grid::GridType::KEY, count) || CurrentLayout->CheckCollisionType(Grid::GridType::WALL, count))
			{
				if (CurrentLayout->CheckCollisionType(Grid::GridType::KEY, count))
					this->KeysCollected++;
				CurrentLayout = Playfield;
				
			}
		}
		///*****************************************************************/
	}







	camera.Update(dt);
	//m_spriteAnimation->Update(dt);
	
	//Playfield->AIGridUpdate();
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

	// ReCalculate the tile offsets
	tileOffset_x = (int) (theHero->GetMapOffset_x() / m_cMap->GetTileSize());
	if (tileOffset_x + m_cMap->GetNumOfTiles_Width() > m_cMap->getNumOfTiles_MapWidth())
	tileOffset_x = m_cMap->getNumOfTiles_MapWidth() - m_cMap->GetNumOfTiles_Width();

	// if the hero enters the kill zone, then enemy goes into kill strategy mode
	int checkPosition_X = (int) ((theHero->GetMapOffset_x() + theHero->GetPos_x()) / m_cMap->GetTileSize());
	int checkPosition_Y = m_cMap->GetNumOfTiles_Height() - (int) ( (theHero->GetPos_y() + m_cMap->GetTileSize()) / m_cMap->GetTileSize());
	if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] == 10)
	{
	theEnemy->ChangeStrategy( new CStrategy_Kill());
	}
	else if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] == 11)
	{
	theEnemy->ChangeStrategy(NULL);
	//		theEnemy->ChangeStrategy( new CStrategy_Kill());
	}
	else
	{
	//theEnemy->ChangeStrategy(NULL);
	}

	// Update the enemies
	theEnemy->SetDestination( theHero->GetPos_x(), theHero->GetPos_y() );
	theEnemy->Update( m_cMap );
	*/

	fps = (float)(1.f / dt);
}

/********************************************************************************
 Update Camera position
 ********************************************************************************/
void CSceneManager2D::UpdateCameraStatus(const unsigned char key, const bool status)
{
	//camera.UpdateStatus(key, status);

	// Update avatar position
}

/********************************************************************************
 Update Weapon status
 ********************************************************************************/
void CSceneManager2D::UpdateMouseStatus(const unsigned char key)
{
	if (key == WA_LEFT_CLICKED)
	{
		if (CurrentLayout == Playfield)
		{
			short NumOfBombs = m_player->GetAmtOfBomb();
			short NumOfBridges = m_player->GetAmtOfBridge();
			//get cursor position
			double x, y;
			Application::GetMousePos(x, y);
			CurrentLayout->UpdateGrid(Vector3(x, y, 0), NumOfBombs, NumOfBridges);
			m_player->SetAmtOfBomb(NumOfBombs);
			m_player->SetAmtOfBridge(NumOfBridges);
		}
		
	}
}

/********************************************************************************
 Render text onto the screen
 ********************************************************************************/
void CSceneManager2D::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, bool enablealpha)
{
	if(!mesh || mesh->textureID <= 0)
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
				for(unsigned i = 0; i < text.length(); ++i)
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
void CSceneManager2D::Render2DMesh(Mesh *mesh, bool enableLight, bool enablealpha, int size, int x, int y, bool rotate, float rotateAngle,bool flip)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 800, 0, 600, -10, 10);
	projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
		viewStack.PushMatrix();
			viewStack.LoadIdentity();
			modelStack.PushMatrix();
				modelStack.LoadIdentity();
				modelStack.Translate( (float)x, (float)y, 0);
				modelStack.Scale( (float)size, (float)size, (float)size);
				if (rotate)
					modelStack.Rotate(rotateAngle, 0, 0, 1);
       
				Mtx44 MVP, modelView, modelView_inverse_transpose;
	
				MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
				if(mesh->textureID > 0)
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
				if(mesh->textureID > 0)
				{
					glBindTexture(GL_TEXTURE_2D, 0);
				}
       
			modelStack.PopMatrix();
		viewStack.PopMatrix();
	projectionStack.PopMatrix();
}

/********************************************************************************
 Render the background
 ********************************************************************************/
void CSceneManager2D::RenderBackground()
{
	// Render the crosshair
	Render2DMesh(meshList[GEO_BACKGROUND], false, false, 1);
}

void CSceneManager2D::RenderGridSystem()
{
	
if (CurrentLayout == Playfield)
{
	//render grid layout
	for (int a = 0; a < CurrentLayout->GetGridsVec().size(); a++)
	{
		modelStack.PushMatrix();
		//get position of a grid in the vector 
		Vector3 GridPos = CurrentLayout->GetGridsVec()[a]->GetPos();

		if (CurrentLayout->GetGridsVec()[a]->GetType() == Grid::GridType::WALL)
			Render2DMesh(meshList[GEO_WALL], false, false, 1, GridPos.x, GridPos.y);
		else if (CurrentLayout->GetGridsVec()[a]->GetType() == Grid::GridType::KEY)
		{
			if (CurrentLayout->GetGridsVec()[a]->keyCollected == false)
			{
				Render2DMesh(meshList[GEO_KEY], false, false, 1, GridPos.x, GridPos.y);
			}
			else
			{
				Render2DMesh(meshList[GEO_FLOORING], false, false, 1, GridPos.x, GridPos.y);
			}
		}
		else if (CurrentLayout->GetGridsVec()[a]->GetType() == Grid::GridType::TRAP)
			Render2DMesh(meshList[GEO_TRAP], false, false, 1, GridPos.x, GridPos.y);
		else if (CurrentLayout->GetGridsVec()[a]->GetType() == Grid::GridType::ROCK)
			Render2DMesh(meshList[GEO_ROCK], false, false, 1, GridPos.x, GridPos.y);
		else if (CurrentLayout->GetGridsVec()[a]->GetType() == Grid::GridType::EXIT)
			Render2DMesh(meshList[GEO_EXIT], false, false, 1, GridPos.x, GridPos.y);
		else if (CurrentLayout->GetGridsVec()[a]->GetType() == Grid::GridType::INTROSIGN)
			Render2DMesh(meshList[GEO_SIGN], false, false, 1, GridPos.x, GridPos.y);
		else if (CurrentLayout->GetGridsVec()[a]->GetType() == Grid::GridType::MOVESIGN)
			Render2DMesh(meshList[GEO_SIGN], false, false, 1, GridPos.x, GridPos.y);
		else if (CurrentLayout->GetGridsVec()[a]->GetType() == Grid::GridType::KEYSIGN)
			Render2DMesh(meshList[GEO_SIGN], false, false, 1, GridPos.x, GridPos.y);
		else if (CurrentLayout->GetGridsVec()[a]->GetType() == Grid::GridType::MONSTERSIGN)
			Render2DMesh(meshList[GEO_SIGN], false, false, 1, GridPos.x, GridPos.y);
		else if (CurrentLayout->GetGridsVec()[a]->GetType() == Grid::GridType::EXITSIGN)
			Render2DMesh(meshList[GEO_SIGN], false, false, 1, GridPos.x, GridPos.y);
		else if (CurrentLayout->GetGridsVec()[a]->GetType() == Grid::GridType::BOMBED)
			Render2DMesh(meshList[GEO_BOMBED], false, false, 1, GridPos.x, GridPos.y);
		else if (CurrentLayout->GetGridsVec()[a]->GetType() == Grid::GridType::BRIDGED)
			Render2DMesh(meshList[GEO_BRIDGED], false, false, 1, GridPos.x, GridPos.y);
		else
			Render2DMesh(meshList[GEO_FLOORING], false, false, 1, GridPos.x, GridPos.y);
		//cout << "rendered at" << Playfield->GetGridsVec()[a]->GetPos().x << ", " << Playfield->GetGridsVec()[a]->GetPos().y << endl;
		modelStack.PopMatrix();
	}
	//render player trail
	for (int a = 0; a < CurrentLayout->GetGridsVec().size(); a++)
	{
		modelStack.PushMatrix();
		//get position of a grid in the vector 
		Vector3 GridPos = CurrentLayout->GetGridsVec()[a]->GetPos();
		if (CurrentLayout->GetGridsVec()[a]->GetStatus() == 1 && (CurrentLayout->GetGridsVec()[a]->GetType() == 0 || CurrentLayout->GetGridsVec()[a]->GetType() == 2))
		{
			float FeetDirection = CurrentLayout->GetGridsVec()[a]->GetDirection();
			if (FeetDirection == 0.f)
				offset = Vector3(0, 0, 0);
			else if (FeetDirection == 180.f)
				offset = Vector3(50, 50, 0);
			else if (FeetDirection == 90.f)
				offset = Vector3(50, 0, 0);
			else if (FeetDirection == -90.f)
				offset = Vector3(0, 50, 0);

			Render2DMesh(meshList[GEO_FEET], false, false, 1, GridPos.x + offset.x, GridPos.y + offset.y, true, FeetDirection);
			//Render2DMesh(meshList[GEO_FEET], false, false, 1, GridPos.x + offset.x, GridPos.y + offset.y, true, direction);

		}

		//cout << "rendered at" << Playfield->GetGridsVec()[a]->GetPos().x << ", " << Playfield->GetGridsVec()[a]->GetPos().y << endl;
		modelStack.PopMatrix();
	}


	//render AI
	for (int a = 0; a < CurrentLayout->GetAIGrids().size(); a++)
	{
		Vector3 AIGridPos = CurrentLayout->GetAIGrids()[a]->GetPos();
		Render2DMesh(meshList[GEO_TILEENEMY_FRAME0], false, false, 1, AIGridPos.x, AIGridPos.y);
	}
}
else
{
	//test field
	//render grid layout
	for (int a = 0; a < Platformer->GetGridsVec().size(); a++)
	{
		modelStack.PushMatrix();
		//get position of a grid in the vector 
		Vector3 GridPos = Platformer->GetGridsVec()[a]->GetPos();
		if (Platformer->GetGridsVec()[a]->GetType() == Grid::GridType::WALL)
			Render2DMesh(meshList[GEO_WALL], false, false, 1, GridPos.x, GridPos.y);
		else if (Platformer->GetGridsVec()[a]->GetType() == Grid::GridType::KEY)
		{
			if (Platformer->GetGridsVec()[a]->keyCollected == false)
			{
				Render2DMesh(meshList[GEO_KEY], false, false, 1, GridPos.x, GridPos.y);
			}
			else
			{
				Render2DMesh(meshList[GEO_FLOORING], false, false, 1, GridPos.x, GridPos.y);
			}
		}
		else if (Platformer->GetGridsVec()[a]->GetType() == Grid::GridType::TRAP)
			Render2DMesh(meshList[GEO_TRAP], false, false, 1, GridPos.x, GridPos.y);
		else if (Platformer->GetGridsVec()[a]->GetType() == Grid::GridType::ROCK)
			Render2DMesh(meshList[GEO_ROCK], false, false, 1, GridPos.x, GridPos.y);
		else if (Platformer->GetGridsVec()[a]->GetType() == Grid::GridType::EXIT)
			Render2DMesh(meshList[GEO_EXIT], false, false, 1, GridPos.x, GridPos.y);
		else
			Render2DMesh(meshList[GEO_FLOORING], false, false, 1, GridPos.x, GridPos.y);
		//cout << "rendered at" << Playfield->GetGridsVec()[a]->GetPos().x << ", " << Playfield->GetGridsVec()[a]->GetPos().y << endl;
		modelStack.PopMatrix();
	}
}




//render player
Vector3 PlayerGridPos = CurrentLayout->GetPlayerGrid()->GetPos();
Render2DMesh(meshList[GEO_CHARACTER], false, false, 1, PlayerGridPos.x, PlayerGridPos.y);

}

void CSceneManager2D::RenderUI()
{
	modelStack.PushMatrix();
	Render2DMesh(meshList[GEO_MOVESLEFT], false, false, 1, 0, 500);

	std::ostringstream MovesLeft;
	MovesLeft << "x " << NoOfMoves;
	RenderTextOnScreen(meshList[GEO_TEXT], MovesLeft.str(), Color(0, 0, 0), 40, 100, 520, true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	Render2DMesh(meshList[GEO_KEYSCOLLECTED], false, false, 1, 200, 500);

	std::ostringstream Keys;
	Keys << "x " << KeysCollected;
	RenderTextOnScreen(meshList[GEO_TEXT], Keys.str(), Color(0, 0, 0), 40, 300, 520, true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	Render2DMesh(meshList[GEO_BOMBSLEFT], false, false, 1, 550, 200);
	std::ostringstream Bombs;
	Bombs << "x " << m_player->GetAmtOfBomb();
	RenderTextOnScreen(meshList[GEO_TEXT], Bombs.str(), Color(0, 0, 0), 40, 650, 220, true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	Render2DMesh(meshList[GEO_BRIDGESLEFT], false, false, 1, 550, 100);
	std::ostringstream Bridges;
	Bridges << "x " << m_player->GetAmtOfBridge();
	RenderTextOnScreen(meshList[GEO_TEXT], Bridges.str(), Color(0, 0, 0), 40, 650, 120, true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	Render2DMesh(meshList[GEO_HEALTHLEFT], false, false, 1, 400, 500);
	std::ostringstream Health;
	Health << "x " << player_Health;
	RenderTextOnScreen(meshList[GEO_TEXT], Health.str(), Color(0, 0, 0), 40, 500, 520, true);
	modelStack.PopMatrix();

	if (ShowStart)
	{
		modelStack.PushMatrix();
		Render2DMesh(meshList[GEO_SIGN1], false, false, 1, 520, 350);
		modelStack.PopMatrix();
	}
	if (ShowMove)
	{
		modelStack.PushMatrix();
		Render2DMesh(meshList[GEO_SIGN2], false, false, 1, 520, 350);
		modelStack.PopMatrix();
	}
	if (ShowKey)
	{
		modelStack.PushMatrix();
		Render2DMesh(meshList[GEO_SIGN3], false, false, 1, 520, 350);
		modelStack.PopMatrix();
	}
	if (ShowMonster)
	{
		modelStack.PushMatrix();
		Render2DMesh(meshList[GEO_SIGN4], false, false, 1, 520, 350);
		modelStack.PopMatrix();
	}
	if (ShowExit)
	{
		modelStack.PushMatrix();
		Render2DMesh(meshList[GEO_SIGN5], false, false, 1, 520, 350);
		modelStack.PopMatrix();
	}

}

/********************************************************************************
 Render this scene
 ********************************************************************************/
void CSceneManager2D::Render()
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

	// Render the background image
	RenderBackground();

	RenderUI();

	//render the grid system and the corresponding image for the each grid
	RenderGridSystem();

	if (m_losed != true && m_WinCondition == -1 && NoOfMoves <= 0)
	Render2DMesh(meshList[GEO_MOVELOSESIGN], false, false, 1, m_windowWidth*0.5, m_windowHeight*0.5);

	else if (m_losed != true && m_WinCondition == -1 && player_Health <= 0)
	Render2DMesh(meshList[GEO_HEALTHLOSESIGN], false, false, 1, m_windowWidth*0.5, m_windowHeight*0.5);
	
	std::ostringstream ss;
	ss.precision(5);
	ss << fps << endl;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0, 0.5f), 30, 0, 6, true);
}

/********************************************************************************
 Exit this scene
 ********************************************************************************/
void CSceneManager2D::Exit()
{
	if (!m_Quitfrompause && m_WinCondition != -1)
	{
		int i = m_player->GetLevelToDifficultyStartAt() - 2;
		int j = i * m_maxlevel;
		int k = j + 1;
		int l = k;
		if (m_player->GetLevelToDifficultyStartAt() == 1)
		{
			l = 0;
		}
		
		theLevelDetailsHolder[l]->SetCleared(true);
		if (theLevelDetailsHolder[l]->GetCollectedKeys() < KeysCollected)
		{
			m_player->SetAmtOfCurrency(m_player->GetAmtOfCurrency() + (KeysCollected - theLevelDetailsHolder[l]->GetCollectedKeys()));
			theLevelDetailsHolder[l]->SetCollectedKeys(KeysCollected);
		}
			
		if (theLevelDetailsHolder[l]->GetCollectedKeys() == 3)
			theLevelDetailsHolder[l]->SetCollectedKeys(3);	

		m_player->SetAmtOfGold(m_player->GetAmtOfGold() + GetScoreToGold());
	}
	m_save->SaveLevelStuff(theLevelDetailsHolder,m_maxleveltutorial, m_maxlevel, m_maxdiff);
	m_save->SavePlayer(m_player);

	// Cleanup VBO
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{

		if (meshList[i] && i != GEO_SPRITE_ANIMATION)
			delete meshList[i];
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	
}