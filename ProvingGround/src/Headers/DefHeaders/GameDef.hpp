#pragma once

void Game::start()
{
	pul::Window::init("Game Window", 1600, 1200);
	pul::Window::setFrameRate(144);

	s_MouseTexture.loadAsset("assets/Mouse.png");
	s_EnemyTexture.loadAsset("assets/Enemy.png");
	s_FlexTexture.loadAsset("assets/Flex.png");

	s_Mouse.setDrawBox(eqx::Rectangle<double>(0.0, 0.0, 50.0, 50.0));
	s_Mouse.setRotationPoint(eqx::Point<double>(25.0, 25.0));

	s_Unit.setDrawBox(eqx::Rectangle<double>(500.0, 500.0, 100.0, 100.0));
	s_Unit.setMoveAcceleration(600.0);
	s_Unit.setMaxMoveSpeed(400.0);

	s_Blade.setDrawBox(eqx::Rectangle<double>(500.0, 500.0, 10.0, 150.0));
	s_Blade.setColor(pul::Texture::Color(0, 255, 0, 150));

	static auto text = pul::Text("Sans", "assets/Sans.ttf", 100);
	static auto text2 =
		pul::Text("Poppins", "assets/Poppins/Poppins-Regular.ttf", 100);
	static auto text3 = pul::Text("Kablammo", 
		"assets/Kablammo/static/Kablammo-Regular.ttf", 100);
	s_Sans = &text;
	s_Poppins = &text2;
	s_Kablammo = &text3;

	pul::Window::setEventFunction(handleEvent);
	pul::Window::setUpdateFunction(update);
	pul::Window::setRenderFunction(render);
	pul::Window::show();
}

void Game::handleEvent(const SDL_Event& e) noexcept
{
	e;
}

void Game::update()
{
	EQX_SUPPRESS_WARNING(26820);
	const auto mouse = pul::Mouse::getCurrentLocation();

	s_Mouse.setLocation(mouse - eqx::Point<double>(25.0, 25.0));
	s_Mouse.setAngle(s_Mouse.getAngle() + 1.5);

	s_Unit.setMoveTarget(pul::Mouse::getRightClickDownLocation());
	s_Unit.update();

	pul::Window::printFPSInfo();
}

void Game::render() noexcept
{
	s_Unit.render();
	s_Mouse.render();
	s_Blade.render();
	s_Sans->render(eqx::Point<double>(0, 0));
	s_Poppins->render(eqx::Point<double>(0, 110));
	s_Kablammo->render(eqx::Point<double>(0, 220));
}
