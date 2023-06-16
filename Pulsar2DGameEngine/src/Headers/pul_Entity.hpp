#pragma once

#include "pul_Dependencies.hpp"

#include "pul_Texture.hpp"

namespace pul
{
	class Entity
	{
	public:
		explicit constexpr Entity() noexcept;
		explicit constexpr Entity(const Texture& texture) noexcept;

		inline void render() const noexcept;

		inline void setTexture(const Texture& texture) noexcept;
		inline void setConfig(const Texture::Config& config) noexcept;
		inline void setLocation(const eqx::Point<double>& loc) noexcept;
		inline void setDrawBox(const eqx::Rectangle<double>& box) noexcept;
		inline void setAngle(double angle) noexcept;
		inline void setRotationPoint(const eqx::Point<double>& point) noexcept;
		inline void setFlip(SDL_RendererFlip flip) noexcept;
		inline void setColor(const Texture::Color& color) noexcept;

		inline Texture::Config& editConfig() noexcept;
		inline eqx::Rectangle<double>& editDrawBox() noexcept;

		inline const Texture& getTexture() const noexcept;
		inline const Texture::Config& getConfig() const noexcept;
		inline eqx::Point<double> getLocation() const noexcept;
		inline const eqx::Rectangle<double>& getDrawBox() const noexcept;
		inline double getAngle() const noexcept;
		inline const eqx::Point<double>& getRotationPoint() const noexcept;
		inline SDL_RendererFlip getFlip() const noexcept;
		inline const Texture::Color& getColor() const noexcept;

	protected:
		const Texture* m_Texture;
		Texture::Config m_Config;
	};
}

#include "pul_DefHeaders/pul_EntityDef.hpp"