#include "Aimbot.h"

C_Aimbot gAimbot;

void C_Aimbot::Run()
{
	if (ShouldRun())
	{
		if (const auto& pLocal = gEntCache.pLocal)
		{
			//Update some vars we need here, to remove need of multiple reads.
			m_vLocalEyePos = pLocal->GetEyePos();
			m_vLocalAngle = gEngine.GetViewAngles();
			m_vLocalPunch = pLocal->GetAimPunch() * 2.0f;

			Target_t Target = { };

			if (GetTarget(pLocal, Target))
			{
				SetAngles(Target, pLocal);
			}
		}
	}
}

bool C_Aimbot::GetTarget(C_BaseEntity* pLocal, Target_t& out)
{
	if (!GetTargets(pLocal))
		return false;

	SortTargets();

	for (auto& Target : m_vecTargets)
	{
		//TODO:
		//-Skip all non-visible entities (Visibility check)
		//-idk

		out = Target;
		return true;
	}

	return false;
}

bool C_Aimbot::GetTargets(C_BaseEntity* pLocal)
{
	m_vecTargets.clear();

	if (Core::Vars::Aimbot::AimPlayers)
	{
		const auto Players = gEntCache.GetGroup(Core::Vars::Aimbot::IgnoreTeam ? GroupType_t::PLAYERS_ENEMIES : GroupType_t::PLAYERS_ALL);

		for (const auto& pEntity : Players)
		{
			if (!pEntity->IsAlive() || pEntity->IsImmune())
				continue;

			Target_t Target = { };

			Target.pEntity = pEntity;
			Target.eType = ETargetType::PLAYER;
			Target.vPosition = pEntity->GetBonePos(Core::Vars::Aimbot::nBone);
			Target.vAngleTo = Math::CalcAngle(m_vLocalEyePos, Target.vPosition);
			Target.fFovTo = Math::CalcFov(m_vLocalAngle + m_vLocalPunch, Target.vAngleTo);

			if (!Core::Vars::Aimbot::SortByDistance && Target.fFovTo > Core::Vars::Aimbot::flFov)
				continue;

			Target.fDistTo = m_vLocalEyePos.DistTo(Target.vPosition);

			m_vecTargets.push_back(Target);
		}
	}

	if (Core::Vars::Aimbot::AimChicken)
	{
		for (const auto& pEntity : gEntCache.GetGroup(GroupType_t::CHICKEN_ALL))
		{
			if (!pEntity->IsAlive())
				continue;

			Target_t Target = { };

			Target.pEntity = pEntity;
			Target.eType = ETargetType::CHICKEN;
			Target.vPosition = pEntity->GetVecOrigin() + Vec3(0, 0, 10);
			Target.vAngleTo = Math::CalcAngle(m_vLocalEyePos, Target.vPosition);
			Target.fFovTo = Math::CalcFov(m_vLocalAngle + m_vLocalPunch, Target.vAngleTo);

			if (!Core::Vars::Aimbot::SortByDistance && Target.fFovTo > Core::Vars::Aimbot::flFov)
				continue;

			Target.fDistTo = m_vLocalEyePos.DistTo(Target.vPosition);

			m_vecTargets.push_back(Target);
		}
	}

	return !m_vecTargets.empty();
}

void C_Aimbot::SetAngles(const Target_t& Target, C_BaseEntity* pLocal)
{
	Vec3 vAngle = Target.vAngleTo - m_vLocalPunch;
	Math::ClampAngles(vAngle);

	if (Core::Vars::Aimbot::SmoothAim)
	{
		Vec3 vDelta = (vAngle - m_vLocalAngle);
		Math::ClampAngles(vDelta);

		if (Core::Vars::Aimbot::CurveAim)
		{
			vDelta += Vec3(vDelta.y / Core::Vars::Aimbot::flCurveX, vDelta.x / Core::Vars::Aimbot::flCurveY, 0.0f);
			Math::ClampAngles(vDelta);
		}

		m_vLocalAngle += vDelta / Core::Vars::Aimbot::flSmooth;
		Math::ClampAngles(m_vLocalAngle);

		gEngine.SetViewAngles(m_vLocalAngle);
	}
	else
	{
		gEngine.SetViewAngles(vAngle);
	}
}

void C_Aimbot::SortTargets()
{
	std::sort(m_vecTargets.begin(), m_vecTargets.end(), [&](const Target_t& a, const Target_t& b) -> bool
		{
			if (Core::Vars::Aimbot::SortByDistance)
				return (a.fDistTo < b.fDistTo);
			else
				return (a.fFovTo < b.fFovTo);
		});
}

bool C_Aimbot::ShouldRun()
{
	if (!Core::Vars::Aimbot::Active || !Util::IsKeyDown(Core::Vars::Aimbot::nKey))
		return false;

	return true;
}