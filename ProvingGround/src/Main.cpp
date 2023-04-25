#include "PGpch.hpp"

namespace Game
{
	void run();
	void handleEvent(const SDL_Event& e);
	void update();
	void render();
}

int main()
{
	std::cout << "Start" << std::endl;

	Game::run();

	std::cout << "End" << std::endl;
}



static auto s_Window = pul::Window("Game Window", 1600, 1200);

static auto s_MouseTexture = 
	pul::Texture(s_Window.getRenderer(), "assets/Mouse.png");
static auto s_EnemyTexture = 
	pul::Texture(s_Window.getRenderer(), "assets/Enemy.png");
static auto s_FlexTexture =
	pul::Texture(s_Window.getRenderer(), "assets/Flex.png");

static auto s_Mouse =
	pul::Entity(s_MouseTexture, 
		eqx::Rectangle<double>(0.0, 0.0, 50.0, 50.0),
		pul::Entity::c_MaxSpeed);
static auto s_Unit = 
	pul::Entity(s_EnemyTexture, 
		eqx::Rectangle<double>(500.0, 500.0, 100.0, 100.0), 
		2'000);
static auto s_Blade =
	pul::Entity(s_FlexTexture, 
		eqx::Rectangle<double>(500.0, 500.0, 10.0, 150.0), 5'000.0);

void Game::run()
{
	//Game::getInstance().m_Window.hideMouse();

	s_Unit.setColor({ 180, 255, 255 });
	s_Mouse.setRotationSpeed(200.0);
	s_Mouse.setRotationDirection(-1);
	s_Mouse.setRotationTarget(1E20);
	s_Mouse.setRotationPoint(eqx::Point<double>(25.0, 25.0));

	s_Blade.setColor({ 0, 0, 255 });
	s_Blade.setRotationSpeed(1'000.0);
	s_Blade.setRotationPoint(eqx::Point<double>(5.0, 125.0));

	s_Window.setEventFunction(handleEvent);
	s_Window.setUpdateFunction(update);
	s_Window.setRenderFunction(render);
	s_Window.show();
}

void Game::handleEvent(const SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_j)
		{
			s_Blade.setRotationTarget(160.0);
		}
		else if (e.key.keysym.sym == SDLK_k)
		{
			s_Blade.setRotationTarget(30.0);
		}
	}
}

void Game::update()
{
	static auto timer = eqx::StopWatch();
	auto dt = s_Window.getDeltaTime();
	auto mouse = pul::Mouse::getCurrentLocation();

	s_Mouse.setTarget(mouse - eqx::Point<double>(25.0, 25.0));
	s_Unit.setTarget(pul::Mouse::getRightClickDownLocation());
	s_Mouse.move(dt);
	s_Mouse.rotate(dt);
	s_Unit.move(dt);

	s_Blade.rotate(dt);

	if (s_Mouse.rotationTargetReached())
	{
		s_Mouse.setRotationTarget(-s_Mouse.getAngle());
	}

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
	s_Blade.render();
}