#pragma once

#include "../../SDK/SDK.h"

class C_Triggerbot
{
public:
	void Run();

private:
	void Attack();

	bool IsValidEntity(int nClassID);
	bool IsPlayer(int nClassID);
	bool IsValid(C_BaseEntity* pEntity, C_BaseEntity* pLocal);
	bool ShouldRun(C_BaseEntity* pLocal);

};

extern C_Triggerbot gTrigger;