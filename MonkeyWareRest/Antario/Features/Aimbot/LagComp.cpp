#include "LagComp.h"
#include "Aimbot.h"
#include "..\..\Utils\Utils.h"
#include "..\..\SDK\IVEngineClient.h"
#include "..\..\SDK\PlayerInfo.h"
#include "..\..\SDK\ICvar.h"
#include "..\..\Utils\Math.h"
#include "..\..\SDK\Hitboxes.h"
#include "..\..\Menu\Menu.h"

LagComp g_LagComp;

float LagComp::LerpTime()
{
	int ud_rate = g_pCvar->FindVar("cl_updaterate")->GetInt();
	ConVar* minupdate = g_pCvar->FindVar("sv_minupdaterate");
	ConVar* maxupdate = g_pCvar->FindVar("sv_maxupdaterate");

	if (minupdate && maxupdate)
		ud_rate = maxupdate->GetInt();

	float ratio = g_pCvar->FindVar("cl_interp")->GetFloat();

	if (ratio == 0)
		ratio = 1.0f;

	float lerp = g_pCvar->FindVar("cl_interp")->GetFloat();
	ConVar* cmin = g_pCvar->FindVar("sv_client_min_interp_ratio");
	ConVar* cmax = g_pCvar->FindVar("sv_client_max_interp_ratio");
	ratio = clamp(ratio, cmin->GetFloat(), cmax->GetFloat());
	return max(g_pCvar->FindVar("cl_interp")->GetFloat(), (ratio / ((minupdate->GetFloat()) ? maxupdate->GetFloat() : ud_rate)));
}

bool LagComp::ValidTick(float simtime)
{
	INetChannelInfo* net_channel = g_pEngine->GetNetChannelInfo();

	if (!net_channel)
		return false;

	float correct = 0;
	correct += net_channel->GetLatency(0);
	correct += net_channel->GetLatency(1);
	correct += LerpTime();

	clamp(correct, 0.f, g_pCvar->FindVar("sv_maxunlag")->GetFloat());

	float delta_time = correct - (TICKS_TO_TIME(Globals::LocalPlayer->GetTickBase()) - simtime);

	float time_limit = 0.2f;

	std::clamp(time_limit, 0.001f, 0.2f);

	return fabsf(delta_time) <= time_limit;
}

void LagComp::StoreRecord(C_BaseEntity* pEnt)
{
	PlayerRecords Setup;

	static float ShotTime[65];
	static float OldSimtime[65];

	if (pEnt != Globals::LocalPlayer)
		pEnt->FixSetupBones(g_Aimbot.Matrix[pEnt->EntIndex()]);

	if (PlayerRecord[pEnt->EntIndex()].size() == 0)
	{
		Setup.Velocity = abs(pEnt->GetVelocity().Length2D());

		Setup.SimTime = pEnt->GetSimulationTime();

		memcpy(Setup.Matrix, g_Aimbot.Matrix[pEnt->EntIndex()], (sizeof(matrix3x4_t) * 128));

		Setup.Shot = false;

		PlayerRecord[pEnt->EntIndex()].push_back(Setup);
	}

	if (OldSimtime[pEnt->EntIndex()] != pEnt->GetSimulationTime())
	{
		Setup.Velocity = abs(pEnt->GetVelocity().Length2D());

		Setup.SimTime = pEnt->GetSimulationTime();

		Setup.m_vecAbsOrigin = pEnt->GetAbsOrigin();

		if (pEnt == Globals::LocalPlayer)
			pEnt->FixSetupBones(g_Aimbot.Matrix[pEnt->EntIndex()]);

		memcpy(Setup.Matrix, g_Aimbot.Matrix[pEnt->EntIndex()], (sizeof(matrix3x4_t) * 128));

		if (pEnt->GetActiveWeapon() && !pEnt->IsKnifeorNade())
		{
			if (ShotTime[pEnt->EntIndex()] != pEnt->GetActiveWeapon()->GetLastShotTime())
			{
				Setup.Shot = true;
				ShotTime[pEnt->EntIndex()] = pEnt->GetActiveWeapon()->GetLastShotTime();
			}
			else
				Setup.Shot = false;
		}
		else
		{
			Setup.Shot = false;
			ShotTime[pEnt->EntIndex()] = 0.f;
		}

		PlayerRecord[pEnt->EntIndex()].push_back(Setup);

		OldSimtime[pEnt->EntIndex()] = pEnt->GetSimulationTime();
	}


	ShotTick[pEnt->EntIndex()] = -1;

	if (PlayerRecord[pEnt->EntIndex()].size() > 0)
		for (int tick = 0; tick < PlayerRecord[pEnt->EntIndex()].size(); tick++)
			if (!ValidTick(TIME_TO_TICKS(PlayerRecord[pEnt->EntIndex()].at(tick).SimTime)))
				PlayerRecord[pEnt->EntIndex()].erase(PlayerRecord[pEnt->EntIndex()].begin() + tick);
			else if (PlayerRecord[pEnt->EntIndex()].at(tick).Shot)
				ShotTick[pEnt->EntIndex()] = tick; // gets the newest shot tick
}

void LagComp::ClearRecords(int i)
{
	if (PlayerRecord[i].size() > 0)
	{
		for (int tick = 0; tick < PlayerRecord[i].size(); tick++)
		{
			PlayerRecord[i].erase(PlayerRecord[i].begin() + tick);
		}
	}
}

template<class T, class U>
T LagComp::clamp(T in, U low, U high)
{
	if (in <= low)
		return low;

	if (in >= high)
		return high;

	return in;
}