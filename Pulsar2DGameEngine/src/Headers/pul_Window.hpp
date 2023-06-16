#pragma once

#include "pul_Dependencies.hpp"

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

		static inline void init(std::string_view name, int width, int height);

		[[nodiscard]] static inline bool isInit() noexcept;

		static inline void show();

		[[nodiscard]] static inline double getDeltaTime() noexcept;

		[[nodiscard]] static inline std::string getFPSInfo();

		static inline void printFPSInfo(long long ms = 1'000);

		static inline void setFrameRate(int frameRate) noexcept;

		static inline void setEventFunction(void (*func)(const SDL_Event& e))
			noexcept;

		static inline void setUpdateFunction(void (*func)()) noexcept; 

		static inline void setRenderFunction(void (*func)()) noexcept;

		[[nodiscard]] static inline int getFrameRate() noexcept;
		[[nodiscard]] static inline int getWidth() noexcept;
		[[nodiscard]] static inline int getHeight() noexcept;
		[[nodiscard]] static inline SDL_Renderer* getRenderer() noexcept;

	private:
		[[nodiscard]] static inline void createWindow() noexcept;

		constinit static inline auto s_IsInit = false;
		constinit static inline auto s_Name = eqx::nullp<std::string>;
		constinit static inline auto s_Width = 0, s_Height = 0, 
			s_FrameRate = 60;
		constinit static inline auto s_FrameCount = 0ULL;
		constinit static inline auto s_LastFrameTime = 0.0, 
			s_LongestFrame = 0.0, s_TotalTime = 0.0,
			s_ShortestFrame = std::numeric_limits<double>::max();

		constinit static inline void (*s_EventFunction)(const SDL_Event& e) = 
			nullptr;
		constinit static inline void (*s_UpdateFunction)() = nullptr;
		constinit static inline void (*s_RenderFunction)() = nullptr;

		constinit static inline auto s_Window = eqx::nullp<SDL_Window>;
		constinit static inline auto s_Renderer = eqx::nullp<SDL_Renderer>;
	};
}

#include "pul_DefHeaders/pul_WindowDef.hpp"
