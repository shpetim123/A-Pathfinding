#ifndef GRID_H
#define GRID_H

#include <vector>
#include <iostream>
#include <SDL.h>

#include "Cell.h"
#include "Mouse.h"

class Grid
{
private:

	SDL_Renderer* m_Renderer;	//This is the main rendere, a pointer will be passed in and assigned to this.
	std::vector<Cell*> m_Cells;	 //Store the list of cells, makes up the grid.
	Cell* m_StartCell = NULL;	//begining Cell, gets assigned with mouse click.
	Cell* m_EndCell = NULL;
	Mouse* m_Mouse = NULL;
	int m_GridHeight = 14;
	int m_GridWidth = 14;


public:
	Grid(SDL_Renderer* _Renderer, Mouse* _Mouse);
	~Grid();
	void GridUpdate();	//Will update grid data E.g. if a cell has collided with the mouse.
	void CreateGrid();		//Populates the vector of cells to create a grid,assigns the neighbours aswell.
	void DrawCells();		//a function used to call the draw the cells.
	std::vector<Cell*> GetGridCells();		//getter for the list of cells that make up Grid.
	Cell* GetStartCell();
	void SetStartCell(Cell* _Cell);
	Cell* GetEndCell();
	void SetEndCell(Cell* _Cell);
	void ResetGrid();



};

#endif