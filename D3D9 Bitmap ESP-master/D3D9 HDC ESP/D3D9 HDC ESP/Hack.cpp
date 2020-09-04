#include "Include.h"

bool WorldToScreen(D3DXVECTOR3* Player, D3DXVECTOR3* Pos, LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 vWorld(Player->x, Player->y, Player->z);
	D3DXMATRIX world, projection, view;
	D3DVIEWPORT9 ViewPort;
	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_WORLD, &world);
	pDevice->GetTransform(D3DTS_PROJECTION, &projection);
	pDevice->GetViewport(&ViewPort);

	D3DXVec3Project(Pos, &vWorld, &ViewPort, &projection, &view, &world);

	if (Pos->z < 1.0f && Pos->x > 0.0f && Pos->y > 0.0f && Pos->x < ViewPort.Width && Pos->y < ViewPort.Height)
	{
		return true;
	}
	return false;
}

DWORD PPDec(DWORD PP)
{
	__try
	{
		PlayerXorKey = *(DWORD*)(PP + 0x2B0);
		Call = *(DWORD*)(*(DWORD*)(PlayerXorKey) + 8);

		__asm
		{
			mov ecx, [PlayerXorKey]
			call dword ptr[Call]
			mov [ReturnPP], eax
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {}

	return ReturnPP;
}

void DrawTextString(int x, int y, COLORREF color, const char* text, UINT Align, int m_nOutlineWidth, COLORREF m_nOutlineColor)
{
	HFONT hOFont = NULL, hNFont = NULL;

	hOFont = (HFONT)SelectObject(MemDC, hNFont);

	SetTextAlign(MemDC, TA_NOUPDATECP | Align);

	SetBkColor(MemDC, RGB(0, 0, 0));
	SetBkMode(MemDC, TRANSPARENT);

	SetTextColor(MemDC, m_nOutlineColor);

	for (int m_nOutlinex = -m_nOutlineWidth; m_nOutlinex <= m_nOutlineWidth; m_nOutlinex++)
		for (int m_nOutliney = -m_nOutlineWidth; m_nOutliney <= m_nOutlineWidth; m_nOutliney++)
			TextOutA(MemDC, x + m_nOutlinex, y + m_nOutliney, text, strlen(text));

	SetTextColor(MemDC, color);
	TextOutA(MemDC, x, y, text, strlen(text));

	DeleteObject(SelectObject(MemDC, hOFont));
}



void pNickESP()
{
	__try
	{
		for (int i = 0; i < 25; i++)
		{
			DWORD PP = PPEAX(*(PDWORD)(*(PDWORD)(dwGetPP)+ i * 4));

			D3DXVECTOR3 MyPos, EnemyPos, CulcuPos;
			MyPos.x = *(FLOAT*)(dwMyPos);
			MyPos.y = *(FLOAT*)(dwMyPos + 0x04) - 15.0f;
			MyPos.z = *(FLOAT*)(dwMyPos + 0x08);

			EnemyPos.x = *(FLOAT*)(PP + 0x12C);
			EnemyPos.y = *(FLOAT*)(PP + 0x130) - 15.0f;
			EnemyPos.z = *(FLOAT*)(PP + 0x134);

			if (WorldToScreen(&EnemyPos, &CulcuPos, DirectDevice))
			{
				D3DXVECTOR3 xDistance = EnemyPos - MyPos;
				D3DXVECTOR3 MyDistance = MyPos - EnemyPos;
				float xaDistance = D3DXVec3Length(&xDistance);
				float MyaDistance = D3DXVec3Length(&MyDistance);

				char* NickName = (PCHAR)(*(PDWORD)(*(PDWORD)(dwGetPP)+ i * 4) + 0x4); 

				DrawTextString((int)CulcuPos.x, (int)CulcuPos.y - (35000 / MyaDistance), RGB(243, 67, 54), NickName, TA_CENTER | TA_BOTTOM, 1, RGB(255, 0, 0));
			}
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {}
}
