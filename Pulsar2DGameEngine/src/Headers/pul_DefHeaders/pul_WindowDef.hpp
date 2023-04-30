#pragma once

namespace pul
{
	inline Window::Window(std::string_view name, int width, int height)
		:
		m_Name(name),
		m_Width(width),
		m_Height(height),
		m_FrameCount(0ULL),
		m_LastFrameTime(0.0),
		m_LongestFrame(0.0),
		m_ShortestFrame(std::numeric_limits<double>::max()),
		m_EventFunction([](const SDL_Event&) {}),
		m_UpdateFunction([]() {}),
		m_RenderFunction([]() {}),
		m_Window(nullptr),
		m_Renderer(nullptr)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printSDLError();
		}

		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printError("Warning: Linear texture filtering not enabled!");
		}

		m_Window = SDL_CreateWindow(m_Name.c_str(), SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, m_Width, m_Height, SDL_WINDOW_HIDDEN);
		if (m_Window == NULL)
		{
			printSDLError();
		}

		m_Renderer = SDL_CreateRenderer(m_Window, -1,
			SDL_RENDERER_ACCELERATED);
		if (m_Renderer == NULL)
		{
			printSDLError();
		}

		SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0x00);
	}

	inline Window::~Window()
	{
		SDL_Quit();
	}

	inline void Window::show()
	{
		using namespace eqx::shortTimeUnits;

		SDL_Event e;
		auto quit = false;
		auto singleFrameTimer = eqx::StopWatch();

		m_FrameTimer.start();

		SDL_ShowWindow(m_Window);
		while (!quit)
		{
			singleFrameTimer.start();
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				else
				{
					Mouse::handleEvent(e);
					m_EventFunction(e);
				}
			}

			m_UpdateFunction();

			SDL_RenderClear(m_Renderer);
			m_RenderFunction();
			SDL_RenderPresent(m_Renderer);

			m_FrameCount++;
			m_LastFrameTime =
				singleFrameTimer.readTime<tu_us>() / 1'000'000.0;
			m_LongestFrame = m_LastFrameTime > m_LongestFrame ?
				m_LastFrameTime : m_LongestFrame;
			m_ShortestFrame = m_LastFrameTime < m_ShortestFrame ?
				m_LastFrameTime : m_ShortestFrame;
		}

		SDL_DestroyRenderer(m_Renderer);
		SDL_DestroyWindow(m_Window);
	}

	inline void Window::setEventFunction(
		const std::function<void(const SDL_Event&)>& func)
	{
		m_EventFunction = func;
	}

	inline void Window::setUpdateFunction(const std::function<void(void)>& func)
	{
		m_UpdateFunction = func;
	}

	inline void Window::setRenderFunction(const std::function<void(void)>& func)
	{
		m_RenderFunction = func;
	}

	inline double Window::getDeltaTime() const
	{
		return m_LastFrameTime;
	}

	inline SDL_Renderer* Window::getRenderer()
	{
		return m_Renderer;
	}

	inline std::string Window::getFPSInfo()
	{
		using namespace eqx::shortTimeUnits;
		auto avgFT = m_FrameTimer.readTime<tu_us>() / m_FrameCount;
		auto avgFPS = 1'000'000.0 / avgFT;
		auto longestFrame =
			static_cast<unsigned long long>(m_LongestFrame * 1'000'000.0);
		auto shortestFrame =
			static_cast<unsigned long long>(m_ShortestFrame * 1'000'000.0);
		auto result = std::string("");

		m_FrameCount = 0ULL;
		m_LongestFrame = 0.0;
		m_ShortestFrame = std::numeric_limits<double>::max();
		m_FrameTimer.start();

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

	inline int Window::getWidth() const
	{
		return m_Width;
	}

	inline int Window::getHeight() const
	{
		return m_Height;
	}

	inline void Window::printSDLError() const
	{
		std::cout << SDL_GetError() << std::endl;
	}

	inline void Window::printError(std::string_view msg) const
	{
		std::cout << msg << std::endl;
	}
}
