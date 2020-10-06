#pragma once

#include "../../SDK/SDK.h"

class C_Aimbot
{
public:
	void Run();

private:
	enum struct ETargetType 
	{
		DEFAULT = -1,
		PLAYER,
		DRONE,
		CHICKEN
	};

	struct Target_t
	{
		C_BaseEntity* pEntity = nullptr;
		ETargetType eType = ETargetType::DEFAULT;
		Vec3 vPosition = Vec3();
		Vec3 vAngleTo = Vec3();
		float fFovTo = 0.0f;
		float fDistTo = 0.0f;
	};

	void SortTargets();
	void SetAngles(const Target_t& Target, C_BaseEntity* pLocal);
	bool GetTargets(C_BaseEntity* pLocal);
	bool GetTarget(C_BaseEntity* pLocal, Target_t& out);
	bool ShouldRun();

	std::vector<Target_t> m_vecTargets;
	Vec3 m_vLocalEyePos;
	Vec3 m_vLocalAngle;
	Vec3 m_vLocalPunch;
};

extern C_Aimbot gAimbot;