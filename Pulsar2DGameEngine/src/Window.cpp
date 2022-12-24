#include "Window.h"

#include <iostream>

#include <EquinoxSTD.h>

namespace pulsar
{
	Window::Window(const std::string& name, int width, int height, Window::Package package)
		:
		m_Package(package),
		m_Window(nullptr),
		m_Renderer(nullptr),
		m_Gamepad(nullptr),
		m_ScreenWidth(width),
		m_ScreenHeight(height),
		m_FrameCount(0ll),
		m_LastFrameTime(0ll),
		m_AvgFrameTime(0.0),
		m_TotalFrameTime(0.0),
		m_Exit(false),
		m_CalcFunc(nullptr),
		m_RenderFunc(nullptr),
		m_EventFunc(nullptr),
		m_WindowName(name)
	{
		m_Packages[Window::Package::Standard] = std::pair<int, int>(SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		m_Packages[Window::Package::NoVsync] = std::pair<int, int>(SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED);

		if (!init())
		{
			eqx::Log::log(eqx::Log::Level::error, std::string("Init Failure!"), eqx::Log::Type::runtimeError);
		}
	}

	Window::~Window()
	{
		if (!m_Exit)
			close();
	}


	void Window::setCalculations(std::function<void()> calcFunction)
	{
		m_CalcFunc = calcFunction;
	}

	void Window::setRenders(std::function<void()> renderFunction)
	{
		m_RenderFunc = renderFunction;
	}

	void Window::setEvents(std::function<void(const SDL_Event&)> eventFunction)
	{
		m_EventFunc = eventFunction;
	}

	void Window::hideMouse()
	{
		SDL_ShowCursor(SDL_DISABLE);
	}

	void Window::showMouse()
	{
		SDL_ShowCursor(SDL_ENABLE);
	}

	void Window::display()
	{
		while (!quit())
		{
			m_FrameTimer.start();

			while (pollEvent())
			{
				if (m_Event.type == SDL_QUIT)
				{
					exit();
					return;
				}
				else if (m_EventFunc != nullptr)
				{
					m_EventFunc(getEvent());
				}
			}

			if (m_CalcFunc != nullptr)
			{
				m_CalcFunc();
			}

			clear();

			if (m_RenderFunc != nullptr)
			{
				m_RenderFunc();
			}

			show();

			m_FrameTimer.stop();

			m_LastFrameTime = m_FrameTimer.getTimeMicro();
			m_FrameCount++;
			m_TotalFrameTime += static_cast<double>(m_FrameTimer.getTimeMicro());
			m_AvgFrameTime = m_TotalFrameTime / m_FrameCount;
		}
	}

	void Window::exit()
	{
		m_Exit = true;
		close();
	}

	SDL_Window* Window::getWindow() const
	{
		return m_Window;
	}

	SDL_Renderer* Window::getRenderer() const
	{
		return m_Renderer;
	}

	int Window::getWidth() const
	{
		return m_ScreenWidth;
	}

	int Window::getHeight() const
	{
		return m_ScreenHeight;
	}

	double Window::getAvgFrameTime() const
	{
		return m_AvgFrameTime;
	}

	double Window::getAvgFps() const
	{
		return 1.0 / m_AvgFrameTime;
	}

	double Window::getCurrentFps() const
	{
		return 1.0 / (m_LastFrameTime / 1'000'000.0);
	}

	long long Window::getLastFrameTime() const
	{
		return m_LastFrameTime;
	}

	double Window::getDeltaTime() const
	{
		return m_LastFrameTime / 1'000'000.0;
	}

	void Window::printFrameInfo() const
	{
		std::cout << "=====================" << std::endl;
		std::cout << "Average FPS: " << getAvgFps() << std::endl;
		std::cout << "Average Frame Time: " << m_AvgFrameTime << std::endl;
		std::cout << "Most Recent Frame Time: " << m_LastFrameTime << std::endl;
		std::cout << "Current Frame Rate: " << getCurrentFps() << std::endl;
		std::cout << "=====================" << std::endl;
	}

	int Window::pollEvent()
	{
		return SDL_PollEvent(&m_Event);
	}

	SDL_Event Window::getEvent() const
	{
		return m_Event;
	}

	bool Window::quit()
	{
		if (m_Exit)
		{
			return true;
		}

		return false;
	}

	void Window::clear()
	{
		SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(m_Renderer);
	}

	void Window::show()
	{
		SDL_RenderPresent(m_Renderer);
	}

	bool Window::init()
	{
		if (!initSDL())
			return false;

		if (!createWindow())
			return false;

		if (!createRenderer())
			return false;

		return true;
	}

	bool Window::initSDL()
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO) < 0)
		{
			eqx::Log::log(eqx::Log::Level::error, std::string("SDL could not initialize! SDL Error: ") + SDL_GetError(), eqx::Log::Type::runtimeError);
			return false;
		}

		/*
		// Initialize SDL_ttf
		if (TTF_Init() == -1)
		{
			std::cout << "SDL_ttf could not initialize! TTF Error: " << TTF_GetError() << std::endl;
			return false;
		}*/

		/*
		// Initialize SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
			return false;
		}*/

		/*
		// Initialize SDL_image
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			std::cout << "SDL_image could not initialize! SDL_image Error: " << SDL_GetError() << std::endl;
			return false;
		}*/

		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			eqx::Log::log(eqx::Log::Level::warning, std::string("Warning: Linear texture filtering not enabled!"));
		}

		if (SDL_NumJoysticks() < 1)
		{
			eqx::Log::log(eqx::Log::Level::info, std::string("No joysticks connected!"), eqx::Log::Type::info);
		}
		else
		{
			m_Gamepad = SDL_GameControllerOpen(0);
			if (m_Gamepad == NULL)
			{
				eqx::Log::log(eqx::Log::Level::warning, std::string("Unable to open game controller! SDL Error: ") + SDL_GetError(), eqx::Log::Type::runtimeWarning);
				return false;
			}
		}


		return true;
	}

	bool Window::createWindow()
	{
		m_Window = SDL_CreateWindow(m_WindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			m_ScreenWidth, m_ScreenHeight, m_Packages[m_Package].first);
		if (m_Window == NULL)
		{
			eqx::Log::log(eqx::Log::Level::error, std::string("Window could not be created! SDL Error: ") + SDL_GetError(), eqx::Log::Type::runtimeError);
			return false;
		}

		return true;
	}

	bool Window::createRenderer()
	{
		m_Renderer = SDL_CreateRenderer(m_Window, -1, m_Packages[m_Package].second);
		if (m_Renderer == NULL)
		{
			eqx::Log::log(eqx::Log::Level::error, std::string("Renderer could not be created! SDL Error: ") + SDL_GetError(), eqx::Log::Type::runtimeError);
			return false;
		}

		SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0x00);

		return true;
	}

	void Window::close()
	{
		if (m_Gamepad != nullptr)
			SDL_GameControllerClose(m_Gamepad);

		SDL_DestroyRenderer(m_Renderer);
		SDL_DestroyWindow(m_Window);

		//TTF_Quit();
		//Mix_Quit();
		//IMG_Quit();
		SDL_Quit();
	}
}