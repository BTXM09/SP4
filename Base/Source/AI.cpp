#include "AI.h"
#include "Application.h"

using namespace std;

cAI::cAI()
{
}

cAI::~cAI()
{
	if (this->WayPoints.size() > 0)
	{
		for (int a = 0; a < WayPoints.size(); a++)
		{
			delete WayPoints[a];
		}
		WayPoints.clear();
	}
}

void cAI::init()
{
	FSM = STATE_IDLE;
	waypointIndex = 0;
	speedMultiplier = 0;
}

cAI::FSM_ENEMY cAI::getState()
{
	return FSM;
}

void cAI::setDifficulty(short difficulty)
{
	this->difficulty = difficulty;
}

short cAI::getDifficulty()
{
	return this->difficulty;
}

void cAI::setPos(int posX, int posY)
{
	this->position = Vector3(posX, posY, 0);
}

void cAI::setWaypoint(int wpX, int wpY)
{
	this->WayPoints.push_back(new Vector3(wpX, wpY, 0));
	nextPosition = WayPoints[0];
}

Vector3 cAI::getPos()
{
	return position;
}

static float limit = 1.f;
static float timer = 0.f;

void cAI::update(Vector3 PlayerPos, bool &playermoved)
{
	switch (FSM)
	{
		case STATE_MOVE:
			UpdateWaypoint();
			break;

		case STATE_IDLE:
			if (Application::IsKeyPressed(VK_RETURN))
			{
				//FSM = STATE_MOVE;
			}
			if (DetectPlayer(PlayerPos))
			{
				FSM = STATE_ATTACK;
				cout << "STATE_ATTACK" << endl;
			}
			break;

		case STATE_ATTACK:

			speedMultiplier = getDifficulty();
			timer += (0.03 * speedMultiplier);

			if (playermoved && timer >= limit)
			{
				UpdateWaypoint();
				*nextPosition = PlayerPos;
				
				timer = 0;
			}
			cout << "speed: " << speedMultiplier << endl;
			break;

		default:
			break;
	}
}

void cAI::UpdateWaypoint()
{
	cout << "waypointIndex: " << waypointIndex << endl;
	if (this->position == *nextPosition)
	{
		/*if (waypointIndex >= WayPoints.size() - 1)
		{
			waypointIndex = 0;
		}
		else
		{
			waypointIndex++;
		}*/

		nextPosition = WayPoints[waypointIndex];
	}
	
	if ((*nextPosition).x != this->position.x)
	{
		if ((*nextPosition).x < this->position.x)	// Move Left
		{
			this->position.x--;
		}
		else if ((*nextPosition).x > this->position.x)	// Move Right
		{
			this->position.x++;
		}
	}
	else if ((*nextPosition).x == this->position.x)
	{
		if ((*nextPosition).y != this->position.y)
		{
			if ((*nextPosition).y < this->position.y)	// Move Down
			{
				this->position.y--;
			}
			else if ((*nextPosition).y > this->position.y)	// Move Up
			{
				this->position.y++;
			}
		}
	}
}

bool cAI::DetectPlayer(Vector3 PlayerPos)
{
	int XDiff = this->position.x - PlayerPos.x;
	int YDiff = this->position.y - PlayerPos.y;

	if (XDiff < 0)
	{
		XDiff = -XDiff;
	}
	if (YDiff < 0)
	{
		YDiff = -YDiff;
	}

	if (XDiff + YDiff <= 50)
	{
		return true;
	}
	return false;
}