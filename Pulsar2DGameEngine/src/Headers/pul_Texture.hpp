#pragma once

#include <iostream>
#include <string>
#include <string_view>

#include <EquinoxSTD.hpp>
#include <SDL.h>
#include <SDL_image.h>

namespace pul
{
	class Texture
	{
	public:
		struct Color
		{
			uint8_t r, g, b;
		};

		struct Config
		{
			eqx::Rectangle<double> destination;
			double angle;
			eqx::Point<double> rotationPoint;
			SDL_RendererFlip flip;
			Color rgb;
		};

		explicit inline Texture() noexcept;
		explicit inline Texture(SDL_Renderer* renderer, 
			std::string_view filePath) noexcept;

		inline Texture(const Texture& other) noexcept;
		inline Texture(Texture&& other) noexcept;
		inline Texture& operator= (const Texture& other) noexcept;
		inline Texture& operator= (Texture&& other) noexcept;

		inline ~Texture() noexcept;

		inline void setRenderer(SDL_Renderer* renderer) noexcept;
		inline void loadFile(std::string_view filePath) noexcept;

		inline void render(const eqx::Point<double>& location) const noexcept;
		inline void 
			render(const eqx::Rectangle<double>& destination) const noexcept;
		inline void render(const Config& config) const noexcept;

	private:
		int m_Width, m_Height;

		std::string m_FilePath;

		SDL_Texture* m_SdlTexture;
		SDL_Renderer* m_Renderer;
	};
}

#include "pul_DefHeaders/pul_TextureDef.hpp"