#include <Windows.h>
#include "Offsets.h"

// Prints A Message To The Screen And The Console In The Top Right
typedef void(__cdecl* _printToConsole)(char* Input, ...);
_printToConsole printToConsole = (_printToConsole)OFFSET_SENDMSGCONSOLE;

// Prints A Message To The Console In The Top Right
typedef void(__cdecl* _printToScreen)(char* Input, ...);
_printToScreen printToScreen = (_printToScreen)OFFSET_SENDMSGSCREEN;

namespace printMessage
{
	void hackLoaded()
	{
		printToConsole("\f9ACHack \f8 Loaded...");
		printToConsole("\f9F1 \f5- \f8 Infinite Ammo");
		printToConsole("\f9F2 \f5- \f8 Rapid Fire");
		printToConsole("\f9F3 \f5- \f8 No Recoil");;
	}

	void hackUnloaded()
	{
		printToConsole("\f9ACHack \f8 Unloaded...");
	}

	void infiniteAmmoOn()
	{
		printToScreen("Infinite Ammo %s", "[\f0On\f5]");
	}
	void infiniteAmmoOff()
	{
		printToScreen("Infinite Ammo %s", "[\f0Off\f5]");
	}

	void rapidFireOn()
	{
		printToScreen("Rapid Fire %s", "[\f0On\f5]");
	}
	void rapidFireOff()
	{
		printToScreen("Rapid Fire %s", "[\f0Off\f5]");
	}

	void noRecoilOn()
	{
		printToScreen("No Recoil %s", "[\f0On\f5]");
	}
	void noRecoilOff()
	{
		printToScreen("No Recoil %s", "[\f0Off\f5]");
	}
}

void infiniteAmmo(bool activate)
{
	DWORD infiniteAmmoTemp;

	VirtualProtect((LPVOID)OFFSET_INFINITEAMMO, 2, PAGE_EXECUTE_READWRITE, &infiniteAmmoTemp);
	if (activate)
	{
		memcpy((void*)OFFSET_INFINITEAMMO, "\x90\x90", 2);
		printMessage::infiniteAmmoOn();
	}
	else
	{
		memcpy((void*)OFFSET_INFINITEAMMO, "\x89\x0A", 2);
		printMessage::infiniteAmmoOff();
	}
	VirtualProtect((LPVOID)OFFSET_INFINITEAMMO, 2, infiniteAmmoTemp, &infiniteAmmoTemp);
}

void rapidFire(bool activate)
{
	DWORD rapidFireTemp;

	VirtualProtect((LPVOID)OFFSET_RAPIDFIRE, 2, PAGE_EXECUTE_READWRITE, &rapidFireTemp);
	if (activate)
	{
		memcpy((void*)OFFSET_RAPIDFIRE, "\x90\x90", 2);
		printMessage::rapidFireOn();
	}
	else
	{
		memcpy((void*)OFFSET_RAPIDFIRE, "\x89\x0A", 2);
		printMessage::rapidFireOff();
	}
	VirtualProtect((LPVOID)OFFSET_RAPIDFIRE, 2, rapidFireTemp, &rapidFireTemp);
}

void noRecoil(bool activate)
{
	DWORD noRecoilTemp;

	VirtualProtect((LPVOID)OFFSET_NORECOIL, 2, PAGE_EXECUTE_READWRITE, &noRecoilTemp);
	if (activate)
	{
		memcpy((void*)OFFSET_NORECOIL, "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 10);
		printMessage::noRecoilOn();
	}
	else
	{
		memcpy((void*)OFFSET_NORECOIL, "\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);
		printMessage::noRecoilOff();
	}
	VirtualProtect((LPVOID)OFFSET_NORECOIL, 2, noRecoilTemp, &noRecoilTemp);
}