#ifndef HANDLER_H
#define HANDLER_H

#include <SDL.h>
#include <iostream>
#include <string>


#include "Grid.h"
#include "Mouse.h"
#include "Pathfinding.h"


class Handler
{
private:
	SDL_Window* m_Window1 = NULL;
	SDL_Renderer* m_Renderer = NULL;
	SDL_Texture* m_Tex = NULL;
	Mouse* m_Mouse = NULL;
	Grid* m_Grid = NULL;
	Pathfinding* m_pathfinding = NULL;

	bool m_quit = false;
	//float m_OldTicks = 0.0f;
	//float m_NewTicks = SDL_GetTicks();
	//float m_Time = 0.0f;


public:
	Handler();
	~Handler();


	void Update();
	SDL_Texture* loadTexture();
	Grid* GetGrid();


};

#endif