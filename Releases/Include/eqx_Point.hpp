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

#include <string>
#include <cmath>
#include <cerrno>
#include <functional>

#include "eqx_Misc.hpp"
#include "eqx_Mathematics.hpp"

namespace eqx
{
	/**
	 * @brief Point On The Cartesian Plane i.e. (X, Y), Note T
	 *		Must Be An Arithmetic Type
	 */
	template <eqx::arithmetic T>
	class Point
	{
	public:
		/**
		 * @brief Initialized With Zeros i.e. ((T)0, (T)0)
		 */
		explicit constexpr Point() noexcept;

		/**
		 * @brief Initialize With Values i.e. (x, y)
		 * 
		 * @param x The x Value
		 * @param y The y Value
		 */
		explicit constexpr Point(T x, T y) noexcept;

		/**
		 * Trivial Move And Copy Operation
		 */
		Point(const Point&) = default;
		Point(Point&&) = default;
		Point& operator= (const Point&) = default;
		Point& operator= (Point&&) = default;
		~Point() = default;

		/**
		 * @brief x + other.x, y + other.y
		 * 
		 * @param other The Same Type Point We Add From
		 * 
		 * @returns Resulting Point
		 */
		[[nodiscard]] constexpr Point<T>
			operator+ (const Point<T>& other) const noexcept;

		/**
		 * @brief x - other.x, y - other.y
		 * 
		 * @param other The Same Type Point We Subtract From
		 * 
		 * @returns Resulting Point
		 */
		[[nodiscard]] constexpr Point<T>
			operator- (const Point<T>& other) const noexcept;

		/**
		 * @brief x += other.x, y += other.y
		 * 
		 * @param other The Same Type Point We Add From
		 * 
		 * @returns *this
		 */
		constexpr Point<T> operator+= (const Point<T>& other) noexcept;

		/**
		 * @brief x -= other.x, y -= other.y
		 *
		 * @param other The Same Type Point We Subtract From
		 * 
		 * @returns *this
		 */
		constexpr Point<T> operator-= (const Point<T>& other) noexcept;

		/**
		 * @brief eqx::equals(x, other.x), eqx::equals(y, other.y)
		 * 
		 * @param other The Same Type Point We Compare Against
		 * 
		 * @returns true If Points Are Equivalent
		 */
		[[nodiscard]] constexpr bool
			operator== (const Point<T>& other) const noexcept;

		/**
		 * @brief !(*this == other)
		 *
		 * @param other The Same Type Point We Compare Against
		 *
		 * @returns true If Points Are Not Equivalent
		 */
		[[nodiscard]] constexpr bool
			operator!= (const Point<T>& other) const noexcept;

		/**
		 * @brief Computes The Distance From This Point To other
		 *
		 * @param other Point To Where The Distance Is Calculated
		 *
		 * @returns Distance Between This Point And other
		 */
		[[nodiscard]] T distanceTo(const Point<T>& other) const noexcept;

		/**
		 * @brief Creates Printable String Of Form "(x, y)"
		 * 
		 * @returns "(x, y)"
		 */
		[[nodiscard]] std::string toString() const;

		T x, y;
	};

	/**
	 * @brief Convert An eqx::Point To A std::string Of Form
	 *		"(point.x, point.y)"
	 *
	 * @param point Point To Be Converted
	 *
	 * @returns Point Converted To A std::string
	 */
	template <typename T>
	[[nodiscard]] std::string toString(const Point<T>& point);

	/**
	 * @brief point1 == point2
	 *
	 * @param point1 First Point
	 * @param point2 Second Point
	 *
	 * @returns true If Points Are Equivalent
	 */
	template <std::floating_point T>
	[[nodiscard]] constexpr bool equals(const Point<T>& point1,
		const Point<T>& point2, double error = 0.001) noexcept;

	/**
	 * @brief point1 == point2
	 *
	 * @param point1 First Point
	 * @param point2 Second Point
	 *
	 * @returns true If Points Are Equivalent
	 */
	template <eqx::integer T>
	[[nodiscard]] constexpr bool equals(const Point<T>& point1,
		const Point<T>& point2) noexcept;

	/**
	 * @brief Computes The Distance Between Two Points
	 * 
	 * @param point1 First Point
	 * @param point2 Second Point
	 * 
	 * @returns Distance Between The Points
	 */
	template <typename T>
	[[nodiscard]] T distance(const Point<T>& point1,
		const Point<T>& point2) noexcept;

	/**
	 * @brief Normalize A Point As If It Were A Vector From The Origin (0, 0),
	 *		Note T Must Be A std::floating_point
	 * 
	 * @param point Point To Be Normalized
	 * 
	 * @returns Normalized Point
	 */
	template <std::floating_point T>
	[[nodiscard]] Point<T> normalize(const Point<T>& point) noexcept;

	/**
	 * @brief Compute The Angle Of A Point In Degrees, Counter Clockwise
	 *		From The Origin (0, 0)
	 * 
	 * @param point Point The Angle Is Computed From
	 * 
	 * @returns Angle In Degrees
	 */
	template <typename T>
	[[nodiscard]] double angle(const Point<T>& point) noexcept;
}

/**
 * @brief std::hash Overload For Hashed Containers
 */
template <typename T>
struct std::hash<eqx::Point<T>>
{
	[[nodiscard]] std::size_t
		operator() (const eqx::Point<T>& point) const noexcept
	{
		return std::hash<T>()(point.x) ^ std::hash<T>()(point.y);
	}
};

#include "eqx_DefHeaders/eqx_PointDef.hpp"
