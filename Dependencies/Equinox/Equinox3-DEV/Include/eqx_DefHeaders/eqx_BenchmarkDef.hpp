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
	inline Benchmark::Benchmark(const std::function<void(void)>& func) 
		noexcept(noexcept(func()))
		:
		m_Function(func),
		m_Bench(std::chrono::nanoseconds())
	{
	}

	void inline Benchmark::bench() noexcept(noexcept(m_Function()))
	{
		StopWatch timer;
		timer.start();
		m_Function();
		timer.stop();
		m_Bench = timer.getDuration<std::chrono::nanoseconds>();
	}

	void inline Benchmark::avgBench(int runs) noexcept(noexcept(m_Function()))
	{
		StopWatch timer;
		timer.start();
		for (int i = 0; i < runs; i++)
		{
			bench();
		}
		timer.stop();
		m_Bench = static_cast<std::chrono::nanoseconds>(
			timer.getTime<std::chrono::nanoseconds>() / runs);
	}

	template <eqx::timeUnit T>
	[[nodiscard]] std::string Benchmark::toString() const
	{
		auto result = std::string("");
		result += "Bench: ";
		result +=
			std::to_string(std::chrono::duration_cast<T>(m_Bench).count());
		if constexpr (std::same_as<T, std::chrono::nanoseconds>)
		{
			result += " ns";
		}
		else if constexpr (std::same_as<T, std::chrono::microseconds>)
		{
			result += " us";
		}
		else if constexpr (std::same_as<T, std::chrono::milliseconds>)
		{
			result += " ms";
		}
		else if constexpr (std::same_as<T, std::chrono::seconds>)
		{
			result += " s";
		}
		return result;
	}
}
