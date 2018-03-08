#include <iostream>
#include <Windows.h>

#include "gameFunctions.h"
#include "Offsets.h"
#include "Classes.h"

void triggerBot(bool activate)
{
	PlayerEntity* localPlayer = reinterpret_cast<PlayerEntity*>(*reinterpret_cast<uintptr_t*>(0x50F4F4));
	PlayerEntity* entityCrossHair = PlayerEntity::getCrossHairPlayer();
	int gameMode = *reinterpret_cast<int*>(0x50F49C);
	if (activate)
	{
		if (entityCrossHair != nullptr)
		{
			if (isTeamGame)
			{
				if (!PlayerEntity::IsSameTeam(localPlayer, entityCrossHair))
				{
					localPlayer->m_Shoot = true;
					Sleep(10);
					localPlayer->m_Shoot = false;
				}
			}
			else
			{
				localPlayer->m_Shoot = true;
				Sleep(10);
				localPlayer->m_Shoot = false;
			}
		}
	}
}

void onInitialize()
{
	printMessage::hackLoaded();

	bool infiniteAmmoState = false;
	bool rapidFireState = false;
	bool noRecoilState = false;
	bool triggerBotState = false;

	while (true)
	{
		if (GetAsyncKeyState(VK_F1) & 1)
		{
			infiniteAmmoState = !infiniteAmmoState;
			infiniteAmmo(infiniteAmmoState);
		}
		if (GetAsyncKeyState(VK_F2) & 1)
		{
			rapidFireState = !rapidFireState;
			rapidFire(rapidFireState);
		}
		if (GetAsyncKeyState(VK_F3) & 1)
		{
			noRecoilState = !noRecoilState;
			noRecoil(noRecoilState);
		}
		if (GetAsyncKeyState(VK_F4) & 1)
		{
			triggerBotState = !triggerBotState;
		}

		triggerBot(triggerBotState);
		Sleep(10);
	}
}