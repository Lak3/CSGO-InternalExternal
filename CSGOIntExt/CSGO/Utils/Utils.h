#pragma once

#pragma warning( disable : 4996 ) //smh

namespace Util
{
	inline int nConAlloc = FALSE;

	inline int RandInt(int nMin, int nMax) 
	{
		std::random_device rd; std::mt19937 gen(rd()); std::uniform_int_distribution<> distr(nMin, nMax);
		return distr(gen);
	}

	inline BOOL InitCon()
	{
		nConAlloc = AllocConsole();

		if (nConAlloc)
		{
			static_cast<void>(freopen("CONIN$", "r", stdin));
			static_cast<void>(freopen("CONOUT$", "w", stdout));
			static_cast<void>(freopen("CONOUT$", "w", stderr));
		}

		return nConAlloc;
	}

	inline int Detach(LPVOID lpParam)
	{
		if (nConAlloc) FreeConsole();

		FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), EXIT_SUCCESS);

		return EXIT_SUCCESS;
	}

	inline bool ErrorBox(std::string_view szMessage)
	{
		MessageBoxA(0, szMessage.data(), "Error blyat(", MB_ICONERROR);
		return false;
	}

	inline void InfoBox(std::string_view szMessage)
	{
		MessageBoxA(0, szMessage.data(), "Info blyat)", MB_ICONINFORMATION);
	}

	inline bool IsKeyDown(int nKey)
	{
		return (GetAsyncKeyState(nKey) & 0x8000);
	}

	inline HWND FindWind(std::string_view szName)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return FindWindowA(0, szName.data());
	}
}