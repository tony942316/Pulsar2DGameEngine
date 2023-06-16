#pragma once

#include "pul_Dependencies.hpp"

namespace pul
{
	class Mouse
	{
	public:
		enum class Button
		{
			Up,
			Down
		};

		Mouse() = delete;
		Mouse(const Mouse&) = delete;
		Mouse(Mouse&&) = delete;
		Mouse& operator= (const Mouse&&) = delete;
		Mouse& operator= (Mouse&&) = delete;
		~Mouse() = delete;

		static inline void handleEvent(const SDL_Event& e) noexcept;
		[[nodiscard]] static inline const eqx::Point<double>& 
			getCurrentLocation() noexcept;
		[[nodiscard]] static inline const eqx::Point<double>& 
			getLeftClickDownLocation() noexcept;
		[[nodiscard]] static inline const eqx::Point<double>& 
			getLeftClickUpLocation() noexcept;
		[[nodiscard]] static inline const eqx::Point<double>& 
			getRightClickDownLocation() noexcept;
		[[nodiscard]] static inline const eqx::Point<double>& 
			getRightClickUpLocation() noexcept;

	private:
		constinit static inline auto m_CurrentLocation = eqx::Point<double>(),
			m_LeftClickDownLocation = eqx::Point<double>(),
			m_LeftClickUpLocation = eqx::Point<double>(),
			m_RightClickDownLocation = eqx::Point<double>(),
			m_RightClickUpLocation = eqx::Point<double>();
		constinit static inline auto m_LeftButtonState = Mouse::Button::Up,
			m_RightButtonState = Mouse::Button::Up;
	};
}

#include "pul_DefHeaders/pul_MouseDef.hpp"
