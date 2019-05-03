#include "misc.h"

Misc* misc = new Misc();

void Misc::NoFlash()
{
	if (settings->misc.noflash && engine->IsInGame())
	{
		localPlayer = engine->GetLocalPlayer();
		if (mem->Read<float>(localPlayer + m_flFlashMaxAlpha) > 0.f)
		{
			//cout << mem->Read<float>(localPlayer + m_flFlashMaxAlpha) << endl;
			mem->Write<float>(localPlayer + m_flFlashMaxAlpha, 255.f);
		}
	}
}

void Misc::Bunnyhop()
{
	if (settings->misc.bhop && engine->IsInGame() && !engine->IsCursorEnabled())
	{
		fFlag = engine->GetFlags();
		if (GetAsyncKeyState(VK_SPACE) && fFlag == 1 || fFlag == 3)
		{
			engine->Jump();
		}
	}
}

void Misc::Keybinds()
{
	if (GetAsyncKeyState(VK_INSERT))
	{
		settings->LoadConfig();
	}

	if (GetAsyncKeyState(VK_END) || !mem->IsProcessRunning())
	{
		engine->OnShutdown();
	}
}
