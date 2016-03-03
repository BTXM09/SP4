#include "Grid.h"


Grid::Grid()
:Type(FLOOR)
, Status(PASSABLE)
, keyCollected(false)
, Win(true)
, Sign1Touched(true)
, Sign2Touched(true)
, Sign3Touched(true)
, Sign4Touched(true)
, Sign5Touched(true)
, direction(0.f)
{
}


Grid::~Grid()
{
	
}

void Grid::SetType(int newType)
{
	this->Type = (GridType)(newType);
	if (Type == KEY)
		keyCollected = false;
	if (Type == EXIT)
		Win = false;
	if (Type == INTROSIGN)
		Sign1Touched = false;
	if (Type == MOVESIGN)
		Sign2Touched = false;
	if (Type == KEYSIGN)
		Sign3Touched = false;
	if (Type == MONSTERSIGN)
		Sign4Touched = false;
	if (Type == EXITSIGN)
		Sign5Touched = false;
}

int Grid::GetType(void)
{
	return this->Type;
}

void Grid::ChangeType(void)
{
	this->Type = (GridType)(this->Type + 1);
	if (this->Type >= TOTAL_TYPE)
	{
		this->Type = FLOOR;
	}
}

void Grid::SetStatus(int newStatus)
{
	this->Status = (GridStatus)newStatus;
}

int Grid::GetStatus(void)
{
	return this->Status;
}

void Grid::SetDirection(char newDirection)
{

	switch (newDirection)
	{
		case 'w':
		{
					this->direction = 0.f;
		}
			break;
		case 's':
		{
					this->direction = 180.f;
		}
			break;
		case 'a':
		{
					this->direction = 90.f;
		}
			break;
		case 'd':
		{
					this->direction = -90.f;
		}
			break;
	}
		
	
}

void Grid::SetDirection(float newDirection)
{
	this->direction = newDirection;
}

float Grid::GetDirection(void)
{
	return this->direction;
}

void Grid::SetPos(float x, float y)
{
	this->Pos = Vector3(x, y, 0);
}

Vector3 Grid::GetPos()
{
	return this->Pos;
}