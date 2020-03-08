#include "aimbot.hpp"
#include "triggerbot.hpp"
#include "glow.hpp"
#include "rcs.hpp"
#include "misc.hpp"

#pragma comment(lib, "user32.lib")

void Aimbot() 
{
	while (true) 
	{
		aimbot->Aimbot_Loop();
		this_thread::sleep_for(std::chrono::milliseconds(1));
	}

}

void RCS()
{
	while (true)
	{
		rcs->DoRCS();
		this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void Triggerbot()
{
	while (true)
	{
		triggerbot->DoTriggerbot();
		this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void GlowESP()
{
	while (true)
	{
		glow->DoGlowESP();
		this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void Misc()
{
	while (true)
	{
		misc->NoFlash();
		misc->Bunnyhop();
		misc->Keybinds();
		this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}


void main()
{
	system("color 6");

	engine->OnSetup();

	thread aimbot(Aimbot);
	thread triggerbot(Triggerbot);
	thread rcs(RCS);
	thread glowesp(GlowESP);
	thread misc(Misc);

	aimbot.join();
	triggerbot.join();
	rcs.join();
	misc.join();

	printf("Loaded");
}
