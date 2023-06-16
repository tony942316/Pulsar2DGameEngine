#pragma once

#include "pul_Dependencies.hpp"

#include "pul_Window.hpp"

namespace pul
{
	class Texture
	{
	public:
		struct Color
		{
			explicit constexpr Color() noexcept;
			constexpr Color(std::uint8_t red, std::uint8_t green,
				std::uint8_t blue, std::uint8_t alpha) noexcept;

			Color(const Color&) = default;
			Color(Color&&) = default;
			Color& operator= (const Color&) = default;
			Color& operator= (Color&&) = default;
			~Color() = default;

			std::uint8_t r, g, b, a;
		};

		struct Config
		{
			explicit constexpr Config() noexcept;
			explicit constexpr Config(const eqx::Rectangle<double>& dest,
				double ang, const eqx::Point<double>& rotP,
				SDL_RendererFlip flp, const Color& col) noexcept;

			Config(const Config&) = default;
			Config(Config&&) = default;
			Config& operator= (const Config&) = default;
			Config& operator= (Config&&) = default;
			~Config() = default;

			eqx::Rectangle<double> destination;
			double angle;
			eqx::Point<double> rotationPoint;
			SDL_RendererFlip flip;
			Color color;
		};

		explicit constexpr Texture() noexcept;

		constexpr Texture(Texture&& other) noexcept;
		constexpr Texture& operator= (Texture&& other) noexcept;

		constexpr ~Texture() noexcept;

		Texture(const Texture&) = delete;
		Texture& operator= (const Texture&) = delete;

		inline void render(const eqx::Point<double>& location) const noexcept;
		inline void render(const eqx::Rectangle<double>& destination) 
			const noexcept;
		inline void render(const Config& config) const noexcept;

	protected:
		int m_Width, m_Height;

		SDL_Texture* m_SdlTexture;
		SDL_Renderer* m_Renderer;
	};

	class Sprite : public Texture
	{
	public:
		inline void loadAsset(std::string_view spritePath) noexcept;
	};

	class Text : public Texture
	{
	public:
		explicit inline Text(std::string_view text, std::string_view fontPath, 
				int pxHeight);

		inline void loadFont(std::string_view fontPath, int pxHeight) noexcept;

	private:
		std::string m_Text;
	};
}

#include "pul_DefHeaders/pul_TextureDef.hpp"