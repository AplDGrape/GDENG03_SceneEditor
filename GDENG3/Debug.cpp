#include "Debug.h"
#pragma once

Debug& Debug::GetInstance()
{
	static Debug instance;

	return instance;
}

std::vector<Debug::DebugMessage> Debug::GetMessageList(LogLevel level)
{
	std::vector<Debug::DebugMessage> filteredMessageList = std::vector<Debug::DebugMessage>();
	
	if (level == LogLevel::None)
	{
		for (auto& debugMessage : m_MessageList)
		{
			filteredMessageList.push_back(debugMessage);
		}
	}

	for (auto& debugMessage : m_MessageList)
	{
		if (debugMessage.Level == level)
		{
			filteredMessageList.push_back(debugMessage);
		}
	}

	return filteredMessageList;
}

Debug::Debug() :m_MessageList{ std::vector<DebugMessage>() }, m_MessageCountLimit{50}
{
	m_MessageList.reserve(m_MessageCountLimit);
}

void Debug::StoreMessage(const LogLevel& level, const std::string& message)
{
	if (m_MessageList.size() >= m_MessageCountLimit)
	{
		m_MessageList.erase(m_MessageList.begin());
	}

	GetInstance().m_MessageList.emplace_back(DebugMessage(level, message));
}