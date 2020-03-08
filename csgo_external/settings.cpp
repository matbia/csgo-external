#include "settings.hpp"
#include "files.hpp"
#include <stdio.h>
#include <string>
#include <windows.h>

Settings* settings = new Settings();

void Settings::Setup() {
	if (CofigExists())
	{
		LoadConfig();
	}
	else
	{
		SaveConfig();
	}
}

void Settings::SaveConfig()
{
	files->OnSetup();
	files->WriteBool("Aimbot", "enabled", aimbot.enabled);
	files->WriteInt("Aimbot", "key", aimbot.key);
	files->WriteFloat("Aimbot", "fov", aimbot.fov);
	files->WriteInt("Aimbot", "bone", aimbot.bone);
	files->WriteFloat("Aimbot", "smooth", aimbot.smooth);
	files->WriteInt("Aimbot", "height", aimbot.height);

	files->WriteBool("Triggerbot", "enabled", triggerbot.enabled);
	files->WriteInt("Triggerbot", "key", triggerbot.key);
	files->WriteInt("Triggerbot", "delay", triggerbot.delay);

	files->WriteBool("RCS", "enabled", rcs.enabled);
	files->WriteInt("RCS", "scale", rcs.scale);
	files->WriteBool("RCS", "standalone", rcs.standalone);

	files->WriteBool("Glow", "enabled", glow.enabled);
	files->WriteBool("Glow", "friendly", glow.friendly);
	files->WriteBool("Glow", "health", glow.health);

	files->WriteBool("Misc", "bhop", misc.bhop);
	files->WriteBool("Misc", "noflash", misc.noflash);

	Beep(195, 200);
}

void Settings::LoadConfig()
{
	if (CofigExists())
	{
		files->OnSetup();
		aimbot.enabled = files->ReadBool("Aimbot", "enabled");
		aimbot.key = files->ReadInt("Aimbot", "key");
		aimbot.fov = files->ReadFloat("Aimbot", "fov");
		aimbot.bone = files->ReadInt("Aimbot", "bone");
		aimbot.smooth = files->ReadInt("Aimbot", "smooth");
		aimbot.height = files->ReadInt("Aimbot", "height");

		triggerbot.enabled = files->ReadBool("Triggerbot", "enabled");
		triggerbot.key = files->ReadInt("Triggerbot", "key");
		triggerbot.delay = files->ReadInt("Triggerbot", "delay");

		rcs.enabled = files->ReadBool("RCS", "enabled");
		rcs.scale = files->ReadInt("RCS", "scale");
		rcs.standalone = files->ReadBool("RCS", "standalone");

		glow.enabled = files->ReadBool("Glow", "enabled");
		glow.friendly = files->ReadBool("Glow", "friendly");
		glow.health = files->ReadBool("Glow", "health");

		misc.bhop = files->ReadBool("Misc", "bhop");
		misc.noflash = files->ReadBool("Misc", "noflash");
	}
}

bool Settings::CofigExists()
{
	struct stat buffer;
	return (stat("settings.cfg", &buffer) == 0);
}
