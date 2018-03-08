#include <iostream>
#include <stdlib.h>
#include <Windows.h>

#include "HackProcess.h"
#include "defines.h"
#include "structInfo.h"

using namespace std;

CHackProcess mem;

struct myPlayer_t {
	DWORD cLocalPlayer;

	int flag;
	int teamNum;
	int ChID;

	void ReadInformation() {
		ReadProcessMemory(mem.__HandleProcess, (PBYTE*)(mem.__dwordClient + playerBase), &cLocalPlayer, sizeof(DWORD), NULL);

		ReadProcessMemory(mem.__HandleProcess, (PBYTE*)(cLocalPlayer + flagOff), &flag, sizeof(int), NULL);
		ReadProcessMemory(mem.__HandleProcess, (PBYTE*)(cLocalPlayer + teamOff), &teamNum, sizeof(int), NULL);
		ReadProcessMemory(mem.__HandleProcess, (PBYTE*)(cLocalPlayer + chIDOff), &ChID, sizeof(int), NULL);
	}
}myPlayer;

struct entityList_t {
	DWORD cEntityBase;

	int TeamNum;

	void ReadInformation(int Player) {
		ReadProcessMemory(mem.__HandleProcess, (PBYTE*)(mem.__dwordClient + entityBase + (Player * 10)), &cEntityBase, sizeof(DWORD), NULL);

		ReadProcessMemory(mem.__HandleProcess, (PBYTE*)(cEntityBase + teamOff), &TeamNum, sizeof(int), NULL);


	}

}entityList[32];

void bHop(void) {
	if (GetAsyncKeyState(spaceKey)) {
		if (myPlayer.flag == 257) {
			keybd_event(MapVirtualKey(spaceKey, 0), 0x39, KEYEVENTF_EXTENDEDKEY, NULL);
			Sleep(3);
			keybd_event(MapVirtualKey(spaceKey, 0), 0x39, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, NULL);
		}
	}
}

void triggerBot(void) {
	if (myPlayer.ChID == 0)
		return;
	if (myPlayer.ChID > numOfPlayers)
		return;
	if (entityList[myPlayer.ChID - 1].TeamNum == myPlayer.teamNum)
		return;
	if (myPlayer.ChID > 0 && myPlayer.ChID < numOfPlayers) {

		if ((GetKeyState(VK_LSHIFT) & 0x100) != 0) {

			Sleep(30);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(30);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
	}
}

int main() {

	mem.RunProcess();
	cout << "CS:GO Found. \n" << endl;

	cout << "Press Space for Bunny Hop. \n"; 
	cout << "Hold Shift to activate Trigger Bot.";


	while (!GetAsyncKeyState(f6Key)) {
		myPlayer.ReadInformation();

		for (int i = 0; i < numOfPlayers; i++) {
			entityList[i].ReadInformation(i);
		}

		bHop();
		triggerBot();
		Sleep(1);
	}
}