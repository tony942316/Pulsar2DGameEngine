#pragma once

#include <iostream>
#include <string_view>
#include <functional>

#include <EquinoxSTD.hpp>
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "pul_Mouse.hpp"

namespace pul
{
	class Window
	{
	public:
		explicit inline Window(std::string_view name, int width, int height);
		inline ~Window();

		inline void show();

		inline void setEventFunction(
			const std::function<void(const SDL_Event&)>& func);
		inline void setUpdateFunction(const std::function<void(void)>& func);
		inline void setRenderFunction(const std::function<void(void)>& func);

		inline double getDeltaTime() const;
		inline SDL_Renderer* getRenderer();
		inline std::string getFPSInfo();

		inline int getWidth() const;
		inline int getHeight() const;

	private:
		inline void printSDLError() const;
		inline void printError(std::string_view msg = "") const;

		std::string m_Name;
		int m_Width, m_Height;
		unsigned long long m_FrameCount;
		double m_LastFrameTime, m_LongestFrame, m_ShortestFrame;

		std::function<void(const SDL_Event&)> m_EventFunction;
		std::function<void(void)> m_UpdateFunction, m_RenderFunction;

		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;

		eqx::StopWatch m_FrameTimer;
	};
}

#include "pul_DefHeaders/pul_WindowDef.hpp"
