#include "EntityCache.h"

C_EntityCache gEntCache;

void C_EntityCache::Fill()
{
	auto _pLocal = gEngine.GetLocalPlayer();

	if (_pLocal && _pLocal->IsInValidTeam())
	{
		pLocal = _pLocal;
		pCrossEnt = gEngine.GetEntity((pLocal->GetCrosshairID() - 1));

		for (int n = 0; n < gEngine.GetMaxUsedServerIndex(); n++)
		{
			auto pEntity = gEngine.GetEntity(n);

			if (!pEntity || !pEntity->IsAlive() || pEntity->IsDormant() || pEntity == pLocal)
				continue;

			switch (pEntity->GetClassID())
			{
				case CCSPlayer:
				{
					Groups[GroupType_t::PLAYERS_ALL].push_back(pEntity);
					Groups[pEntity->GetTeamNum() != pLocal->GetTeamNum() ? GroupType_t::PLAYERS_ENEMIES : GroupType_t::PLAYERS_TEAMMATES].push_back(pEntity);
					break;
				}

				case CChicken:
				{
					Groups[GroupType_t::CHICKEN_ALL].push_back(pEntity);
					break;
				}
			}
		}
	}
}

void C_EntityCache::Clear()
{
	pLocal = nullptr;
	pCrossEnt = nullptr;

	for (auto& group : Groups)
		group.second.clear();
}

const std::vector<C_BaseEntity*>& C_EntityCache::GetGroup(const GroupType_t& group)
{
	return Groups[group];
}