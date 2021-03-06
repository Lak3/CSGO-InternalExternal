#include "Memory.h"

C_Memory gMem;

void C_Memory::Clear()
{
	if (m_lpAlloc) VirtualFreeEx(m_hProcess, m_lpAlloc, 0, MEM_RELEASE);
	if (m_hProcess) CloseHandle(m_hProcess);
}

bool C_Memory::GetProcess(std::string_view szName)
{
	if (auto hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL))
	{
		PROCESSENTRY32 ProcEntry;
		ProcEntry.dwSize = sizeof(ProcEntry);

		while (Process32Next(hProcess, &ProcEntry))
		{
			if (ProcEntry.szExeFile == szName)
			{
				CloseHandle(hProcess);

				m_dwPID = ProcEntry.th32ProcessID;
				m_hProcess = OpenProcess(0x38, FALSE, m_dwPID);

				return true; //Return success
			}
		}

		CloseHandle(hProcess);
	}

	return false; //Return failure
}

DWORD C_Memory::GetModule(std::string_view szModule)
{
	if (auto hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, m_dwPID))
	{
		MODULEENTRY32 ModEntry;
		ModEntry.dwSize = sizeof(ModEntry);

		while (Module32Next(hModule, &ModEntry))
		{
			if (ModEntry.szModule == szModule)
			{
				CloseHandle(hModule);
				return reinterpret_cast<DWORD>(ModEntry.modBaseAddr);
			}
		}

		CloseHandle(hModule);
	}

	return 0x0;
}

DWORD C_Memory::GetModuleSize(std::string_view szModule)
{
	if (auto hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, m_dwPID))
	{
		MODULEENTRY32 ModEntry;
		ModEntry.dwSize = sizeof(ModEntry);

		while (Module32Next(hModule, &ModEntry))
		{
			if (ModEntry.szModule == szModule)
			{
				CloseHandle(hModule);
				return ModEntry.modBaseSize;
			}
		}

		CloseHandle(hModule);
	}

	return 0x0;
}