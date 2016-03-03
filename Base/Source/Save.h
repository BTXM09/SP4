#ifndef SAVE_H
#define SAVE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Player.h"
#include "Shop.h"
#include "LevelDetails.h"
#include "AllLevelDetails.h"

using namespace std;

class Save
{
public:
	Save(void);
	~Save(void);
	//In case of emergency(Lua files Deleted!)
	void SaveEveryThing(int FileNumber);
	//Boolean String Conversion
	string BoolToStringConversion(bool convert);
	//Save AllLevelDetails
	void SaveLevelStuff(vector<AllLevelDetails*> theLevelDetailsHolder, int maxleveltutorial, int maxlevel, int maxdifficulty);
	//Save Playerinfo
	void SavePlayer(Player* playerinfo);
	//Save Music
	void SaveMusic(float sound);
	//Save Shop
	void SaveShop(Shop* shopinfo);
	//Lua Open Table
	string OpenTable(string text);
	//Lua Save Table Indiv
	string SaveTableIndiv(string text, int integertosave = 0, string booltosave = "", string stringtosave = "");
	//Lua Close Table
	string CloseTable(bool close = false);
private:
};
#endif