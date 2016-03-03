#ifndef LUAUSAGE_H
#define LUAUSAGE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "lua.hpp"

using namespace std;

class LuaUsage
{
public:
	LuaUsage(void);
	~LuaUsage(void);
	//LuaUsage Checking for files
	bool LuaUsageCheckit(string LuaFileName);
	//LuaUsage Init & open files
	void LuaUsageInit(string LuaFileName);
	//LuaUsage Close files
	void LuaUsageClose();
	//LuaUsage Clean
	void clean();

	//Lua Get
	template<typename T>
	T get(const std::string& variableName) 
	{
		if (!LuaState) 
		{
			Seterrorstring(variableName, "Script is not loaded");
			return lua_getdefault<T>();
		}

		T result;
		if (lua_gettostack(variableName)) { // variable succesfully on top of stack
			result = lua_get<T>(variableName);
		}
		else {
			result = lua_getdefault<T>();
		}
		clean();
		return result;
	}
	//Lua GetToStack
	bool lua_gettostack(const std::string& variableName) 
	{
		level = 0;
		std::string var = "";
		for (unsigned int i = 0; i < variableName.size(); i++) 
		{
			if (variableName.at(i) == '.') 
			{
				if (level == 0) {
					lua_getglobal(LuaState, var.c_str());
				}
				else 
				{
					lua_getfield(LuaState, -1, var.c_str());
				}

				if (lua_isnil(LuaState, -1)) 
				{
					Seterrorstring(variableName, var + " is not defined");
					return false;
				}
				else 
				{
					var = "";
					level++;
				}
			}
			else 
			{
				var += variableName.at(i);
			}
		}
		if (level == 0) 
		{
			lua_getglobal(LuaState, var.c_str());
		}
		else 
		{
			lua_getfield(LuaState, -1, var.c_str());
		}
		if (lua_isnil(LuaState, -1)) 
		{
			Seterrorstring(variableName, var + " is not defined");
			return false;
		}

		return true;
	}

	//Template Style get
	template<typename T>
	T lua_get(const std::string& variableName) 
	{
		return 0;
	}
	//Template Style get(if it is not available)
	template<typename T>
	T lua_getdefault() 
	{
		return 0;
	}

	//Set up ErrorString of what is wrong
	void Seterrorstring(const string& Variablename, const string& reason);
	//Set up making of LuaErrorLog
	void LuaErrorLog();
private:
	//LuaState
	lua_State *LuaState;
	//ErrorString
	string Errorstring;
	//FileName
	string Filename;
	//Lua usage to check
	int level;
};
//LuaGet Boolean
template <>
inline bool LuaUsage::lua_get<bool>(const std::string& variableName)
{
	return (bool)lua_toboolean(LuaState, -1);
}
//LuaGet Float
template <>
inline float LuaUsage::lua_get<float>(const std::string& variableName)
{
	if (!lua_isnumber(LuaState, -1)) {
		Seterrorstring(variableName, "Not a number");
	}
	return (float)lua_tonumber(LuaState, -1);
}
//LuaGet Int
template <>
inline int LuaUsage::lua_get<int>(const std::string& variableName)
{
	if (!lua_isnumber(LuaState, -1)) {
		Seterrorstring(variableName, "Not a number");
	}
	return (int)lua_tonumber(LuaState, -1);
}
//LuaGet String
template <>
inline string LuaUsage::lua_get<std::string>(const std::string& variableName) {
	string s = "null";
	if (lua_isstring(LuaState, -1)) {
		s = string(lua_tostring(LuaState, -1));
	}
	else
	{
		Seterrorstring(variableName, "Not a string");
	}
	return s;
}
//LuaGet Default
template<>
inline string LuaUsage::lua_getdefault<std::string>() {
	return "null";
}

#endif