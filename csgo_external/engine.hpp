#pragma once
#include "memory.hpp"
#include "offsets.hpp"

enum WeaponIndex
{
	WEAPON_NONE,
	WEAPON_DEAGLE = 1,
	WEAPON_DUAL = 2,
	WEAPON_FIVE7 = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALIL = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250_CZ75 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG553 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFEGG = 41,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKE = 45,
	WEAPON_T_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_CT_MOLOTOV = 48,
	WEAPON_C4 = 49,
	WEAPON_MAX
};

class Engine
{
public:
	/*[junk_enable 2 5 /]
	[junk_enable_declares /]
	[swap_lines]*/
	DWORD GetLocalPlayer();
	DWORD GetEnginePointer();
	byte GetFlags();
	bool IsInGame();
	Vector GetViewAngles();
	void SetViewAngles(Vector angles);
	void Shoot();
	void Jump();
	bool CanCurrentWeaponShoot();
	int GetLocalPlayerTeam();
	WeaponIndex GetCurrentWeapon();
	int GetShotsFired();
	DWORD GetEntity(int i);
	int GetEntityHealth(DWORD entity);
	bool IsEntityDormant(DWORD entity);
	int GetEntityClassId(DWORD entity);
	float GetEntityVelocity(DWORD entity);
	int GetMaxClients();
	bool IsEntityEnemy(DWORD entity);
	bool IsEntityScoped(DWORD entity);
	void OnSetup();
	void OnShutdown();
	bool IsCursorEnabled();
	/*[/ swap_lines]
	[junk_disable /]*/
};

extern Engine* engine;
