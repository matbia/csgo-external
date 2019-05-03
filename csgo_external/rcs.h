#pragma once
#include "engine.h"
#include "settings.h"

class RCS
{
public:
	void DoRCS();
private:
	/*[junk_enable 2 5 /]
	[junk_enable_declares /]
	[swap_lines]*/
	Vector viewAngle;
	Vector punchAngle;
	Vector oldAngle;
	/*[/ swap_lines]
	[junk_disable /]*/
};
extern RCS* rcs;