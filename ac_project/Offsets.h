#pragma once

#define isTeamGame (gameMode == 0 || gameMode == 4 || gameMode == 5 || gameMode == 7 || gameMode == 11 || gameMode == 13 || gameMode == 14 || gameMode == 16 || gameMode == 17 || gameMode == 20 || gameMode == 21)

// Functions
#define OFFSET_SENDMSGCONSOLE 0x46B060
#define OFFSET_SENDMSGSCREEN 0x4090F0

#define OFFSET_INFINITEAMMO 0x004637E9
#define OFFSET_INFINITEHEALTH 0x0042CA5E
#define OFFSET_RAPIDFIRE 0x04637E4
#define OFFSET_NORECOIL 0x463786
