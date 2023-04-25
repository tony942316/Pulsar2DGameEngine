#include "pul_Texture.hpp"

#include <iostream>

#include <SDL_image.h>

namespace pul
{
	Texture::Texture() noexcept
		:
		Texture(nullptr, "")
	{
	}

	Texture::Texture(SDL_Renderer* renderer, 
		std::string_view filePath) noexcept
		:
		m_Width(0),
		m_Height(0),
		m_FilePath(""),
		m_SdlTexture(nullptr),
		m_Renderer(renderer)
	{
		if (m_Renderer != nullptr && filePath != "")
		{
			loadFile(filePath);
		}
	}

	Texture::Texture(const Texture& other) noexcept
		:
		m_Width(0),
		m_Height(0),
		m_FilePath(""),
		m_SdlTexture(nullptr),
		m_Renderer(other.m_Renderer)
	{
		if (m_Renderer != nullptr && other.m_FilePath != "")
		{
			loadFile(other.m_FilePath);
		}
	}

	Texture::Texture(Texture&& other) noexcept
		:
		m_Width(other.m_Width),
		m_Height(other.m_Height),
		m_FilePath(other.m_FilePath),
		m_SdlTexture(other.m_SdlTexture),
		m_Renderer(other.m_Renderer)
	{
		other.m_Width = 0;
		other.m_Height = 0;
		other.m_FilePath = "";
		other.m_SdlTexture = nullptr;
		other.m_Renderer = nullptr;
	}

	Texture& Texture::operator= (const Texture& other) noexcept
	{
		if (m_SdlTexture != nullptr)
		{
			SDL_DestroyTexture(m_SdlTexture);
		}

		m_Renderer = other.m_Renderer;

		if (m_Renderer != nullptr && other.m_FilePath != "")
		{
			loadFile(other.m_FilePath);
		}

		return *this;
	}

	Texture& Texture::operator= (Texture&& other) noexcept
	{
		std::swap(m_Width, other.m_Width);
		std::swap(m_Height, other.m_Height);
		std::swap(m_FilePath, other.m_FilePath);
		std::swap(m_SdlTexture, other.m_SdlTexture);
		std::swap(m_Renderer, other.m_Renderer);

		return *this;
	}

	Texture::~Texture() noexcept
	{
		if (m_SdlTexture != nullptr)
		{
			SDL_DestroyTexture(m_SdlTexture);
		}
	}

	void Texture::setRenderer(SDL_Renderer* renderer) noexcept
	{
		m_Renderer = renderer;
	}

	void Texture::loadFile(std::string_view filePath) noexcept
	{
		eqx::runtimeAssert(m_Renderer != nullptr,
			"Attempted To Load A File Without Setting A Renderer!");

		if (m_SdlTexture != nullptr)
		{
			SDL_DestroyTexture(m_SdlTexture);
		}

		m_FilePath = filePath;

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

	void Texture::render(const eqx::Point<double>& location) const noexcept
	{
		render(Config({ eqx::Rectangle<double>( 
				location.x, 
				location.y,
				static_cast<double>(m_Width), 
				static_cast<double>(m_Height)),
				0.0, eqx::Point<double>(0.0, 0.0), SDL_FLIP_NONE, 
				{ 255, 255, 255 }
		}));
	}

	void Texture::render(
		const eqx::Rectangle<double>& destination) const noexcept
	{
		render(Config({ destination, 0.0, eqx::Point<double>(0.0, 0.0), 
			SDL_FLIP_NONE, { 255, 255, 255 } }));
	}

	void Texture::render(const Config& config) const noexcept
	{
		SDL_Rect source = {
			0, 0, m_Width, m_Height
		};

		SDL_Rect dest = {
			static_cast<int>(config.destination.x),
			static_cast<int>(config.destination.y),
			static_cast<int>(config.destination.w),
			static_cast<int>(config.destination.h)
		};

		SDL_Point rotationPoint = {
			static_cast<int>(config.rotationPoint.x),
			static_cast<int>(config.rotationPoint.y)
		};

		if (SDL_SetTextureColorMod(m_SdlTexture, 
			config.rgb.r, config.rgb.g, config.rgb.b) == -1)
		{
			std::cout << SDL_GetError() << std::endl;
		}

		if (SDL_RenderCopyEx(
			m_Renderer, m_SdlTexture, &source, &dest,
			config.angle, &rotationPoint, config.flip) == -1)
		{
			std::cout << SDL_GetError() << std::endl;
		}

		if (SDL_SetTextureColorMod(m_SdlTexture,
			255, 255, 255) == -1)
		{
			std::cout << SDL_GetError() << std::endl;
		}
	}
}