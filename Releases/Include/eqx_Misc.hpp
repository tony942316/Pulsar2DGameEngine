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

#include "eqx_Dependencies.hpp"

#include "eqx_UtilityMacros.hpp"

#ifdef NDEBUG
#define eqx_debugOnly_runtimeAssert(expr, message) 0;
#else

/**
 * @brief Checks If A Boolean Expression Is True, If Not Then Print
 *		A Message To std::cerr And Call std::abort()
 * @brief Note: Removed If NDEBUG Is Defined
 *
 * @param expr Expression To Be Checked
 * @param msg Message To Print To std::cerr
 */
constexpr void eqx_debugOnly_runtimeAssert(bool expr,
	std::string_view msg = "") noexcept;

#endif

namespace eqx
{
	/**
	 * @brief Type Accurate nullptr
	 */
	template <typename T>
	inline constexpr auto nullp = static_cast<T*>(nullptr);

	/**
	 * @brief Constrain T To Be A signed Integer Type, Note Unlike
	 *		std::is_integeral The bool And char Types Are Not Included
	 */
	template <typename T>
	concept SignedInteger =
		std::is_same_v<std::remove_cvref_t<T>, signed short> ||
		std::is_same_v<std::remove_cvref_t<T>, signed int> ||
		std::is_same_v<std::remove_cvref_t<T>, signed long> ||
		std::is_same_v<std::remove_cvref_t<T>, signed long long>;

	/**
	 * @brief Constrain T To Be An unsigned Integer Type, Note Unlike
	 *		std::is_integeral The bool And char Types Are Not Included
	 */
	template <typename T>
	concept UnsignedInteger =
		std::is_same_v<std::remove_cvref_t<T>, unsigned short> ||
		std::is_same_v<std::remove_cvref_t<T>, unsigned int> ||
		std::is_same_v<std::remove_cvref_t<T>, unsigned long> ||
		std::is_same_v<std::remove_cvref_t<T>, unsigned long long>;

	/**
	 * @brief Constrain T To Be An Integer Type, Note Unlike std::is_integeral
	 *		The bool And char Types Are Not Included
	 */
	template <typename T>
	concept Integer = SignedInteger<T> || UnsignedInteger<T>;

	/**
	 * brief Constrain T To Be A signed Arithmetic Type, Note Unlike
	 *		std::is_arithmetic The bool And char Types Are Not Included
	 */
	template <typename T>
	concept SignedArithmetic = SignedInteger<T> || std::floating_point<T>;

	/**
	 * brief Constrain T To Be An unsigned Arithmetic Type, Note Unlike
	 *		std::is_arithmetic The bool And char Types Are Not Included
	 */
	template <typename T>
	concept UnsignedArithmetic = UnsignedInteger<T> || std::floating_point<T>;

	/**
	 * @brief Constrain T To Be An Arithmetic Type, Note Unlike
	 *		std::is_arithmetic The bool And char Types Are Not Included
	 */
	template <typename T>
	concept Arithmetic = SignedArithmetic<T> || UnsignedArithmetic<T>;

	/**
	 * @brief Constrain T To Be Convertable To A String
	 */
	template <typename T>
	concept Stringable = requires(const T& val)
	{
		std::to_string(val);
	};

	/**
	 * @brief Constrain T To Be A String Type
	 */
	template <typename T>
	concept StringType =
		std::is_same<std::remove_cvref_t<T>, std::string>::value ||
		std::is_same<std::remove_cvref_t<T>, std::wstring>::value ||
		std::is_same<std::remove_cvref_t<T>, std::u8string>::value ||
		std::is_same<std::remove_cvref_t<T>, std::u16string>::value ||
		std::is_same<std::remove_cvref_t<T>, std::u32string>::value ||
		std::is_same<std::remove_cvref_t<T>, std::string_view>::value ||
		std::is_same<std::remove_cvref_t<T>, std::wstring_view>::value ||
		std::is_same<std::remove_cvref_t<T>, std::u8string_view>::value ||
		std::is_same<std::remove_cvref_t<T>, std::u16string_view>::value ||
		std::is_same<std::remove_cvref_t<T>, std::u32string_view>::value;

	/**
	 * @brief Constrain T To Be A Const Collection
	 */
	template <typename T>
	concept ConstCollection = !StringType<T> &&
		requires(const T& val)
		{
			std::ranges::cbegin(val);
			std::ranges::cend(val);
			std::ranges::size(val);
		};

	/**
	 * @brief Convert A const char* To A std::string
	 * 
	 * @param cstring Value To Be Converted
	 * 
	 * @returns Value Converted To std::string
	 */
	[[nodiscard]] inline std::string toString(const char* cstring);

	/**
	 * @brief Convert A Value To A std::string
	 * 
	 * @param val Value To Be Converted, Must Be eqx::Stringable Compliant
	 * 
	 * @returns Value Converted To std::string
	 */
	template <typename T>
		requires Stringable<T>
	[[nodiscard]] std::string toString(const T& val);

	/**
	 * @brief Convert A Value To A std::string
	 *
	 * @param val Value To Be Converted, Must Be eqx::stringType Compliant
	 *
	 * @returns Value Converted To std::string
	 */
	template <typename T>
		requires StringType<T>
	[[nodiscard]] std::string toString(const T& val);

	/**
	 * @brief Convert A std::pair To A std::string Of Form
	 *		"(p.first, p.second)"
	 *
	 * @param val Pair To Be Converted
	 *
	 * @returns Pair Converted To std::string
	 */
	template <typename T, typename U>
	[[nodiscard]] std::string toString(const std::pair<T, U>& val);

	/**
	 * @brief Convert A Collection To A std::string Of Form
	 *		"{ val[0], val[1], val[2], ... }"
	 * 
	 * @param val Collection To Be Converted, Must Be eqx::constCollection
	 *		Compliant
	 * 
	 * @returns Collection Converted To std::string
	 */
	template <typename T>
		requires ConstCollection<T>
	[[nodiscard]] std::string toString(const T& val);

	namespace pairPrint
	{
		/**
		 * @brief Allow std::pair To Be Streamed In The Form
		 *		"(p.first, p.second)"
		 */
		template <typename T, typename U>
		std::ostream& operator<< (std::ostream& os, std::pair<T, U> p);
	}

	/**
	 * @brief Implementation Of gsl::narrow_cast<>
	 */
	template <typename T, typename U>
	[[nodiscard]] constexpr T narrowCast(U x) noexcept;

	namespace literals
	{
		using namespace std::literals;

		/**
		 * @brief std::size_t Literal
		 */
		consteval std::size_t operator""_size (unsigned long long x) noexcept;

		/**
		 * @brief short Literal
		 */
		consteval short operator""_short (unsigned long long x) noexcept;

		/**
		 * @brief unsigned short Literal
		 */
		consteval unsigned short 
			operator""_ushort (unsigned long long x) noexcept;

		/**
		 * @brief KiloBytes Literal Conversion
		 */
		constexpr long long operator""_KB(unsigned long long x) noexcept;
	}

	/**
	 * @brief Print A String To A Stream
	 * 
	 * @param msg Message To Be Printed
	 * @param out Stream To Print To
	 */
	inline void print(std::string_view msg, std::ostream& out = std::cout) 
		noexcept;

	/**
	 * @brief Print A String To A Stream With A '\n'
	 * 
	 * @param msg Message To Be Printed
	 * @param out Stream To Print To
	 */
	inline void println(std::string_view msg, std::ostream& out = std::cout) 
		noexcept;

	/**
	 * @brief Checks If A Boolean Expression Is True, If Not Then Print
	 *		A Message To std::cerr And Call std::abort()
	 * 
	 * @param expr Expression To Be Checked
	 * @param msg Message To Print To std::cerr
	 */
	constexpr void runtimeAssert(bool expr, std::string_view msg = "") 
		noexcept;

	/**
	 * @brief "Zip" Two Collections Together In The Form Of
	 *		A std::vector<std::pair<C1 Held Value, C2 Held Value>>
	 * 
	 * @param x, y Must Be eqx::constCollection Compliant And 
	 *		Must Be The Same Size
	 * 
	 * @returns std::vector<std::pair<C1 Held Value, C2 Held Value>>
	 */
	template <typename C1, typename C2>
		requires ConstCollection<C1> && ConstCollection<C2>
	[[nodiscard]] inline auto zip(const C1& x, const C2& y);
}

#include "eqx_DefHeaders/eqx_MiscDef.hpp"