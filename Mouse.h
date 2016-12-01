#ifndef MOUSE_H
#define MOUSE_H

#include <iostream>
#include <SDL.h>


class Mouse
{
private:
	SDL_Rect m_MouseBox;
	bool m_LeftMouseClick = false;		//bool checks if left mouse has been clicked.
	bool m_RightMouseClick = false;
	int m_LeftClicked = 0;

public:

	Mouse();
	~Mouse();
	void Update();
	bool GetLeftMouseClick();
	void SetLeftMouseClick(bool _SetBool);
	bool GetRightMouseClick();
	void SetRightMouseClick(bool _SetBool);
	void ResetLeftMouse();
	void ResetRightMouse();
	SDL_Rect GetMouseRect();
	int GetLeftClicks();		//returns the amount of left clicks that have been made, stops after 2
	void AddLeftClicks(int _click);
	void ResetLeftClicks();


};

#endif