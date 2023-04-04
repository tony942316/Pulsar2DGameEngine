#include "pul_Texture.hpp"

#include <iostream>

#include <SDL_image.h>

namespace pul
{
	Texture::Texture()
		:
		Texture(nullptr, "")
	{
	}

	Texture::Texture(SDL_Renderer* renderer, std::string_view filePath)
		:
		m_Width(0),
		m_Height(0),
		m_SdlTexture(nullptr),
		m_Renderer(renderer)
	{
		if (renderer != nullptr)
		{
			loadFile(filePath);
		}
	}

	Texture::~Texture()
	{
		SDL_DestroyTexture(m_SdlTexture);
	}

	void Texture::setRenderer(SDL_Renderer* renderer)
	{
		m_Renderer = renderer;
	}

	void Texture::loadFile(std::string_view filePath)
	{
		if (m_SdlTexture != nullptr)
		{
			SDL_DestroyTexture(m_SdlTexture);
		}

		SDL_Surface* surface = IMG_Load(filePath.data());
		if (surface == NULL)
		{
			std::cout << IMG_GetError() << std::endl;
			return;
		}

		SDL_SetColorKey(surface, SDL_TRUE,
			SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
		m_Width = surface->w;
		m_Height = surface->h;

		m_SdlTexture = SDL_CreateTextureFromSurface(m_Renderer, surface);
		if (m_SdlTexture == NULL)
		{
			std::cout << SDL_GetError() << std::endl;
			return;
		}

		SDL_FreeSurface(surface);
	}

	void Texture::render(eqx::Point<double> location) const
	{
		render({ location.x, location.y, 
			static_cast<double>(m_Width), static_cast<double>(m_Height) });
	}

	void Texture::render(eqx::Rectangle<double> destination) const
	{
		SDL_Rect source = {
			0,
			0,
			m_Width,
			m_Height
		};

		SDL_Rect dest = {
			static_cast<int>(destination.x),
			static_cast<int>(destination.y),
			static_cast<int>(destination.w),
			static_cast<int>(destination.h)
		};

		if (SDL_RenderCopy(m_Renderer, m_SdlTexture, &source, &dest) == -1)
		{
			std::cout << SDL_GetError() << std::endl;
		}
	}
}