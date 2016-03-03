#include "Save.h"
Save::Save(void)
{

}

Save::~Save(void)
{
}

string Save::BoolToStringConversion(bool convert)
{
	string ReturnString = "";
	if (convert)
		ReturnString = "true";
	else
		ReturnString = "false";
	return ReturnString;
}

void Save::SaveEveryThing(int FileNumber)
{
	switch (FileNumber)
	{

	case 0:
	{
			  ofstream SaveFile("Lua/Application.lua");
			  if (SaveFile.is_open())
			  {
				  SaveFile << "--ScreenWidth, ScreenHeight--\nWindowSize = {\nScreenSize = {\nScreenWidth = 800, ScreenHeight = 600\n}\n}";
			  }
	}

	case 1:
	{
			  ofstream SaveFile("Lua/Button.lua");
			  if (SaveFile.is_open())
			  {
				  SaveFile << "--Button Save File--" << endl;
				  SaveFile << "  Button = {" << endl;
				  SaveFile << "  Play = { Position = { x = 295, y = 290 }, TempPosition = { x = -100, y = 290 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  Instruction = { Position = { x = 295, y = 235 }, TempPosition = { x = 800, y = 235 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  Highscore = { Position = { x = 295, y = 180 }, TempPosition = { x = -100, y = 180 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  Option = { Position = { x = 295, y = 125 }, TempPosition = { x = 800, y = 125 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  Exit = { Position = { x = 295, y = 70 }, TempPosition = { x = -100, y = 70 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  LevelSelect = { Position = { x = 295, y = 350 }, TempPosition = { x = -100, y = 350 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  Shop = { Position = { x = 295, y = 295 }, TempPosition = { x = 800, y = 295 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  ContinueLevel = { Position = { x = 295, y = 240 }, TempPosition = { x = -100, y = 240 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  DifficultyTutorial = { Position = { x = 295, y = 405 }, TempPosition = { x = 800, y = 405 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  DifficultyEasy = { Position = { x = 295, y = 350 }, TempPosition = { x = -100, y = 350 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  DifficultyNormal = { Position = { x = 295, y = 295 }, TempPosition = { x = 800, y = 295 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  DifficultyHard = { Position = { x = 295, y = 240 }, TempPosition = { x = -100, y = 240 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  Level1 = { Position = { x = 295, y = 350 }, TempPosition = { x = -100, y = 350 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  Level2 = { Position = { x = 295, y = 295 }, TempPosition = { x = 800, y = 295 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  Level3 = { Position = { x = 295, y = 240 }, TempPosition = { x = -100, y = 240 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  Level4 = { Position = { x = 295, y = 185 }, TempPosition = { x = 800, y = 185 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  HighscoreTutorial = { Position = { x = 295, y = 330 }, TempPosition = { x = -100, y = 330 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  HighscoreEasy = { Position = { x = 295, y = 275 }, TempPosition = { x = 800, y = 275 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  HighscoreNormal = { Position = { x = 295, y = 220 }, TempPosition = { x = -100, y = 220 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  HighscoreHard = { Position = { x = 295, y = 165 }, TempPosition = { x = 800, y = 165 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  HighscoreLevel1 = { Position = { x = 295, y = 275 }, TempPosition = { x = 800, y = 275 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  HighscoreLevel2 = { Position = { x = 295, y = 220 }, TempPosition = { x = -100, y = 220 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  HighscoreLevel3 = { Position = { x = 295, y = 165 }, TempPosition = { x = 800, y = 165 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  HighscoreLevel4 = { Position = { x = 295, y = 110 }, TempPosition = { x = -100, y = 110 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  Resume = { Position = { x = 295, y = 350 }, TempPosition = { x = -100, y = 350 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  QuitToMenu = { Position = { x = 295, y = 295 }, TempPosition = { x = 800, y = 295 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  NextLevel = { Position = { x = 295, y = 350 }, TempPosition = { x = -100, y = 350 }, Offset = { x = 100, y = 5 }, Speed = 1000.0 }," << endl;
				  SaveFile << "  }" << endl;

			  }
	}

	case 2:
	{
			  ofstream SaveFile("Lua/Item.lua");
			  if (SaveFile.is_open())
			  {
				  SaveFile << "--Item Save File--" << endl;
				  SaveFile << "Amount = 5" << endl;
				  SaveFile << "Item = {" << endl;
				  SaveFile << "Number1 = { Name = \"EasyLevel\", Bought = false, Price = 2 }," << endl;
				  SaveFile << "Number2 = { Name = \"NormalLevel\", Bought = false, Price = 12 }," << endl;
				  SaveFile << "Number3 = { Name = \"HardLevel\", Bought = false, Price = 15 }," << endl;
				  SaveFile << "Number4 = { Name = \"Bomb\", Bought = false, Price = 100}," << endl; 
				  SaveFile << "Number5 = { Name = \"Ladder\", Bought = false, Price = 50}" << endl;
				  SaveFile << "}" << endl;
			  }
	}

	case 3:
	{
			  ofstream SaveFile("Lua/Level.lua");
			  if (SaveFile.is_open())
			  {
			  }
	}

	case 4:
	{
			  ofstream SaveFile("Lua/LeveltoSave.lua");
			  if (SaveFile.is_open())
			  {
				  SaveFile << "--Level Template--\n--LevelNumber = { Key }--\nAmountOfLevel = 4\nAmountOfDiff = 4\nAmountOfTutorialDiff = 1" << endl;
				  SaveFile << "Level = {" << endl;
				  SaveFile << "Tutorial = {\nLevel1 = { Cleared = false, CollectedKeys = 0 }\n }," << endl;
				  SaveFile << "Easy = { \nLevel1 = { Cleared = false, CollectedKeys = 0, Highscore = 0 }, \nLevel2 = { Cleared = false, CollectedKeys = 0, Highscore = 0 }, \nLevel3 = { Cleared = false, CollectedKeys = 0, Highscore = 0 }, \nLevel4 = { Cleared = false, CollectedKeys = 0, Highscore = 0 }\n }, " << endl;
				  SaveFile << "Normal = {\nLevel1 = { Cleared = false, CollectedKeys = 0, Highscore = 0 },\nLevel2 = { Cleared = false, CollectedKeys = 0, Highscore = 0 },\nLevel3 = { Cleared = false, CollectedKeys = 0, Highscore = 0 },\nLevel4 = { Cleared = false, CollectedKeys = 0, Highscore = 0 }\n}," << endl;
				  SaveFile << "Hard = {\nLevel1 = { Cleared = false, CollectedKeys = 0, Highscore = 0 },\nLevel2 = { Cleared = false, CollectedKeys = 0, Highscore = 0 },\nLevel3 = { Cleared = false, CollectedKeys = 0, Highscore = 0 },\nLevel4 = { Cleared = false, CollectedKeys = 0, Highscore = 0 }\n }" << endl;
				  SaveFile << "}" << endl;

			  }
	}

	case 5:
	{
			  ofstream SaveFile("Lua/Player.lua");
			  if (SaveFile.is_open())
			  {
				  SaveFile << "--Player Save File--\nLevelAmt = 3\nCurrency = 0\nGoldCurrency = 0\nBombAmt = 0\nBridgeAmt = 0\nLevelToStartAt = 0\nLevelDifficultyToStartAt = 0\nLevelStopAt = 0\nLevelDifficultyStopAt = 0\nPlayer = { \nEASYLEVEL = { \nLevelCleared = 0, LevelUnlocked = false\n }, \nNORMALLEVEL = { \nLevelCleared = 0, LevelUnlocked = false\n }, \nHARDLEVEL = { \nLevelCleared = 0, LevelUnlocked = false\n }\n }";
			  }
	}

	case 6:
	{
			  ofstream SaveFile("Lua/Sound.lua");
			  if (SaveFile.is_open())
			  {
				  SaveFile << "Volume = 0.8";
			  }
	}

	case 7:
	{
			  ofstream SaveFile("Lua/Sprite.lua");
			  if (SaveFile.is_open())
			  {
				  SaveFile << "--Star Sprite = { row, col, float MinTime, float MaxTime }--\n--Time is use to swap--\n--Star = { 6, 3, 0.5, 1.0 }--\nStarRow = 6\nStarCol = 3\nStarMinTime = 0.5\nStarMaxTime = 1.0";
			  }
	}

	}
}

void Save::SaveLevelStuff(vector<AllLevelDetails*> theLevelDetailsHolder,int maxleveltutorial, int maxlevel, int maxdifficulty)
{
	ofstream SaveFile("Lua/LeveltoSave.lua");
	if (SaveFile.is_open())
	{
		SaveFile << "--Level Template--" << endl;
		SaveFile << "--LevelNumber = { Key }--" << endl;
		SaveFile << "AmountOfLevel = " << maxlevel << endl;
		SaveFile << "AmountOfDiff = " << maxdifficulty << endl;
		SaveFile << "AmountOfTutorialDiff = " << maxleveltutorial << endl;
		SaveFile << "Level = {" << endl;
		for (int j = 0; j < maxdifficulty; ++j)
		{
			switch (j)
			{
			case 0:
			{
					  SaveFile << "Tutorial = {" << endl;
					  for (int i = 0; i < maxleveltutorial; ++i)
					  {
						  string itemnumber = "Level";
						  itemnumber = itemnumber + to_string(i + 1);
						  SaveFile << OpenTable(itemnumber) << SaveTableIndiv("Cleared", 0, BoolToStringConversion(theLevelDetailsHolder[((j * 4) + i)]->GetCleared()), "") << "," << SaveTableIndiv("CollectedKeys", theLevelDetailsHolder[((j * 4) + i)]->GetCollectedKeys());
						  if (i == (maxleveltutorial - 1))
							  SaveFile << CloseTable(true) << endl;
						  else
							  SaveFile << CloseTable() << endl;
					  }
					  SaveFile << "}," << endl;
					  break;
			}
			case 1:
			{
					  SaveFile << "Easy = {" << endl;
					  for (int i = 0; i < maxlevel; ++i)
					  {
						  string itemnumber = "Level";
						  itemnumber = itemnumber + to_string(i + 1);
						  SaveFile << OpenTable(itemnumber) << SaveTableIndiv("Cleared", 0, BoolToStringConversion(theLevelDetailsHolder[((j - 1) * 4 + (i + 1))]->GetCleared()), "") << "," << SaveTableIndiv("CollectedKeys", theLevelDetailsHolder[((j - 1) * 4 + (i + 1))]->GetCollectedKeys());
						  if (i == (maxlevel - 1))
							  SaveFile << CloseTable(true) << endl;
						  else
							  SaveFile << CloseTable() << endl;
					  }
					  SaveFile << "}," << endl;
					  break;
			}
			case 2:
			{
					  SaveFile << "Normal = {" << endl;
					  for (int i = 0; i < maxlevel; ++i)
					  {
						  string itemnumber = "Level";
						  itemnumber = itemnumber + to_string(i + 1); SaveFile << OpenTable(itemnumber) << SaveTableIndiv("Cleared", 0, BoolToStringConversion(theLevelDetailsHolder[((j - 1) * 4 + (i + 1))]->GetCleared()), "") << "," << SaveTableIndiv("CollectedKeys", theLevelDetailsHolder[((j - 1) * 4 + (i + 1))]->GetCollectedKeys());
						  if (i == (maxlevel - 1))
							  SaveFile << CloseTable(true) << endl;
						  else
							  SaveFile << CloseTable() << endl;
					  }
					  SaveFile << "}," << endl;
					  break;
			}
			case 3:
			{
					  SaveFile << "Hard = {" << endl;
					  for (int i = 0; i < maxlevel; ++i)
					  {
						  string itemnumber = "Level";
						  itemnumber = itemnumber + to_string(i + 1); SaveFile << OpenTable(itemnumber) << SaveTableIndiv("Cleared", 0, BoolToStringConversion(theLevelDetailsHolder[((j - 1) * 4 + (i + 1))]->GetCleared()), "") << "," << SaveTableIndiv("CollectedKeys", theLevelDetailsHolder[((j - 1) * 4 + (i + 1))]->GetCollectedKeys());
						  if (i == (maxlevel - 1))
							  SaveFile << CloseTable(true) << endl;
						  else
							  SaveFile << CloseTable() << endl;
					  }
					  SaveFile << "}" << endl;
					  break;
			}
			}
		}
		SaveFile << "}" << endl;
	}
}

void Save::SaveMusic(float sound)
{
	ofstream SaveFile("Lua/Sound.lua");
	if (SaveFile.is_open())
	{
		SaveFile << "Volume = " << sound << endl;
	}
}
void Save::SaveShop(Shop* shopinfo)
{
	ofstream SaveFile("Lua/Item.lua");
	if (SaveFile.is_open())
	{
		SaveFile << "--Item Save File--" << endl;
		SaveFile << "Amount = " << shopinfo->theItemHolder.size() << endl;
		SaveFile << "Item = {" << endl;
		
		for (int i = 0; i < shopinfo->theItemHolder.size(); ++i)
		{
			string itemnumber = "Number";
			itemnumber = itemnumber + to_string(i + 1);
			SaveFile << OpenTable(itemnumber) << endl;
			SaveFile << SaveTableIndiv("Name", 0, "",shopinfo->theItemHolder[i]->GetName()) << ",";
			SaveFile << SaveTableIndiv("Bought", 0, BoolToStringConversion(shopinfo->theItemHolder[i]->GetBought()),"") << ",";
			SaveFile << SaveTableIndiv("Price", shopinfo->theItemHolder[i]->GetPrice()) << endl;
			if (i == shopinfo->theItemHolder.size()-1)
				SaveFile << CloseTable(true) << endl;
			else
				SaveFile << CloseTable() << endl;
		}
		SaveFile << "}" << endl;
	}
}
void Save::SavePlayer(Player* playerinfo)
{
	ofstream SaveFile("Lua/Player.lua");
	if (SaveFile.is_open())
	{
		SaveFile << "--Player Save File--" << endl;
		SaveFile << "LevelAmt = " << playerinfo->GetAmtOfLevelDiff() << endl;
		SaveFile << "Currency = " << playerinfo->GetAmtOfCurrency() << endl;
		SaveFile << "GoldCurrency = " << playerinfo->GetAmtOfGold() << endl;
		SaveFile << "BombAmt = " << playerinfo->GetAmtOfBomb() << endl;
		SaveFile << "BridgeAmt = " << playerinfo->GetAmtOfBridge() << endl;
		SaveFile << "LevelToStartAt = " << playerinfo->GetLevelToStartAt() << endl;
		SaveFile << "LevelDifficultyToStartAt = " << playerinfo->GetLevelToDifficultyStartAt() << endl;
		SaveFile << "LevelStopAt = " << playerinfo->GetLevelStopAt() << endl;
		SaveFile << "LevelDifficultyStopAt = " << playerinfo->GetLevelDifficultyStopAt() << endl;
		SaveFile << "Player = {" << endl;
		SaveFile << OpenTable("EASYLEVEL") << endl;
		SaveFile << SaveTableIndiv("LevelCleared", playerinfo->GetAmtOfClearedLevelEasy()) << ",";
		SaveFile << SaveTableIndiv("LevelUnlocked", 0, BoolToStringConversion(playerinfo->GetEasyLevelUnlocked())) << endl;
		SaveFile << CloseTable() << endl;
		SaveFile << OpenTable("NORMALLEVEL") << endl;
		SaveFile << SaveTableIndiv("LevelCleared", playerinfo->GetAmtOfClearedLevelNormal()) << ",";
		SaveFile << SaveTableIndiv("LevelUnlocked", 0, BoolToStringConversion(playerinfo->GetNormalLevelUnlocked())) << endl;
		//SaveFile << "		LevelCleared = " << playerinfo->GetAmtOfClearedLevelNormal() << "," << "LevelUnlocked = " << BoolToStringConversion(playerinfo->GetNormalLevelUnlocked()) << endl;
		SaveFile << CloseTable() << endl;
		SaveFile << OpenTable("HARDLEVEL") << endl; 
		SaveFile << SaveTableIndiv("LevelCleared", playerinfo->GetAmtOfClearedLevelHard()) << ",";
		SaveFile << SaveTableIndiv("LevelUnlocked", 0, BoolToStringConversion(playerinfo->GetHardLevelUnlocked())) << endl;
		//SaveFile << "		LevelCleared = " << playerinfo->GetAmtOfClearedLevelHard() << "," << "LevelUnlocked = " << BoolToStringConversion(playerinfo->GetHardLevelUnlocked()) << endl;
		SaveFile << CloseTable(true) << endl;
		SaveFile << "}"  << endl;
		SaveFile.close();
	}
}
string Save::SaveTableIndiv(string text, int integertosave, string booltosave, string stringtosave)
{
	string returnstring = text;
	if (booltosave == "" && stringtosave == "")
		returnstring = returnstring + " = " + to_string(integertosave);
	else if (stringtosave == "")
		returnstring = returnstring + " = " + booltosave;
	else
		returnstring = returnstring + " = \"" + stringtosave + "\"";
	return returnstring;
}
string Save::OpenTable(string text)
{
	string returnstring = text + " = {";
	return returnstring;
}
string Save::CloseTable(bool close)
{
	if (!close)
		return "},";
	else
		return "}";
}