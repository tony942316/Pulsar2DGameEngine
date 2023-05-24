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

#include <type_traits>
#include <concepts>
#include <limits>
#include <cmath>

namespace eqx
{
	template <eqx::integer T>
	[[nodiscard]] constexpr bool equals(T x, T y) noexcept
	{
		return x == y;
	}

	template <std::floating_point T>
	[[nodiscard]] bool equals(T x, T y, T error) noexcept
	{
		return (std::abs(x - y) < error);
	}

	template <eqx::arithmetic T>
	[[nodiscard]] int constexpr getSign(T val) noexcept
	{
		if (val > eqx::zero<T>)
		{
			return 1;
		}
		else if (val < eqx::zero<T>)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}

	template <eqx::arithmetic T>
	[[nodiscard]] bool constexpr isPositive(T val) noexcept
	{
		if (getSign(val) == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <eqx::arithmetic T>
	[[nodiscard]] bool constexpr isNegative(T val) noexcept
	{
		if (getSign(val) == -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <eqx::arithmetic T>
	[[nodiscard]] bool constexpr willOverflowAddition(T x, T y) noexcept
	{
		if (x >= eqx::zero<T> && y >= eqx::zero<T>)
		{
			return (std::numeric_limits<T>::max() - x) < y;
		}
		else if (x <= eqx::zero<T> && y <= eqx::zero<T>)
		{
			return (std::numeric_limits<T>::lowest() - x) > y;
		}
		else
		{
			return false;
		}
	}

	template <eqx::signedArithmetic T>
	[[nodiscard]] bool constexpr willOverflowSubtraction(T x, T y) noexcept
	{
		if (y == std::numeric_limits<T>::lowest() && eqx::signedInteger<T>)
		{
			return true;
		}
		else
		{
			return willOverflowAddition(x, -y);
		}
	}

	template <eqx::unsignedInteger T>
	[[nodiscard]] bool constexpr willOverflowSubtraction(T x, T y) noexcept
	{
		return y > x;
	}

	template <eqx::arithmetic T>
	[[nodiscard]] T distance(T x1, T x2) noexcept
	{
		if (x2 > x1)
		{
			std::swap(x1, x2);
		}

		eqx::runtimeAssert(!willOverflowSubtraction(x1, x2),
			"Arithmetic Overflow!");

		return static_cast<T>(std::fabs(x1 - x2));
	}

	template <eqx::arithmetic T>
	[[nodiscard]] double constexpr degreesToRadians(T degrees) noexcept
	{
		return static_cast<double>(degrees) * (eqx::pi / 180.0);
	}

	template <eqx::arithmetic T>
	[[nodiscard]] double constexpr radiansToDegrees(T radians) noexcept
	{
		return static_cast<double>(radians) * (180.0 / eqx::pi);
	}

	template <eqx::arithmetic T>
	[[nodiscard]] std::pair<double, double> arccos(T value) noexcept
	{
		eqx::runtimeAssert(value >= -1.0 && value <= 1.0, "Domain Error!");

		std::pair<double, double> result;
		result.first = eqx::radiansToDegrees(std::acos(value));
		result.second = 360.0 - result.first;
		return result;
	}

	template <eqx::arithmetic T>
	[[nodiscard]] std::pair<double, double> arcsin(T value) noexcept
	{
		eqx::runtimeAssert(value >= -1.0 && value <= 1.0, "Domain Error!");

		std::pair<double, double> result;
		result.first = eqx::radiansToDegrees(std::asin(value));
		result.second = 180.0 - result.first;
		result.first = result.first >= 0.0 ?
			result.first : 360.0 + result.first;
		return result;
	}
}
