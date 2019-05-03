#include "glow.h"

GlowESP* glow = new GlowESP();

struct GlowESP::glowColor
{
	float r, g, b, a;

	glowColor(float _r, float _g, float _b, float _a)
	{
		r = _r; g = _g; b = _b; a = _a;
	}
};

struct GlowESP::glowSettings
{
	bool renderWhenOccluded, renderWhenUnoccluded, fullBloom;

	glowSettings(bool _renderWhenOccluded, bool _renderWhenUnoccluded, bool _fullBloom)
	{
		renderWhenOccluded = _renderWhenOccluded; renderWhenUnoccluded = _renderWhenUnoccluded; fullBloom = _fullBloom;
	}
};

void GlowESP::WriteGlow(float r, float g, float b, float a, bool renderWhenOccluded, bool renderWhenUnoccluded, bool fullBloom)
{
	mem->Write<glowColor>((glowPointer + ((entityGlowIndex * 0x38) + 0x4)), glowColor(r, g, b, a));
	mem->Write<glowSettings>((glowPointer + ((entityGlowIndex * 0x38) + 0x24)), glowSettings(renderWhenOccluded, renderWhenUnoccluded, fullBloom));
}

void GlowESP::DoGlowESP()
{
	if (settings->glow.enabled && engine->IsInGame())
	{
		glowPointer = mem->Read<DWORD>(mem->clientdll + dwGlowObjectManager);
		if (!glowPointer)
		{
			return;
		}

		for (int i = 0; i < mem->Read<int>(mem->clientdll + dwGlowObjectManager + 0xC); i++)
		{
			DWORD entity = engine->GetEntity(i);
			if (!entity)
			{
				continue;
			}
			entityGlowIndex = mem->Read<int>(entity + m_iGlowIndex);

			if (!entityDormant && engine->GetEntityClassId(entity) == 35)
			{
				if (engine->IsEntityEnemy(entity))
				{
					if (settings->glow.health)
					{
						int entityHealth = engine->GetEntityHealth(entity);
						WriteGlow(1.f - (entityHealth * 0.01f), entityHealth * 0.01f, 0, 0.6f, true, false, false);
					}
					else
					{
						WriteGlow(1.0f, 0.2f, 0.6f, 0.8f, true, false, false);
					}
				}
				else if (settings->glow.friendly)
				{
					WriteGlow(0.2f, 0.2f, 0.9f, 0.6f, true, false, false);
				}
			}	
		}
	}
}
