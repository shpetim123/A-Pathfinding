#include "Grid.h"

Grid::Grid(SDL_Renderer* _Renderer, Mouse* _Mouse)
{
	m_Renderer = _Renderer;
	m_Mouse = _Mouse;
	if (!m_Renderer)
	{
		std::cout << "renderer is not receivied in Grid" << std::endl;
	}
}

Grid::~Grid()
{
	SDL_DestroyRenderer(m_Renderer);
	m_Cells.clear();

	delete m_EndCell;
	delete m_StartCell;
	delete m_Mouse;

}

void Grid::CreateGrid()
{
	Cell* currCell = NULL;		//Will be used as a temparoary cell to store current cell.
	Cell* otherCell = NULL;

	for (int y = 0; y < m_GridHeight; y++)	//Nested for loop to Cycle throught the Grid height and width.
	{

		for (int x = 0; x < m_GridWidth; x++)
		{
			currCell = new Cell(m_Renderer, x, y);
			if (x > 0)	// as iterator, if it is greater than zero.
			{
				otherCell = m_Cells.at(m_Cells.size() - 1);	//assigns othercell to the cell prevoius to this. 
				currCell->SetNeighbour(otherCell, GRID_LEFT);	//assigning the neighbours to each other.
				otherCell->SetNeighbour(currCell, GRID_RIGHT);

				if (y > 0)	// if x is and y is greater than zero it will assign the topleft, if not there is a chance it will go outside the grid,null reference.
				{
					otherCell = m_Cells.at(m_Cells.size() - m_GridWidth - 1);	//assigning the other cell to the currCell topLeft position, by minusing the grid width -1.
					currCell->SetNeighbour(otherCell, GRID_TOPLEFT);
					otherCell->SetNeighbour(currCell, GRID_BOTTOMRIGHT);
				}


			}

			if (y > 0)
			{
				otherCell = m_Cells.at(m_Cells.size() - m_GridWidth);	//the Define make it alot easier to assign theneighbours.
				currCell->SetNeighbour(otherCell, GRID_TOP);
				otherCell->SetNeighbour(currCell, GRID_BOTTOM);
			}

			if (y > 0 && y < m_GridHeight && x < m_GridWidth - 1)		// check to see if it is suitable for assigning the topright cell//bottom left for the other cell.
			{
				otherCell = m_Cells.at(m_Cells.size() - m_GridWidth + 1);
				currCell->SetNeighbour(otherCell, GRID_TOPRIGHT);
				otherCell->SetNeighbour(currCell, GRID_BOTTOMLEFT);
			}
			
			m_Cells.push_back(currCell);	//pushBack the current Cell with its neighbours linked up.


		}


	}


}
void Grid::GridUpdate()
{
	if (m_Mouse->GetLeftMouseClick() == true)
	{
		for (int i = 0; i < m_Cells.size(); i++)	//iterate through the grid.
		{
			SDL_Rect tempCell = m_Cells.at(i)->GetCellRect();
			if (SDL_HasIntersection(&tempCell, &m_Mouse->GetMouseRect()) == SDL_TRUE)	//has intersected is a fucntion to see if two SDL_rects have collided.
			{
				if (m_Mouse->GetLeftClicks() == 0)	//checks to see if mouse clicks are 0, if so it will be ready to set start position.
				{
					m_Cells.at(i)->LoadImage("Start.bmp");	//loads the image for start BMP.
					m_Cells.at(i)->SetFValue(0);
					m_Cells.at(i)->SetGValue(0);
					SetStartCell(m_Cells.at(i));	//Sets the start cell to where the left mouse has clicked on the grid.
					m_Mouse->AddLeftClicks(1);
				}
				else if (m_Mouse->GetLeftClicks() == 1)	//ready to set end.
				{
					m_Cells.at(i)->LoadImage("End.bmp");
					m_Cells.at(i)->SetHValue(0);
					SetEndCell(m_Cells.at(i));
					m_Mouse->AddLeftClicks(1);
				}
				else if (m_Mouse->GetLeftClicks() == 2)
				{
					m_Cells.at(i)->LoadImage("Obstacle.bmp");
					m_Cells.at(i)->SetObstacle(true);	//sets the cell colliding with the mouse to an obstacle.
				}
			}
		}
	}
}
void Grid::DrawCells()
{
	for (int i = 0; i < m_Cells.size(); i++)
	{
		m_Cells.at(i)->Draw();
	}
}
std::vector<Cell*> Grid::GetGridCells()
{
	return m_Cells;
}

Cell* Grid::GetStartCell()
{
	return m_StartCell;
}
void Grid::SetStartCell(Cell* _Cell)
{
	m_StartCell = _Cell;
}
Cell* Grid::GetEndCell()
{
	return m_EndCell;
}
void Grid::SetEndCell(Cell* _Cell)
{
	m_EndCell = _Cell;
}
void Grid::ResetGrid()
{
	m_StartCell = NULL;
	m_EndCell = NULL;
	m_Mouse->ResetLeftClicks();
	for (int i = 0; i < m_Cells.size(); i++)
	{
		m_Cells.at(i)->SetParent(NULL);
		m_Cells.at(i)->SetObstacle(false);
		m_Cells.at(i)->LoadImage("Grass.bmp");
		m_Cells.at(i)->ResetFGH();
	}
	

}