#include "Include.h"

void dwMain(void)
{
	int readp = 0;
	HWND hWnd = FindWindow(0, L"");
	DWORD PID = dwPID(TEXT(""));
	GetWindowThreadProcessId(hWnd, &PID);
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	printf("PID  %d\n", &PID);
	printf("HANDLE %p\n", handle);

	HMODULE dwCshell = GetExModuleHandle(PID, ""); //GetModuleHandleA is OK.
	printf("dwCshell: %p\n", dwCshell);

	SleepEx(10, true);

	dwDirectDevice = *(PDWORD)0x00; 
	dwDirectDevice = *(PDWORD)(dwDirectDevice);
	DirectDevice = (LPDIRECT3DDEVICE9)(dwDirectDevice);

	HMODULE dwMyPos = 0x00 + 0x00;
	HMODULE dwGetPP = dwCshell + 0x00; 

	for (;;) {
		GameWnd = FindWindow(0, L"");

		MemDC = GetDC(GameWnd);
		ReleaseDC(GameWnd, MemDC);
		pNickESP();
	}

}
