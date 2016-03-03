#ifndef ALLLEVELDETAILS_H
#define ALLLEVELDETAILS_H

#include <iostream>
#include <string>
#include "LuaUsage.h"

using namespace std;

class AllLevelDetails
{
public:
	AllLevelDetails(void);
	~AllLevelDetails(void);
	//AllLevelDetails Init
	void AllLevelDetailsInit(string Varfilepath);
	//Get & Set of LevelCleared
	bool GetCleared();
	void SetCleared(bool m_Cleared);
	//Get & Set of CollectedKeys
	short GetCollectedKeys();
	void SetCollectedKeys(int m_CollectedKeys);
private:
	//LevelCleared
	bool m_Cleared;
	//Collectedkeys per level
	short m_CollectedKeys;

	
};
#endif