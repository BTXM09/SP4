#include "LevelDetails.h"


LevelDetails::LevelDetails(void) 
: theLevelDetailsinfoLua(NULL)
{
}

LevelDetails::~LevelDetails(void)
{
	if (theLevelDetailsinfoLua)
	{
		delete theLevelDetailsinfoLua;
		theLevelDetailsinfoLua = NULL;
	}
}
//void LevelDetailsInit(int Difficulty, int LevelinDifficulty);
void LevelDetails::LevelDetailsInit(int Difficulty, int LevelinDifficulty, string FilePath)
{
	this->m_DifficultyReference = Difficulty;
	this->m_LevelinDifficultyReference = LevelinDifficulty;
	theLevelDetailsinfoLua = new LuaUsage();
	theLevelDetailsinfoLua->LuaUsageInit(FilePath);
	string GetLevelDetails = FilePath;
	switch (this->m_DifficultyReference)
	{
	case 1:
	{
			  GetLevelDetails = GetLevelDetails + ".Tutorial";
			  break;
	}
	case 2:
	{
			  GetLevelDetails = GetLevelDetails + ".Easy";
			  break;
	}
	case 3:
	{
			  GetLevelDetails = GetLevelDetails + ".Normal";
			  break;
	}
	case 4:
	{
			  GetLevelDetails = GetLevelDetails + ".Hard";
			  break;
	}
	}
	GetLevelDetails = GetLevelDetails + ".Level" + std::to_string(this->m_LevelinDifficultyReference) + ".";
	this->m_AmountOfMoves = theLevelDetailsinfoLua->get<int>((GetLevelDetails + "AmountOfMoves"));
	this->m_PositionXOfGrid = theLevelDetailsinfoLua->get<float>((GetLevelDetails+"PositionXOfGrid"));
	this->m_PositionYOfGrid = theLevelDetailsinfoLua->get<float>((GetLevelDetails + "PositionYOfGrid"));
	this->m_LengthXOfAGrid = theLevelDetailsinfoLua->get<float>((GetLevelDetails + "LengthXOfAGrid"));
	this->m_LengthYOfAGrid = theLevelDetailsinfoLua->get<float>((GetLevelDetails + "LengthYOfAGrid"));
	this->m_NumberOfGridX = theLevelDetailsinfoLua->get<int>((GetLevelDetails + "NumberOfGridX"));
	this->m_NumberOfGridY = theLevelDetailsinfoLua->get<int>((GetLevelDetails + "NumberOfGridY"));
	this->m_PlayerPositionX = theLevelDetailsinfoLua->get<int>((GetLevelDetails + "PlayerPositionX"));
	this->m_PlayerPositionY = theLevelDetailsinfoLua->get<int>((GetLevelDetails + "PlayerPositionY"));
	this->m_NameOfLevelFile = theLevelDetailsinfoLua->get<string>((GetLevelDetails + "NameOfLevelFile"));
	this->m_Difficulty = theLevelDetailsinfoLua->get<string>((GetLevelDetails + "Difficulty"));
	theLevelDetailsinfoLua->LuaUsageClose();


}


float LevelDetails::GetPositionXOfGrid()
{
	return m_PositionXOfGrid;
}
float LevelDetails::GetPositionYOfGrid()
{
	return m_PositionYOfGrid;
}
float LevelDetails::GetLengthXOfAGrid()
{
	return m_LengthXOfAGrid;
}
float LevelDetails::GetLengthYOfAGrid()
{
	return m_LengthYOfAGrid;
}
int LevelDetails::GetNumberOfGridX()
{
	return m_NumberOfGridX;
}
int LevelDetails::GetNumberOfGridY()
{
	return m_NumberOfGridY;
}
int LevelDetails::GetPlayerPositionX()
{
	return m_PlayerPositionX;
}
int LevelDetails::GetPlayerPositionY()
{
	return m_PlayerPositionY;
}
string LevelDetails::GetNameOfLevelFile()
{
	return m_NameOfLevelFile;
}
string LevelDetails::GetDifficulty()
{
	return m_Difficulty;
}


void LevelDetails::SetPositionXOfGrid(float m_PositionXOfGrid)
{
	this->m_PositionXOfGrid = m_PositionXOfGrid;
}
void LevelDetails::SetPositionYOfGrid(float m_PositionYOfGrid)
{
	this->m_PositionYOfGrid = m_PositionYOfGrid;
}
void LevelDetails::SetLengthXOfAGrid(float m_LengthXOfAGrid)
{
	this->m_LengthXOfAGrid = m_LengthXOfAGrid;
}
void LevelDetails::SetLengthYOfAGrid(float m_LengthYOfAGrid)
{
	this->m_LengthYOfAGrid = m_LengthYOfAGrid;
}
void LevelDetails::SetNumberOfGridX(int m_NumberOfGridX)
{
	this->m_NumberOfGridX = m_NumberOfGridX;
}
void LevelDetails::SetNumberOfGridY(int m_NumberOfGridY)
{
	this->m_NumberOfGridY = m_NumberOfGridY;
}
void LevelDetails::SetPlayerPositionX(int m_PlayerPositionX)
{
	this->m_PlayerPositionX = m_PlayerPositionX;
}
void LevelDetails::SetPlayerPositionY(int m_PlayerPositionY)
{
	this->m_PlayerPositionY = m_PlayerPositionY;
}
void LevelDetails::SetNameOfLevelFile(string m_NameOfLevelFile)
{
	this->m_NameOfLevelFile = m_NameOfLevelFile;
}
void LevelDetails::SetDifficulty(string m_Difficulty)
{
	this->m_Difficulty = m_Difficulty;
}

void LevelDetails::SetDifficultyReference(int m_DifficultyReference)
{
	this->m_DifficultyReference = m_DifficultyReference;
}
void LevelDetails::SetLevelinDifficultyReference(int m_LevelinDifficultyReference)
{
	this->m_LevelinDifficultyReference = m_LevelinDifficultyReference;
}
short LevelDetails::GetDifficultyReference()
{
	return this->m_DifficultyReference;
}
short LevelDetails::GetLevelinDifficultyReference()
{
	return this->m_LevelinDifficultyReference;
}
short LevelDetails::GetAmountOfMoves()
{
	return this->m_AmountOfMoves;
}