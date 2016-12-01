#ifndef CELL_H
#define CELL_H

#include <SDL.h>
#include <iostream>

#define GRID_TOP 0			//Defining Grid positions to make it easier later on, when passing grid position.
#define GRID_BOTTOM 1
#define GRID_LEFT 2
#define GRID_RIGHT 3
#define GRID_TOPLEFT 4
#define GRID_BOTTOMRIGHT 5
#define GRID_TOPRIGHT 6
#define GRID_BOTTOMLEFT 7

class Cell
{
private:
	SDL_Rect m_Rect;			//Use for rendering the image to the siize of the box and used for collision
	SDL_Renderer* m_Renderer = NULL;
	SDL_Texture* m_Tex = NULL;
	SDL_Surface* tempImage2 = SDL_LoadBMP("Grass.bmp");		//Assign grass as a default image for each cell.
	bool m_Obstacle = false;
	//Used for the pathfinding alogrithm.
	float m_F;		//m_F = m_G + m_H
	float m_H;		//current to the end
	float m_G;		//start to current

	Cell* m_LeftNeighbour = NULL;			//Used to store the neighbouring Cells.
	Cell* m_RightNeighbour = NULL;
	Cell* m_TopNeighbour = NULL;
	Cell* m_BottomNeighbour = NULL;
	Cell* m_TopLeftNeighbour = NULL;
	Cell* m_ToptRightNeighbour = NULL;
	Cell* m_BottomLeftNeighbour = NULL;
	Cell* m_BottomRightNeighbour = NULL;

	Cell* m_Parent = NULL;		//Will be used when backtracking the alogirthm to find a path.
public:
	Cell(SDL_Renderer* _Renderer, int _X, int _Y);
	~Cell();

	void Draw();		//Contain the draw function, will draw the entire grid.
	void LoadImage(const char* _Image);		//load an image by inputting the bmp image name.
	void SetPosition(int _X, int _Y);		//Set the SDlRect xy positions
	void SetNeighbour(Cell* _Cell, int _Position);		//Set neighbour which a number is required to iterate through the neighbours.
	Cell* GetNeighbour(int _Position);
	SDL_Rect GetCellRect();
	float GetFValue();
	float GetHValue();
	float GetGValue();
	void SetFValue(float _F);
	void SetHValue(float _H);
	void SetGValue(float _G);
	float CalculateHDistance(Cell* _EndCell);		//Can be used to calculate the distance between nodes.
	float CalculateGDistance(Cell* _CurrCell);		//used to calculate the H of a cell, used in conjuction with set SetGValue()
	void CalculateFDistance();
	Cell* GetParent();
	void SetParent(Cell* _ParentCell);
	void SetObstacle(bool _Obstacle);
	bool GetObstacle();
	void ResetFGH();


};

#endif