#include "Mouse.h"

eqx::Point<double> Mouse::Location = eqx::Point<double>();
eqx::Point<double> Mouse::LeftClickDownLocation = eqx::Point<double>();
eqx::Point<double> Mouse::RightClickDownLocation = eqx::Point<double>();
eqx::Point<double> Mouse::LeftClickUpLocation = eqx::Point<double>();
eqx::Point<double> Mouse::RightClickUpLocation = eqx::Point<double>();
Mouse::Button Mouse::LeftButton = Mouse::Button::up;
Mouse::Button Mouse::RightButton = Mouse::Button::up;

void Mouse::handleEvent(const SDL_Event& e)
{
	switch (e.type)
	{
	case SDL_MOUSEMOTION:
		Location.x = static_cast<double>(e.motion.x);
		Location.y = static_cast<double>(e.motion.y);
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			LeftButton = Mouse::Button::down;
			LeftClickDownLocation = Location;
		}
		else if (e.button.button == SDL_BUTTON_RIGHT)
		{
			RightButton = Mouse::Button::down;
			RightClickDownLocation = Location;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			LeftButton = Mouse::Button::up;
			LeftClickUpLocation = Location;
		}
		else if (e.button.button == SDL_BUTTON_RIGHT)
		{
			RightButton = Mouse::Button::up;
			RightClickUpLocation = Location;
		}
		break;
	default:
		break;
	}
}

Mouse::Mouse()
{
	refresh();
}

Mouse& Mouse::getInstance()
{
	static Mouse instance;
	return instance;
}

void Mouse::refresh()
{
	int x, y;
	Uint32 buttons = SDL_GetMouseState(&x, &y);
	Location.x = static_cast<double>(x);
	Location.y = static_cast<double>(y);
	LeftButton = buttons & SDL_BUTTON(SDL_BUTTON_LEFT) ? Button::down : Button::up;
	RightButton = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT) ? Button::down : Button::up;
	LeftClickDownLocation = eqx::Point<double>();
	RightClickDownLocation = eqx::Point<double>();
	LeftClickUpLocation = eqx::Point<double>();
	RightClickUpLocation = eqx::Point<double>();
}