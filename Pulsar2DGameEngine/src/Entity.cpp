#include "pul_Entity.hpp"

namespace pul
{
	Entity::Entity()
		:
		Entity(nullptr, "", { 0, 0, 0, 0 }, 0.0)
	{
	}

	Entity::Entity(SDL_Renderer* renderer, std::string_view filePath,
		eqx::Rectangle<double> drawBox, double speed)
		:
		m_Texture(renderer, filePath),
		m_DrawBox(drawBox),
		m_Direction({ 0.0, 0.0 }),
		m_Target({ 0.0, 0.0 }),
		m_Speed(speed)
	{
	}

	void Entity::render() const
	{
		m_Texture.render(m_DrawBox);
	}

	const eqx::Rectangle<double>& Entity::getLocation() const
	{
		return m_DrawBox;
	}

	const Texture& Entity::getTexture() const
	{
		return m_Texture;
	}

	double Entity::getSpeed() const
	{
		return m_Speed;
	}

	eqx::Point<double> Entity::getDirection() const
	{
		return m_Direction;
	}

	bool Entity::targetReached() const
	{
		return targetReached(m_Target);
	}

	bool Entity::targetReached(eqx::Point<double> point) const
	{
		if (eqx::equals(m_DrawBox.getLocation(), point, 4.0))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Entity::setTexture(SDL_Renderer* renderer, std::string_view filePath)
	{
		m_Texture.setRenderer(renderer);
		m_Texture.loadFile(filePath);
	}

	void Entity::setLocation(eqx::Point<double> point)
	{
		m_DrawBox.x = point.x;
		m_DrawBox.y = point.y;
	}

	void Entity::setRect(eqx::Rectangle<double> rect)
	{
		m_DrawBox = rect;
	}

	void Entity::setSpeed(double speed)
	{
		m_Speed = speed;
	}

	Texture& Entity::editTexture()
	{
		return m_Texture;
	}

	eqx::Rectangle<double>& Entity::editRect()
	{
		return m_DrawBox;
	}

	void Entity::move(double dt)
	{
		if (m_Direction != eqx::Point<double>(0.0, 0.0))
		{
			m_DrawBox.x += eqx::normalize(m_Direction).x * m_Speed * dt;
			m_DrawBox.y += eqx::normalize(m_Direction).y * m_Speed * dt;
		}
	}

	void Entity::setTarget(eqx::Point<double> point)
	{
		m_Target = point;
		setDirection(point - m_DrawBox.getLocation());
	}

	void Entity::setDirection(eqx::Point<double> point)
	{
		m_Direction = point;
	}
}