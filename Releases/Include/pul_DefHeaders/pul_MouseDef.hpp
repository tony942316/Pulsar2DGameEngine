#pragma once

namespace pul
{
	inline void Mouse::handleEvent(const SDL_Event& e) noexcept
	{
		switch (e.type)
		{
		case SDL_MOUSEMOTION:
			m_CurrentLocation = eqx::Point<double>(e.motion.x, e.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				m_LeftButtonState = Mouse::Button::Down;
				m_LeftClickDownLocation = m_CurrentLocation;
			}
			else if (e.button.button == SDL_BUTTON_RIGHT)
			{
				m_RightButtonState = Mouse::Button::Down;
				m_RightClickDownLocation = m_CurrentLocation;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				m_LeftButtonState = Mouse::Button::Up;
				m_LeftClickUpLocation = m_CurrentLocation;
			}
			else if (e.button.button == SDL_BUTTON_RIGHT)
			{
				m_RightButtonState = Mouse::Button::Up;
				m_RightClickUpLocation = m_CurrentLocation;
			}
			break;
		default:
			break;
		}
	}

	[[nodiscard]] inline const eqx::Point<double>& 
		Mouse::getCurrentLocation() noexcept
	{
		return m_CurrentLocation;
	}

	[[nodiscard]] inline const eqx::Point<double>& 
		Mouse::getLeftClickDownLocation() noexcept
	{
		return m_LeftClickDownLocation;
	}

	[[nodiscard]] inline const eqx::Point<double>& 
		Mouse::getLeftClickUpLocation() noexcept
	{
		return m_LeftClickUpLocation;
	}

	[[nodiscard]] inline const eqx::Point<double>& 
		Mouse::getRightClickDownLocation() noexcept
	{
		return m_RightClickDownLocation;
	}

	[[nodiscard]] inline const eqx::Point<double>& 
		Mouse::getRightClickUpLocation() noexcept
	{
		return m_RightClickUpLocation;
	}
}
