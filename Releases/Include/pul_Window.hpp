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
		Window() = delete;
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator= (const Window&) = delete;
		Window& operator= (Window&&) = delete;
		~Window() = delete;

		static inline void init(std::string_view name, int width,
			int height) noexcept;
		static inline void shutDown() noexcept;

		static inline void show();
		[[nodiscard]] static inline double getDeltaTime() noexcept;
		[[nodiscard]] static inline std::string getFPSInfo();
		[[nodiscard]] static inline bool isOk() noexcept;

		static inline void setFrameRate(int frameRate) noexcept;
		static inline void setEventFunction(
			const std::function<void(const SDL_Event&)>& func) noexcept;
		static inline void 
			setUpdateFunction(const std::function<void(void)>& func) noexcept;
		static inline void 
			setRenderFunction(const std::function<void(void)>& func) noexcept;

		[[nodiscard]] static inline int getFrameRate() noexcept;
		[[nodiscard]] static inline int getWidth() noexcept;
		[[nodiscard]] static inline int getHeight() noexcept;
		[[nodiscard]] static inline SDL_Renderer* getRenderer() noexcept;

	private:
		[[nodiscard]] static inline bool createWindow() noexcept;
		static inline void printSDLError() noexcept;
		static inline void printError(std::string_view msg = "") noexcept;

		static inline auto s_IsOk = createWindow();
		static inline auto s_Name = std::string("");
		static inline auto s_Width = 0, s_Height = 0, s_FrameRate = 60;
		static inline auto s_FrameCount = 0ULL;
		static inline auto s_LastFrameTime = 0.0, s_LongestFrame = 0.0, 
			s_TotalTime = 0.0,
			s_ShortestFrame = std::numeric_limits<double>::max();

		static inline auto s_EventFunction = 
			std::function<void(const SDL_Event&)>();
		static inline auto s_UpdateFunction = std::function<void(void)>(), 
			s_RenderFunction = std::function<void(void)>();

		static inline auto s_Window = static_cast<SDL_Window*>(nullptr);
		static inline auto s_Renderer = static_cast<SDL_Renderer*>(nullptr);

		static inline auto s_FrameRateTimer = eqx::StopWatch();
	};
}

#include "pul_DefHeaders/pul_WindowDef.hpp"
