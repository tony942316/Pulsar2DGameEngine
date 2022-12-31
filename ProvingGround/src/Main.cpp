#include <iostream>

#include "Pulsar.h"

class Game
{
public:
	static Game& getInstance();
	static void run();

	Game(const Game& g) = delete;
	void operator= (const Game& g) = delete;

private:
	Game();

	static void render();
	static void calculate();
	static void handleEvent(const SDL_Event& e);

	pulsar::Window m_Window;
	pulsar::Entity m_Mouse, m_Unit;
};

int main()
{
	std::cout << "Start" << std::endl;

	eqx::Log::setLevel(eqx::Log::Level::warning);

	Game::run();

	std::cout << "End" << std::endl;
}

Game::Game()
	:
	m_Window("Game Window", 1200, 700),
	m_Mouse(m_Window, "assets/Mouse.png", { 0.0, 0.0, 50.0, 50.0 }, 900.0),
	m_Unit(m_Window, "assets/Enemy.png", { 500.0, 500.0, 100.0, 100.0 }, 500.0)
{

}

Game& Game::getInstance()
{
	static Game instance;
	return instance;
}

void Game::run()
{
	//Game::getInstance().m_Window.hideMouse();
	Game::getInstance().m_Window.setCalculations(calculate);
	Game::getInstance().m_Window.setRenders(render);
	Game::getInstance().m_Window.setEvents(handleEvent);
	Game::getInstance().m_Window.display();
}

void Game::render()
{
	//Game::getInstance().m_Mouse.render();
	pulsar::Entity e(Game::getInstance().m_Unit);
	e = Game::getInstance().m_Unit;
	e.setLocation({ 100.0, 100.0 });
	e.render();
	Game::getInstance().m_Unit.render();
}

void Game::calculate()
{
	double dt = Game::getInstance().m_Window.getDeltaTime();
	if (!Game::getInstance().m_Unit.targetReached())
		Game::getInstance().m_Unit.move(dt);
}

void Game::handleEvent(const SDL_Event& e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT)
	{
		Game::getInstance().m_Unit.setTarget(pulsar::Mouse::RightClickDownLocation);
	}
}