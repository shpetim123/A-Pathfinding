#include "Pathfinding.h"

Pathfinding::Pathfinding(Grid* _Grid)
{
	m_Grid = _Grid;

}

Pathfinding::~Pathfinding()
{
	m_OpenList.clear();
	m_ClosedList.clear();
	m_Path.clear();
	

	delete m_Grid;

}


void Pathfinding::UpdateAlgorithm()
{
	m_OpenList.push_back(m_Grid->GetStartCell());	//push the start Cell to the openList,outside of the while loop so it doesnt keep pushing the start cell.
	while (m_OpenList.empty() == false && m_EndFound == false)
	{
		Cell* tempCell = NULL;
     	float tempLowestf = m_OpenList.at(0)->GetFValue();
		//checks to assign lowest f value to the first cell;
		for (int i = 0; i < m_OpenList.size(); i++)	//iterate throughopenlist
		{
			if (m_OpenList.at(i)->GetFValue() <= tempLowestf) //if cell in openlist has lowerf than current, assign that cell to temp cell and lowestf.
			{
				tempLowestf = m_OpenList.at(i)->GetFValue();
				tempCell = m_OpenList.at(i);
				//std::cout << " i am in m_OpenList" << std::endl;
			}
		}
		//erases the current cell from openlist
		for (int i = 0; i < m_OpenList.size(); i++)
		{
			if (tempCell == m_OpenList.at(i))
			{
				m_OpenList.erase(m_OpenList.begin() + i);	//erases at begin + i which is i.	
				m_ClosedList.push_back(tempCell);

				if (m_ClosedList.empty() == false) //only runs if closedList is not emepty, to prevent access empty memeory.
				{
					if (m_ClosedList.back() != m_Grid->GetStartCell() && tempCell->GetObstacle() == false)	//checks if obstacle and closedList isnt on start cell.
					{
						m_ClosedList.back()->LoadImage("ClosedList.bmp");
					}
				}
			}
		}
		//for loop iterating through the neighbours.
		for (int i = 0; i < 8; i++)
		{
			if (tempCell->GetNeighbour(i) != NULL && tempCell->GetNeighbour(i)->GetObstacle() == false)	//check is neighbour cell is NuLL if not carry on
			{
				if (tempCell->GetNeighbour(i) == m_Grid->GetEndCell())	//check if end has been found.
				{
					m_EndFound = true;
				}
				for (int j = 0; j < m_OpenList.size(); j++)
				{
					if (tempCell->GetNeighbour(i) == m_OpenList.at(j))	// if neighbour is already in openlist skip this cell.
					{
						if (m_EndFound == false )
						{
							m_SkipSuccessor = true;
						}
					}
					
				}
				if (m_ClosedList.empty() == false)	//same as before but if neighbour is in closed list.
				{
					for (int j = 0; j < m_ClosedList.size(); j++)
					{
						if (tempCell->GetNeighbour(i) == m_ClosedList.at(j))
						{
							if (m_EndFound == false)
							{
								m_SkipSuccessor = true;
							}
						}

					}
				}
				if (m_SkipSuccessor == false && m_EndFound == false ) //if end  hasnt been found or skip successor push the current cell to the open list.
				{
					tempCell->GetNeighbour(i)->SetParent(tempCell);		//goes through neighbour and set parent to current node, it will lead into a chain which will lead back to the begining in the end.
					tempCell->GetNeighbour(i)->SetHValue(tempCell->GetNeighbour(i)->CalculateHDistance(m_Grid->GetEndCell()));
					tempCell->GetNeighbour(i)->SetGValue(tempCell->GetNeighbour(i)->CalculateGDistance(tempCell));
					tempCell->GetNeighbour(i)->CalculateFDistance();
					m_OpenList.push_back(tempCell->GetNeighbour(i));
					if (tempCell->GetObstacle() == false)	//if obstacle is set false, draw the openlist image , this is to avoid overwriting images.
					{
						m_OpenList.back()->LoadImage("OpenList.bmp");
					}
				}

			}
			m_SkipSuccessor = false;
		}

		if (m_EndFound == true)	//this loop find the path using an iterator and iterating back the parents cell through the cell.
		{
			m_Grid->GetEndCell()->SetParent(tempCell);
			Cell* tempPathCell = m_Grid->GetEndCell()->GetParent();
			while (tempPathCell != m_Grid->GetStartCell())
			{
				m_Path.push_back(tempPathCell);
				m_Path.back()->LoadImage("Path.bmp");
				tempPathCell = m_Path.back()->GetParent();
			}
		}
	}
	if (m_OpenList.empty() == true)		//if path not found it triggers this.
	{
		std::cout << "End goal not found " << std::endl;
	}
	m_OpenList.clear();
	m_ClosedList.clear();
	m_Path.clear();
	m_EndFound = false;
	m_SkipSuccessor = false;
}
