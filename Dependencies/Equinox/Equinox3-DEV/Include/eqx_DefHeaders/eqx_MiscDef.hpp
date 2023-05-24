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

#ifndef NDEBUG

inline void eqx_debugOnly_runtimeAssert(bool expr,
	std::string_view msg) noexcept
{
	if (!expr)
	{
		std::fprintf(stderr, msg.data());
		std::abort();
	}
}

#endif

namespace eqx
{
	[[nodiscard]] inline std::string toString(const char* cstring)
	{
		return std::string(cstring);
	}

	template <eqx::stringable T>
	[[nodiscard]] std::string toString(const T& val)
	{
		return std::to_string(val);
	}

	template <eqx::stringType T>
	[[nodiscard]] std::string toString(const T& val)
	{
		return std::string(val);
	}

	template <typename T, typename U>
	[[nodiscard]] std::string toString(const std::pair<T, U>& val)
	{
		return std::string("(" + eqx::toString(val.first) +
			", " + eqx::toString(val.second) + ")");
	}

	template <eqx::constCollection T>
	[[nodiscard]] std::string toString(const T& val)
	{
		auto result = std::string("");
		result += "{ ";
		std::ranges::for_each(val,
			[&result](const auto& x)
			{
				result += eqx::toString(x);
				result += ", ";
			});
		result.pop_back();
		result.pop_back();
		result += " }";
		return result;
	}

	namespace pairPrint
	{
		template <typename T, typename U>
		std::ostream& operator<< (std::ostream& os, std::pair<T, U> p)
		{
			return os << eqx::toString(p);
		}
	}

	template <typename T, typename U>
	[[nodiscard]] constexpr T narrowCast(U x) noexcept
	{
#pragma warning(suppress: 26472)
		return static_cast<T>(x);
	}

	namespace literals
	{
		consteval std::size_t operator""_size (unsigned long long x) noexcept
		{
			return narrowCast<std::size_t>(x);
		}

		consteval short operator""_short (unsigned long long x) noexcept
		{
			return narrowCast<short>(x);
		}

		consteval unsigned short 
			operator""_ushort (unsigned long long x) noexcept
		{
			return narrowCast<unsigned short>(x);
		}
	}

	inline void runtimeAssert(bool expr, std::string_view msg) noexcept
	{
		if (!expr)
		{
			std::fprintf(stderr, msg.data());
			std::abort();
		}
	}

	template <eqx::constCollection C1, eqx::constCollection C2>
	[[nodiscard]] auto zip(const C1& x, const C2& y)
	{
		eqx::runtimeAssert(std::ranges::size(x) == std::ranges::size(y),
			"eqx::zip std::ranges::size(x) != std::ranges::size(y)!");

		using C1HeldValue =
			std::remove_cvref_t<decltype(*std::ranges::cbegin(x))>;
		using C2HeldValue =
			std::remove_cvref_t<decltype(*std::ranges::cbegin(y))>;

		auto zippedRange =
			std::vector<std::pair<C1HeldValue, C2HeldValue>>();
		zippedRange.reserve(std::ranges::size(x));

		auto xIter = std::ranges::cbegin(x);
		auto yIter = std::ranges::cbegin(y);
		for (; xIter != std::ranges::cend(x); xIter++, yIter++)
		{
			zippedRange.emplace_back(*xIter, *yIter);
		}

		return zippedRange;
	}
}
