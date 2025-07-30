#pragma once
#include <iostream>
#include "DebugStreamBuf.h"
#include "Debug.h"

class DebugRedirector {
public:
	static void Initialize()
	{
		static bool initialized = false;
		if (initialized) return;

		static DebugStreamBuf debugOutBuf(Debug::LogLevel::Info);
		static DebugStreamBuf debugErrBuf(Debug::LogLevel::Error);

		std::cout.rdbuf(&debugOutBuf);
		std::cerr.rdbuf(&debugErrBuf);

		// Important: Use fwrite to bypass redirection and avoid recursion
		std::string startup = "Redirection now active.\n";
		std::fwrite(startup.c_str(), 1, startup.size(), stdout);

		Debug::GetInstance().StoreMessage(Debug::LogLevel::Info, startup);

		initialized = true;
	}
};