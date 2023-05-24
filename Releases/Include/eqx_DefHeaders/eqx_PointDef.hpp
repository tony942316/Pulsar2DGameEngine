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
	constexpr Point<T>::Point() noexcept
		:
		Point(eqx::zero<T>, eqx::zero<T>)
	{
	}

	template <eqx::arithmetic T>
	constexpr Point<T>::Point(T x, T y) noexcept
		:
		x(x),
		y(y)
	{
	}

	template <eqx::arithmetic T>
	[[nodiscard]] constexpr Point<T> 
		Point<T>::operator+ (const Point<T>& other) const noexcept
	{
		return Point<T>(x + other.x, y + other.y);
	}

	template <eqx::arithmetic T>
	[[nodiscard]] constexpr Point<T>
		Point<T>::operator- (const Point<T>& other) const noexcept
	{
		return Point<T>(x - other.x, y - other.y);
	}

	template <eqx::arithmetic T>
	constexpr Point<T> Point<T>::operator+= (const Point<T>& other) noexcept
	{
		return *this = *this + other;
	}

	template <eqx::arithmetic T>
	constexpr Point<T> Point<T>::operator-= (const Point<T>& other) noexcept
	{
		return *this = *this - other;
	}

	template <eqx::arithmetic T>
	[[nodiscard]] constexpr bool
		Point<T>::operator== (const Point<T>& other) const noexcept
	{
		return equals(*this, other);
	}

	template <eqx::arithmetic T>
	[[nodiscard]] constexpr bool
		Point<T>::operator!= (const Point<T>& other) const noexcept
	{
		return !(*this == other);
	}

	template <eqx::arithmetic T>
	[[nodiscard]] T Point<T>::distanceTo(const Point<T>& other) const noexcept
	{
		eqx::runtimeAssert(errno == 0, "Previous errno Failure Detected!");

		const auto dx = static_cast<double>(distance(x, other.x));
		const auto dy = static_cast<double>(distance(y, other.y));
		const auto result = std::hypot(dx, dy);

		eqx::runtimeAssert(errno != ERANGE, "errno == ERANGE!");

		return static_cast<T>(result);
	}

	template <eqx::arithmetic T>
	[[nodiscard]] std::string Point<T>::toString() const
	{
		auto res = std::string("");
		res += "(";
		res += std::to_string(x);
		res += ", ";
		res += std::to_string(y);
		res += ")";
		return res;
	}

	template <typename T>
	[[nodiscard]] std::string toString(const Point<T>& point)
	{
		return point.toString();
	}

	template <std::floating_point T>
	[[nodiscard]] constexpr bool equals(const Point<T>& point1,
		const Point<T>& point2, double error) noexcept
	{
		return equals(point1.x, point2.x, error) &&
			equals(point1.y, point2.y, error);
	}

	template <eqx::integer T>
	[[nodiscard]] constexpr bool equals(const Point<T>& point1,
		const Point<T>& point2) noexcept
	{
		return equals(point1.x, point2.x) && equals(point1.y, point2.y);
	}

	template <typename T>
	[[nodiscard]] T distance(const Point<T>& point1,
		const Point<T>& point2) noexcept
	{
		return point1.distanceTo(point2);
	}

	template <std::floating_point T>
	[[nodiscard]] Point<T> normalize(const Point<T>& point) noexcept
	{
		constexpr auto origin = Point<T>();

		auto dist = eqx::distance(origin, point);

		auto result = dist != eqx::zero<T> ?
			Point<T>(point.x / dist, point.y / dist) :
			Point<T>();
		return result;
	}

	template <typename T>
	[[nodiscard]] double angle(const Point<T>& point) noexcept
	{
		const auto normPoint = eqx::normalize(point);
		const auto sinVals = eqx::arcsin(normPoint.y);
		const auto cosVals = eqx::arccos(normPoint.x);

		auto correctValue = equals(sinVals.first, cosVals.first) ||
			equals(sinVals.second, cosVals.second) ?
			sinVals.first : sinVals.second;

		return correctValue;
	}
}
