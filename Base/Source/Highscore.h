#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Highscore
{
private:
	int newScore;

public:
	Highscore();
	~Highscore();

	void addScore(int newScore);
	int getScore();
};

