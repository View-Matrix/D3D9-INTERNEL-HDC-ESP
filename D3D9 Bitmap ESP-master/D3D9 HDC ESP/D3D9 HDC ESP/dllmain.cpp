#include "Include.h"


//D3D9 Internel ESP

DWORD WINAPI Console(LPVOID lParam)
{
	AllocConsole();
	FILE* acStreamOut;
	FILE* acStreamIn;
	freopen_s(&acStreamOut, "CONOUT$", "wt", stdout);
	freopen_s(&acStreamIn, "CONIN$", "r", stdin);
	printf("환영합니다.");
	printf("\n\n");
	printf("XXXX를 기다리는중입니다...\n");
	while (true)
	{
		HWND hWnd = FindWindowA(NULL, ""); 

		if (hWnd != 0) {
			printf("XXXX를 찾았습니다.\n");
			dwMain();
		}
	}
	return 0;
}

extern "C"
{
	HMODULE Kernel32Dll;
	BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
	{
		HANDLE hThread = NULL;
		switch (fdwReason)
		{
		case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls(hinstDLL);
			EraseHeaders(hinstDLL);
			HideModule(hinstDLL);
			ZeroMemory(hinstDLL, 0x1000);
			FreeLibrary(Kernel32Dll);
			CloseHandle(CreateThread(NULL, 0, Console, NULL, 0, NULL));
			break;
		}
		}

		return TRUE;
	}
}