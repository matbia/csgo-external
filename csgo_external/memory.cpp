#include "memory.hpp"

Mem* mem = new Mem();

DWORD Mem::Module(LPSTR ModuleName)
{
	hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	mEntry.dwSize = sizeof(mEntry);
	do
	{
		if (!strcmp(mEntry.szModule, ModuleName))
		{
			CloseHandle(hModule);
			return (DWORD)mEntry.modBaseAddr;
		}
		this_thread::sleep_for(std::chrono::milliseconds(1));
	} while (Module32Next(hModule, &mEntry));
	return NULL;
}

void Mem::GetProcessHandle()
{
	hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	ProcEntry.dwSize = sizeof(ProcEntry);
	bool csgoFound = false;
	while (!csgoFound)
	{
		//Loop through processes until csgo.exe if found
		do
		{
			if (!strcmp(ProcEntry.szExeFile, "csgo.exe"))
			{
				dwPID = ProcEntry.th32ProcessID;
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID); //Open handle to csgo.exe
				Beep(320, 200);
				csgoFound = true;
				return;
			}
		} while (Process32Next(hPID, &ProcEntry) && !csgoFound);

		hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	}
}

bool Mem::IsProcessRunning()
{
	if (hProcess != NULL)
	{
		DWORD ret = WaitForSingleObject(hProcess, 0);
		return ret == WAIT_TIMEOUT;
	}
	return false;
}

void Mem::GetCsgoModules()
{
	while (clientdll == NULL)
	{
		clientdll = Module("client_panorama.dll");
		this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	while (enginedll == NULL)
	{
		enginedll = Module("engine.dll");
		this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
