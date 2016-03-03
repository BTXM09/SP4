#include "LevelLoader.h"


LevelLoader::LevelLoader()
	: screenHeight(0)
	, screenWidth(0)
	, NumofTiles_Height(0)
	, NumofTiles_Width(0)
	, TileSize(0)
{
	screenMap.clear();
}

LevelLoader::~LevelLoader()
{
	screenMap.clear();
}

void LevelLoader::Init(const int screenHeight, const int screenWidth,
	const int NumofTiles_Height, const int NumofTiles_Width,
	const int TileSize)
{
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
	this->NumofTiles_Height = NumofTiles_Height;
	this->NumofTiles_Width = NumofTiles_Width;
	this->TileSize = TileSize;

	screenMap.resize(NumofTiles_Height);
	for (int i = 0; i < NumofTiles_Height; ++i)
		screenMap[i].resize(NumofTiles_Width);
}

bool LevelLoader::LevelLoaded(const string filename)
{
	if (LoadLevel(filename) == true)
	{
		printf("Level (%s) loaded successfully\n", filename.c_str());
		return true;
	}
	return false;
}

bool LevelLoader::LoadLevel(const string filename)
{
	int LineCounter = 0;
	int MaxNumOfColumns = 0;

	ifstream file(filename.c_str());
	if (file.is_open())
	{
		int i = 0, k = 0;
		while(file.good())
		{
			string LineofText = "";
			getline(file, LineofText);

			if (LineCounter >= NumofTiles_Height)
				break;

			// If this line is not a comment, process it
			if (!(LineofText.find("//*") == NULL) && LineofText != "")
			{
				if (LineCounter == 0)
				{
					// This is the first line of the level data
					string token;
					istringstream iss(LineofText);
					while (getline(iss, token, ','))
					{
						// Count the number of columns
						MaxNumOfColumns = atoi(token.c_str());
					}
					if (MaxNumOfColumns != NumofTiles_Width)
						return false;
				}
				else
				{
					int ColumnCounter = 0;

					string token;
					istringstream iss(LineofText);
					while (getline(iss, token, ',') && (ColumnCounter < NumofTiles_Width))
					{
						screenMap[LineCounter][ColumnCounter++] = atoi(token.c_str());
					}
				}
			}
			LineCounter++;
		}
	}
	return true;
}

int LevelLoader::getNumTile_Height()
{
	return NumofTiles_Height;
}

int LevelLoader::getNumTile_Width()
{
	return NumofTiles_Width;
}

int LevelLoader::getTileSize()
{
	return TileSize;
}