#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <iostream>
#include <vector>
#include <math.h>

#include "Grid.h"

class Pathfinding
{
private:
	Grid* m_Grid = NULL;		//Get the grid an assign it to this pointer
	std::vector<Cell*> m_OpenList;
	std::vector<Cell*> m_ClosedList;
	std::vector<Cell*> m_Path;

	bool m_EndFound = false;		//if the endCell is found.
	bool m_SkipSuccessor = false;	//to help avoid multiple duplications when pushing to open or closed list.

public:
	Pathfinding(Grid* _Grid);
	~Pathfinding();

	void UpdateAlgorithm();

};



#endif