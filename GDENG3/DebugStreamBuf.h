#pragma once
#include <streambuf>
#include <string>
#include "Debug.h"

class DebugStreamBuf : public std::streambuf
{
public:
	DebugStreamBuf(Debug::LogLevel level) : m_level(level) {}

protected:
	int_type overflow(int_type ch) override
	{
		if (ch != EOF) {
			m_buffer += static_cast<char>(ch);
			if (ch == '\n') {
				Debug::GetInstance().StoreMessage(m_level, m_buffer);
				m_buffer.clear();
			}
		}
		return ch;
	}

private:
	Debug::LogLevel m_level;
	std::string m_buffer;
};
