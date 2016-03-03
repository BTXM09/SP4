#include "PathFinding.h"

CPathFinding::CPathFinding(void)
{
	m_initialisedStartGoal = false;
	m_foundGoal = false;
}

CPathFinding::~CPathFinding(void)
{
}

void CPathFinding::FindPath(Vector3 currentPos, Vector3 targetPos)
{
	if (!m_initialisedStartGoal)
	{
		for (int i = 0; i < m_openList.size(); i++)
		{
			delete m_openList[i];
		}
		m_openList.clear();

		for (int i = 0; i < m_visitedList.size(); i++)
		{
			delete m_visitedList[i];
		}
		m_visitedList.clear();

		for (int i = 0; i < m_pathToGoal.size(); i++)
		{
			delete m_pathToGoal[i];
		}
		m_pathToGoal.clear();

		// Initialise start
		CSearchCell start;
		start.m_xCoord = currentPos.x;
		start.m_zCoord = currentPos.z;

		// Initialise goal
		CSearchCell goal;
		goal.m_xCoord = targetPos.x;
		goal.m_zCoord = targetPos.z;

		SetStartAndGoal(start, goal);
		m_initialisedStartGoal = true;
	}
	if (m_initialisedStartGoal)
	{
		ContinuePath();
	}
}

void CPathFinding::SetStartAndGoal(CSearchCell start, CSearchCell goal)
{
	m_startCell = new CSearchCell(start.m_xCoord, start.m_zCoord, NULL);
	m_goalCell = new CSearchCell(goal.m_xCoord, goal.m_zCoord, &goal);

	m_startCell->G = 0;
	m_startCell->H = m_startCell->ManhattanDist(m_goalCell);
	m_startCell->parent = 0;

	m_openList.push_back(m_startCell);
}

CSearchCell* CPathFinding::GetNextCell()
{
	float bestF = 999999.0f;
	int cellIndex = -1;
	CSearchCell* nextCell = NULL;

	for (int i = 0; i < m_openList.size(); i++)
	{
		if (m_openList[i]->GetF() < bestF)
		{
			bestF = m_openList[i]->GetF();
			cellIndex = i;
		}
	}

	if (cellIndex >= 0)
	{
		nextCell = m_openList[cellIndex];
		m_visitedList.push_back(nextCell);
		m_openList.erase(m_openList.begin() + cellIndex);
	}

	return nextCell;
}

void CPathFinding::PathOpened(int x, int z, float newCost, CSearchCell *parent)
{
	/*if (CELL_BLOCKED)
	{
		return;
	}*/

	int id = z * WORLD_SIZE + x;

	for (int i = 0; i < m_visitedList.size(); i++)
	{
		if (id == m_visitedList[i]->m_id)
		{
			return;
		}
	}

	CSearchCell* newChild = new CSearchCell(x, z, parent);
	newChild->G = newCost;
	newChild->H = parent->ManhattanDist(m_goalCell);

	for (int i = 0; i < m_openList.size(); i++)
	{
		if (id == m_openList[i]->m_id)
		{
			float newF = newChild->G + newCost + m_openList[i]->H;

			if (m_openList[i]->GetF() > newF)
			{
				m_openList[i]->G = newChild->G + newCost;
				m_openList[i]->parent = newChild;
			}
			else  // If newF is not better than current F
			{
				delete newChild;
				return;
			}
		}
	}
	m_openList.push_back(newChild);
}

void CPathFinding::ContinuePath()
{
	if (m_openList.empty())
	{
		return;
	}

	CSearchCell* currentCell = GetNextCell();

	if (currentCell->m_id == m_goalCell->m_id)
	{
		m_goalCell->parent = currentCell->parent;

		CSearchCell* getPath;

		for (getPath = m_goalCell; getPath != NULL; getPath = getPath->parent)	// Checks through m_goalCell to find shortest path & push to m_pathToGoal list
		{
			m_pathToGoal.push_back(new Vector3(getPath->m_xCoord, 0, getPath->m_zCoord));
		}

		m_foundGoal = true;
		return;
	}
	else 
	{
		// Right Side
		PathOpened(currentCell->m_xCoord + 1, currentCell->m_zCoord, currentCell->G + 1, currentCell);

		// Left Side
		PathOpened(currentCell->m_xCoord - 1, currentCell->m_zCoord, currentCell->G + 1, currentCell);

		// Top
		PathOpened(currentCell->m_xCoord, currentCell->m_zCoord + 1, currentCell->G + 1, currentCell);

		// Bottom
		PathOpened(currentCell->m_xCoord, currentCell->m_zCoord - 1, currentCell->G + 1, currentCell);

		for (int i = 0; i < m_openList.size(); i++)
		{
			if (currentCell->m_id == m_openList[i]->m_id)
			{
				m_openList.erase(m_openList.begin() + 1);
			}
		}
	}
}

Vector3 CPathFinding::NextPathPos()	// Gets first position from the shortest path in the list
{
	int index = 1;

	Vector3 nextPos;
	nextPos.x = m_pathToGoal[m_pathToGoal.size() - index]->x;
	nextPos.z = m_pathToGoal[m_pathToGoal.size() - index]->z;

	Vector3 distance = nextPos - AI->getPos();

	if (index < m_pathToGoal.size())
	{
		if (distance.Length() /* < AI's radius */)
		{
			m_pathToGoal.erase(m_pathToGoal.end() - index);
		}

		return nextPos;
	}
}