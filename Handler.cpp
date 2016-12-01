#include "Handler.h"

Handler::Handler()
{
	m_Window1 = SDL_CreateWindow("A.I A* Path-Finding", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );	//creates the Window,size,name etc.
	m_Renderer = SDL_CreateRenderer(m_Window1, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
	m_Mouse = new Mouse();
	m_Grid = new Grid(m_Renderer, m_Mouse);

	SDL_SetRenderDrawColor(m_Renderer, 192, 192, 192, 255);	//Sets the background colour of the renderer.
	m_Grid->CreateGrid();	//this call the fiunctions that populates the Grid.
	m_pathfinding = new Pathfinding(m_Grid);

}

Handler::~Handler()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window1);
	SDL_DestroyTexture(m_Tex);
}

void Handler::Update()
{
	SDL_Event m_Event;	//Used to handle Controls and venets related to keyboard or mouse.

	while (!m_quit)
	{
		SDL_RenderClear(m_Renderer);
		m_Mouse->Update();
		while (SDL_PollEvent(&m_Event))
		{
			switch (m_Event.type)
			{
				case SDL_QUIT :  //SDL_Quit is quit the application by pressing the x on the top right of the window.
					m_quit = true;
					break;
				case SDL_MOUSEBUTTONUP:	//check to see when a mouse button is released, will trigger the if statment.
					if (m_Event.button.button == SDL_BUTTON_LEFT)	//if mouse left button is realesed Sets left  mouse click to true.
					{
						m_Mouse->SetLeftMouseClick(true);
					}
					if (m_Event.button.button == SDL_BUTTON_RIGHT)
					{
						m_Mouse->SetRightMouseClick(true);
					}
					break;
				case SDL_KEYDOWN:
				if (m_Event.key.keysym.sym == SDLK_SPACE)
				{
					m_Grid->ResetGrid();
				}
			}

		}
		m_Grid->GridUpdate();	//checks to see if mouse has collided etc.
		if (m_Mouse->GetRightMouseClick() == true)
		{
			m_pathfinding->UpdateAlgorithm();	//only ruyns algoirthm once the right mouse button has been clicked.
		}
		m_Grid->DrawCells();
		m_Mouse->ResetLeftMouse();
		m_Mouse->ResetRightMouse();
		SDL_RenderPresent(m_Renderer);

	}
}
Grid* Handler::GetGrid()
{
	return m_Grid;
}

