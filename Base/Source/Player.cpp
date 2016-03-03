
#include "Player.h"


Player::Player(void) 
: thePlayerinfoLua(NULL)
, LevelToStartAt(0)
, LevelToDifficultyStartAt(0)
, LevelStopAt(0)
, LevelDifficultyStopAt(0)
, AmtOfClearedLevelEasy(0)
, EasyLevelUnlocked(false)
, AmtOfClearedLevelNormal(0)
, NormalLevelUnlocked(false)
, AmtOfClearedLevelHard(0)
, HardLevelUnlocked(false)
{
}

Player::~Player(void)
{
	if (thePlayerinfoLua)
	{
		delete thePlayerinfoLua;
		thePlayerinfoLua = NULL;
	}
}

void Player::PlayerInit(string PlayerFileName)
{
	thePlayerinfoLua = new LuaUsage();
	thePlayerinfoLua->LuaUsageInit(PlayerFileName);
	AmtOfCurrency = thePlayerinfoLua->get<int>("Currency");
	AmtOfLevelDiff = thePlayerinfoLua->get<int>("LevelAmt");
	AmtOfGold = thePlayerinfoLua->get<int>("GoldCurrency");
	AmtOfBomb = thePlayerinfoLua->get<int>("BombAmt");
	AmtOfBridge = thePlayerinfoLua->get<int>("BridgeAmt");
	LevelToStartAt = thePlayerinfoLua->get<int>("LevelToStartAt");
	LevelToDifficultyStartAt = thePlayerinfoLua->get<int>("LevelDifficultyToStartAt");
	LevelStopAt = thePlayerinfoLua->get<int>("LevelStopAt");
	LevelDifficultyStopAt = thePlayerinfoLua->get<int>("LevelDifficultyStopAt");
	for (int i = 0; i < AmtOfLevelDiff; ++i)
	{
		string GetLevel = PlayerFileName;
		switch (i)
		{
		case Easylevel:
		{
						  GetLevel = GetLevel + ".EASYLEVEL.";
						  string IntLevel = GetLevel + "LevelCleared";
						  string BoolLevel = GetLevel + "LevelUnlocked";
						  this->AmtOfClearedLevelEasy = thePlayerinfoLua->get<int>(IntLevel);
						  this->EasyLevelUnlocked = thePlayerinfoLua->get<bool>(BoolLevel);
						  break;
		}
		case Normallevel:
		{
							GetLevel = GetLevel + ".NORMALLEVEL.";
							string IntLevel = GetLevel + "LevelCleared";
							string BoolLevel = GetLevel + "LevelUnlocked";
							this->AmtOfClearedLevelNormal = thePlayerinfoLua->get<int>(IntLevel);
							this->NormalLevelUnlocked = thePlayerinfoLua->get<bool>(BoolLevel);
							break;
		}
		case Hardlevel:
		{
						  GetLevel = GetLevel + ".HARDLEVEL.";
						  string IntLevel = GetLevel + "LevelCleared";
						  string BoolLevel = GetLevel + "LevelUnlocked";
						  this->AmtOfClearedLevelHard = thePlayerinfoLua->get<int>(IntLevel);
						  this->HardLevelUnlocked = thePlayerinfoLua->get<bool>(BoolLevel);
						  break;
		}
		}
	}
	thePlayerinfoLua->LuaUsageClose();
}

void Player::SetAmtOfClearedLevelEasy(short AmtOfClearedLevelEasy)
{
	this->AmtOfClearedLevelEasy = AmtOfClearedLevelEasy;
}
short Player::GetAmtOfClearedLevelEasy()
{
	return this->AmtOfClearedLevelEasy;
}
void Player::SetAmtOfClearedLevelNormal(short AmtOfClearedLevelNormal)
{
	this->AmtOfClearedLevelNormal = AmtOfClearedLevelNormal;
}
short Player::GetAmtOfClearedLevelNormal()
{
	return this->AmtOfClearedLevelNormal;
}
void Player::SetAmtOfClearedLevelHard(short AmtOfClearedLevelHard)
{
	this->AmtOfClearedLevelHard = AmtOfClearedLevelHard;
}
short Player::GetAmtOfClearedLevelHard()
{
	return this->AmtOfClearedLevelHard;
}

void Player::SetEasyLevelUnlocked(bool EasyLevelUnlocked)
{
	this->EasyLevelUnlocked = EasyLevelUnlocked;
}
bool Player::GetEasyLevelUnlocked()
{
	return this->EasyLevelUnlocked;
}
void Player::SetNormalLevelUnlocked(bool NormalLevelUnlocked)
{
	this->NormalLevelUnlocked = NormalLevelUnlocked;
}
bool Player::GetNormalLevelUnlocked()
{
	return this->NormalLevelUnlocked;
}
void Player::SetHardLevelUnlocked(bool HardLevelUnlocked)
{
	this->HardLevelUnlocked = HardLevelUnlocked;
}
bool Player::GetHardLevelUnlocked()
{
	return this->HardLevelUnlocked;
}
void Player::SetAmtOfLevelDiff(short AmtOfLevelDiff)
{
	this->AmtOfLevelDiff = AmtOfLevelDiff;
}
short Player::GetAmtOfLevelDiff()
{
	return this->AmtOfLevelDiff;
}

void Player::SetAmtOfCurrency(short AmtOfCurrency)
{
	this->AmtOfCurrency = AmtOfCurrency;
}
short Player::GetAmtOfCurrency()
{
	return this->AmtOfCurrency;
}

void Player::SetAmtOfGold(short AmtOfGold)
{
	this->AmtOfGold = AmtOfGold;
}
short Player::GetAmtOfGold()
{
	return this->AmtOfGold;
}

void Player::SetLevelStopAt(short LevelStopAt, short LevelDifficultyStopAt)
{
	this->LevelStopAt = LevelStopAt;
	this->LevelDifficultyStopAt = LevelDifficultyStopAt;
}
short Player::GetLevelStopAt()
{
	return this->LevelStopAt;
}

short Player::GetLevelDifficultyStopAt()
{
	return this->LevelDifficultyStopAt;
}

short Player::GetLevelToStartAt()
{
	return this->LevelToStartAt;
}
short Player::GetLevelToDifficultyStartAt()
{
	return this->LevelToDifficultyStartAt;
}

void Player::SetLevelToStartAt(short LevelToStartAt)
{
	this->LevelToStartAt = LevelToStartAt;
}
void Player::SetLevelToDifficultyStartAt(short LevelToDifficultyStartAt)
{
	this->LevelToDifficultyStartAt = LevelToDifficultyStartAt;
}

void Player::SetAmtOfBomb(short AmtOfBomb)
{
	this->AmtOfBomb = AmtOfBomb;
}
short Player::GetAmtOfBomb()
{
	return AmtOfBomb;
}
void Player::SetAmtOfBridge(short AmtOfBridge)
{
	this->AmtOfBridge = AmtOfBridge;
}
short Player::GetAmtOfBridge()
{
	return AmtOfBridge;
}