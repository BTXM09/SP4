#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();

	void Init(const int screenHeight, const int screenWidth,
		const int NumofTiles_Height, const int NumofTiles_Width,
		const int TileSize = 25);

	bool LevelLoaded(const string filename);
	int getNumTile_Height();		// Get number of tiles for screen height
	int getNumTile_Width();			// Get number of tiles for screen width
	int getTileSize();

	vector<vector<int>> screenMap;

private:
	int screenHeight;
	int screenWidth;
	int NumofTiles_Height;			// Number of tiles in screen's height
	int NumofTiles_Width;			// Number of tiles in screen's width
	int TileSize;

	bool LoadLevel(const string filename);
};

