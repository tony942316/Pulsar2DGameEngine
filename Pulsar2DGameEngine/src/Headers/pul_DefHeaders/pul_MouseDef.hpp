#pragma once

namespace pul
{
	inline void Mouse::handleEvent(const SDL_Event& e)
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

	inline const eqx::Point<double>& Mouse::getCurrentLocation()
	{
		return m_CurrentLocation;
	}

	inline const eqx::Point<double>& Mouse::getLeftClickDownLocation()
	{
		return m_LeftClickDownLocation;
	}

	inline const eqx::Point<double>& Mouse::getLeftClickUpLocation()
	{
		return m_LeftClickUpLocation;
	}

	inline const eqx::Point<double>& Mouse::getRightClickDownLocation()
	{
		return m_RightClickDownLocation;
	}

	inline const eqx::Point<double>& Mouse::getRightClickUpLocation()
	{
		return m_RightClickUpLocation;
	}
}
