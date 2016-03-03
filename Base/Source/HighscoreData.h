#pragma once
#include "Highscore.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class HighscoreData
{
private:
	int currentSize;
	int value;
	int MAX_SCORES;
	Highscore scores[6]; // Make the array of scores, 6 is the limit
	Highscore Player;

public:
	HighscoreData();
	~HighscoreData();

	int ReadTextFile(string filename); // read from text file
	int WriteTextFile(string filename); // write to text file

	void UpdateHighscore(Highscore PlayerScore);
	void AddScores(Highscore theHighscore);

	void MergeHighscore(Highscore list[], int first, int middle, int last);
	void MergeSortHighscore(Highscore list[], int first, int last);

	int GetAllHighscores(int index);
	int GetCurrentSize();
	void setPlayer(Highscore theHighscore);
	Highscore GetPlayer();
};

