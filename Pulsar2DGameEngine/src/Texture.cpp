#include "Texture.h"

#include <iostream>
#include <SDL_image.h>

namespace pulsar
{
	Texture::Texture(const Window& window)
		:
		Texture(window, "")
	{
	}

	Texture::Texture(const Window& window, const std::string& filePath)
		:
		m_Window(window),
		m_Width(0),
		m_Height(0),
		m_Angle(0.0),
		m_Filepath(filePath),
		m_SdlTexture(nullptr),
		m_SourceRect({ 0, 0, 0, 0 }),
		m_Flip(SDL_FLIP_NONE),
		m_RotationPoint({ 0, 0 })
	{
		if (m_Filepath != "")
			loadFile(filePath);
	}

	Texture::Texture(const Texture& other)
		:
		m_Window(other.m_Window),
		m_Filepath(other.m_Filepath),
		m_SdlTexture(nullptr)
	{
		loadFile(m_Filepath);
	}

	Texture::~Texture()
	{
		SDL_DestroyTexture(m_SdlTexture);
	}

	bool Texture::loadFile(const std::string& filePath)
	{
		if (m_SdlTexture != nullptr)
			SDL_DestroyTexture(m_SdlTexture);

		//Create surface from image
		SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
		if (loadedSurface == NULL)
		{
			std::cout << "Unable to load image " << filePath << "! SDL_image Error: " << IMG_GetError() << std::endl;
			return false;
		}

		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		m_Width = loadedSurface->w;
		m_Height = loadedSurface->h;
		m_RotationPoint.x = m_Width / 2;
		m_RotationPoint.y = m_Height / 2;
		m_SourceRect = {
			0,
			0,
			m_Width,
			m_Height
		};

		//Create texture from surface pixels
		m_SdlTexture = SDL_CreateTextureFromSurface(m_Window.getRenderer(), loadedSurface);
		if (m_SdlTexture == NULL)
		{
			std::cout << "Unable to create texture from " << filePath << "! SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}
		SDL_FreeSurface(loadedSurface);

		return true;
	}

	bool Texture::render(int x, int y, float scale) const
	{
		eqx::Rectangle<int> rect = { x, y, m_Width, m_Height };
		return render(rect, scale);
	}

	void Texture::hFlip()
	{
		m_Flip = SDL_FLIP_HORIZONTAL;
	}

	void Texture::unFlip()
	{
		m_Flip = SDL_FLIP_NONE;
	}

	bool Texture::isFliped() const
	{
		return m_Flip == SDL_FLIP_NONE ? false : true;
	}

	void Texture::setSourceRect(const eqx::Rectangle<int>& source)
	{
		m_SourceRect = source;
	}

	bool Texture::modColor(Uint8 r, Uint8 g, Uint8 b)
	{
		if (SDL_SetTextureColorMod(m_SdlTexture, r, g, b) == -1)
		{
			std::cout << "Texture Render Error! SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}

		return true;
	}

	void Texture::setAngle(double degrees)
	{
		m_Angle = degrees;
	}

	void Texture::rotate(double degrees)
	{
		m_Angle += degrees;
	}

	void Texture::setRotationPoint(const eqx::Point<int>& point)
	{
		m_RotationPoint = point;
	}

	const eqx::Rectangle<int>& Texture::getSourceRect() const
	{
		return m_SourceRect;
	}

	int Texture::getWidth() const
	{
		return m_Width;
	}

	int Texture::getHeight() const
	{
		return m_Height;
	}

	double Texture::getAngle() const
	{
		return m_Angle;
	}

	const eqx::Point<int>& Texture::getRotationPoint() const
	{
		return m_RotationPoint;
	}

	std::string Texture::getFilepath() const
	{
		return m_Filepath;
	}
}