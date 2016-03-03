#include "Highscore.h"

Highscore::Highscore()
	: newScore(0)
{
}


Highscore::~Highscore()
{
}

void Highscore::addScore(int newScore)
{
	this->newScore = newScore;
}

int Highscore::getScore()
{
	return newScore;
}