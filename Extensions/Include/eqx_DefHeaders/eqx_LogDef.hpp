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
	inline void Log::log(Level level, std::string_view msg,
		Type type, const std::source_location& loc)
	{
		auto logString = getFormattedString(loc, level, msg);
		if (level >= s_LogLevel)
		{
			if (s_OutputStream != nullptr)
			{
				*s_OutputStream << logString << std::endl;
			}
			s_LogFile << logString << std::endl;
			s_LastErrorType = type;
			s_LastMessage = msg;
		}
	}

	inline void Log::setLevel(Level level) noexcept
	{
		s_LogLevel = level;
	}

	inline void Log::setOutputStream(std::ostream& stream) noexcept
	{
		s_OutputStream = &stream;
	}

	inline void Log::setOutputFile(std::string_view file)
	{
		if (s_LogFile.is_open())
		{
			s_LogFile.close();
		}
		s_LogFile.open(file.data(), std::ios::out | std::ios::trunc);
	}

	inline void Log::clear() noexcept
	{
		s_LastErrorType = Log::Type::None;
		s_LastMessage = "";
	}

	[[nodiscard]] inline Log::Level Log::getCurrentLogLevel() noexcept
	{
		return s_LogLevel;
	}

	[[nodiscard]] inline Log::Type Log::getLastLogType() noexcept
	{
		return s_LastErrorType;
	}

	[[nodiscard]] inline std::string_view Log::getLastLogMessage() noexcept
	{
		return s_LastMessage;
	}

	[[nodiscard]] inline std::string 
		Log::getFormattedString(const std::source_location& loc, Level level,
			std::string_view msg)
	{
		auto result = std::string("");
		result.reserve(100);

		const auto fileName = std::string_view(loc.file_name());
		auto functionName = std::string(loc.function_name());
		auto lineNumber = std::to_string(loc.line());

		result += "..";
		result += fileName.substr(fileName.rfind('\\'));
		result += "(";
		result += functionName;
		result += ",";
		result += lineNumber;
		result += ") ";
		switch (level)
		{
		case Level::Info:
			result += "[INFO]: ";
			break;

		case Level::Warning:
			result += "[WARNING]: ";
			break;

		case Level::Error:
			result += "[ERROR]: ";
			break;

		default:
			result += "[UNKNOWN]: ";
			break;
		}
		result += msg;

		return result;
	}

	[[nodiscard]] constexpr std::array<Log::Level, 3ULL>
		Log::getLoggableLevels() noexcept
	{
		return std::array<Level, 3ULL>({
			Level::Info, Level::Warning, Level::Error });
	}
}
