#pragma once

#include "../../SDK.h"

class C_BaseEntity
{
public:
	void SetSpotted(bool bState);

	int GetHealth()				 const;
	int GetCrosshairID()		 const;
	int GetFlags()				 const;
	int GetGlowIndex()			 const;
	int GetOwner()				 const;
	int GetTeamNum()			 const;
	int GetClassID()			 const;
	int GetIndex()				 const;

	bool IsDormant()			 const;
	bool IsAlive()				 const;
	bool IsInValidTeam()		 const;
	bool IsSpotted()			 const;
	bool IsOnGround()			 const;
	bool IsImmune()				 const;

	Vec3 GetVecOrigin()          const;
	Vec3 GetAimPunch()           const;
	Vec3 GetEyePos()             const;
	Vec3 GetBonePos(int nBoneID) const;

	DWORD GetBoneMatrix()        const;

	byte GetLifeState()          const;
};