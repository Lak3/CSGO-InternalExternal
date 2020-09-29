#pragma once

#include "../../SDK.h"

enum struct GroupType_t
{
	PLAYERS_ALL,
	PLAYERS_ENEMIES,
	PLAYERS_TEAMMATES,

	CHICKEN_ALL
};

class C_BaseEntity;
class C_EntityCache
{
public:
	void Fill();
	void Clear();

	C_BaseEntity* pLocal;
	C_BaseEntity* pCrossEnt;
	const std::vector<C_BaseEntity*>& GetGroup(const GroupType_t& group);

private:
	std::map<GroupType_t, std::vector<C_BaseEntity*>> Groups;
};

extern C_EntityCache gEntCache;