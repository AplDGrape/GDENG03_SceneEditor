#pragma once
#include <iostream>
#include "Debug.h"
#include "DebugStreamBuf.h"

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

		Debug::Log("Redirection now active.");

		initialized = true;
	}
};