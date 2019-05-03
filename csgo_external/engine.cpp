#include "engine.h"
#include "settings.h"

Engine* engine = new Engine();

DWORD Engine::GetLocalPlayer()
{
	//printf_s((const char *)GetWeaponType());
	return mem->Read<DWORD>(mem->clientdll + dwLocalPlayer);
}

DWORD Engine::GetEnginePointer()
{
	return mem->Read<DWORD>(mem->enginedll + dwClientState);
}

byte Engine::GetFlags()
{
	return mem->Read<byte>(engine->GetLocalPlayer() + m_fFlags);
}

bool Engine::IsInGame()
{
	if (mem->Read<int>(GetEnginePointer() + dwClientState_State) == 6)
	{
		return true;
	}
	return false;
}

Vector Engine::GetViewAngles()
{
	return mem->Read<Vector>(GetEnginePointer() + dwClientState_ViewAngles);
}

void Engine::SetViewAngles(Vector angles)
{
	ClampVector(angles);
	mem->Write<Vector>(GetEnginePointer() + dwClientState_ViewAngles, angles);
}

void Engine::Shoot()
{
	mem->Write<int>(mem->clientdll + dwForceAttack, 1);
	Sleep(10);
	mem->Write<int>(mem->clientdll + dwForceAttack, 0);
}

void Engine::Jump()
{
	mem->Write<int>(mem->clientdll + dwForceJump, 1);
	Sleep(100);
	mem->Write<int>(mem->clientdll + dwForceJump, 0);
}

bool Engine::CanCurrentWeaponShoot()
{
	WeaponIndex currWeapon = GetCurrentWeapon();
	if (currWeapon == WEAPON_NONE || currWeapon == WEAPON_KNIFEGG || currWeapon == WEAPON_KNIFE || currWeapon == WEAPON_FLASHBANG || currWeapon == WEAPON_HEGRENADE ||
		currWeapon == WEAPON_SMOKE || currWeapon == WEAPON_T_MOLOTOV || currWeapon == WEAPON_DECOY || currWeapon == WEAPON_CT_MOLOTOV || currWeapon == WEAPON_C4) 
	{
		return false;
	}
	return true;
}

int Engine::GetLocalPlayerTeam()
{
	return mem->Read<int>(GetLocalPlayer() + m_iTeamNum);
}

WeaponIndex Engine::GetCurrentWeapon()
{
	return WeaponIndex(mem->Read<int>((mem->Read<DWORD>(mem->clientdll + dwEntityList + ((mem->Read<DWORD>(GetLocalPlayer() + m_hActiveWeapon) & 0xFFF) - 1) * 0x10)) + m_iItemDefinitionIndex));
}

int Engine::GetShotsFired()
{
	return mem->Read<int>(GetLocalPlayer() + m_iShotsFired);
}

DWORD Engine::GetEntity(int i)
{
	return mem->Read<DWORD>(mem->clientdll + dwEntityList + (i * 0x10));
}

int Engine::GetEntityHealth(DWORD entity)
{
	return mem->Read<int>(entity + 0xFC);
}

bool Engine::IsEntityDormant(DWORD entity)
{
	return mem->Read<bool>(entity + isDormant);
}

int Engine::GetEntityClassId(DWORD entity)
{
	return mem->Read<int>(mem->Read<int>(mem->Read<int>(mem->Read<int>(entity + 0x8) + 0x8) + 0x1) + 0x14);
}

//Buggy
float Engine::GetEntityVelocity(DWORD entity)
{
	Vector vel = mem->Read<Vector>(engine->GetLocalPlayer() + m_vecVelocity);
	float flSpeed =sqrt(vel.x * vel.x + vel.y * vel.y);
	return abs(flSpeed);
}

int Engine::GetMaxClients()
{
	/*globalVars = Main.memManager.ReadMemory<int*>(Main.ClientDLL + Offsetek.offsetGlobals);
	MaxClients = Main.memManager.ReadMemory<int>(globalVars + Offsetek.offsetMaxClients);*/
	//Not implemented yet
	return 0;
}

bool Engine::IsEntityEnemy(DWORD entity)
{
	if (mem->Read<int>(entity + m_iTeamNum) != GetLocalPlayerTeam())
	{
		return true;
	}
	return false;
}

bool Engine::IsEntityScoped(DWORD entity)
{
	return mem->Read<bool>(GetLocalPlayer() + m_bIsScoped);
}

void Engine::OnSetup()
{
	//Check if program is already running
	CreateMutexA(0, FALSE, "Local\\$myprogram$");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		exit(0);
	}

	settings->Setup();
	mem->GetProcessHandle();
	Sleep(5000);
	mem->GetCsgoModules();
}

void Engine::OnShutdown()
{
	CloseHandle(mem->hProcess);
	exit(0);
}

//Broken
bool Engine::IsCursorEnabled()
{
	if (!mem->Read<bool>(mem->clientdll + dwInput + 0x6) || !(mem->Read<byte>(mem->clientdll + dwMouseEnable) & 1))
	{
		return true;
	}
	return false;
}
