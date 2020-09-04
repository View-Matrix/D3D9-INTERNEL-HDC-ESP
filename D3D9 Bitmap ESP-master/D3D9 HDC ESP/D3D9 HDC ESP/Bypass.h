#ifndef BYPASS
#define BYPASS

#include "Include.h"

typedef struct _LDR_MODULE
{
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID BaseAddress;
	PVOID EntryPoint;
	ULONG SizeOfImage;
}LDR_MODULE, * PLDR_MODULE;

typedef struct _PEB_LDR_DATA
{
	ULONG Length;
	BOOLEAN Initialized;
	PVOID SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
}PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct _PEB
{
	BYTE Reserved1[2];
	BYTE BeingDebugged;
	BYTE Reserved2[1];
	PVOID Reserved3[2];
	PPEB_LDR_DATA Ldr;
}PEB, * PPEB;

void HideModule(HINSTANCE hModule)
{
	DWORD dwPEB_LDR_DATA = 0;
	__asm
	{
		MOV EAX, FS: [0x30]
		MOV EAX, [EAX + 0xC]
		MOV EAX, [EAX + 0xC]
		MOV DWORD PTR[EAX + 0x20], 0xFFFFFFFF
	}
	__asm
	{
		PUSHAD
		PUSHFD
		MOV EAX, FS: [30h]
		MOV EAX, [EAX + 0Ch]
		MOV dwPEB_LDR_DATA, EAX
		InLoadOrderModuleList :
		MOV ESI, [EAX + 0Ch]
			MOV EDX, [EAX + 10h]
			LoopInLoadOrderModuleList :
			LODSD
			MOV ESI, EAX
			MOV ECX, [EAX + 18h]
			CMP ECX, hModule
			JNE SkipA
			MOV EBX, [EAX]
			MOV ECX, [EAX + 4]
			MOV[ECX], EBX
			MOV[EBX + 4], ECX
			JMP InMemoryOrderModuleList
			SkipA :
		CMP EDX, ESI
			JNE LoopInLoadOrderModuleList
			InMemoryOrderModuleList :
		MOV EAX, dwPEB_LDR_DATA
			MOV ESI, [EAX + 14h]
			MOV EDX, [EAX + 18h]
			LoopInMemoryOrderModuleList :
			LODSD
			MOV ESI, EAX
			MOV ECX, [EAX + 10h]
			CMP ECX, hModule
			JNE SkipB
			MOV EBX, [EAX]
			MOV ECX, [EAX + 4]
			MOV[ECX], EBX
			MOV[EBX + 4], ECX
			JMP InInitializationOrderModuleList
			SkipB :
		CMP EDX, ESI
			JNE LoopInMemoryOrderModuleList
			InInitializationOrderModuleList :
		MOV EAX, dwPEB_LDR_DATA
			MOV ESI, [EAX + 1Ch]
			MOV EDX, [EAX + 20h]
			LoopInInitializationOrderModuleList :
			LODSD
			MOV ESI, EAX
			MOV ECX, [EAX + 08h]
			CMP ECX, hModule
			JNE SkipC
			MOV EBX, [EAX]
			MOV ECX, [EAX + 4]
			MOV[ECX], EBX
			MOV[EBX + 4], ECX
			JMP Finished
			SkipC :
		CMP EDX, ESI
			JNE LoopInInitializationOrderModuleList
			Finished :
		POPFD;
		POPAD;
	}
}

void EraseHeaders(HINSTANCE hModule)
{
	PIMAGE_DOS_HEADER pDoH;
	PIMAGE_NT_HEADERS pNtH;
	DWORD i, ersize, protect;

	if (!hModule) return;

	pDoH = (PIMAGE_DOS_HEADER)(hModule);
	pNtH = (PIMAGE_NT_HEADERS)((LONG)hModule + ((PIMAGE_DOS_HEADER)hModule)->e_lfanew);

	ersize = sizeof(IMAGE_DOS_HEADER);
	if (VirtualProtect(pDoH, ersize, PAGE_READWRITE, &protect))
	{
		for (i = 0; i < ersize; i++)
			*(BYTE*)((BYTE*)pDoH + i) = 0;
	}

	ersize = sizeof(IMAGE_NT_HEADERS);
	if (pNtH && VirtualProtect(pNtH, ersize, PAGE_READWRITE, &protect))
	{
		for (i = 0; i < ersize; i++)
			*(BYTE*)((BYTE*)pNtH + i) = 0;
	}
	return;
}
#endif // ! BYPASS