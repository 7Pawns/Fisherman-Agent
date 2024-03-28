#pragma once
#include <iostream>

#ifdef _DEBUG
#define LOG_MSG(...) printf(__VA_ARGS__)
#define SETUP_DEBUG_CONSOLE SetupDebugConsole
#else
#define LOG_MSG(...)
#define SETUP_DEBUG_CONSOLE
#endif