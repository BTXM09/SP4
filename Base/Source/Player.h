#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "LuaUsage.h"

using namespace std;



class Player
{
	enum LevelType
	{
		Easylevel = 0,
		Normallevel,
		Hardlevel,

		TotalLevel,
	};
public:
	Player(void);
	~Player(void);

	void PlayerInit(string PlayerFileName);

	void SetAmtOfClearedLevelEasy(short AmtOfClearedLevelEasy);
	short GetAmtOfClearedLevelEasy();
	void SetAmtOfClearedLevelNormal(short AmtOfClearedLevelNormal);
	short GetAmtOfClearedLevelNormal();
	void SetAmtOfClearedLevelHard(short AmtOfClearedLevelHard);
	short GetAmtOfClearedLevelHard();

	void SetEasyLevelUnlocked(bool EasyLevelUnlocked);
	bool GetEasyLevelUnlocked();
	void SetNormalLevelUnlocked(bool NormalLevelUnlocked);
	bool GetNormalLevelUnlocked();
	void SetHardLevelUnlocked(bool HardLevelUnlocked);
	bool GetHardLevelUnlocked();

	void SetAmtOfLevelDiff(short AmtOfLevelDiff);
	short GetAmtOfLevelDiff();

	void SetAmtOfCurrency(short AmtOfCurrency);
	short GetAmtOfCurrency();
	void SetAmtOfGold(short AmtOfGold);
	short GetAmtOfGold();

	void SetLevelStopAt(short LevelStopAt, short LevelDifficultyStopAt);
	short GetLevelStopAt();
	short GetLevelDifficultyStopAt();


	void SetLevelToStartAt(short LevelToStartAt);
	void SetLevelToDifficultyStartAt(short LevelToDifficultyStartAt);
	short GetLevelToStartAt();
	short GetLevelToDifficultyStartAt();

	void SetAmtOfBomb(short AmtOfBomb);
	short GetAmtOfBomb();
	void SetAmtOfBridge(short AmtOfBridge);
	short GetAmtOfBridge();

private:
	short AmtOfCurrency;
	short AmtOfGold;
	short AmtOfLevelDiff;

	short AmtOfBomb;
	short AmtOfBridge;

	short LevelToStartAt;
	short LevelToDifficultyStartAt;
	short LevelStopAt;
	short LevelDifficultyStopAt;
	short AmtOfClearedLevelEasy;
	bool EasyLevelUnlocked;
	short AmtOfClearedLevelNormal;
	bool NormalLevelUnlocked;
	short AmtOfClearedLevelHard;
	bool HardLevelUnlocked;
	LuaUsage* thePlayerinfoLua;
};
#endif