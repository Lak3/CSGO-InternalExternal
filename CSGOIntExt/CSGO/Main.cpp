#include "SDK/SDK.h"

#include "Utils/Memory/Memory.h"

#include "Features/Misc/Misc.h"
#include "Features/Visual/Glow/Glow.h"
#include "Features/Visual/Radar/Radar.h"
#include "Features/Aimbot/Aimbot.h"
#include "Features/Triggerbot/Triggerbot.h"

DWORD WINAPI MainThread(LPVOID lpParam)
{
	if (gEngine.TrainingSoftware())
	{
		Beep(300, 200); //Beep

		while (!(GetAsyncKeyState(VK_F11) & 0x01))
		{
			if (gEngine.IsGameFocused())
			{
				gEntCache.Fill();
				{
					gTrigger.Run();
					gAimbot.Run();
					gMisc.Run();
					gGlow.Run();
					gRadar.Run();
				}
				gEntCache.Clear();
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	
	Beep(300, 200); //Beep
	Beep(200, 200); //Boop

	gMem.Clear();

	return Util::Detach(lpParam);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH: 
		{
			if (auto hEntry = CreateThread(0, 0, MainThread, hinstDLL, 0, 0))
				CloseHandle(hEntry);

			break;
		}
		
		default:
		{
			break;
		}
	}

	return TRUE;
}

namespace Core
{
	DWORD Client = 0;
	DWORD Engine = 0;

	HWND GameWindow = 0;
}