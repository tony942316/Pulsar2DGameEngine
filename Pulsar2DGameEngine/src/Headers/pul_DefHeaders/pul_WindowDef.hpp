#pragma once

namespace pul
{
	[[nodiscard]] inline void Window::createWindow() noexcept
	{
		eqx::runtimeAssert(SDL_Init(SDL_INIT_VIDEO) == 0, SDL_GetError());
		eqx::runtimeAssert(TTF_Init() == 0, TTF_GetError());

		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			eqx::println("Warning: Linear Texture Filtering Not Enabled!");
		}

		s_Window = SDL_CreateWindow(s_Name->c_str(), SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, s_Width, s_Height, SDL_WINDOW_HIDDEN);
		EQX_SUPPRESS_WARNING(26477);
		eqx::runtimeAssert(s_Window != NULL, SDL_GetError());

		s_Renderer = SDL_CreateRenderer(s_Window, -1,
			SDL_RENDERER_ACCELERATED);
		EQX_SUPPRESS_WARNING(26477);
		eqx::runtimeAssert(s_Renderer != NULL, SDL_GetError());

		SDL_SetRenderDrawColor(s_Renderer, 0x00, 0x00, 0x00, 0x00);
	}

	inline void Window::init(std::string_view name, int width, 
		int height)
	{
		static auto nameStorage = std::string(name);
		s_Name = &nameStorage;
		s_Width = width;
		s_Height = height;
		s_EventFunction = [](const SDL_Event& e) { e; };
		s_UpdateFunction = []() {};
		s_RenderFunction = []() {};

		createWindow();
		s_IsInit = true;
	}

	[[nodiscard]] inline bool Window::isInit() noexcept
	{
		return s_IsInit;
	}

	inline void Window::show()
	{
		eqx::runtimeAssert(isInit(), 
			"Call pul::Window::init(...) Before Calling pul::Window::show()");

		using namespace eqx::TimeTypes;

		SDL_Event e;
		auto frameTimer = eqx::StopWatch();

		SDL_ShowWindow(s_Window);
		while (true)
		{
			if (frameTimer.readTime<t_US>() < 
				(1'000'000 / (s_FrameRate + 5)))
			{
				continue;
			}

			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					EQX_SUPPRESS_WARNING(26438);
					goto DOUBLEBREAK;
				}
				else
				{
					Mouse::handleEvent(e);
					std::invoke(s_EventFunction, e);
				}
			}

			std::invoke(s_UpdateFunction);

			SDL_RenderClear(s_Renderer);
			std::invoke(s_RenderFunction);
			SDL_RenderPresent(s_Renderer);

			s_LastFrameTime = frameTimer.readSeconds();
			s_TotalTime += frameTimer.getSeconds();
			s_LongestFrame = std::max(s_LongestFrame, s_LastFrameTime);
			s_ShortestFrame = std::min(s_ShortestFrame, s_LastFrameTime);
			s_FrameCount++;
			frameTimer.start();
		}

		DOUBLEBREAK:

		SDL_DestroyRenderer(s_Renderer);
		SDL_DestroyWindow(s_Window);

		SDL_Quit();
	}

	[[nodiscard]] inline double Window::getDeltaTime() noexcept
	{
		return s_LastFrameTime;
	}

	[[nodiscard]] inline std::string Window::getFPSInfo()
	{
		const auto avgFT = std::round((s_TotalTime / s_FrameCount) * 1E6);
		const auto avgFPS = std::round(s_FrameCount / s_TotalTime);
		const auto longestFrame =
			eqx::narrowCast<unsigned long long>(s_LongestFrame * 1'000'000.0);
		const auto shortestFrame =
			eqx::narrowCast<unsigned long long>(s_ShortestFrame * 1'000'000.0);

		s_FrameCount = 0ULL;
		s_LongestFrame = 0.0;
		s_ShortestFrame = std::numeric_limits<double>::max();
		s_TotalTime = 0.0;

		return std::format("{:=<25}\n", "") +
			std::format("Average Frame Time: {}us\n", avgFT) +
			std::format("Average FPS: {} fps\n", avgFPS) +
			std::format("Longest Frame Time: {}us\n", longestFrame) +
			std::format("Shortest Frame Time: {}us\n", shortestFrame) +
			std::format("{:=<25}\n", "");
	}

	inline void Window::printFPSInfo(long long ms)
	{
		static auto timer = eqx::StopWatch();
		if (timer.readTime() > ms)
		{
			eqx::println(getFPSInfo());
			timer.start();
		}
	}

	inline void Window::setFrameRate(int frameRate) noexcept
	{
		s_FrameRate = frameRate;
	}

	inline void Window::setEventFunction(void (*func)(const SDL_Event& e))
		noexcept
	{
		s_EventFunction = func;
	}

	inline void Window::setUpdateFunction(void (*func)()) noexcept
	{
		s_UpdateFunction = func;
	}

	inline void Window::setRenderFunction(void (*func)()) noexcept
	{
		s_RenderFunction = func;
	}

	[[nodiscard]] inline int Window::getFrameRate() noexcept
	{
		return s_FrameRate;
	}

	[[nodiscard]] inline int Window::getWidth() noexcept
	{
		return s_Width;
	}

	[[nodiscard]] inline int Window::getHeight() noexcept
	{
		return s_Height;
	}

	[[nodiscard]] inline SDL_Renderer* Window::getRenderer() noexcept
	{
		eqx::runtimeAssert(isInit(), "pul::Window::init(...) Was Not Called");
		return s_Renderer;
	}
}
