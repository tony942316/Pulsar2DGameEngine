#pragma once

#include <EquinoxSTD.hpp>

#include "pul_Texture.hpp"

namespace pul
{
	class Entity
	{
	public:
		explicit inline Entity() noexcept;
		explicit inline Entity(Texture& texture, 
			const eqx::Rectangle<double>& location, double speed) noexcept;

		inline void render() const noexcept;

		[[nodiscard]] inline bool targetReached() const noexcept;
		[[nodiscard]] inline bool rotationTargetReached() const noexcept;
		inline void move(double dt) noexcept;
		inline void rotate(double dt) noexcept;

		inline void setRotationDirection(int direction) noexcept;
		inline void setSpeed(double speed) noexcept;
		inline void setRotationSpeed(double speed) noexcept;
		inline void setRotationTarget(double target) noexcept;
		inline void setDirection(const eqx::Point<double>& direction) noexcept;
		inline void setTarget(const eqx::Point<double>& target) noexcept;
		inline void setRotationPoint(const eqx::Point<double>& point) noexcept;
		inline void setTexture(Texture& texture) noexcept;
		inline void setLocation(const eqx::Point<double>& point) noexcept;
		inline void setDrawBox(const eqx::Rectangle<double>& rect) noexcept;
		inline void setColor(const Texture::Color& rgb) noexcept;

		[[nodiscard]] inline eqx::Rectangle<double>& editDrawBox() noexcept;

		[[nodiscard]] inline int getRotationDirection() const noexcept;
		[[nodiscard]] inline double getSpeed() const noexcept;
		[[nodiscard]] inline double getRotationSpeed() const noexcept;
		[[nodiscard]] inline double getRotationTarget() const noexcept;
		[[nodiscard]] inline const eqx::Point<double>& 
			getDirection() const noexcept;
		[[nodiscard]] inline const eqx::Point<double>& 
			getTarget() const noexcept;
		[[nodiscard]] inline const eqx::Point<double>& 
			getRotationPoint() const noexcept;
		[[nodiscard]] inline eqx::Point<double> getLocation() const noexcept;
		[[nodiscard]] inline const eqx::Rectangle<double>& 
			getDrawBox() const noexcept;
		[[nodiscard]] inline double getAngle() const noexcept;
		[[nodiscard]] inline const Texture::Color& getColor() const noexcept;

		static constexpr inline auto c_MaxSpeed = 1'000'000.0;

	private:
		int m_RotationDirection;
		double m_Speed, m_RotationSpeed, m_RotationTarget;

		eqx::Point<double> m_Direction, m_Target;

		Texture* m_Texture;
		Texture::Config m_RenderConfiguration;
	};
}

#include "pul_DefHeaders/pul_EntityDef.hpp"