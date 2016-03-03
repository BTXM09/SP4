#include "AllLevelDetails.h"


AllLevelDetails::AllLevelDetails(void) 
{
}

AllLevelDetails::~AllLevelDetails(void)
{
}

void AllLevelDetails::AllLevelDetailsInit(string Varfilepath)
{
	LuaUsage* theAllLevelDetailsinfoLua = new LuaUsage();
	theAllLevelDetailsinfoLua->LuaUsageInit("LeveltoSave");
	this->m_Cleared = theAllLevelDetailsinfoLua->get<bool>((Varfilepath + "Cleared"));
	this->m_CollectedKeys = theAllLevelDetailsinfoLua->get<int>((Varfilepath + "CollectedKeys"));
	theAllLevelDetailsinfoLua->LuaUsageClose();
	delete theAllLevelDetailsinfoLua;
	theAllLevelDetailsinfoLua = NULL;
}


void AllLevelDetails::SetCollectedKeys(int m_CollectedKeys)
{
	this->m_CollectedKeys = m_CollectedKeys;
}
short AllLevelDetails::GetCollectedKeys()
{
	return this->m_CollectedKeys;
}

void AllLevelDetails::SetCleared(bool m_Cleared)
{
	this->m_Cleared = m_Cleared;
}
bool AllLevelDetails::GetCleared()
{
	return m_Cleared;
}