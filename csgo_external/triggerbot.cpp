#include "triggerbot.hpp"

Triggerbot* triggerbot = new Triggerbot();

bool Triggerbot::EntityValidator(DWORD entity)
{
	return mem->Read<int>((mem->Read<DWORD>(mem->clientdll + dwEntityList + (0x10 * (entity - 1)))) + 0xF0) != engine->GetLocalPlayerTeam(); //Is entity enemy
}

void Triggerbot::DoTriggerbot()
{
	if (engine->IsInGame() && !engine->IsCursorEnabled() && settings->triggerbot.enabled && GetAsyncKeyState(settings->triggerbot.key) && engine->CanCurrentWeaponShoot())
	{
		DWORD entityInCrosshair = mem->Read<DWORD>(engine->GetLocalPlayer() + m_iCrosshairId);
		if (entityInCrosshair > 0 && entityInCrosshair <= 64 && EntityValidator(entityInCrosshair))
		{
			Sleep(settings->triggerbot.delay);
			engine->Shoot();
		}
	}
	Sleep(settings->triggerbot.delay);
}
