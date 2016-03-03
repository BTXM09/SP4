#ifndef LEVELDETAILS_H
#define LEVELDETAILS_H

#include <iostream>
#include <string>
#include "LuaUsage.h"

using namespace std;

class LevelDetails
{
public:
	LevelDetails(void);
	~LevelDetails(void);
	//LevelDetails Init
	void LevelDetailsInit(int Difficulty, int LevelinDifficulty, string FilePath);
	//Get & Set of X Position of grid
	float GetPositionXOfGrid();
	void SetPositionXOfGrid(float m_PositionXOfGrid);
	//Get & Set of Y Position of grid
	float GetPositionYOfGrid();
	void SetPositionYOfGrid(float m_PositionYOfGrid);
	//Get & Set of X Length of grid
	float GetLengthXOfAGrid();
	void SetLengthXOfAGrid(float m_LengthXOfAGrid);
	//Get & Set of Y Length of grid
	float GetLengthYOfAGrid();
	void SetLengthYOfAGrid(float m_LengthYOfAGrid);
	//Get & Set of X Number of grid
	int GetNumberOfGridX();
	void SetNumberOfGridX(int m_NumberOfGridX);
	//Get & Set of Y Number of grid
	int GetNumberOfGridY();
	void SetNumberOfGridY(int m_NumberOfGridY);
	//Get & Set of X Position of Player
	int GetPlayerPositionX();
	void SetPlayerPositionX(int m_PlayerPositionX);
	//Get & Set of Y Position of Player
	int GetPlayerPositionY();
	void SetPlayerPositionY(int m_PlayerPositionY);
	//Get & Set of Name of File
	string GetNameOfLevelFile();
	void SetNameOfLevelFile(string m_NameOfLevelFile);
	//Get & Set of Difficulty of level
	string GetDifficulty();
	void SetDifficulty(string m_Difficulty);
	//Get & Set of Difficulty Reference
	short GetDifficultyReference();
	void SetDifficultyReference(int m_DifficultyReference);
	//Get & Set of Level Reference
	short GetLevelinDifficultyReference();
	void SetLevelinDifficultyReference(int m_LevelinDifficultyReference);
	//Get Amount of moves in that level
	short GetAmountOfMoves();

private:
	//X Position of grid
	float m_PositionXOfGrid;
	//Y Position of grid
	float m_PositionYOfGrid;
	//X Length of grid
	float m_LengthXOfAGrid;
	//Y Length of grid
	float m_LengthYOfAGrid;
	//X Number of grid
	int m_NumberOfGridX;
	//Y Number of grid
	int m_NumberOfGridY;
	//X Position of Player
	int m_PlayerPositionX;
	//Y Position of Player
	int m_PlayerPositionY;
	
	//Name of File
	string m_NameOfLevelFile;
	//Difficulty of level
	string m_Difficulty;

	//Amount of moves in that level
	short m_AmountOfMoves;
	//Difficulty Reference
	short m_DifficultyReference; 
	//Level Reference
	short m_LevelinDifficultyReference;
	//Loading
	LuaUsage* theLevelDetailsinfoLua;
};
#endif