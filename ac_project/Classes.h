#pragma once
#include <vector>

typedef int(__cdecl* getCrossID)(); 
getCrossID getID = (getCrossID)0x4607C0;

struct vector3
{
	float x, y, z;

	inline vector3& operator = (const vector3& source)
	{
		this->x = source.x;
		this->y = source.y;
		this->z = source.z;
	}
};

class PlayerEntity;
class PlayerEntity
{
public:
	void* vTable; //0x0000

	struct HeadCoordinatesVec
	{
		float x; //0x0004
		float y;
		float z;
	}headCoords;

	BYTE padding1[0x24]; //0x0010

	struct CoordinatesVec
	{
		float x; //0x0034
		float y;
		float z;
	}coordinates;

	float m_Yaw; //0x0040
	float m_Pitch; //0x0044
	BYTE padding2[0x20]; //0x0048
	int m_JumpFlags; //0x0068
	BYTE padding3[0x8C]; //0x006C
	int m_Health; //0x00F8
	int m_Armor; //0x00FC
	BYTE padding4[0x3C]; //0x0100
	int m_PistolClips; //0x013C
	BYTE padding5[0x10]; //0x0140
	int m_ARClips; //0x0150
	BYTE padding6[0x4]; //0x0154
	int m_Grenades; //0x0158
	char _0x0235[0xF7];
	int Team;
	BYTE padding7[0x44]; //0x015C
	int m_ARClipsShot; //0x01A0
	BYTE padding8[0x80]; //0x01A4
	bool m_Shoot; //0x0224
	char m_Name[16]; //0x10A7888
	BYTE padding9[0x312]; //0x0235
	char _0x0378[0x90];
	vector3 m_visible;


	static PlayerEntity* getCrossHairPlayer()
	{
		return (PlayerEntity*)getID();
	}

	static int GetPlayerCount()
	{
		return *(int*)((DWORD)GetModuleHandleA("ac_client.exe") + 0x10F500);
	}

	static std::vector<PlayerEntity*> GetPlayerArray()
	{
		std::vector<PlayerEntity*> playerArray;
		DWORD EntityListAddress = *(DWORD*)((DWORD)GetModuleHandleA("ac_client.exe") + 0x10F4F8);
		DWORD LocalPlayer = *(DWORD*)((DWORD)GetModuleHandleA("ac_client.exe") + 0x10F4F4);
		if (!EntityListAddress || !LocalPlayer)
		{
			return playerArray;
		}
		for (int i = 0; (int)playerArray.size() < GetPlayerCount() - 1; i++)
		{
			DWORD PlayerAddress = *(DWORD*)(EntityListAddress + (0x4 * i));
			if (PlayerAddress == 0)
			{
				continue;
			}
			playerArray.push_back((PlayerEntity*)PlayerAddress);
		}
		return playerArray;
	}


	static float Get3dDistance(PlayerEntity* to, PlayerEntity* from)
	{
		return sqrt((to->coordinates.x - from->coordinates.x)*(to->coordinates.x - from->coordinates.x) + (to->coordinates.y - from->coordinates.y)*(to->coordinates.y - from->coordinates.y) + (to->coordinates.z - from->coordinates.z)*(to->coordinates.z - from->coordinates.z));
	}

	static bool IsSameTeam(PlayerEntity* local, PlayerEntity* other)
	{
		return *(int*)((int)local + 0x32c) == *(int*)((int)other + 0x32c);
	}

	static bool IsDucked(PlayerEntity* playerentity)
	{
		return *(BYTE*)((DWORD)playerentity + 0x6E) == true;
	}

	BOOL IsVisible()
	{
		return this->m_visible.x != -1 && this->m_visible.y != -1 && this->m_visible.z != -1;
	}

	static PlayerEntity* GetClosestEntity(std::vector<PlayerEntity*>& entityArray)
	{
		PlayerEntity* player = nullptr;
		PlayerEntity* localPlayer = (PlayerEntity*)*(DWORD*)((DWORD)GetModuleHandleA("ac_client.exe") + 0x10F4F4);
		for (int i = 0; i < (int)entityArray.size(); i++)
		{
			if (entityArray[i]->m_Health <= 0 || entityArray[i]->m_Health > 100 || IsSameTeam(localPlayer, entityArray[i]))
			{
				continue;
			}
			if (player == nullptr)
			{
				player = entityArray[i];
			}
			else
			{
				if (Get3dDistance(localPlayer, entityArray[i]) < Get3dDistance(localPlayer, player))
				{
					player = entityArray[i];
				}
			}
		}
		return player;
	}
};

struct Game
{
	int GameMode;
	char _0x0004[0x54];
	PlayerEntity* LocalPlayer;
	PlayerEntity** Players;
	char _0x0060[0x4];
	int NumberOfPlayers;
	BOOL TeamGame()
	{
		int GameModes[] = { 0, 4, 5, 7, 13, 11, 14, 17, 16, 20, 21 };
		for (int i = 0; i < 11; ++i)
			if (GameModes[i] == GameMode)
				return TRUE;
		return FALSE;
	}
};