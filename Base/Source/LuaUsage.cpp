#include "LuaUsage.h"


LuaUsage::LuaUsage(void) 
:LuaState(NULL)
, Errorstring("")
, Filename("")
{
}

LuaUsage::~LuaUsage(void)
{
}
bool LuaUsage::LuaUsageCheckit(string LuaFileName)
{
	bool Returned = false;
	Filename = LuaFileName;
	LuaState = lua_open();
	string LuaOpenFilename = "Lua/";
	LuaOpenFilename = LuaOpenFilename + LuaFileName;
	LuaOpenFilename = LuaOpenFilename + ".lua";
	if (luaL_loadfile(LuaState, LuaOpenFilename.c_str()) || lua_pcall(LuaState, 0, 0, 0))
	{
		Returned = true;
		std::cout << "Error: failed to load (" << LuaFileName << ")" << std::endl;
		LuaState = NULL;
	}
	if (LuaState)
		luaL_openlibs(LuaState);
	LuaUsageClose();
	return Returned;
}
void LuaUsage::LuaUsageInit(string LuaFileName)
{
	Filename = LuaFileName;
	LuaState = lua_open();
	string LuaOpenFilename = "Lua/";
	LuaOpenFilename = LuaOpenFilename + LuaFileName;
	LuaOpenFilename = LuaOpenFilename + ".lua";
	if (luaL_loadfile(LuaState, LuaOpenFilename.c_str()) || lua_pcall(LuaState, 0, 0, 0))
	{
		std::cout << "Error: failed to load (" << LuaFileName << ")" << std::endl;
		LuaState = NULL;
	}
	if (LuaState)
		luaL_openlibs(LuaState);
}

void LuaUsage::Seterrorstring(const string& Variablename, const string& reason)
{
	Errorstring = Errorstring + Variablename + ": " + reason + "\n";
}

void LuaUsage::LuaUsageClose()
{
	if (LuaState)
		lua_close(LuaState);
	if (Errorstring.size() > 1)
	{
		LuaErrorLog();
	}
}
void LuaUsage::clean()
{
	int i = lua_gettop(LuaState);
	lua_pop(LuaState, i);
}
void LuaUsage::LuaErrorLog()
{
	string thefilename = "Lua/";
	thefilename = thefilename + this->Filename;
	thefilename = thefilename + "Error.lua";
	ofstream Error(thefilename);
	if (Error.is_open())
	{
		Error << "--ErrorLog--" << endl;
		Error << this->Errorstring << endl;
	}
}
