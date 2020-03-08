#pragma once
#include "engine.hpp"
#include "settings.hpp"

class Aimbot
{
public:
	void Aimbot_Loop();
private:
	struct BoneVector
	{
		float x;
		char _pad0x04[0xC];
		float y;
		char _pad0x14[0xC];
		float z;
	};
	/*[junk_enable 2 5 /]
	[junk_enable_declares /]
	[swap_lines]*/
	Vector CalcEnemyBone(DWORD entity, int bone);
	void SmoothAngleSet(Vector dest, Vector orig);
	Vector CalcLocalPos();
	Vector CalcAngle(Vector src, Vector dst);
	float CalcFOV(Vector angle, Vector playerAngle);
	bool IsEntityValid(DWORD entity);
	DWORD localPlayer;
	bool entityDormant;
	int entityHealth;
	Vector enemyAngle;
	Vector currentAngles;
	Vector vAngle;
	DWORD entity;
	/*[/swap_lines]
	[junk_disable /]*/
};

extern Aimbot* aimbot;
