#include "aimbot.h"
#include <cmath>
#include <iomanip>

Aimbot* aimbot = new Aimbot();

Vector Aimbot::CalcEnemyBone(DWORD entity, int bone)
{
	DWORD bonematrix = mem->Read<DWORD>(entity + m_dwBoneMatrix);
	BoneVector vBone = mem->Read<BoneVector>(bonematrix + 0x30 * bone + 0xC);
	Vector boneVec;
	boneVec.x = vBone.x;
	boneVec.y = vBone.y;
	boneVec.z = vBone.z - 64.f + settings->aimbot.height;
	return boneVec;
}

void Aimbot::SmoothAngleSet(Vector dest, Vector orig)
{
	if (settings->aimbot.smooth > 0)
	{
		Vector vecDelta;
		vecDelta.x = orig.x - dest.x;
		vecDelta.y = orig.y - dest.y;
		ClampVector(vecDelta);
		dest.x = orig.x - vecDelta.x / (5.f * settings->aimbot.smooth);
		dest.y = orig.y - vecDelta.y / (5.f * settings->aimbot.smooth);
	}
	engine->SetViewAngles(dest);
}

Vector Aimbot::CalcLocalPos()
{
	localPlayer = engine->GetLocalPlayer();
	Vector LocalHeadPos;
	Vector Origin = mem->Read<Vector>(localPlayer + m_vecOrigin);
	Vector ViewVector = mem->Read<Vector>(localPlayer + m_vecViewOffset);
	LocalHeadPos.x = Origin.x - ViewVector.x;
	LocalHeadPos.y = Origin.y - ViewVector.y;
	LocalHeadPos.z = Origin.z - ViewVector.z;
	return LocalHeadPos;
}

Vector Aimbot::CalcAngle(Vector src, Vector dst)
{
	Vector delta;
	delta.x = src.x - dst.x;
	delta.y = src.y - dst.y;
	delta.z = src.z - dst.z;

	vAngle.x = (float)(asinf((delta.z + 64.f) / FastSQRT(delta.x*delta.x + delta.y*delta.y)) * M_RADPI);
	vAngle.y = (float)(atanf(delta.y / delta.x) * M_RADPI);

	if (delta.x >= 0.0)
	{
		vAngle.y += 180.0f;
	}

	//RCS for Aimbot
	if (engine->GetShotsFired() > 1 && settings->rcs.enabled)
	{
		Vector aimPunch = mem->Read<Vector>(engine->GetLocalPlayer() + m_aimPunchAngle);

		vAngle.x -= aimPunch.x * (settings->rcs.scale * 0.02f);
		vAngle.y -= aimPunch.y * (settings->rcs.scale * 0.02f);
	}

	return vAngle;
}

float Aimbot::CalcFOV(Vector angle, Vector playerAngle)
{
	ClampVector(angle);
	return (float)FastSQRT(pow(angle.x - playerAngle.x, 2) + pow(angle.y - playerAngle.y, 2)); //Basic Pythagorean theorem
}

bool Aimbot::IsEntityValid(DWORD entity)
{
	if (entity == NULL || engine->IsEntityDormant(entity) || !engine->IsEntityEnemy(entity))
	{
		return false;
	}
	return true;
}

void Aimbot::Aimbot_Loop()
{
	if (settings->aimbot.enabled && engine->IsInGame() && !engine->IsEntityScoped(engine->GetLocalPlayer()) && !engine->IsCursorEnabled() && engine->CanCurrentWeaponShoot())
	{
		for (int i = 0; i <= 64; i++)
		{
			entity = engine->GetEntity(i);
			//Skip loop iteration if entity is invalid
			if (!IsEntityValid(entity))
			{
				continue;
			}

			while (GetAsyncKeyState(settings->aimbot.key))
			{
				enemyAngle = CalcAngle(CalcLocalPos(), CalcEnemyBone(entity, settings->aimbot.bone));
				currentAngles = engine->GetViewAngles();

				if (CalcFOV(enemyAngle, currentAngles) < settings->aimbot.fov &&  engine->GetEntityHealth(entity) > 0) //Health check prevents weird snapping above enemy's head after kill
				{
					SmoothAngleSet(enemyAngle, currentAngles);
				}
				else
				{
					break;
				}
			}
		}
	}
}
