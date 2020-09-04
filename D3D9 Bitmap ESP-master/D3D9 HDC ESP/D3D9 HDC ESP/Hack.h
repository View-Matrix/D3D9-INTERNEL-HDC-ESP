#pragma once

#include "Include.h"

bool WorldToScreen(D3DXVECTOR3* Player, D3DXVECTOR3* Pos, LPDIRECT3DDEVICE9 pDevice);
void DrawTextString(int x, int y, COLORREF color, const char* text, UINT Align, int m_nOutlineWidth, COLORREF m_nOutlineColor);
void pNickESP();
DWORD PPDec(DWORD PP);