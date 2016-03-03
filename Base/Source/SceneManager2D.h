#ifndef SCENE_MANAGER_2D_H
#define SCENE_MANAGER_2D_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Minimap.h"
#include "Map.h"
#include "Vector2.h"
#include "PlayerInfo.h"
#include "Enemy.h"
#include "Player.h"
#include "Save.h"
#include "SpriteAnimation.h"
#include "SoundManager.h"
#include "LevelDetails.h"
#include "AllLevelDetails.h"

#include "Highscore.h"
#include "HighscoreData.h"
#include "LuaUsage.h"

// Goodies and Goodies Factory
#include "GoodiesFactory.h"
#include "Goodies.h"
#include "TreasureChest.h"

//grid system and grid class
#include "GridSystem.h"

// level loader
#include "LevelLoader.h"

class CSceneManager2D : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_LIGHTENABLED,
		U_COLOR_TEXTURE0,
		U_COLOR_TEXTURE_ENABLED0,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TEXT_ALPHA_ENABLED,
		U_TEXT_ALPHA,
		U_TOTAL,
	};
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_BACKGROUND,
		GEO_TILEGROUND,
		GEO_TILEHERO,
		GEO_TILETREE,
		GEO_TILESTRUCTURE,
		GEO_TILEHERO_FRAME0,
		GEO_TILEHERO_FRAME1,
		GEO_TILEHERO_FRAME2,
		GEO_TILEHERO_FRAME3,
		GEO_TILE_KILLZONE,
		GEO_TILE_SAFEZONE,
		GEO_TILEENEMY_FRAME0,
		GEO_TILE_TREASURECHEST,
		GEO_SPRITE_ANIMATION,
		GEO_OBJECT,

		GEO_MENU,
		GEO_SELECT,
		GEO_INSTRUCTION,
		GEO_HIGHSCORE,
		GEO_VOL_MUTE,
		GEO_VOL,
		GEO_SOUND_MUTE,
		GEO_SOUND,

		GEO_FLOORING,
		GEO_CHARACTER,
		GEO_ROCK,
		GEO_TRAP,
		GEO_SNAKE,
		GEO_MONSTER,
		GEO_WALL,
		GEO_KEY,
		//power ups
		GEO_BOMBED,
		GEO_BRIDGED,
		GEO_EXIT,

		GEO_MOVELOSESIGN,
		GEO_HEALTHLOSESIGN,

		// Tutorial
		GEO_SIGN,
		GEO_SIGN1,
		GEO_SIGN2,
		GEO_SIGN3,
		GEO_SIGN4,
		GEO_SIGN5,
		GEO_SIGN6,

		// UI
		GEO_KEYSCOLLECTED,
		GEO_MOVESLEFT,
		GEO_BOMBSLEFT,
		GEO_BRIDGESLEFT,
		GEO_HEALTHLEFT,

		// Show Movement
		GEO_FEET,

		GEO_TEXT,
		NUM_GEOMETRY,
	};
	enum PARTICLE_STYLE
	{
		DROPDOWN = 0,
		CONFETTI,
		NUM_PARTICLE_STYLE
	};
public:
	CSceneManager2D();
	CSceneManager2D(const int m_window_width, const int m_window_height);
	~CSceneManager2D();

	virtual void Init();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);
	// Update mouse status
	virtual void UpdateMouseStatus(const unsigned char key);
	virtual void Render();
	virtual void Exit();


	int GetWinCondition();
	bool GetLoseCondition();

	void SetQuitfrompause(bool m_Quitfrompause);

	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, bool enablealpha = false);
	void RenderBackground();
	void RenderUI();
	void Render2DMesh(Mesh *mesh, const bool enableLight, bool enablealpha = false, const int size = 1, const int x = 0, const int y = 0, const bool rotate = false, float rotateAngle = 0.f, const bool flip = false);
	void PreInit();
	void RenderGridSystem();

	// Option States
	bool SoundSelect;
	bool VolumeSelect;
	bool muted;
	
	// UI
	int KeysCollected;
	int NoOfMoves;
	int NoOfBombs;
	int NoOfBridges;
	bool MoveChar;

	// Highscore
	Highscore PlayerScore;
	Highscore PrevScore;
	void AddHighscore();
	HighscoreData theScore;
	void ReadHighscoreText();
	void WriteHighscoreText();

	// Score to Gold
	void SetScoreToGold(int ScoreToGold); // This is used to set the finalized score for each level
	int GetScoreToGold(); // This is used to get the score

	CSoundManager Sound;

	float tempsound;

	enum WEAPON_ACTION
	{
		WA_NIL = 0,
		WA_LEFT_CLICKED,
		WA_FIRE,
		WA_RELOAD,
		WA_CHANGEWEAPON,
		WA_TOTAL,
	};

private:
	bool m_Quitfrompause;
	bool m_losed;

	// Win Condition
	int m_WinCondition;
	
	// Vector to Hold all level Details to be saved
	vector<AllLevelDetails*> theLevelDetailsHolder;
	
	// MaxLevel and MaxDifferent
	int m_maxlevel;
	int m_maxdiff;
	int m_maxleveltutorial;
	// Loading
	LuaUsage* m_Load;

	//Player
	Player* m_player;
	
	//Saving
	Save* m_save;

	//LevelDetails
	LevelDetails* m_LevelDetails;

	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Camera3 camera;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	// Fps
	float fps;

	// Tutorial
	bool ShowStart;		// Sign.1
	bool ShowMove;		// Sign.2
	bool ShowKey;		// Sign.3
	bool ShowMonster;	// Sign.4
	bool ShowExit;		// Sign.5

	// Checks if player has pressed 'X'
	bool Sign1Exited;
	bool Sign2Exited;
	bool Sign3Exited;
	bool Sign4Exited;
	bool Sign5Exited;

	// Score to Gold Conversion
	int ScoreToGold;

	//time Buffer for continuous key press
	float timeBuffer;

	//grid system and grids
	GridSystem* Playfield;
	GridSystem* Platformer;
	GridSystem* CurrentLayout;
	bool switchStage;

	//determine direction : 0 = up,180 = down, -90 = left, 90 = right and offset
	float direction;
	Vector3 offset;
	
	//window height and width
	int m_windowHeight;
	int m_windowWidth;

	//loaded level;
	LevelLoader *m_cLevel;

	// vector of AI
	vector<cAI*> AIList;
	//player health
	int player_Health;
	float damage_Buffer;
};

#endif