#pragma once

#include "../../SDK.h"

//"Engine"
class C_BaseEntity;
class C_Engine
{
public:
	bool  TrainingSoftware();
	void  SetViewAngles(Vec3 vAngle);
	int   GetMaxUsedServerIndex();
	bool  IsGameFocused();
	C_BaseEntity* GetLocalPlayer();
	C_BaseEntity* GetEntity(int nIndex);
	DWORD GetClientState();
	DWORD GetGlowManager();
	Vec3  GetViewAngles();
};

extern C_Engine gEngine;