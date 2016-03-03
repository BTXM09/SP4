#include "HighscoreData.h"


HighscoreData::HighscoreData()
: MAX_SCORES(6)
, currentSize(0)
, value(-1)
{
	for (int i = 0; i < MAX_SCORES; i++)
		this->scores[i] = Highscore::Highscore();

	this->Player.addScore(value);
}

HighscoreData::~HighscoreData()
{
}

int HighscoreData::ReadTextFile(string filename)
{
	ifstream is(filename);
	int i = 0;

	if (is.is_open()) // if the file is open
	{
		while (!is.eof()) // while it is not the end of the file
		{
			int temp; // make a temporary variable
			is >> temp; // write the value into this temporary value.
			this->scores[i].addScore(temp); // add the temp value into the highscore database

			i++; // increment the i
			currentSize++;
		}
		//is.close();
	}
	return i;
}

int HighscoreData::WriteTextFile(string filename)
{
	ofstream of(filename);
	int i = 0;
	if (of.is_open()) // if the file is open
	{
		while (i < MAX_SCORES - 1)
		{
			of << this->scores[i].getScore(); // write the score into the text file
			if (i < MAX_SCORES - 2)
			{
				of << endl;
			}
			i++; // increment the i
			currentSize--;
		}
	}
	return i;
}

void HighscoreData::AddScores(Highscore theHighscore)
{
	if (currentSize < MAX_SCORES)
	{
		this->scores[currentSize] = theHighscore;
		currentSize++;
		MergeSortHighscore(this->scores, 0, currentSize - 1); // sort
	}
	else
	{
		this->scores[MAX_SCORES - 1] = theHighscore;
		MergeSortHighscore(this->scores, 0, currentSize - 1); // sort
	}
}

void HighscoreData::UpdateHighscore(Highscore PlayerScore)
{
	if (this->Player.getScore() != PlayerScore.getScore()) // if my highscore is not player score
	{
		this->Player.addScore(PlayerScore.getScore()); // add the score
		AddScores(this->Player);
		MergeSortHighscore(this->scores, 0, MAX_SCORES - 1);
	}
}

void HighscoreData::MergeSortHighscore(Highscore list[], int first, int last)
{
	if (first < last)
	{
		int middle = (first + last) / 2;
		MergeSortHighscore(list, first, middle);
		MergeSortHighscore(list, middle + 1, last);
		MergeHighscore(list, first, middle, last);
	}
}

void HighscoreData::MergeHighscore(Highscore list[], int first, int middle, int last)
{
	//temp array to hold 1st list
	Highscore *temp = new Highscore[middle - first + 1];
	//i is index for temp array, 
	//j is index for 2nd list, 
	//k is index for combine list
	int i, j, k;
	for (j = first, i = 0; j <= middle; i++, j++)
	{
		temp[i] = list[j]; //duplicate 1st list
	}
	i = 0; k = first;
	while (k < j && j <= last)
	{
		//if element from 1st list > 2nd list 
		if (temp[i].getScore() >= list[j].getScore())
		{
			list[k++] = temp[i++]; //copy from 1st list 
		}
		else
		{
			list[k++] = list[j++]; //copy from 2nd list 
		}
	}
	while (k < j) //copy remaining elements in temp, if any 
	{
		list[k++] = temp[i++];
	}
	delete[] temp; //remove temp array 
}

int HighscoreData::GetAllHighscores(int index)
{
	return scores[index].getScore();
}

int HighscoreData::GetCurrentSize()
{
	return this->currentSize;
}

void HighscoreData::setPlayer(Highscore theHighscore)
{
	this->Player = theHighscore;
}

Highscore HighscoreData::GetPlayer()
{
	return this->Player;
}