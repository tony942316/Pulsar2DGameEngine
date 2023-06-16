#pragma once

#include "pul_Dependencies.hpp"

#include "pul_Entity.hpp"

namespace pul
{
	class AccEntity : public Entity
	{
	public:
		explicit constexpr AccEntity() noexcept;
		explicit constexpr AccEntity(const Texture& texture) noexcept;

		inline void update() noexcept;

		inline void setMoveTarget(const eqx::Point<double>& target) noexcept;
		inline void setMoveDirection(const eqx::Point<double>& dir) noexcept;
		inline void setMoveSpeed(double speed) noexcept;
		inline void setMoveAcceleration(double acc) noexcept;
		inline void setMaxMoveSpeed(double speed) noexcept;

		inline const eqx::Point<double>& getMoveTarget() const noexcept;
		inline const eqx::Point<double>& getMoveDirection() const noexcept;
		inline double getMoveSpeed() const noexcept;
		inline double getMoveAcceleration() const noexcept;
		inline double getMaxMoveSpeed() const noexcept;

	private:
		eqx::Point<double> m_MoveTarget, m_MoveDirection;
		double m_MoveSpeed, m_MoveAcceleration, m_MaxMoveSpeed;

		eqx::Point<int> m_MoveTargetReached;
	};
}

#include "pul_DefHeaders/pul_AccEntityDef.hpp"
