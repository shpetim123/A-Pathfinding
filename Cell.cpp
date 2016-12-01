#include "Cell.h"

Cell::Cell(SDL_Renderer* _Renderer, int _X, int _Y)
{
	m_Renderer = _Renderer;
	if (!m_Renderer)
	{
		std::cout << " cell is not revieiving renderer" << std::endl;
	}

	m_Rect.x = (_X) * 32;		//assigns the Cell its rects, multiplication is to stop cells from overlapping by setting them width and height apart.
	m_Rect.y = (_Y) * 32;
	m_Rect.w = 32;	
	m_Rect.h = 32;

	m_Tex = SDL_CreateTextureFromSurface(m_Renderer,tempImage2);	//Creating a texture from the surface which its default is Grass.bmp.

}
Cell::~Cell()
{
	SDL_DestroyTexture(m_Tex);
	SDL_DestroyRenderer(m_Renderer);
	SDL_FreeSurface(tempImage2);

	delete m_LeftNeighbour;
	delete m_RightNeighbour;
	delete m_TopNeighbour;
	delete m_BottomNeighbour;
	delete m_TopLeftNeighbour; 
	delete m_ToptRightNeighbour;
	delete m_BottomLeftNeighbour;
	delete m_BottomRightNeighbour;

}

void Cell::Draw()
{
	SDL_RenderCopy(m_Renderer,m_Tex,NULL,&m_Rect);
}

void Cell::LoadImage(const char* _Image)
{
	SDL_Surface* tempImage = SDL_LoadBMP(_Image);		//inputted name will be searched for, if image exist its assigned to a surface then texture.

	if (!tempImage)
	{
		std::cout << "Error loading Cell Image" << std::endl;
		tempImage = NULL;
	}
	else
	{
		m_Tex = SDL_CreateTextureFromSurface(m_Renderer, tempImage);
	}
	SDL_FreeSurface(tempImage);
}
void Cell::SetPosition(int _X, int _Y)
{
	m_Rect.x = _X;
	m_Rect.y = _Y;
}

void Cell::SetNeighbour(Cell* _Cell, int _Position)		//by using the define from earlier its easier to regnise the positions of the neighbours.
{
	if (_Position == GRID_TOP)		//checks for inputted position, when found assigns the cell passed in to be the neighbour of current cell.
	{
		m_TopNeighbour = _Cell;
	}
	else if (_Position == GRID_BOTTOM)
	{
		m_BottomNeighbour = _Cell;
	}
	else if (_Position == GRID_LEFT)
	{
		m_LeftNeighbour = _Cell;
	}
	else if (_Position == GRID_RIGHT)
	{
		m_RightNeighbour = _Cell;
	}
	else if (_Position == GRID_TOPLEFT)
	{
		m_TopLeftNeighbour = _Cell;
	}
	else if (_Position == GRID_BOTTOMRIGHT)
	{
		m_BottomRightNeighbour = _Cell;
	}
	else if (_Position == GRID_TOPRIGHT)
	{
		m_ToptRightNeighbour = _Cell;
	}
	else if (_Position == GRID_BOTTOMLEFT)
	{
		m_BottomLeftNeighbour = _Cell;
	}
}

Cell* Cell::GetNeighbour(int _Position)	//Getter for the neighbour.
{
	if (_Position == GRID_TOP)
	{
		return m_TopNeighbour;
	}
	else if (_Position == GRID_BOTTOM)
	{
		return m_BottomNeighbour;
	}
	else if (_Position == GRID_LEFT)
	{
		return m_LeftNeighbour;
	}
	else if (_Position == GRID_RIGHT)
	{
		return m_RightNeighbour;
	}
	else if (_Position == GRID_TOPLEFT)
	{
		return m_TopLeftNeighbour;
	}
	else if (_Position == GRID_BOTTOMRIGHT)
	{
		return m_BottomRightNeighbour;
	}
	else if (_Position == GRID_TOPRIGHT)
	{
		return m_ToptRightNeighbour;
	}
	else if (_Position == GRID_BOTTOMLEFT)
	{
		return m_BottomLeftNeighbour;
	}
}
SDL_Rect Cell::GetCellRect()
{
	return m_Rect;
}

///Getters and Setters///
float Cell::GetFValue()
{
	return m_F;
}

float Cell::GetHValue()
{
	return m_H;
}
float Cell::GetGValue()
{
	return m_G;
}
void Cell::SetFValue(float _F)
{
	m_F = _F;
}
void Cell::SetHValue(float _H)
{
	m_H = _H;
}
void Cell::SetGValue(float _G)
{
	m_G = _G;
}

float Cell::CalculateHDistance(Cell* _EndCell)
{
	//By using Euclidean or pythag the distance between the end and current cell can be found and assigned to H.
	float tempDistance = sqrt(((m_Rect.x - _EndCell->GetCellRect().x) * (m_Rect.x - _EndCell->GetCellRect().x)) + abs((m_Rect.y - _EndCell->GetCellRect().y) * (m_Rect.y - _EndCell->GetCellRect().y)));
	return tempDistance;

}
float Cell::CalculateGDistance(Cell* _CurrCell )
{
	//this is similar to CalcualteH but this include the current_G added on and instead of Endcell, its the previous Cell.
	float tempDistance = sqrt(((_CurrCell->GetCellRect().x - m_Rect.x) * (_CurrCell->GetCellRect().x - m_Rect.x)) + ((_CurrCell->GetCellRect().y - m_Rect.y) * (_CurrCell->GetCellRect().y - m_Rect.y))) + m_G;
	return tempDistance;
}
void Cell::CalculateFDistance()
{
	m_F = m_G + m_H;
}
     
Cell* Cell::GetParent()
{
	return m_Parent;
}
void Cell::SetParent(Cell* _ParentCell)
{
	m_Parent = _ParentCell;
}
void Cell::SetObstacle(bool _Obstacle)	//obstacle is used to differentiate passible from impassible obstacles.
{
	m_Obstacle = _Obstacle;
}
bool Cell::GetObstacle()
{
	return m_Obstacle;
}
void Cell::ResetFGH()
{
	m_F = 0;
	m_G = 0;
	m_H = 0;
}



