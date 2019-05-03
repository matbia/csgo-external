#pragma once
class Settings
{
public:
	void Setup();
	void SaveConfig();
	void LoadConfig();

	struct aimbot
	{
		bool enabled = true;
		int key = 0x01;
		float fov = 2.2f;
		int bone = 7;
		short smooth = 19;
		int height = -5;
	} aimbot;

	struct triggerbot
	{
		bool enabled = true;
		int key = 0x12;
		int delay = 0;
	} triggerbot;

	struct rcs
	{
		bool enabled = true;
		int scale = 100;
		bool standalone = false;
	} rcs;

	struct glow
	{
		bool enabled = true;
		bool friendly = false;
		bool health = true;
	} glow;

	struct misc
	{
		bool bhop = true;
		bool noflash = false;
	} misc;
private:
	bool CofigExists();
};
extern Settings* settings;