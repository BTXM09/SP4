#ifndef AI_H
#define AI_H


#include <vector>
#include "Vector3.h"

class cAI
{
public:
	enum FSM_ENEMY
	{
		STATE_MOVE,
		STATE_IDLE,
		STATE_ATTACK,

	};


	cAI();
	virtual ~cAI();

	void init();
	void update(Vector3 PlayerPos, bool &playermoved);

	void setPos(int posX, int posY);
	void setWaypoint(int wpX, int wpY);
	void UpdateWaypoint();
	Vector3 getPos();

	bool DetectPlayer(Vector3 PlayerPos);

	FSM_ENEMY getState();
	//void setState(FSM_ENEMY state);

	void setDifficulty(short difficulty);
	short getDifficulty();

private:
	int waypointIndex;
	FSM_ENEMY FSM;
	std::vector<Vector3*> WayPoints;
	Vector3 position;
	Vector3* nextPosition;
	short difficulty;
	short speedMultiplier;
};
#endif