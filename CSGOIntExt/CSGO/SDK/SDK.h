#pragma once

#include <Windows.h>
#include <winternl.h>
#include <stdio.h>
#include <tchar.h>
#include <TlHelp32.h>
#include <iphlpapi.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <psapi.h>
#include <sstream>
#include <math.h>
#include <codecvt>
#include <random>
#include <conio.h>
#include <stdint.h>
#include <thread>
#include <stdlib.h>
#include <process.h>
#include <unordered_map>
#include <thread>
#include <array>
#include <map>
#include <playsoundapi.h>
#include <mmsystem.h>
#include <urlmon.h>
#include <immintrin.h>
#include <algorithm>
#include <string_view>
#include <xstring>

#include "Includes/Enums.h"
#include "Includes/Classes.h"
#include "Includes/Structs.h"

#include "../Utils/Utils.h"
#include "../Utils/Math/Math.h"
#include "../Utils/Memory/Memory.h"

#include "Main/Engine/Engine.h"
#include "Main/BaseEntity/BaseEntity.h"
#include "Main/EntityCache/EntityCache.h"
#include "Main/ClientState/ClientState.h"

#include "Includes/Const.h"
#include "Includes/Enums.h"
#include "Includes/Structs.h"
#include "Includes/Classes.h"

namespace Core
{
	inline DWORD Client = 0x0;
	inline DWORD Engine = 0x0;

	inline HWND GameWindow = nullptr;

	namespace Vars
	{
		namespace Aimbot
		{
			inline bool Active = true;
			inline bool CurveAim = false;
			inline bool AimPlayers = true;
			inline bool IgnoreTeam = true;
			inline bool SortByDistance = false;
			inline bool SmoothAim = true;
			inline bool AimChicken = false;
			inline int nKey = 0x01;
			inline int nBone = 8;
			inline float flFov = 3.0f;
			inline float flSmooth = 5.0f;
			inline float flCurveX = 1.3f;
			inline float flCurveY = 3.7f;
		}

		namespace Trigger
		{
			inline bool Active = true;
			inline bool Players = true;
			inline bool IgnoreTeam = true;
			inline bool IgnoreJumping = false;
			inline bool WaitForPunch = true;
			inline bool OnlyOnGround = true;
			inline bool Chickens = true;
			inline int nKey = 0x06;
		}

		namespace Glow
		{
			inline bool Active = true;
			inline bool Players = true;
			inline bool IgnoreTeam = true;
		}

		namespace Radar
		{
			inline bool Active = false;
		}

		namespace Misc
		{
			inline bool Bunnyhop = true;
		}
	}

	namespace Offsets
	{
		constexpr std::int32_t m_fFlags = 0x104;
		constexpr std::int32_t m_iHealth = 0x100;
		constexpr std::int32_t m_iTeamNum = 0xF4;
		constexpr std::int32_t m_bDormant = 0xED;
		constexpr std::int32_t m_bSpotted = 0x93D;
		constexpr std::int32_t m_vecOrigin = 0x138;
		constexpr std::int32_t m_lifeState = 0x25F;
		constexpr std::int32_t m_hOwner = 0x29CC;
		constexpr std::int32_t m_hOwnerEntity = 0x14C;
		constexpr std::int32_t m_iGlowIndex = 0xA438;
		constexpr std::int32_t m_iCrosshairId = 0xB3E4;
		constexpr std::int32_t m_aimPunchAngle = 0x302C;
		constexpr std::int32_t dwEntityList = 0x4D5022C;
		constexpr std::int32_t dwLocalPlayer = 0xD3BC5C;
		constexpr std::int32_t m_dwBoneMatrix = 0x26A8;
		constexpr std::int32_t m_bGunGameImmunity = 0x3944;
		constexpr std::int32_t m_vecViewOffset = 0x108;
		constexpr std::int32_t dwClientState = 0x589DD4;
		constexpr std::int32_t dwClientState_MapDirectory = 0x188;
		constexpr std::int32_t dwClientState_MaxPlayer = 0x388;
		constexpr std::int32_t dwClientState_State = 0x108;
		constexpr std::int32_t dwClientState_ViewAngles = 0x4D88;
		constexpr std::int32_t dwGlowObjectManager = 0x5298078;
	}

	//These have no real meaning lol.
	namespace String
	{
		constexpr std::string_view szCSGO("csgo.exe");
		constexpr std::string_view szSteam("steam.exe");
		constexpr std::string_view szClientDLL("client.dll");
		constexpr std::string_view szEngineDLL("engine.dll");
		constexpr std::string_view szCSGOWindow("Counter-Strike: Global Offensive");

		constexpr std::string_view szFailModules("Failed to get module(s).");
		constexpr std::string_view szFailExe("Failed to find csgo.exe.");
		constexpr std::string_view szFailConsole("Failed to alloc console.");
		constexpr std::string_view szFailHandle("Invalid handle or PID (NULL).");
		constexpr std::string_view szFailSteam("Close Steam/CSGO before injecting!");

		constexpr std::string_view szInfoWaiting("Injected, close this and run Steam/CSGO!");
	}
}