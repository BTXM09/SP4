#pragma once
#include "Vector3.h"
#include <vector>
#include "SearchCell.h"
#include "AI.h"

class CPathFinding
{
public:
	CPathFinding(void);
	~CPathFinding(void);

	void FindPath(Vector3 currentPos, Vector3 targetPos);				// Sets current position of AI & target position
	Vector3 NextPathPos();												// Gets first position of the shortest path from the list
	void ClearOpenList() { m_openList.clear(); }						// Clear Lists
	void ClearVisitedList() { m_visitedList.clear(); }
	void ClearPathToGoal() { m_pathToGoal.clear(); }
	bool m_initialisedStartGoal;										// To check if Start and Goal have been initialized
	bool m_foundGoal;													// To check if goal has been found

private:
	void SetStartAndGoal(CSearchCell start, CSearchCell goal);			// Set Start & Goal cells
	void PathOpened(int x, int z, float newCost, CSearchCell *parent);	// Check if current cell is in m_openList
	CSearchCell *GetNextCell();											// Gets next available cell in the list
	void ContinuePath();												// Searches through and expands position to find target position & calculate G & H values

	CSearchCell *m_startCell;
	CSearchCell *m_goalCell;
	std::vector<CSearchCell*> m_openList;
	std::vector<CSearchCell*> m_visitedList;
	std::vector<Vector3*> m_pathToGoal;

	cAI *AI;
};