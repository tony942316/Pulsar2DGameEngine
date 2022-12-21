#pragma once

#include <type_traits>
#include <limits>

#include "Log.h"

namespace eqx
{
	/**
	 * @brief Long Double Pi Accurate To 36 Decimal Points
	 */
	long double constexpr pi = 3.141592653589793238462643383279502884L;

	/**
	 * @brief Check If Two Aritmetic Types Will Overflow
	 *
	 * @param val1 Value To Be Checked
	 * @param val2 Other Value To Be Checked
	 *
	 * @returns If Overflow Would Occur
	 */
	template<typename T>
	bool willOverflowAddition(T x, T y)
	{
		T zero = static_cast<T>(0);
		if (!std::is_arithmetic<T>::value)
		{
			eqx::Log::log(eqx::Log::Level::error, "Not defined for non arithmetic types", eqx::Log::Type::runtimeError);
			return true;
		}
		else if (x == zero || y == zero)
		{
			return false;
		}
		else if (x > zero && y > zero)
		{
			if ((std::numeric_limits<T>::max() - x) < y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (x < zero && y < zero)
		{
			if ((std::numeric_limits<T>::lowest() - x) > y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (x > zero && y < zero ||
				 x < zero && y > zero)
		{
			return false;
		}
		else
		{
			eqx::Log::log(eqx::Log::Level::error, "willOverflowAdditionIntegral should not have reached this line", eqx::Log::Type::unreachableCodeError);
			return true;
		}
	}

	/**
	 * @brief Compute The Distance Between Two One Dimensional Points
	 * @brief Must Be Arithmetic Types
	 * 
	 * @param x1 First Point
	 * @param x2 Second Point
	 *
	 * @returns Distance Between Two One Dimensional Points
	 */
	template<typename T>
	T distance(T x1, T x2)
	{
		if (!std::is_arithmetic<T>::value)
		{
			eqx::Log::log(eqx::Log::Level::error, "Not defined for non arithmetic types", eqx::Log::Type::runtimeError);
			return static_cast<T>(0);
		}
		else if (willOverflowAddition(x1, -x2) ||
				 std::is_integral<T>::value && (x1 - x2) == std::numeric_limits<T>::lowest())
		{
			eqx::Log::log(eqx::Log::Level::error, "Arithmetic Overflow", eqx::Log::Type::overflowError);
			return static_cast<T>(0);
		}
		else if (std::is_integral<T>::value)
		{
			return static_cast<T>(std::abs(x1 - x2));
		}
		else if (std::is_floating_point<T>::value)
		{
			return static_cast<T>(std::fabs(x1 - x2));
		}
		else
		{
			eqx::Log::log(eqx::Log::Level::error, "Unknown Case", eqx::Log::Type::runtimeError);
			return static_cast<T>(0);
		}
	}

	template <typename T>
	T degreesToRadians(T degrees)
	{
		if (std::is_integral<T>::value)
		{
			eqx::Log::log(eqx::Log::Level::warning, "Integer degree to radian conversion", eqx::Log::Type::runtimeWarning);
		}
		
		return static_cast<T>(degrees * (static_cast<long double>(eqx::pi) / 180.0l));
	}

	template <typename T>
	T radiansToDegrees(T radians)
	{
		if (std::is_integral<T>::value)
		{
			eqx::Log::log(eqx::Log::Level::warning, "Integer degree to radian conversion", eqx::Log::Type::runtimeWarning);
		}

		return static_cast<T>(radians * (180.0l / static_cast<long double>(eqx::pi)));
	}
}