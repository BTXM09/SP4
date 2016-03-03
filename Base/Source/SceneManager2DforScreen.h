#ifndef SCENE_MANAGER_2D_FS_H
#define SCENE_MANAGER_2D_FS_H

#include <string>
#include "GameStateManager.h"
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

#include "Highscore.h"
#include "HighscoreData.h"
#include "Particle.h"
#include "LuaUsage.h"

// Goodies and Goodies Factory
#include "GoodiesFactory.h"
#include "Goodies.h"
#include "TreasureChest.h"

//grid system and grid class
#include "GridSystem.h"

#include "Shop.h"
#include "Button.h"

class SceneManagerLevel2DforScreen : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_LIGHTENABLED,
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
		GEO_VOL_BAR,

		GEO_MENU,
		GEO_SELECT,
		GEO_INSTRUCTION,
		GEO_HIGHSCORE,
		GEO_PAUSE,
		GEO_LEVELSHOPSELECT,
		GEO_SHOP,
		GEO_WIN,
		GEO_LEVELSELECT,
		GEO_DIFFICULTYSELECT,

		//Menu button
		GEO_MENU_PLAY,
		GEO_MENU_INSTRUCTION,
		GEO_MENU_HIGHSCORE,
		GEO_MENU_OPTION,
		GEO_MENU_EXIT,

		//LevelShopSelect button
		GEO_LEVELSHOPSELECT_LEVELSELECT,
		GEO_LEVELSHOPSELECT_SHOP,
		GEO_LEVELSHOPSELECT_CONTINUELEVEL,

		//Difficulty button
		GEO_DIFFICULTY_TUTORIAL,
		GEO_DIFFICULTY_EASY,
		GEO_DIFFICULTY_NORMAL,
		GEO_DIFFICULTY_HARD,

		GEO_LEVELSELECT_LEVEL,

		//Pause button
		GEO_PAUSE_RESUME,
		GEO_PAUSE_QUITTOMENU,

		GEO_BACKTOEXIT,

		GEO_WIN_NEXTLEVEL,

		GEO_LEVELSELECT_LEVEL1,
		GEO_LEVELSELECT_LEVEL2,
		GEO_LEVELSELECT_LEVEL3,
		GEO_LEVELSELECT_LEVEL4,

		// TEMPO NAME
		GEO_VOL_MUTE,
		GEO_VOL,
		GEO_SOUND_MUTE,
		GEO_SOUND,

		//Highscore buttons
		GEO_HIGHSCORE_TUTORIAL,
		GEO_HIGHSCORE_EASY,
		GEO_HIGHSCORE_NORMAL,
		GEO_HIGHSCORE_HARD,
		GEO_HIGHSCORE_LEVEL1,
		GEO_HIGHSCORE_LEVEL2,
		GEO_HIGHSCORE_LEVEL3,
		GEO_HIGHSCORE_LEVEL4,

		//Items
		GEO_BOMB,
		GEO_BRIDGE,

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
	SceneManagerLevel2DforScreen();
	SceneManagerLevel2DforScreen(const int m_window_width, const int m_window_height, const int ScreenValue);
	~SceneManagerLevel2DforScreen();

	virtual void Init();
	void PreInit();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);
	// Update mouse status
	virtual void UpdateMouseStatus(const unsigned char key);
	virtual void Render();
	virtual void Exit();

	void CreateButton(string name);

	void SetSpriteAnimation(Particle *ParticleVector, int SAIndex);
	void SetParticleStyle(Particle *ParticleVector, int ParticleStyle);

	int GetLevelReferencetoContinue();

	void SetContinuedLevel();

	// States Function
	//void SetSelection(short);
	bool CheckEligibleForNextLevel();
	void NextLevel();
	void ResetPlayer();
	void SetSelection(short m_select);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, bool enablealpha = false);
	void RenderBackground();
	void RenderMainMenu();
	void RenderHighscore();
	void RenderInstructions();
	void RenderOption();
	void RenderPause();
	void RenderShop();
	void RenderWin();
	void RenderLevelShopSelect();
	void RenderLevelSelect();
	void RenderDifficulty();
	void Render2DMesh(Mesh *mesh, const bool enableLight, bool enablealpha = false, const float size = 1, const int x = 0, const int y = 0, const bool rotate = false, const bool flip = false);
	void SetScreenTransition(bool m_ScreenTransition);
	bool ReturnScreenTransition();
	void SetChangeScreen(bool m_ChangeScreen);
	bool ReturnChangeScreen();

	void SetLevelDifficulty(int LevelDifficulty);
	void SetLevelNumber(int LevelNumber);

	bool ReturnPlayerDifficultySelection(int difficultyselection);

	void SetShopSelect(int shopSelect);
	void SetShopSelectItem(int shopSelectItem);

	// Highscore States
	void setHSDifficulty(int theDifficulty);
	int getHSDifficulty();
	void setHSLevel(int theLevel);
	int getHSLevel();
	void setDifficultyButton(bool theDifficultyButton);
	bool getDifficultyButton();
	void setLevelButton(bool theLevelButton);
	bool getLevelButton();
	void setHighscoreDisplay(bool DisplayHighscore); 
	bool getHighscoreDisplay();
	void setLevelButtonSelection(int theLevelButtonSelection);
	int getLevelButtonSelection();

	// Option States
	bool SoundSelect;
	bool VolumeSelect;
	bool muted;

	// Highscore
	void GetHighscore();
	HighscoreData theScore;
	void ReadHighscoreTextFiles();



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
	int m_maxlevel;
	int m_maxdiff;
	int m_maxleveltutorial;
	vector<AllLevelDetails*> theLevelDetailsHolder;


	vector<Button*> theButtonHolder;
	Button* m_button;
	//sprite animation
	LuaUsage* m_SpriteAnimationLoad;
	SpriteAnimation *m_spriteAnimation;
	Particle *m_particle;
	Particle *m_particle2;
	bool confettiRightside;

	Shop* m_shop;
	Player* m_player;
	Save* m_save;
	LuaUsage* m_loading;
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	short m_select;

	float m_alpha;
	bool m_ChangeScreen;
	bool m_ScreenTransition;

	Camera3 camera;

	float rotateAngle;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	float fps;

	// Highscore State
	int theDifficulty;
	int theLevel;
	int theLevelButtonSelection;
	bool theDifficultyButton;
	bool theLevelButton;
	bool DisplayHighscore;

	//window height and width
	short m_screenvalue;
	int m_windowHeight;
	int m_windowWidth;
	/*
	// Handle to the minimap
	CMinimap* m_cMinimap;

	// Handle to the tilemaps
	CMap* m_cMap;
	void RenderTileMap();
	// Hero's information
	CPlayerInfo* theHero;

	// Codes for Scrolling
	int tileOffset_x, tileOffset_y;

	// Codes for Parallax Scrolling
	CMap* m_cRearMap;
	void RenderRearTileMap();
	int rearWallOffset_x, rearWallOffset_y;
	int rearWallTileOffset_x, rearWallTileOffset_y;
	int rearWallFineOffset_x, rearWallFineOffset_y;

	// Enemies
	CEnemy* theEnemy;

	// Goodies and Goodies Factory
	CGoodiesFactory theGoodiesFactory;
	CGoodies** theArrayOfGoodies;
	void RenderGoodies(void);
	*/
};

#endif