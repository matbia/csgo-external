#pragma once
#include "engine.hpp"
#include "settings.hpp"

class Misc
{
public:
	/*[junk_enable 2 5 /]
	[junk_enable_declares /]
	[swap_lines]*/
	void NoFlash();
	void Bunnyhop();
	void Keybinds();
	/*[/ swap_lines]
	[junk_disable /]*/
private:
	/*[junk_enable 2 5 /]
	[junk_enable_declares /]
	[swap_lines]*/
	DWORD localPlayer;
	byte fFlag;
	/*[/ swap_lines]
	[junk_disable /]*/
};
extern Misc* misc;
