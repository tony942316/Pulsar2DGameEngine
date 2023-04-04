#include <iostream>

#include "Pulsar.hpp"

class Game
{
public:
	Game() = delete;
	Game(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator= (const Game& other) = delete;
	Game& operator= (Game&& other) = delete;

	static void run();
	static void handleEvent(const SDL_Event& e);
	static void update();
	static void render();

	static pul::Window s_Window;
	static pul::Entity s_Mouse, s_Unit;
};

int main()
{
	std::cout << "Start" << std::endl;

	Game::run();

	std::cout << "End" << std::endl;
}

pul::Window Game::s_Window = { "Game Window", 1200, 700 };
pul::Entity Game::s_Mouse = {
	Game::s_Window.getRenderer(), "assets/Mouse.png",
	{ 0.0, 0.0, 50.0, 50.0 }, 900.0
};
pul::Entity Game::s_Unit = {
	Game::s_Window.getRenderer(), "assets/Enemy.png",
	{ 500.0, 500.0, 100.0, 100.0 }, 500.0
};

void Game::run()
{
	//Game::getInstance().m_Window.hideMouse();
	s_Window.setEventFunction(handleEvent);
	s_Window.setUpdateFunction(update);
	s_Window.setRenderFunction(render);
	s_Window.show();
}

void Game::handleEvent(const SDL_Event& e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT)
	{
		s_Unit.setTarget(pul::Mouse::getRightClickDownLocation());
	}
}

void Game::update()
{
	static auto timer = eqx::StopWatch();
	auto dt = s_Window.getDeltaTime();
	if (!s_Unit.targetReached())
	{
		s_Unit.move(dt);
	}

	s_Mouse.setLocation(pul::Mouse::getCurrentLocation());

	if (timer.readTime() > 1'000)
	{
		timer.start();
		std::cout << s_Window.getFPSInfo() << std::endl;
	}
}

void Game::render()
{
	s_Unit.render();
	s_Mouse.render();
}