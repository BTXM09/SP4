#pragma once
#include "Grid.h"
#include <vector>
#include "AI.h"


using std::vector;

class GridSystem
{
public:
	GridSystem();
	~GridSystem();

	//initialise various needed variables
	void Init(Vector3 Pos, float LengthX, float LengthY, int NumOfGridsX, int NumOfGridsY);
	//default update the grid system 
	void UpdateGrid(Vector3, short&, short&);
	//set map layout
	void SetMap(vector<vector<int>>);
	//set player grid and Position
	Vector3 PlayerGridSetUp(int, int);
	//Player Update
	bool PlayerGridUpdate(char key);
	//set player grid and Position
	void AIGridSetUp(vector<cAI*>);
	//AI Update
	void AIGridUpdate();
	
	// for tetris like blocks falling
	void GridDropInit(int);
	void GridDropUpdate(int);
	bool PlayerGridDropUpdate(char key);

	void PlayerGridDropPushPull(char key, bool grab);
	void PlayerGridDropStateChange(char key);

	void ResetGridDrop(int, int, int);

	void CreateNewIdx();

	//for checking collision between player to specific grid 
	bool CheckCollisionType(Grid::GridType, int&);
	//bool CheckCollisionType(Grid::GridType, Grid::GridType, int&);

	// get grid vector to get each grids pos
	vector<Grid*> GetGridsVec();
	Grid* GetPlayerGrid();
	vector<Grid*> GetAIGrids();
private:
	vector<Grid*> GridsVec;
	Grid* PlayerGrid;
	vector<cAI*> AIVec;
	vector<int> AIGridsVec;
	

	Vector3 Pos;
	Vector3 PlayerGridPos;
	bool PlayerMoved;

	int NumOfGridsX;
	int NumOfGridsY;
	float LengthOfGridsX;
	float LengthOfGridsY;
	Vector3 PosOfGrid;
	
	//for dropping blocks
	vector<int> PrevMovedBlockIdx;
	bool movingActive;
	Grid* MovingBlock;
	vector<Grid*> FallingBlocks;
	float timer;
	bool PlayerJumped;
	float PlayerJumpedTimer;
	float PlayerBuffer;
	bool PlayerPushPull;
	bool CanPush;
	bool PushPull;
	float PushPullTimer;
	Vector3 KeyGridDropPos;
};

