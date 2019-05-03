#include "engine.h"
#include "settings.h"

class Triggerbot
{
public:
	void DoTriggerbot();
private:
	bool EntityValidator(DWORD entity);
};
extern Triggerbot* triggerbot;