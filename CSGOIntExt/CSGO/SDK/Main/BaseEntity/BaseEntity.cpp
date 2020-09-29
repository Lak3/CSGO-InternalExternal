#include "BaseEntity.h"

void C_BaseEntity::SetSpotted(bool bState)
{
	gMem.lpWrite<bool>(this + Core::Offsets::m_bSpotted, bState);
}

int C_BaseEntity::GetHealth() const
{
	return gMem.lpRead<int>(this + Core::Offsets::m_iHealth);
}

int C_BaseEntity::GetFlags() const
{
	return gMem.lpRead<int>(this + Core::Offsets::m_fFlags);
}

int C_BaseEntity::GetCrosshairID() const
{
	return gMem.lpRead<int>(this + Core::Offsets::m_iCrosshairId);
}

int C_BaseEntity::GetTeamNum() const
{
	return gMem.lpRead<int>(this + Core::Offsets::m_iTeamNum);
}

int C_BaseEntity::GetOwner() const
{
	return gMem.lpRead<int>(this + Core::Offsets::m_hOwnerEntity);
}

int C_BaseEntity::GetGlowIndex() const
{
	return gMem.lpRead<int>(this + Core::Offsets::m_iGlowIndex);
}

int C_BaseEntity::GetIndex() const
{
	int m_nVT = gMem.lpRead<int>(this + 0x8);
	return gMem.Read<int>(m_nVT + 9 * 0x4);
}

int C_BaseEntity::GetClassID() const
{
	int m_nVT = gMem.lpRead<int>(this + 0x8); //Networkable
	int m_nFN = gMem.Read<int>(m_nVT + 2 * 0x4); //GetClientClass
	int m_nCC = gMem.Read<int>(m_nFN + 0x1); //sClientClass
	return gMem.Read<int>(m_nCC + 20); //And finally, class ID
}

bool C_BaseEntity::IsImmune() const
{
	return gMem.lpRead<bool>(this + Core::Offsets::m_bGunGameImmunity);
}

bool C_BaseEntity::IsDormant() const
{
	return gMem.lpRead<bool>(this + Core::Offsets::m_bDormant);
}

bool C_BaseEntity::IsSpotted() const
{
	return gMem.lpRead<bool>(this + Core::Offsets::m_bSpotted);
}

bool C_BaseEntity::IsOnGround() const
{
	return (GetFlags() & FL_ONGROUND);
}

bool C_BaseEntity::IsInValidTeam() const
{
	int m_nTeam = GetTeamNum();
	return (m_nTeam == 2 || m_nTeam == 3);
}

bool C_BaseEntity::IsAlive() const
{
	return (GetLifeState() == LIFE_ALIVE);
}

byte C_BaseEntity::GetLifeState() const
{
	return gMem.lpRead<byte>(this + Core::Offsets::m_lifeState);
}

Vec3 C_BaseEntity::GetVecOrigin() const
{
	return gMem.lpRead<Vec3>(this + Core::Offsets::m_vecOrigin);
}

Vec3 C_BaseEntity::GetAimPunch() const
{
	return gMem.lpRead<Vec3>(this + Core::Offsets::m_aimPunchAngle);
}

Vec3 C_BaseEntity::GetEyePos() const
{
	return (gMem.lpRead<Vec3>(this + Core::Offsets::m_vecViewOffset)) + GetVecOrigin();
}

Vec3 C_BaseEntity::GetBonePos(int nBoneID) const
{
	Vec3 vBone = Vec3();

	if (const auto dwBase = GetBoneMatrix())
	{
		vBone.x = gMem.Read<float>(dwBase + 0x30 * nBoneID + 0x0C);
		vBone.y = gMem.Read<float>(dwBase + 0x30 * nBoneID + 0x1C);
		vBone.z = gMem.Read<float>(dwBase + 0x30 * nBoneID + 0x2C);
	}

	return vBone;
}

DWORD C_BaseEntity::GetBoneMatrix() const
{
	return gMem.lpRead<DWORD>(this + Core::Offsets::m_dwBoneMatrix);
}