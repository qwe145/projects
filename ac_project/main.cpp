#include <iostream>
#include <Windows.h>

#include "hackMain.h"
#include "gameFunctions.h"

DWORD WINAPI onDllAttach(LPVOID base)
{
	onInitialize();
	FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
}

DWORD WINAPI onDllDetach()
{
	FreeConsole();
	return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, onDllAttach, hinstDll, 0, nullptr);
		return TRUE;

	case DLL_PROCESS_DETACH:
		if (lpvReserved == nullptr)
			return onDllDetach();
		return TRUE;

	default:
		return TRUE;
	}
}

