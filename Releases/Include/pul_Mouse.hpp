#pragma once

#include <EquinoxSTD.hpp>
#include <SDL.h>

namespace pul
{
	class Mouse
	{
	public:
		enum class Button
		{
			up,
			down
		};

		Mouse() = delete;
		Mouse(const Mouse& other) = delete;
		Mouse(Mouse&& other) = delete;
		Mouse& operator= (const Mouse&& other) = delete;
		Mouse& operator= (Mouse&& other) = delete;
		~Mouse() = delete;

		static inline void handleEvent(const SDL_Event& e);
		static inline const eqx::Point<double>& getCurrentLocation();
		static inline const eqx::Point<double>& getLeftClickDownLocation();
		static inline const eqx::Point<double>& getLeftClickUpLocation();
		static inline const eqx::Point<double>& getRightClickDownLocation();
		static inline const eqx::Point<double>& getRightClickUpLocation();

	private:
		static inline auto m_CurrentLocation = eqx::Point<double>(),
			m_LeftClickDownLocation = eqx::Point<double>(),
			m_LeftClickUpLocation = eqx::Point<double>(),
			m_RightClickDownLocation = eqx::Point<double>(),
			m_RightClickUpLocation = eqx::Point<double>();
		static inline auto m_LeftButtonState = Mouse::Button::up,
			m_RightButtonState = Mouse::Button::up;
	};
}

#include "pul_DefHeaders/pul_MouseDef.hpp"
