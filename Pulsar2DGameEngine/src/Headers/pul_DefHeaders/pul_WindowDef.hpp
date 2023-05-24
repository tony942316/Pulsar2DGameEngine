#pragma once

namespace pul
{
	[[nodiscard]] inline bool Window::createWindow() noexcept
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printSDLError();
			return false;
		}

		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printError("Warning: Linear texture filtering not enabled!");
		}

		s_Window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_HIDDEN);
		if (s_Window == NULL)
		{
			printSDLError();
			return false;
		}

		s_Renderer = SDL_CreateRenderer(s_Window, -1,
			SDL_RENDERER_ACCELERATED);
		if (s_Renderer == NULL)
		{
			printSDLError();
			return false;
		}

		SDL_SetRenderDrawColor(s_Renderer, 0x00, 0x00, 0x00, 0x00);
		return true;
	}

	inline void Window::printSDLError() noexcept
	{
		printError(SDL_GetError());
	}

	inline void Window::printError(std::string_view msg) noexcept
	{
		std::cout << msg << std::endl;
	}

	inline void Window::init(std::string_view name, int width, 
		int height) noexcept
	{
		eqx::runtimeAssert(s_IsOk, "Window Creation Failed!!");
		s_Name = name;
		s_Width = width;
		s_Height = height;
		
		auto wndPos = eqx::Point<int>();
		SDL_GetWindowPosition(s_Window, &wndPos.x, &wndPos.y);
		wndPos -= eqx::Point<int>(width / 2, height / 2);

		SDL_SetWindowTitle(s_Window, s_Name.data());
		SDL_SetWindowSize(s_Window, s_Width, s_Height);
		SDL_SetWindowPosition(s_Window, wndPos.x, wndPos.y);
	}

	inline void Window::shutDown() noexcept
	{
		SDL_Quit();
	}

	inline void Window::show()
	{
		using namespace eqx::shortTimeUnits;

		SDL_Event e;
		auto quit = false;
		auto singleFrameTimer = eqx::StopWatch();

		s_FrameRateTimer.start();

		SDL_ShowWindow(s_Window);
		while (!quit)
		{
			if (s_FrameRateTimer.readTime<tu_us>() < 
				(1'000'000 / (s_FrameRate + 5)))
			{
				continue;
			}

			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				else
				{
					Mouse::handleEvent(e);
					s_EventFunction(e);
				}
			}

			s_UpdateFunction();

			SDL_RenderClear(s_Renderer);
			s_RenderFunction();
			SDL_RenderPresent(s_Renderer);

			s_FrameCount++;
			s_LastFrameTime =
				singleFrameTimer.readTime<tu_us>() / 1'000'000.0;
			s_TotalTime += singleFrameTimer.getTime<tu_us>();
			s_LongestFrame = s_LastFrameTime > s_LongestFrame ?
				s_LastFrameTime : s_LongestFrame;
			s_ShortestFrame = s_LastFrameTime < s_ShortestFrame ?
				s_LastFrameTime : s_ShortestFrame;
			s_FrameRateTimer.start();
			singleFrameTimer.start();
		}

		SDL_DestroyRenderer(s_Renderer);
		SDL_DestroyWindow(s_Window);
	}

	[[nodiscard]] inline double Window::getDeltaTime() noexcept
	{
		return s_LastFrameTime;
	}

	[[nodiscard]] inline std::string Window::getFPSInfo()
	{
		using namespace eqx::shortTimeUnits;
		auto avgFT = s_TotalTime / s_FrameCount;
		auto avgFPS = 1'000'000.0 / avgFT;
		auto longestFrame =
			static_cast<unsigned long long>(s_LongestFrame * 1'000'000.0);
		auto shortestFrame =
			static_cast<unsigned long long>(s_ShortestFrame * 1'000'000.0);
		auto result = std::string("");

		s_FrameCount = 0ULL;
		s_LongestFrame = 0.0;
		s_ShortestFrame = std::numeric_limits<double>::max();
		s_TotalTime = 0.0;

		result += "=====================\n";
		result += "Average Frame Time: ";
		result += std::to_string(avgFT);
		result += "\n";
		result += "Average FPS: ";
		result += std::to_string(avgFPS);
		result += "\n";
		result += "Longest Frame Time: ";
		result += std::to_string(longestFrame);
		result += "\n";
		result += "Shortest Frame Time: ";
		result += std::to_string(shortestFrame);
		result += "\n";
		result += "=====================\n";
		return result;
	}

	[[nodiscard]] inline bool Window::isOk() noexcept
	{
		return s_IsOk;
	}

	inline void Window::setFrameRate(int frameRate) noexcept
	{
		s_FrameRate = frameRate;
	}

	inline void Window::setEventFunction(
		const std::function<void(const SDL_Event&)>& func) noexcept
	{
		s_EventFunction = func;
	}

	inline void Window::setUpdateFunction(
		const std::function<void(void)>& func) noexcept
	{
		s_UpdateFunction = func;
	}

	inline void Window::setRenderFunction(
		const std::function<void(void)>& func) noexcept
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
		return s_Renderer;
	}
}
