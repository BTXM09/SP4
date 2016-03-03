#pragma once
#include <math.h>

#define WORLD_SIZE 64

struct CSearchCell
{
public:
	int m_xCoord, m_zCoord;						// Store grid coordinates
	int m_id;
	CSearchCell *parent;
	float G;									// Accumulated distance between start node and current node
	float H;									// Estimated distance to goal (Heuristic)

	CSearchCell(void) : parent(0){}
	CSearchCell(int x, int z, CSearchCell *_parent = NULL) : m_xCoord(x), m_zCoord(z),
		parent(_parent), m_id(z * WORLD_SIZE + x), G(0), H(0) {};

	float GetF() { return G + H; }				// Total value of accmumlated dist & heuristic
	float ManhattanDist(CSearchCell *nodeEnd)	// Distance from current node to targetPos node
	{
		float x = (fabs((float)(this->m_xCoord - nodeEnd->m_xCoord)));	// Distance of x from current node to targetPos node
		float z = (fabs((float)(this->m_zCoord - nodeEnd->m_zCoord)));	// Distance of z from current node to targetPos node

		return x + z;
	}	
};