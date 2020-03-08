#pragma once
#include "engine.hpp"
#include "settings.hpp"

class GlowESP
{
public:
	void DoGlowESP();
private:
	/*[junk_enable 2 5 /]
	[junk_enable_declares /]
	[swap_lines]*/
	void WriteGlow(float r, float g, float b, float a, bool renderWhenOccluded, bool renderWhenUnoccluded, bool fullBloom);
	bool entityDormant;
	int entityGlowIndex;
	DWORD glowPointer;
	struct glowSettings;
	struct glowColor;
	/*[/ swap_lines]
	[junk_disable /]*/
};

extern GlowESP* glow;
