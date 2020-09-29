#include "Misc.h"

C_Misc gMisc;

void C_Misc::Run()
{
	if (Core::Vars::Misc::Bunnyhop)
		RunBhop();

	//...
}

void C_Misc::RunBhop()
{
	if (const auto& pLocal = gEntCache.pLocal)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000 && pLocal->IsOnGround())
			SendMessage(Core::GameWindow, WM_MOUSEWHEEL, -32, NULL);
	}
}