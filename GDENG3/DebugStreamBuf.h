#pragma once
#include <streambuf>
#include <ostream>
#include <string>
#include "Debug.h"

class DebugStreamBuf : public std::streambuf 
{
public:
	DebugStreamBuf(Debug::LogLevel level = Debug::LogLevel::Info)
		: m_level(level) {}

protected:
	virtual int overflow(int c) override {
		if (c != EOF) {
			m_buffer += static_cast<char>(c);
			if (c == '\n') {
				Debug::GetInstance().StoreMessage(m_level, m_buffer);
				m_buffer.clear();
			}
		}
		return c;
	}

	virtual int sync() override {
		if (!m_buffer.empty()) {
			Debug::GetInstance().StoreMessage(m_level, m_buffer);
			m_buffer.clear();
		}
		return 0;
	}

private:
	std::string m_buffer;
	Debug::LogLevel m_level;
};
