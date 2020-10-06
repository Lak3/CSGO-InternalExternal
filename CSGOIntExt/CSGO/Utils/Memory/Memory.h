#pragma once

#include "../../SDK/SDK.h"

class C_Memory
{
public:
	DWORD m_dwPID	  = 0x0;
	HANDLE m_hProcess = 0;
	LPVOID m_lpAlloc = nullptr;

public:
	template<class cDataType>
	cDataType lpRead(LPCVOID lpBase)
	{
		cDataType Data;
		ReadProcessMemory(m_hProcess, lpBase, &Data, sizeof(cDataType), NULL);
		return Data;
	}

	template<class cDataType>
	cDataType Read(DWORD dwBase)
	{
		cDataType Data;
		ReadProcessMemory(m_hProcess, reinterpret_cast<LPCVOID>(dwBase), &Data, sizeof(cDataType), NULL);
		return Data;
	}

	template<class cDataType>
	void lpWrite(LPVOID lpBase, cDataType dwBuff)
	{
		WriteProcessMemory(m_hProcess, lpBase, &dwBuff, sizeof(cDataType), NULL);
	}

	template<class cDataType>
	void Write(DWORD dwBase, cDataType dwBuff)
	{
		WriteProcessMemory(m_hProcess, reinterpret_cast<LPVOID>(dwBase), &dwBuff, sizeof(cDataType), NULL);
	}

public:
	void Clear();

	bool GetProcess(std::string_view szName);
	DWORD GetModule(std::string_view szName);
	DWORD GetModuleSize(std::string_view szName);

};

extern C_Memory gMem;