#pragma once

namespace pul
{
	constexpr Entity::Entity() noexcept
		:
		m_Texture(nullptr),
		m_Config()
	{
	}

	constexpr Entity::Entity(const Texture& texture) noexcept
		:
		m_Texture(&texture),
		m_Config()
	{
	}

	inline void Entity::render() const noexcept
	{
		m_Texture->render(m_Config);
	}

	inline void Entity::setTexture(const Texture& texture) noexcept
	{
		m_Texture = &texture;
	}

	inline void Entity::setConfig(const Texture::Config& config) noexcept
	{
		m_Config = config;
	}

	inline void Entity::setLocation(const eqx::Point<double>& loc) noexcept
	{
		m_Config.destination.setLocation(loc);
	}

	inline void Entity::setDrawBox(const eqx::Rectangle<double>& box) noexcept
	{
		m_Config.destination = box;
	}

	inline void Entity::setAngle(double angle) noexcept
	{
		m_Config.angle = angle;
	}

	inline void Entity::setRotationPoint(const eqx::Point<double>& point)
		noexcept
	{
		m_Config.rotationPoint = point;
	}

	inline void Entity::setFlip(SDL_RendererFlip flip) noexcept
	{
		m_Config.flip = flip;
	}

	inline void Entity::setColor(const Texture::Color& color) noexcept
	{
		m_Config.color = color;
	}

	inline Texture::Config& Entity::editConfig() noexcept
	{
		return m_Config;
	}

	inline eqx::Rectangle<double>& Entity::editDrawBox() noexcept
	{
		return m_Config.destination;
	}

	inline const Texture& Entity::getTexture() const noexcept
	{
		return *m_Texture;
	}
	inline const Texture::Config& Entity::getConfig() const noexcept
	{
		return m_Config;
	}

	inline eqx::Point<double> Entity::getLocation() const noexcept
	{
		return m_Config.destination.getTopLeftPoint();
	}

	inline const eqx::Rectangle<double>& Entity::getDrawBox() const noexcept
	{
		return m_Config.destination;
	}

	inline double Entity::getAngle() const noexcept
	{
		return m_Config.angle;
	}

	inline const eqx::Point<double>& Entity::getRotationPoint() const noexcept
	{
		return m_Config.rotationPoint;
	}

	inline SDL_RendererFlip Entity::getFlip() const noexcept
	{
		return m_Config.flip;
	}

	inline const Texture::Color& Entity::getColor() const noexcept
	{
		return m_Config.color;
	}

	//inline Entity::Entity() noexcept
	//	:
	//	m_RotationDirection(0),
	//	m_Speed(0.0),
	//	m_RotationSpeed(0.0),
	//	m_RotationTarget(0.0),
	//	m_Direction(eqx::Point<double>(0.0, 0.0)),
	//	m_Target(eqx::Point<double>(0.0, 0.0)),
	//	m_Texture(nullptr),
	//	m_RenderConfiguration({ eqx::Rectangle<double>(0.0, 0.0, 0.0, 0.0),
	//		0.0, eqx::Point<double>(0.0, 0.0), SDL_FLIP_NONE,
	//		{ 255, 255, 255, 255 } })
	//{
	//}

	//inline Entity::Entity(Texture& texture, 
	//	const eqx::Rectangle<double>& location, double speed) noexcept
	//	:
	//	m_RotationDirection(0),
	//	m_Speed(speed),
	//	m_RotationSpeed(0.0),
	//	m_RotationTarget(0.0),
	//	m_Direction(eqx::Point<double>(0.0, 0.0)),
	//	m_Target(eqx::Point<double>(0.0, 0.0)),
	//	m_Texture(&texture),
	//	m_RenderConfiguration({ location, 0.0,
	//		eqx::Point<double>(0.0, 0.0), SDL_FLIP_NONE,
	//		{ 255, 255, 255, 255 } })
	//{
	//}

	//inline void Entity::render() const noexcept
	//{
	//	m_Texture->render(m_RenderConfiguration);
	//}

	//[[nodiscard]] inline bool Entity::targetReached() const noexcept
	//{
	//	if (eqx::equals(getLocation(), m_Target, 0.01))
	//	{
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}

	//[[nodiscard]] inline bool Entity::rotationTargetReached() const noexcept
	//{
	//	if (eqx::equals(getAngle(), m_RotationTarget, 0.01))
	//	{
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}

	//inline void Entity::move(double dt) noexcept
	//{
	//	auto loc = getDrawBox();

	//	editDrawBox().x += m_Direction.x * m_Speed * dt;
	//	if (eqx::getSign(m_Target.x - getDrawBox().x) !=
	//		eqx::getSign(m_Target.x - loc.x))
	//	{
	//		editDrawBox().x = m_Target.x;
	//	}

	//	editDrawBox().y += m_Direction.y * m_Speed * dt;
	//	if (eqx::getSign(m_Target.y - getDrawBox().y) !=
	//		eqx::getSign(m_Target.y - loc.y))
	//	{
	//		editDrawBox().y = m_Target.y;
	//	}
	//}

	//inline void Entity::rotate(double dt) noexcept
	//{
	//	auto loc = getAngle();
	//	m_RenderConfiguration.angle +=
	//		m_RotationDirection * m_RotationSpeed * dt;
	//	if (eqx::getSign(m_RotationTarget - getAngle()) !=
	//		eqx::getSign(m_RotationTarget - loc))
	//	{
	//		m_RenderConfiguration.angle = m_RotationTarget;
	//	}
	//}

	//inline void Entity::setRotationDirection(int direction) noexcept
	//{
	//	m_RotationDirection = direction;
	//}

	//inline void Entity::setSpeed(double speed) noexcept
	//{
	//	m_Speed = speed;
	//}

	//inline void Entity::setRotationSpeed(double speed) noexcept
	//{
	//	m_RotationSpeed = speed;
	//}

	//inline void Entity::setRotationTarget(double target) noexcept
	//{
	//	m_RotationTarget = target;
	//	setRotationDirection(eqx::getSign(target - getAngle()));
	//}

	//inline void 
	//	Entity::setDirection(const eqx::Point<double>& direction) noexcept
	//{
	//	m_Direction = eqx::normalize(direction);
	//}

	//inline void Entity::setTarget(const eqx::Point<double>& target) noexcept
	//{
	//	m_Target = target;
	//	setDirection(m_Target - getLocation());
	//}

	//inline void 
	//	Entity::setRotationPoint(const eqx::Point<double>& point) noexcept
	//{
	//	m_RenderConfiguration.rotationPoint = point;
	//}

	//inline void Entity::setTexture(Texture& texture) noexcept
	//{
	//	m_Texture = &texture;
	//}

	//inline void Entity::setLocation(const eqx::Point<double>& point) noexcept
	//{
	//	m_RenderConfiguration.destination.x = point.x;
	//	m_RenderConfiguration.destination.y = point.y;
	//}

	//inline void Entity::setDrawBox(const eqx::Rectangle<double>& rect) noexcept
	//{
	//	m_RenderConfiguration.destination = rect;
	//}

	//inline void Entity::setColor(const Texture::Color& rgba) noexcept
	//{
	//	m_RenderConfiguration.rgba = rgba;
	//}

	//[[nodiscard]] inline eqx::Rectangle<double>& Entity::editDrawBox() noexcept
	//{
	//	return m_RenderConfiguration.destination;
	//}

	//[[nodiscard]] inline int Entity::getRotationDirection() const noexcept
	//{
	//	return m_RotationDirection;
	//}

	//[[nodiscard]] inline double Entity::getSpeed() const noexcept
	//{
	//	return m_Speed;
	//}

	//[[nodiscard]] inline double Entity::getRotationSpeed() const noexcept
	//{
	//	return m_RotationSpeed;
	//}

	//[[nodiscard]] inline double Entity::getRotationTarget() const noexcept
	//{
	//	return m_RotationTarget;
	//}

	//[[nodiscard]] inline const eqx::Point<double>&
	//	Entity::getDirection() const noexcept
	//{
	//	return m_Direction;
	//}

	//[[nodiscard]] inline const 
	//	eqx::Point<double>& Entity::getTarget() const noexcept
	//{
	//	return m_Target;
	//}

	//[[nodiscard]] inline const eqx::Point<double>&
	//	Entity::getRotationPoint() const noexcept
	//{
	//	return m_RenderConfiguration.rotationPoint;
	//}

	//[[nodiscard]] inline eqx::Point<double> Entity::getLocation() const noexcept
	//{
	//	return m_RenderConfiguration.destination.getLocation();
	//}

	//[[nodiscard]] inline const eqx::Rectangle<double>&
	//	Entity::getDrawBox() const noexcept
	//{
	//	return m_RenderConfiguration.destination;
	//}

	//[[nodiscard]] inline double Entity::getAngle() const noexcept
	//{
	//	return m_RenderConfiguration.angle;
	//}

	//[[nodiscard]] inline const Texture::Color& 
	//	Entity::getColor() const noexcept
	//{
	//	return m_RenderConfiguration.rgba;
	//}
}
