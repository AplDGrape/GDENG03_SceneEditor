#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <format>
#include <source_location>

class Debug final
{
public:
	enum class LogLevel
	{
		None,
		Info,
		Error
	};

	struct DebugMessage
	{
		LogLevel Level;
		std::string Message;
	};

	static Debug& GetInstance();

	~Debug() = default;

	template <typename... Args>
	static void Log(std::string_view message, Args&&... args);

	template <typename... Args>
	static void LogError(bool assertTrue, std::string_view message, Args&&... args);

	std::vector<DebugMessage> GetMessageList(LogLevel level);
private:
	Debug();

	void StoreMessage(const LogLevel& level, const std::string& message);

	std::vector<DebugMessage> m_MessageList;

	int m_MessageCountLimit = 50;
};

template<typename ...Args>
inline void Debug::Log(std::string_view message, Args&&... args)
{
	std::string debugString = std::vformat(message, std::make_format_args(args...));
	std::string logString = std::format("{0}\n", debugString);

	GetInstance().StoreMessage(LogLevel::Info, logString);

	std::cout << logString;
}

template<typename ...Args>
inline void Debug::LogError(bool assertTrue, std::string_view message, Args&&... args)
{
	if (assertTrue)
	{
		return;
	}

	std::string debugString = std::vformat(message, std::make_format_args(args...));
	std::string errorString = std::format("[Error] {0}\n", debugString);

	GetInstance().StoreMessage(LogLevel::Error, errorString);

	std::cout << errorString;
}