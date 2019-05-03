#pragma once
#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <thread>
#include "math.h"

using namespace std;

class Mem
{
public:
	/*[junk_enable 2 5 /]
	[junk_enable_declares /]
	[swap_blocks]
	[block]*/
	template<class cData>
	cData Read(DWORD dwAddress)
	{
		cData read;
		ReadProcessMemory(hProcess, (LPVOID)dwAddress, &read, sizeof(read), NULL);
		return read;
	}
	/*[/block]
	[block]*/
	template<class cData>
	void Write(DWORD dwAddress, cData data)
	{
		WriteProcessMemory(hProcess, (LPVOID)dwAddress, &data, sizeof(data), NULL);
	}
	/*[/block]
	[/swap_blocks]
	[swap_lines]*/
	DWORD Module(LPSTR ModuleName);
	void GetProcessHandle();
	bool IsProcessRunning();
	void GetCsgoModules();
	DWORD clientdll = NULL;
	DWORD enginedll = NULL;
	HANDLE hProcess;
	/*[/swap_lines]
	[junk_disable /]*/
private:
	/*[junk_enable 2 5 /]
	[junk_enable_declares /]
	[swap_lines]*/
	DWORD dwPID;
	HANDLE hPID;
	PROCESSENTRY32 ProcEntry;
	MODULEENTRY32 mEntry;
	HANDLE hModule;
	/*[/swap_lines]
	[junk_disable /]*/
};

extern Mem* mem;
