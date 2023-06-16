#pragma once

namespace pul
{
	inline Font::Font()
		:
		m_Text(""),
		m_FontPath(""),
		m_Texture(nullptr)
	{

	}

	inline Font::~Font() noexcept
	{
		if (m_Texture != nullptr)
		{
			SDL_DestroyTexture(m_Texture);
		}
	}

	inline void
		Font::loadFont(std::string_view fontPath, std::string_view fontText)
	{
		if (m_Texture != nullptr)
		{
			SDL_DestroyTexture(m_Texture);
		}

		m_FontPath = fontPath;
		TTF_Font* font = TTF_OpenFont(m_FontPath.c_str(), 60);
		if (font == NULL)
		{
			std::cout << "Font Load Error! SDL Error: " << SDL_GetError() << std::endl;
			return;
		}
		unsigned char r, g, b;
		unsigned int colorBytes = static_cast<unsigned int>(0xFFFFFF);
		r = (colorBytes >> 16) & 0xFF;
		g = (colorBytes >> 8) & 0xFF;
		b = colorBytes & 0xFF;
		m_Text = fontText;
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, m_Text.c_str(), { r, g, b });
		TTF_CloseFont(font);

		m_Texture = SDL_CreateTextureFromSurface(pul::Window::getRenderer(), surfaceMessage);
		if (m_Texture == NULL)
		{
			std::cout << "Texture Creation Error! SDL Error: " << SDL_GetError() << std::endl;
			return;
		}
		SDL_FreeSurface(surfaceMessage);
	}

	inline void Font::render(const eqx::Point<double>& location)
	{
		SDL_Rect dest = { location.x, location.y, getWidth(30), 30 };
		SDL_RenderCopy(pul::Window::getRenderer(), m_Texture, NULL, &dest);
	}

	inline int Font::getWidth(int height) const
	{
		return static_cast<int>(m_Text.length()) * height / 3;
	}

}
