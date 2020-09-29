#include "Triggerbot.h"

C_Triggerbot gTrigger;

void C_Triggerbot::Run()
{
	if (const auto& pLocal = gEntCache.pLocal)
	{
		if (ShouldRun(pLocal))
		{
			if (const auto& pEntity = gEntCache.pCrossEnt)
			{
				if (IsValid(pEntity, pLocal))
					Attack();
			}
		}
	}
}

bool C_Triggerbot::ShouldRun(C_BaseEntity* pLocal)
{
	if (!Core::Vars::Trigger::Active || !Util::IsKeyDown(Core::Vars::Trigger::nKey)) return false;
	if (Core::Vars::Trigger::WaitForPunch && !pLocal->GetAimPunch().IsZero()) return false;
	if (Core::Vars::Trigger::OnlyOnGround && !pLocal->IsOnGround()) return false;

	return true;
}

bool C_Triggerbot::IsValid(C_BaseEntity* pEntity, C_BaseEntity* pLocal)
{
	if (!pEntity) return false;

	auto nClassID = pEntity->GetClassID();

	if (!IsValidEntity(nClassID)) return false;

	if (IsPlayer(nClassID))
	{
		if (pEntity->IsImmune()) return false;
		if (Core::Vars::Trigger::IgnoreTeam && pEntity->GetTeamNum() == pLocal->GetTeamNum()) return false;
		if (Core::Vars::Trigger::IgnoreJumping && !pEntity->IsOnGround()) return false;
	}

	return true;
}

bool C_Triggerbot::IsValidEntity(int nClassID)
{
	switch (nClassID)
	{
		case CCSPlayer:	if (Core::Vars::Trigger::Players) return true; break;
		case CChicken: if (Core::Vars::Trigger::Chickens) return true; break;
		default: break;
	}

	return false;
}

bool C_Triggerbot::IsPlayer(int nClassID)
{
	return (nClassID == CCSPlayer);
}

//TODO: This is quite stupid
void C_Triggerbot::Attack()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	std::this_thread::sleep_for(std::chrono::milliseconds(Util::RandInt(1, 25)));
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}