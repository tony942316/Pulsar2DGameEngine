#include "pul_Entity.hpp"

namespace pul
{
	Entity::Entity() noexcept
		:
		m_RotationDirection(0),
		m_Speed(0.0),
		m_RotationSpeed(0.0),
		m_RotationTarget(0.0),
		m_Direction(eqx::Point<double>(0.0, 0.0)),
		m_Target(eqx::Point<double>(0.0, 0.0)),
		m_Texture(nullptr),
		m_RenderConfiguration({ eqx::Rectangle<double>(0.0, 0.0, 0.0, 0.0), 
			0.0, eqx::Point<double>(0.0, 0.0), SDL_FLIP_NONE, 
			{ 255, 255, 255 } })
	{
	}

	Entity::Entity(Texture& texture, const eqx::Rectangle<double>& location,
		double speed) noexcept
		:
		m_RotationDirection(0),
		m_Speed(speed),
		m_RotationSpeed(0.0),
		m_RotationTarget(0.0),
		m_Direction(eqx::Point<double>(0.0, 0.0)),
		m_Target(eqx::Point<double>(0.0, 0.0)),
		m_Texture(&texture),
		m_RenderConfiguration({ location, 0.0, 
			eqx::Point<double>(0.0, 0.0), SDL_FLIP_NONE,
			{ 255, 255, 255 } })
	{
	}

	void Entity::render() const noexcept
	{
		m_Texture->render(m_RenderConfiguration);
	}

	[[nodiscard]] bool Entity::targetReached() const noexcept
	{
		if (eqx::equals(getLocation(), m_Target, 0.01))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	[[nodiscard]] bool Entity::rotationTargetReached() const noexcept
	{
		if (eqx::equals(getAngle(), m_RotationTarget, 0.01))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Entity::move(double dt) noexcept
	{
		auto loc = getDrawBox();

		editDrawBox().x += m_Direction.x * m_Speed * dt;
		if (eqx::getSign(m_Target.x - getDrawBox().x) !=
			eqx::getSign(m_Target.x - loc.x))
		{
			editDrawBox().x = m_Target.x;
		}

		editDrawBox().y += m_Direction.y * m_Speed * dt;
		if (eqx::getSign(m_Target.y - getDrawBox().y) !=
			eqx::getSign(m_Target.y - loc.y))
		{
			editDrawBox().y = m_Target.y;
		}
	}

	void Entity::rotate(double dt) noexcept
	{
		auto loc = getAngle();
		m_RenderConfiguration.angle +=
			m_RotationDirection * m_RotationSpeed * dt;
		if (eqx::getSign(m_RotationTarget - getAngle()) != 
			eqx::getSign(m_RotationTarget - loc))
		{
			m_RenderConfiguration.angle = m_RotationTarget;
		}
	}

	void Entity::setRotationDirection(int direction) noexcept
	{
		m_RotationDirection = direction;
	}

	void Entity::setSpeed(double speed) noexcept
	{
		m_Speed = speed;
	}

	void Entity::setRotationSpeed(double speed) noexcept
	{
		m_RotationSpeed = speed;
	}

	void Entity::setRotationTarget(double target) noexcept
	{
		m_RotationTarget = target;
		setRotationDirection(eqx::getSign(target - getAngle()));
	}

	void Entity::setDirection(const eqx::Point<double>& direction) noexcept
	{
		m_Direction = eqx::normalize(direction);
	}

	void Entity::setTarget(const eqx::Point<double>& target) noexcept
	{
		m_Target = target;
		setDirection(m_Target - getLocation());
	}

	void Entity::setRotationPoint(const eqx::Point<double>& point) noexcept
	{
		m_RenderConfiguration.rotationPoint = point;
	}

	void Entity::setTexture(Texture& texture) noexcept
	{
		m_Texture = &texture;
	}

	void Entity::setLocation(const eqx::Point<double>& point) noexcept
	{
		m_RenderConfiguration.destination.x = point.x;
		m_RenderConfiguration.destination.y = point.y;
	}

	void Entity::setDrawBox(const eqx::Rectangle<double>& rect) noexcept
	{
		m_RenderConfiguration.destination = rect;
	}

	void Entity::setColor(const Texture::Color& rgb) noexcept
	{
		m_RenderConfiguration.rgb = rgb;
	}

	[[nodiscard]] eqx::Rectangle<double>& Entity::editDrawBox() noexcept
	{
		return m_RenderConfiguration.destination;
	}

	[[nodiscard]] int Entity::getRotationDirection() const noexcept
	{
		return m_RotationDirection;
	}

	[[nodiscard]] double Entity::getSpeed() const noexcept
	{
		return m_Speed;
	}

	[[nodiscard]] double Entity::getRotationSpeed() const noexcept
	{
		return m_RotationSpeed;
	}

	[[nodiscard]] double Entity::getRotationTarget() const noexcept
	{
		return m_RotationTarget;
	}

	[[nodiscard]] const eqx::Point<double>& 
		Entity::getDirection() const noexcept
	{
		return m_Direction;
	}

	[[nodiscard]] const eqx::Point<double>& Entity::getTarget() const noexcept
	{
		return m_Target;
	}

	[[nodiscard]] const eqx::Point<double>& 
		Entity::getRotationPoint() const noexcept
	{
		return m_RenderConfiguration.rotationPoint;
	}

	[[nodiscard]] eqx::Point<double> Entity::getLocation() const noexcept
	{
		return m_RenderConfiguration.destination.getLocation();
	}

	[[nodiscard]] const eqx::Rectangle<double>& 
		Entity::getDrawBox() const noexcept
	{
		return m_RenderConfiguration.destination;
	}

	[[nodiscard]] double Entity::getAngle() const noexcept
	{
		return m_RenderConfiguration.angle;
	}

	[[nodiscard]] const Texture::Color& Entity::getColor() const noexcept
	{
		return m_RenderConfiguration.rgb;
	}
}