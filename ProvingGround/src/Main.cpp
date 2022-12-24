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

	eqx::Point<int> m_MouseLocation;
	pulsar::Window m_Window;
	pulsar::Texture m_MouseTexture;
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
	m_Window("Game Window", 900, 600),
	m_MouseTexture(m_Window, "assets/Mouse.png")
{

}

Game& Game::getInstance()
{
	static Game instance;
	return instance;
}

void Game::run()
{
	Game::getInstance().m_Window.hideMouse();
	Game::getInstance().m_Window.setCalculations(calculate);
	Game::getInstance().m_Window.setRenders(render);
	Game::getInstance().m_Window.setEvents(handleEvent);
	Game::getInstance().m_Window.display();
}

void Game::render()
{
	Game::getInstance().m_MouseTexture.render(Game::getInstance().m_MouseLocation);
}

void Game::calculate()
{
	
}

void Game::handleEvent(const SDL_Event& e)
{
	if (e.type == SDL_MOUSEMOTION)
	{
		Game::getInstance().m_MouseLocation.x = e.motion.x;
		Game::getInstance().m_MouseLocation.y = e.motion.y;
	}
}