#pragma once

namespace pul
{
	constexpr Texture::Color::Color() noexcept
		:
		r(255),
		g(255),
		b(255),
		a(255)
	{
	}

	constexpr Texture::Color::Color(std::uint8_t red, std::uint8_t green,
		std::uint8_t blue, std::uint8_t alpha) noexcept
		:
		r(red),
		g(green),
		b(blue),
		a(alpha)
	{
	}

	constexpr Texture::Config::Config() noexcept
		:
		destination(),
		angle(0.0),
		rotationPoint(),
		flip(SDL_FLIP_NONE),
		color()
	{
	}

	constexpr Texture::Config::Config(const eqx::Rectangle<double>& dest,
		double ang, const eqx::Point<double>& rotP,
		SDL_RendererFlip flp, const Color& col) noexcept
		:
		destination(dest),
		angle(ang),
		rotationPoint(rotP),
		flip(flp),
		color(col)
	{
	}

	constexpr Texture::Texture() noexcept
		:
		m_Width(0),
		m_Height(0),
		m_SdlTexture(nullptr),
		m_Renderer(nullptr)
	{
	}

	constexpr Texture::Texture(Texture&& other) noexcept
		:
		m_Width(std::move(other.m_Width)),
		m_Height(std::move(other.m_Height)),
		m_SdlTexture(std::move(other.m_SdlTexture)),
		m_Renderer(std::move(other.m_Renderer))
	{
		other.m_SdlTexture = nullptr;
	}

	constexpr Texture& Texture::operator= (Texture&& other) noexcept
	{
		std::swap(m_Width, other.m_Width);
		std::swap(m_Height, other.m_Height);
		std::swap(m_SdlTexture, other.m_SdlTexture);
		std::swap(m_Renderer, other.m_Renderer);

		return *this;
	}

	constexpr Texture::~Texture() noexcept
	{
		if (m_SdlTexture != nullptr)
		{
			SDL_DestroyTexture(m_SdlTexture);
		}
	}

	inline void Texture::render(const eqx::Point<double>& location) 
		const noexcept
	{
		render(eqx::Rectangle<double>(location.x, location.y, 
			static_cast<double>(m_Width), static_cast<double>(m_Height)));
	}

	inline void Texture::render(const eqx::Rectangle<double>& destination) 
		const noexcept
	{
		render(Config(destination, 0.0, eqx::Point<double>(0.0, 0.0),
			SDL_FLIP_NONE, Color(255, 255, 255, 255)));
	}

	inline void Texture::render(const Config& config) const noexcept
	{
		const SDL_Rect source = {
			0, 0, m_Width, m_Height };

		const SDL_Rect dest = {
			static_cast<int>(config.destination.x),
			static_cast<int>(config.destination.y),
			static_cast<int>(config.destination.w),
			static_cast<int>(config.destination.h) };

		const SDL_Point rotationPoint = {
			static_cast<int>(config.rotationPoint.x),
			static_cast<int>(config.rotationPoint.y) };

		eqx::runtimeAssert(SDL_SetTextureColorMod(m_SdlTexture,
			config.color.r, config.color.g, config.color.b) == 0, 
			SDL_GetError());
		eqx::runtimeAssert(SDL_SetTextureAlphaMod(m_SdlTexture,
			config.color.a) == 0, SDL_GetError());

		eqx::runtimeAssert(SDL_RenderCopyEx(m_Renderer, m_SdlTexture, 
			&source, &dest, config.angle, &rotationPoint, config.flip) == 0, 
			SDL_GetError());

		eqx::runtimeAssert(SDL_SetTextureColorMod(m_SdlTexture, 255, 255, 
			255) == 0, SDL_GetError());
		eqx::runtimeAssert(SDL_SetTextureAlphaMod(m_SdlTexture, 255) == 0, 
			SDL_GetError());
	}

	inline void Sprite::loadAsset(std::string_view assetPath) noexcept
	{
		m_Renderer = pul::Window::getRenderer();

		if (m_SdlTexture != nullptr)
		{
			SDL_DestroyTexture(m_SdlTexture);
		}

		SDL_Surface* surface = IMG_Load(assetPath.data());
		EQX_SUPPRESS_WARNING(26477);
		eqx::runtimeAssert(surface != NULL, IMG_GetError());
		m_Width = surface->w;
		m_Height = surface->h;

		//SDL_SetColorKey(surface, SDL_TRUE,
		//	SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

		m_SdlTexture = SDL_CreateTextureFromSurface(m_Renderer, surface);
		EQX_SUPPRESS_WARNING(26477);
		eqx::runtimeAssert(m_SdlTexture != NULL, SDL_GetError());

		SDL_FreeSurface(surface);
	}

	inline Text::Text(std::string_view text, std::string_view fontPath,
		int pxHeight)
		:
		Texture(),
		m_Text(text)
	{
		loadFont(fontPath, pxHeight);
	}

	inline void Text::loadFont(std::string_view fontPath, int pxHeight) 
		noexcept
	{
		m_Renderer = pul::Window::getRenderer();

		if (m_SdlTexture != nullptr)
		{
			SDL_DestroyTexture(m_SdlTexture);
		}

		TTF_Font* font = TTF_OpenFont(fontPath.data(), pxHeight);
		EQX_SUPPRESS_WARNING(26477);
		eqx::runtimeAssert(font != NULL, TTF_GetError());

		SDL_Surface* surface = TTF_RenderText_Solid(font, m_Text.c_str(), 
			SDL_Color({ 255, 255, 255 }));
		EQX_SUPPRESS_WARNING(26477);
		eqx::runtimeAssert(surface != NULL, TTF_GetError());
		m_Width = surface->w;
		m_Height = surface->h;

		m_SdlTexture = SDL_CreateTextureFromSurface(m_Renderer, surface);
		EQX_SUPPRESS_WARNING(26477);
		eqx::runtimeAssert(surface != NULL, SDL_GetError());

		TTF_CloseFont(font);
		SDL_FreeSurface(surface);
	}
}
