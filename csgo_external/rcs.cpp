#include "rcs.h"

RCS* rcs = new RCS();

//Standalone RCS
void RCS::DoRCS()
{
	if (engine->IsInGame() && settings->rcs.enabled && engine->GetCurrentWeapon() == 0 && settings->rcs.standalone)
	{
		viewAngle = engine->GetViewAngles();
		punchAngle = mem->Read<Vector>(engine->GetLocalPlayer() + m_aimPunchAngle);
		if (engine->GetShotsFired() > 1)
		{
			viewAngle.x -= (punchAngle.x - oldAngle.x) * (settings->rcs.scale * 0.02f);
			viewAngle.y -= (punchAngle.y - oldAngle.y) * (settings->rcs.scale * 0.02f);
			ClampVector(viewAngle);
			engine->SetViewAngles(viewAngle);

			oldAngle.x = punchAngle.x;
			oldAngle.y = punchAngle.y;
		}
		else
		{
			oldAngle.x = punchAngle.x;
			oldAngle.y = punchAngle.y;
		}
	}
}
