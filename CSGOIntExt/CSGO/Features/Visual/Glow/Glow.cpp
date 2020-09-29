#include "Glow.h"

C_Glow gGlow;

static constexpr fColor_t clrTer = { 0.4f, 0.4f, 0.1f, 1.0f };
static constexpr fColor_t clrCT = { 0.1f, 0.4f, 0.4f, 1.0f };

void C_Glow::Run()
{
	if (ShouldRun())
	{
		if (const auto dwGlowBase = gEngine.GetGlowManager())
		{
			if (Core::Vars::Glow::Players)
			{
				const auto Players = 
				gEntCache.GetGroup(Core::Vars::Glow::IgnoreTeam ? GroupType_t::PLAYERS_ENEMIES : GroupType_t::PLAYERS_ALL);

				for (const auto& pEntity : Players)
					ForceGlow(dwGlowBase, pEntity->GetGlowIndex(), pEntity->GetTeamNum() == 3 ? clrCT : clrTer);
			}
		}
	}
}

void C_Glow::ForceGlow(DWORD dwBase, int nIndex, fColor_t clrGlow)
{
	ReadProcessMemory(gMem.m_hProcess, reinterpret_cast<LPCVOID>((dwBase + (nIndex * 0x38) + 0x4)), &m_sGlowObj, sizeof(m_sGlowObj), NULL);
	m_sGlowObj.r = clrGlow.r;
	m_sGlowObj.g = clrGlow.g;
	m_sGlowObj.b = clrGlow.b;
	m_sGlowObj.a = clrGlow.a;
	//m_sGlowObj.m_nGlowStyle = 0; //Should be 0 by default NOTE: See what to do with 3
	m_sGlowObj.m_bRenderWhenOccluded = true;
	m_sGlowObj.m_bRenderWhenUnoccluded = false;
	WriteProcessMemory(gMem.m_hProcess, reinterpret_cast<LPVOID>((dwBase + (nIndex * 0x38) + 0x4)), &m_sGlowObj, sizeof(m_sGlowObj), NULL);
}

bool C_Glow::ShouldRun()
{
	if (!Core::Vars::Glow::Active)
		return false;

	return true;
}