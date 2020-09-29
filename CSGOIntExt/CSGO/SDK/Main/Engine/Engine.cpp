#include "Engine.h"

C_Engine gEngine;

bool C_Engine::TrainingSoftware()
{
	if (gMem.GetProcess(Core::String::szSteam) || gMem.GetProcess(Core::String::szCSGO))
		return Util::ErrorBox(Core::String::szFailSteam);

	Util::InfoBox(Core::String::szInfoWaiting);

	while (!gMem.GetProcess(Core::String::szCSGO))
		std::this_thread::sleep_for(std::chrono::seconds(1));

	while (!Core::GameWindow)
		Core::GameWindow = Util::FindWind(Core::String::szCSGOWindow);

	if (!gMem.m_hProcess || !gMem.m_dwPID)
		return Util::ErrorBox(Core::String::szFailHandle);

	//Once we get client, engine should be ready too, so I'll just wait for client.
	while (!Core::Client)
	{
		Core::Client = gMem.GetModule(Core::String::szClientDLL);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	Core::Engine = gMem.GetModule(Core::String::szEngineDLL);

	if (!Core::Client || !Core::Engine)
		return Util::ErrorBox(Core::String::szFailModules);

	return true;
}

void C_Engine::SetViewAngles(Vec3 vAngle)
{
	gMem.Write<Vec3>(GetClientState() + Core::Offsets::dwClientState_ViewAngles, vAngle);
}

int C_Engine::GetMaxUsedServerIndex()
{
	return gMem.Read<int>(Core::Client + Core::Offsets::dwEntityList + 0x24);
}

bool C_Engine::IsGameFocused()
{
	return (GetForegroundWindow() == Core::GameWindow);
}

C_BaseEntity* C_Engine::GetLocalPlayer()
{
	return gMem.Read<C_BaseEntity*>(Core::Client + Core::Offsets::dwLocalPlayer);
}

C_BaseEntity* C_Engine::GetEntity(int nIndex)
{
	return gMem.Read<C_BaseEntity*>(Core::Client + Core::Offsets::dwEntityList + (nIndex * 0x10));
}

DWORD C_Engine::GetClientState()
{
	return gMem.Read<DWORD>(Core::Engine + Core::Offsets::dwClientState);
}

DWORD C_Engine::GetGlowManager()
{
	return gMem.Read<DWORD>(Core::Client + Core::Offsets::dwGlowObjectManager);
}

Vec3 C_Engine::GetViewAngles()
{
	return gMem.Read<Vec3>(GetClientState() + Core::Offsets::dwClientState_ViewAngles);
}