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
	[[nodiscard]] inline unsigned int Random::flipCoin()
	{
		return randomNumber(0, 1);
	}

	template <std::integral T>
	[[nodiscard]] T Random::randomNumber(T lowerBound, T upperBound)
	{
		static auto dist =
			std::uniform_int_distribution<T>(lowerBound, upperBound);
		static auto engine = std::mt19937_64(generateSeed());

		eqx::runtimeAssert(lowerBound < upperBound,
			"Lower Bound Is Larger Than UpperBound!");

		if (lowerBound != dist.min() || upperBound != dist.max())
		{
			dist =
				std::uniform_int_distribution<T>(lowerBound, upperBound);
		}

		return dist(engine);
	}

	template <std::floating_point T>
	[[nodiscard]] T Random::randomNumber(T lowerBound, T upperBound)
	{
		static auto dist = std::uniform_real_distribution<T>();
		static auto engine = std::mt19937_64(generateSeed());

		eqx::runtimeAssert(upperBound >= lowerBound,
			"Lower Bound Is Larger Than UpperBound!");

		if (lowerBound >= eqx::zero<T> && upperBound >= eqx::zero<T>)
		{
			auto prevErr = errno;
			T decoyValue = std::nexttoward(lowerBound,
				std::numeric_limits<T>::lowest());
			errno = prevErr;
			dist = std::uniform_real_distribution<T>(
				decoyValue, upperBound);
			const double producedValue = dist(engine);
			if (producedValue == decoyValue)
			{
				return upperBound;
			}
			else
			{
				return producedValue;
			}
		}
		else if (lowerBound <= eqx::zero<T> && upperBound <= eqx::zero<T>)
		{
			return -randomNumber(-upperBound, -lowerBound);
		}
		else if (lowerBound < eqx::zero<T> && upperBound > eqx::zero<T>)
		{
			T offset = (-upperBound - lowerBound) / static_cast<T>(2.0);
			if (flipCoin())
			{
				return randomNumber(lowerBound + offset, eqx::zero<T>) -
					offset;
			}
			else
			{
				return randomNumber(eqx::zero<T>, upperBound + offset) -
					offset;
			}
		}
		else
		{
			eqx::runtimeAssert(false, "Code Should Never Reach This!");
			return eqx::zero<T>;
		}
	}

	[[nodiscard]] inline unsigned int Random::rollDice(unsigned int sides)
	{
		eqx::runtimeAssert(sides > 2U,
			"Dice Should Have At Least 3 Sides!");

		return randomNumber(1U, sides);
	}

	[[nodiscard]] inline unsigned int Random::generateSeed()
	{
		static std::random_device rd;
		return narrowCast<unsigned int>(rd());
	}
}
