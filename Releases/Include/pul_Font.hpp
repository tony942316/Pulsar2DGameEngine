#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

namespace pul
{
	class Font
	{
	public:
		explicit inline Font();
		inline ~Font() noexcept;

		inline void loadFont(std::string_view fontPath, std::string_view fontText);

		inline void render(const eqx::Point<double>& location);

	private:
		inline int getWidth(int height) const;

		std::string m_Text, m_FontPath;
		SDL_Texture* m_Texture;
	};
}

#include "pul_DefHeaders/pul_FontDef.hpp"
