#pragma once

#ifndef INCLU
#define INCLU

#include <Windows.h>
#include <stdio.h>
#include <assert.h> 
#include <d3d9.h>
#include <d3dx9.h>
#include <process.h>
#include <TlHelp32.h>
#include <psapi.h>
#include "Main.h"
#include "Mem.h"
#include "Bypass.h"
#include "Hack.h"

#pragma comment(lib, "d3dx9.lib")



HWND GameWnd = NULL;
HDC MemDC = NULL;
DWORD PlayerXorKey, Call, ReturnPP, dwGetPP, dwMyPos, dwCshell, dwDirectDevice;
LPDIRECT3DDEVICE9 DirectDevice;

#endif