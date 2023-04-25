#include "pul_Mouse.hpp"

namespace pul
{
	eqx::Point<double> Mouse::m_CurrentLocation = 
		eqx::Point<double>(0.0, 0.0);
	eqx::Point<double> Mouse::m_LeftClickDownLocation = 
		eqx::Point<double>(0.0, 0.0);
	eqx::Point<double> Mouse::m_LeftClickUpLocation = 
		eqx::Point<double>(0.0, 0.0);
	eqx::Point<double> Mouse::m_RightClickDownLocation = 
		eqx::Point<double>(0.0, 0.0);
	eqx::Point<double> Mouse::m_RightClickUpLocation = 
		eqx::Point<double>(0.0, 0.0);
	Mouse::Button Mouse::m_LeftButtonState = Mouse::Button::up;
	Mouse::Button Mouse::m_RightButtonState = Mouse::Button::up;

	void Mouse::handleEvent(const SDL_Event& e)
	{
		switch (e.type)
		{
		case SDL_MOUSEMOTION:
			m_CurrentLocation.x = static_cast<double>(e.motion.x);
			m_CurrentLocation.y = static_cast<double>(e.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				m_LeftButtonState = Mouse::Button::down;
				m_LeftClickDownLocation = m_CurrentLocation;
			}
			else if (e.button.button == SDL_BUTTON_RIGHT)
			{
				m_RightButtonState = Mouse::Button::down;
				m_RightClickDownLocation = m_CurrentLocation;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				m_LeftButtonState = Mouse::Button::up;
				m_LeftClickUpLocation = m_CurrentLocation;
			}
			else if (e.button.button == SDL_BUTTON_RIGHT)
			{
				m_RightButtonState = Mouse::Button::up;
				m_RightClickUpLocation = m_CurrentLocation;
			}
			break;
		default:
			break;
		}
	}

	const eqx::Point<double>& Mouse::getCurrentLocation()
	{
		return m_CurrentLocation;
	}

	const eqx::Point<double>& Mouse::getLeftClickDownLocation()
	{
		return m_LeftClickDownLocation;
	}

	const eqx::Point<double>& Mouse::getLeftClickUpLocation()
	{
		return m_LeftClickUpLocation;
	}

	const eqx::Point<double>& Mouse::getRightClickDownLocation()
	{
		return m_RightClickDownLocation;
	}

	const eqx::Point<double>& Mouse::getRightClickUpLocation()
	{
		return m_RightClickUpLocation;
	}
}