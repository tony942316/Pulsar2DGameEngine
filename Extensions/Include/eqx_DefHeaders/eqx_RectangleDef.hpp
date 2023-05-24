/*
 * Copyright (C) 2023 Anthony H. Grasso
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

namespace eqx
{
	template <eqx::arithmetic T>
	constexpr Rectangle<T>::Rectangle() noexcept
		:
		Rectangle(eqx::zero<T>, eqx::zero<T>, eqx::zero<T>, eqx::zero<T>)
	{
	}

	template <eqx::arithmetic T>
	constexpr Rectangle<T>::Rectangle(T x, T y, T w, T h) noexcept
		:
		x(x),
		y(y),
		w(w),
		h(h)
	{
	}

	template <eqx::arithmetic T>
	[[nodiscard]] constexpr bool
		Rectangle<T>::operator== (const Rectangle<T>& other) const noexcept
	{
		return equals(*this, other);
	}

	template <eqx::arithmetic T>
	[[nodiscard]] constexpr bool
		Rectangle<T>::operator!= (const Rectangle<T>& other) const noexcept
	{
		return !(*this == other);
	}

	template <eqx::arithmetic T>
	[[nodiscard]] constexpr Point<T> Rectangle<T>::getLocation() const noexcept
	{
		return getTopLeftPoint();
	}

	template <eqx::arithmetic T>
	[[nodiscard]] constexpr Point<T> 
		Rectangle<T>::getTopLeftPoint() const noexcept
	{
		return Point<T>(x, y);
	}

	template <eqx::arithmetic T>
	[[nodiscard]] constexpr Point<T> 
		Rectangle<T>::getTopRightPoint() const noexcept
	{
		return eqx::Point<T>(x + w, y);
	}

	template <eqx::arithmetic T>
	[[nodiscard]] constexpr Point<T>
		Rectangle<T>::getBottomLeftPoint() const noexcept
	{
		return eqx::Point<T>(x, y + h);
	}

	template <eqx::arithmetic T>
	[[nodiscard]] constexpr Point<T>
		Rectangle<T>::getBottomRightPoint() const noexcept
	{
		return eqx::Point<T>(x + w, y + h);
	}

	template <eqx::arithmetic T>
	[[nodiscard]] constexpr Point<T> 
		Rectangle<T>::getCenterPoint() const noexcept
	{
		auto dx = static_cast<T>(w * 0.5);
		auto dy = static_cast<T>(h * 0.5);
		return eqx::Point<T>(x + dx, y + dy);
	}

	template <eqx::arithmetic T>
	[[nodiscard]] std::string Rectangle<T>::toString() const
	{
		auto res = std::string("");
		res += "(";
		res += std::to_string(x);
		res += ", ";
		res += std::to_string(y);
		res += ", ";
		res += std::to_string(w);
		res += ", ";
		res += std::to_string(h);
		res += ")";
		return res;
	}

	template <typename T>
	[[nodiscard]] std::string toString(const Rectangle<T>& rect)
	{
		return rect.toString();
	}

	template <std::floating_point T>
	[[nodiscard]] constexpr bool equals(const Rectangle<T>& rect1,
		const Rectangle<T>& rect2, double error) noexcept
	{
		return equals(rect1.x, rect2.x, error) && 
			equals(rect1.y, rect2.y, error) &&
			equals(rect1.w, rect2.w, error) && 
			equals(rect1.h, rect2.h, error);
	}

	template <eqx::integer T>
	[[nodiscard]] constexpr bool equals(const Rectangle<T>& rect1,
		const Rectangle<T>& rect2) noexcept
	{
		return equals(rect1.x, rect2.x) &&
			equals(rect1.y, rect2.y) &&
			equals(rect1.w, rect2.w) &&
			equals(rect1.h, rect2.h);
	}

	template <typename T>
	[[nodiscard]] constexpr bool intersect(const Rectangle<T>& rect, 
		const Point<T>& point) noexcept
	{
		if (point.x < rect.getTopLeftPoint().x ||
			point.x > rect.getTopRightPoint().x ||
			point.y > rect.getBottomLeftPoint().y ||
			point.y < rect.getTopLeftPoint().y)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	template <typename T>
	[[nodiscard]] constexpr bool intersect(const Rectangle<T>& rect1,
		const Rectangle<T>& rect2) noexcept
	{
		if (rect1.getBottomRightPoint().x < rect2.getBottomLeftPoint().x ||
			rect1.getBottomLeftPoint().x > rect2.getBottomRightPoint().x ||
			rect1.getBottomLeftPoint().y < rect2.getTopLeftPoint().y ||
			rect1.getTopLeftPoint().y > rect2.getBottomLeftPoint().y)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	template <typename T>
	[[nodiscard]] constexpr bool intersectExclusive(const Rectangle<T>& rect,
		const Point<T>& point) noexcept
	{
		if (point.x <= rect.getTopLeftPoint().x ||
			point.x >= rect.getTopRightPoint().x ||
			point.y >= rect.getBottomLeftPoint().y ||
			point.y <= rect.getTopLeftPoint().y)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	template <typename T>
	[[nodiscard]] constexpr bool intersectExclusive(const Rectangle<T>& rect1,
		const Rectangle<T>& rect2) noexcept
	{
		if (rect1.getBottomRightPoint().x <= rect2.getBottomLeftPoint().x ||
			rect1.getBottomLeftPoint().x >= rect2.getBottomRightPoint().x ||
			rect1.getBottomLeftPoint().y <= rect2.getTopLeftPoint().y ||
			rect1.getTopLeftPoint().y >= rect2.getBottomLeftPoint().y)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}
