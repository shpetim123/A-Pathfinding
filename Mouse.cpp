#include "Mouse.h"

Mouse::Mouse()
{
	m_MouseBox.x = 0;	
	m_MouseBox.y = 0;
	m_MouseBox.w = 1;	//mouse width and height set 1 one so it doesnt colides with multiple cells.
	m_MouseBox.h = 1;
}

Mouse::~Mouse()
{
	
}
void Mouse::Update()
{
	SDL_GetMouseState(&m_MouseBox.x, &m_MouseBox.y);	//get current mouse position and sets its it to current xy.
}
bool Mouse::GetLeftMouseClick()
{
	return m_LeftMouseClick;	
}
void Mouse::SetLeftMouseClick(bool _SetBool)
{
	m_LeftMouseClick = _SetBool;
}
bool Mouse::GetRightMouseClick()
{
	return m_RightMouseClick;
}
void Mouse::SetRightMouseClick(bool _SetBool)
{
	m_RightMouseClick = _SetBool;
}
void Mouse::ResetLeftMouse()
{
	m_LeftMouseClick = false;
}
void Mouse::ResetRightMouse()
{
	m_RightMouseClick = false;
}

SDL_Rect Mouse::GetMouseRect()
{
	return m_MouseBox;
}
int Mouse::GetLeftClicks()
{
	return m_LeftClicked;
}
void Mouse::AddLeftClicks(int _click)
{
	m_LeftClicked += _click;
}
void Mouse::ResetLeftClicks()
{
	m_LeftClicked = 0;              
}