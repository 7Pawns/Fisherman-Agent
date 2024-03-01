#pragma once

#ifdef _DEBUG
#define LOG_MSG(...) printf(__VA_ARGS__)
#else
#define LOG_MSG(...)          
#endif