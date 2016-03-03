#pragma once
#include "Vector3.h"

class Grid
{
public:
	enum GridType
	{
		FLOOR = 0,
		WALL,
		KEY,
		TRAP,
		ROCK,
		EXIT,
		INTROSIGN,
		MOVESIGN,
		KEYSIGN,
		MONSTERSIGN,
		EXITSIGN,
		BOMBED,
		BRIDGED,
		TOTAL_TYPE,
	};

	enum GridStatus
	{
		//can walk on
		PASSABLE = 0,
		//cannot walk on(anymore)
		UNPASSABLE,
		TOTAL_STATUS,
	};

	Grid();
	~Grid();

	void SetType(int);
	int GetType(void);
	void ChangeType(void);

	void SetStatus(int);
	int GetStatus(void);

	void SetDirection(char);
	void SetDirection(float);
	float GetDirection(void);

	void SetPos(float, float);
	Vector3 GetPos();

	bool keyCollected;
	bool Win;
	bool Sign1Touched;
	bool Sign2Touched;
	bool Sign3Touched;
	bool Sign4Touched;
	bool Sign5Touched;

private:
	GridType Type;
	GridStatus Status;
	Vector3 Pos;
	float direction;

};

