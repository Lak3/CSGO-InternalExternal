#include "Radar.h"

C_Radar gRadar;

void C_Radar::Run()
{
	if (ShouldRun())
	{
		for (auto& pEntity : gEntCache.GetGroup(GroupType_t::PLAYERS_ENEMIES))
		{
			if (!pEntity->IsSpotted())
				pEntity->SetSpotted(true);
		}
	}
}

bool C_Radar::ShouldRun()
{
	if (!Core::Vars::Radar::Active)
		return false;

	return true;
}