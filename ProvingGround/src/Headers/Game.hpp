#pragma once

#include "Dependencies.hpp"

class Game
{
public:
	Game() = delete;
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator= (const Game&) = delete;
	Game& operator= (Game&&) = delete;
	~Game() = delete;

	static void start();

private:
	static void handleEvent(const SDL_Event& e) noexcept;
	static void update();
	static void render() noexcept;

	constinit static inline auto s_MouseTexture = pul::Sprite(),
		s_EnemyTexture = pul::Sprite(), s_FlexTexture = pul::Sprite();

	constinit static inline auto s_Mouse = pul::AccEntity(s_MouseTexture),
		s_Unit = pul::AccEntity(s_EnemyTexture), 
		s_Blade = pul::AccEntity(s_FlexTexture);

	constinit static inline auto s_Sans = eqx::nullp<pul::Text>;
	constinit static inline auto s_Poppins = eqx::nullp<pul::Text>;
	constinit static inline auto s_Kablammo = eqx::nullp<pul::Text>;
};

#include "DefHeaders/GameDef.hpp"
