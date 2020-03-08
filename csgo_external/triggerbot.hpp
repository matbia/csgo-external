#include "engine.hpp"
#include "settings.hpp"

class Triggerbot
{
public:
	void DoTriggerbot();
private:
	bool EntityValidator(DWORD entity);
};
extern Triggerbot* triggerbot;
