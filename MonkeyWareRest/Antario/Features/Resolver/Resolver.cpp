#include "Resolver.h"
#include "..\Aimbot\Aimbot.h"
#include "..\Aimbot\Autowall.h"
#include "..\Aimbot\LagComp.h"
#include "..\..\Utils\Utils.h"
#include "..\..\SDK\IVEngineClient.h"
#include "..\..\SDK\Hitboxes.h"
#include "..\..\SDK\PlayerInfo.h"
#include "..\..\Utils\Math.h"
#include "..\..\Menu\Menu.h"
#include "..\..\Menu\config.h"
#include "../../SDK/vector2d.h"
Resolver g_Resolver;

void Resolver::AnimationFix(C_BaseEntity* pEnt)
{
	if (pEnt == Globals::LocalPlayer) {
		pEnt->ClientAnimations(true);
		auto player_animation_state = pEnt->AnimState();
		player_animation_state->m_flLeanAmount = 20;
		player_animation_state->m_flCurrentTorsoYaw += 15;
		pEnt->UpdateClientAnimation();
		pEnt->SetAbsAngles(Vector(0, player_animation_state->m_flGoalFeetYaw, 0));
		pEnt->ClientAnimations(false);
	}
	else {
		auto player_index = pEnt->EntIndex() - 1;

		pEnt->ClientAnimations(true);

		auto old_curtime = g_pGlobalVars->curtime;
		auto old_frametime = g_pGlobalVars->frametime;

		g_pGlobalVars->curtime = pEnt->GetSimulationTime();
		g_pGlobalVars->frametime = g_pGlobalVars->intervalPerTick;

		auto player_animation_state = pEnt->AnimState();
		auto player_model_time = reinterpret_cast<int*>(player_animation_state + 112);
		if (player_animation_state != nullptr && player_model_time != nullptr)
			if (*player_model_time == g_pGlobalVars->framecount)
				*player_model_time = g_pGlobalVars->framecount - 1;


		pEnt->UpdateClientAnimation();

		g_pGlobalVars->curtime = old_curtime;
		g_pGlobalVars->frametime = old_frametime;

		//pEnt->SetAbsAngles(Vector(0, player_animation_state->m_flGoalFeetYaw, 0));

		pEnt->ClientAnimations(false);
	}
	
}
void Resolver::ResolverPoints()
{
	if (Globals::FreeStandPoints.size() > 0)
		Globals::FreeStandPoints.clear();

	if (!c_config::get().aimbot_resolver)
		return;

	auto pLocalEnt = Globals::LocalPlayer;

	if (!pLocalEnt)
		return;

	if (!pLocalEnt->IsAlive())
		return;

	if (!pLocalEnt->GetActiveWeapon())
		return;

	for (int index = 1; index < MAX_NETWORKID_LENGTH; ++index)
	{
		C_BaseEntity* pPlayerEntity = g_pEntityList->GetClientEntity(index);

		if (!pPlayerEntity
			|| !pPlayerEntity->IsAlive()
			|| !pPlayerEntity->IsPlayer()
			|| pLocalEnt->EntIndex() == index
			|| pPlayerEntity->IsDormant()
			|| pLocalEnt->GetTeam() == pPlayerEntity->GetTeam()
			|| g_LagComp.PlayerRecord[index].empty())
		{
			continue;
		}

		bUseFreestandAngle[index] = false;

		//	if ( !bUseFreestandAngle[ index ] )
		{
			bool Autowalled = false, HitSide1 = false, HitSide2 = false;

			float angToLocal = g_Math.CalcAngle(pLocalEnt->GetVecOrigin(), pPlayerEntity->GetVecOrigin()).y;
			Vector ViewPoint = pLocalEnt->GetVecOrigin() + Vector(0, 0, 80);

			vec2_t Side1 = vec2_t((40 * sin(DEG2RAD(angToLocal))), (40 * cos(DEG2RAD(angToLocal))));
			vec2_t Side2 = vec2_t((40 * sin(DEG2RAD(angToLocal + 180))), (40 * cos(DEG2RAD(angToLocal + 180))));

			vec2_t Side3 = vec2_t((-60 * sin(DEG2RAD(angToLocal))), (60 * cos(DEG2RAD(angToLocal))));
			vec2_t Side4 = vec2_t((-60 * sin(DEG2RAD(angToLocal + 180))), (60 * cos(DEG2RAD(angToLocal + 180))));

			Vector Origin = pPlayerEntity->GetVecOrigin();

			vec2_t OriginLeftRight[] = { vec2_t(Side1.x, Side1.y), vec2_t(Side2.x, Side2.y) };

			vec2_t OriginLeftRightLocal[] = { vec2_t(Side3.x, Side3.y), vec2_t(Side4.x, Side4.y) };

			if (!g_Autowall.CanHitFloatingPoint(g_LagComp.PlayerRecord[index][8].m_vecAbsOrigin, pLocalEnt->GetEyePosition()))
			{
				for (int side = 0; side < 2; side++)
				{
					Vector OriginAutowall = Vector(Origin.x + OriginLeftRight[side].x, Origin.y - OriginLeftRight[side].y, g_LagComp.PlayerRecord[index][8].m_vecAbsOrigin.z);
					Vector OriginAutowall2 = Vector(ViewPoint.x + OriginLeftRightLocal[side].x, ViewPoint.y - OriginLeftRightLocal[side].y, ViewPoint.z);

					Globals::FreeStandPoints.push_back(OriginAutowall);

					Globals::FreeStandPoints.push_back(OriginAutowall2);

					if (g_Autowall.CanHitFloatingPoint(OriginAutowall, ViewPoint))
					{
						if (side == 0)
						{
							HitSide1 = true;
							flFreestandAngle[index] = 90;
						}
						else if (side == 1)
						{
							HitSide2 = true;
							flFreestandAngle[index] = -90;
						}

						Autowalled = true;
					}
					else
					{
						for (int side222 = 0; side222 < 2; side222++)
						{
							Vector OriginAutowall222 = Vector(Origin.x + OriginLeftRight[side222].x, Origin.y - OriginLeftRight[side222].y, g_LagComp.PlayerRecord[index][8].m_vecAbsOrigin.z);

							Globals::FreeStandPoints.push_back(OriginAutowall222);

							if (g_Autowall.CanHitFloatingPoint(OriginAutowall222, OriginAutowall2))
							{
								if (side222 == 0)
								{
									HitSide1 = true;
									flFreestandAngle[index] = 90;
								}
								else if (side222 == 1)
								{
									HitSide2 = true;
									flFreestandAngle[index] = -90;
								}

								Autowalled = true;
							}
						}
					}
				}
			}


			if (Autowalled)
			{
				if (HitSide1 && HitSide2)
					bUseFreestandAngle[index] = false;
				else
				{
					bUseFreestandAngle[index] = true;
					flLastFreestandAngle[index] = flFreestandAngle[index];
				}
			}
		}
	}
}
void Resolver::PreResolver(C_AnimState* AnimState, C_BaseEntity* pEntity, bool bShot)
{
	if (!c_config::get().aimbot_resolver)
		return;

	if (!AnimState)
		return;

	if (!pEntity)
		return;

	auto RemapVal = [](float val, float A, float B, float C, float D) -> float
	{
		if (A == B)
			return val >= B ? D : C;
		return C + (D - C) * (val - A) / (B - A);
	};

	int iIndex = pEntity->EntIndex();
	auto pLocalEnt = Globals::LocalPlayer;

	ResolverMode[iIndex] = "r:none";
	static int ResolveInt = 0;
	static int LastResolveMode[MAX_NETWORKID_LENGTH];

	static int iMode[MAX_NETWORKID_LENGTH];

	float flLastResolveYaw[MAX_NETWORKID_LENGTH];

	flGoalFeetYawB[iIndex] = 0.f;
	flLbyB[iIndex] = pEntity->GetLowerBodyYaw();

	int ShotDelta = Globals::MissedShots[iIndex];

	if (pLocalEnt && pLocalEnt->IsAlive() && pLocalEnt != pEntity)
	{
		Vector source = pLocalEnt->GetVecOrigin();
		Vector dest = pEntity->GetVecOrigin();

		float angToLocal = g_Math.NormalizeYaw(g_Math.CalcAngle(source, dest).y);

		float Back = g_Math.NormalizeYaw(angToLocal);

		float Brute = AnimState->m_flGoalFeetYaw;

		if (!isnan(angToLocal) && !isinf(angToLocal) && pEntity != pLocalEnt && pEntity->GetTeam() != pLocalEnt->GetTeam())
		{
			float AntiSide = 0.f;

			float EyeDelta = fabs(g_Math.NormalizeYaw(vOldEyeAng[iIndex].y - pEntity->GetEyeAngles().y));

			if (bUseFreestandAngle[iIndex])
			{
				ResolveInt = 1;

				if (LastResolveMode[iIndex] != ResolveInt)
				{
					Globals::MissedShots[iIndex] = 0;
					ShotDelta = 0;
					LastResolveMode[iIndex] = ResolveInt;
				}

				ResolverMode[iIndex] = "r:smart";
				Brute = g_Math.NormalizeYaw(Back + flLastFreestandAngle[iIndex]);

				if ((ShotDelta % 3) == 2)
				{
					ResolverMode[iIndex] += " bf";
					Brute = g_Math.NormalizeYaw(g_Math.NormalizeYaw(Back + flLastFreestandAngle[iIndex]) + 180.f);
				}
				else
				{
					if (flLastFreestandAngle[iIndex] > 0)
						ResolverMode[iIndex] += " <";
					else
						ResolverMode[iIndex] += " >";
				}

				if (fabs(g_Math.NormalizeYaw(g_Math.NormalizeYaw(Back + flLastFreestandAngle[iIndex]) - pEntity->GetEyeAngles().y)) <= 90.f && fabs(g_Math.NormalizeYaw(g_Math.NormalizeYaw(Back) - pEntity->GetEyeAngles().y)) <= 30.f)
					iMode[iIndex] = 1;
				else
					iMode[iIndex] = 0;
			}
			else if (fabs(g_Math.NormalizeYaw(pEntity->GetEyeAngles().y - Back)) >= 60.f && fabs(g_Math.NormalizeYaw(pEntity->GetEyeAngles().y - g_Math.NormalizeYaw(Back + 180))) >= 60.f && EyeDelta > 50)
			{
				ResolveInt = 2;

				if (LastResolveMode[iIndex] != ResolveInt)
				{
					Globals::MissedShots[iIndex] = 0;
					ShotDelta = 0;
					LastResolveMode[iIndex] = ResolveInt;
				}

				ResolverMode[iIndex] = "r:jitter";

				if (fabs(g_Math.NormalizeYaw(pEntity->GetEyeAngles().y - g_Math.NormalizeYaw(Back))) <= 105.f)
					AntiSide = 0.f;
				else if (fabs(g_Math.NormalizeYaw(pEntity->GetEyeAngles().y - g_Math.NormalizeYaw(Back + 180))) <= 75.f)
					AntiSide = 180.f;

				Brute = g_Math.NormalizeYaw(Back + AntiSide);

				iMode[iIndex] = 0;
			}
			else
			{
				ResolveInt = 3;

				if (LastResolveMode[iIndex] != ResolveInt)
				{
					Globals::MissedShots[iIndex] = 0;
					ShotDelta = 0;
					LastResolveMode[iIndex] = ResolveInt;
				}

				if (iMode[iIndex] == 0)
				{
					ResolverMode[iIndex] = "r:inverse";
					switch (ShotDelta % 2)
					{
					case 0:
						if (g_Math.NormalizeYaw(pEntity->GetEyeAngles().y - Back) > 0.f)
						{
							ResolverMode[iIndex] += " >";
							AntiSide = -90.f;
						}
						else if (g_Math.NormalizeYaw(pEntity->GetEyeAngles().y - Back) < 0.f)
						{
							ResolverMode[iIndex] += " <";
							AntiSide = 90.f;
						}
						break;

					case 1:
						if (g_Math.NormalizeYaw(pEntity->GetEyeAngles().y - Back) > 0.f)
						{
							ResolverMode[iIndex] += " < bf";
							AntiSide = 90.f;
						}
						else if (g_Math.NormalizeYaw(pEntity->GetEyeAngles().y - Back) < 0.f)
						{
							ResolverMode[iIndex] += " > bf";
							AntiSide = -90.f;
						}

						break;
					}
				}
				else if (iMode[iIndex] == 1)
				{
					ResolverMode[iIndex] = "r:center";

					switch (ShotDelta % 2)
					{
					case 0:
						if (fabs(g_Math.NormalizeYaw(pEntity->GetEyeAngles().y - g_Math.NormalizeYaw(Back))) <= 105.f)
						{
							ResolverMode[iIndex] += " ^";
							AntiSide = 0.f;
						}
						else if (fabs(g_Math.NormalizeYaw(pEntity->GetEyeAngles().y - g_Math.NormalizeYaw(Back + 180))) <= 75.f)
						{
							ResolverMode[iIndex] += " v";
							AntiSide = 180.f;
						}

						break;
					case 1:
						if (fabs(g_Math.NormalizeYaw(pEntity->GetEyeAngles().y - g_Math.NormalizeYaw(Back))) <= 105.f)
						{
							ResolverMode[iIndex] += " v bf";
							AntiSide = 180.f;
						}
						else if (fabs(g_Math.NormalizeYaw(pEntity->GetEyeAngles().y - g_Math.NormalizeYaw(Back + 180))) <= 75.f)
						{
							ResolverMode[iIndex] += " ^ bf";
							AntiSide = 0.f;
						}
						break;
					}
				}

				Brute = g_Math.NormalizeYaw(Back + AntiSide);
			}

			//--------------------------------------------------------------------------------------------------------------------

			if (pEntity != pLocalEnt && pEntity->GetTeam() != pLocalEnt->GetTeam() && (pEntity->GetFlags() & FL_ONGROUND))
			{
				if (bShot)
				{
					ResolveInt = 4;
					ResolverMode[iIndex] = "r:shot";

					Brute = vOldEyeAng[iIndex].y;
				}
				else
					flLastResolveYaw[iIndex] = Brute;

				if (fabs(g_Math.NormalizeYaw(pEntity->GetEyeAngles().y - Brute)) > 58.f)
				{
					if (g_Math.NormalizeYaw(Brute - pEntity->GetEyeAngles().y) > 0)
					{
						Brute = g_Math.NormalizeYaw(pEntity->GetEyeAngles().y + 58.f);
					}
					else
					{
						Brute = g_Math.NormalizeYaw(pEntity->GetEyeAngles().y - 58.f);
					}
				}

				AnimState->m_flGoalFeetYaw = Brute;
				flGoalFeetYawB[iIndex] = AnimState->m_flGoalFeetYaw;
				flLbyB[iIndex] = pEntity->GetLowerBodyYaw();
				pEntity->SetLowerBodyYaw(Brute);
			}
		}
	}

	if (!bShot)
		vOldEyeAng[iIndex] = pEntity->GetEyeAngles();
}
void Resolver::PostResolver(C_AnimState* AnimState, C_BaseEntity* pEntity, bool bShot)
{
	if (!c_config::get().aimbot_resolver)
		return;

	if (!AnimState)
		return;

	if (!pEntity)
		return;

	flGoalFeetYaw[pEntity->EntIndex()] = AnimState->m_flGoalFeetYaw;

	int iIndex = pEntity->EntIndex();

	auto pLocalEnt = Globals::LocalPlayer;

	if (!pLocalEnt)
		return;

	if (pEntity != pLocalEnt)
	{
		pEntity->SetLowerBodyYaw(flLbyB[iIndex]);
		if (flGoalFeetYawB[iIndex] != 0.f)
			AnimState->m_flGoalFeetYaw = flGoalFeetYawB[iIndex];
	}
}

float flAngleMod(float flAngle)
{
	return((360.0f / 65536.0f) * ((int32_t)(flAngle * (65536.0f / 360.0f)) & 65535));
}
float ApproachAngle(float target, float value, float speed)
{
	target = flAngleMod(target);
	value = flAngleMod(value);

	float delta = target - value;

	// Speed is assumed to be positive
	if (speed <= 0) // fixed speed
		speed = -speed;

	if (delta < -180)
		delta += 360;
	else if (delta > 180)
		delta -= 360;

	if (delta > speed)
		value += speed;
	else if (delta < -speed)
		value -= speed;
	else
		value = target;

	return value;
}

void update_state(C_AnimState * state, Vector angles) {
	using Fn = void(__vectorcall*)(void *, void *, float, float, float, void *);
	static auto fn = reinterpret_cast<Fn>(Utils::FindSignature("client.dll", "55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 F3 0F 11 54 24"));
	fn(state, nullptr, 0.0f, angles[1], angles[0], nullptr);
}

void HandleBackUpResolve(C_BaseEntity* pEnt) {

	if (!c_config::get().aimbot_resolver)
		return;

	if (pEnt->GetTeam() == Globals::LocalPlayer->GetTeam())
		return;

	const auto player_animation_state = pEnt->AnimState();

	if (!player_animation_state)
		return;

	float m_flLastClientSideAnimationUpdateTimeDelta = fabs(player_animation_state->m_iLastClientSideAnimationUpdateFramecount - player_animation_state->m_flLastClientSideAnimationUpdateTime);

	auto v48 = 0.f;

	if (player_animation_state->m_flFeetSpeedForwardsOrSideWays >= 0.0f)
	{
		v48 = fminf(player_animation_state->m_flFeetSpeedForwardsOrSideWays, 1.0f);
	}
	else
	{
		v48 = 0.0f;
	}

	float v49 = ((player_animation_state->m_flStopToFullRunningFraction * -0.30000001) - 0.19999999) * v48;

	float flYawModifier = v49 + 1.0;

	if (player_animation_state->m_fDuckAmount > 0.0)
	{
		float v53 = 0.0f;

		if (player_animation_state->m_flFeetSpeedUnknownForwardOrSideways >= 0.0)
		{
			v53 = fminf(player_animation_state->m_flFeetSpeedUnknownForwardOrSideways, 1.0);
		}
		else
		{
			v53 = 0.0f;
		}
	}

	float flMaxYawModifier = player_animation_state->pad10[516] * flYawModifier;
	float flMinYawModifier = player_animation_state->pad10[512] * flYawModifier;

	float newFeetYaw = 0.f;

	auto eyeYaw = player_animation_state->m_flEyeYaw;

	auto lbyYaw = player_animation_state->m_flGoalFeetYaw;

	float eye_feet_delta = fabs(eyeYaw - lbyYaw);

	if (eye_feet_delta <= flMaxYawModifier)
	{
		if (flMinYawModifier > eye_feet_delta)
		{
			newFeetYaw = fabs(flMinYawModifier) + eyeYaw;
		}
	}
	else
	{
		newFeetYaw = eyeYaw - fabs(flMaxYawModifier);
	}

	float v136 = fmod(newFeetYaw, 360.0);

	if (v136 > 180.0)
	{
		v136 = v136 - 360.0;
	}

	if (v136 < 180.0)
	{
		v136 = v136 + 360.0;
	}

	player_animation_state->m_flGoalFeetYaw = v136;

	/*static int stored_yaw = 0;

	if (pEnt->GetEyeAnglesPointer()->y != stored_yaw) {
		if ((pEnt->GetEyeAnglesPointer()->y - stored_yaw > 120)) { // Arbitrary high angle value.
			if (pEnt->GetEyeAnglesPointer()->y - stored_yaw > 120) {
				pEnt->GetEyeAnglesPointer()->y = pEnt->GetEyeAnglesPointer()->y - (pEnt->GetEyeAnglesPointer()->y - stored_yaw);
			}

			stored_yaw = pEnt->GetEyeAnglesPointer()->y;
		}
	}*/
	//if (pEnt->GetVelocity().Length2D() > 0.1f)
	//{
	//	player_animation_state->m_flGoalFeetYaw = ApproachAngle(pEnt->GetLowerBodyYaw(), player_animation_state->m_flGoalFeetYaw, (player_animation_state->m_flStopToFullRunningFraction * 20.0f) + 30.0f *player_animation_state->m_flLastClientSideAnimationUpdateTime);
	//}
	//else
	//{
	//	player_animation_state->m_flGoalFeetYaw = ApproachAngle(pEnt->GetLowerBodyYaw(), player_animation_state->m_flGoalFeetYaw, (m_flLastClientSideAnimationUpdateTimeDelta * 100.0f));
	//}
	//if (Globals::MissedShots[pEnt->EntIndex()] > 3) {
	//	switch (Globals::MissedShots[pEnt->EntIndex()] % 4) {
	//	case 0: pEnt->GetEyeAnglesPointer()->y = pEnt->GetEyeAnglesPointer()->y + 45; break;
	//	case 1: pEnt->GetEyeAnglesPointer()->y = pEnt->GetEyeAnglesPointer()->y - 45; break;
	//	case 2: pEnt->GetEyeAnglesPointer()->y = pEnt->GetEyeAnglesPointer()->y - 30; break;
	//	case 3: pEnt->GetEyeAnglesPointer()->y = pEnt->GetEyeAnglesPointer()->y + 30; break;
	//	}
	//}
}

void HandleHits(C_BaseEntity* pEnt)
{
	auto NetChannel = g_pEngine->GetNetChannelInfo();

	if (!NetChannel)
		return;

	static float predTime[65];
	static bool init[65];

	if (Globals::Shot[pEnt->EntIndex()])
	{
		if (init[pEnt->EntIndex()])
		{
			g_Resolver.pitchHit[pEnt->EntIndex()] = pEnt->GetEyeAngles().x;
			predTime[pEnt->EntIndex()] = g_pGlobalVars->curtime + NetChannel->GetAvgLatency(FLOW_INCOMING) + NetChannel->GetAvgLatency(FLOW_OUTGOING) + TICKS_TO_TIME(1) + TICKS_TO_TIME(g_pEngine->GetNetChannel()->m_nChokedPackets);
			init[pEnt->EntIndex()] = false;
		}

		if (g_pGlobalVars->curtime > predTime[pEnt->EntIndex()] && !Globals::Hit[pEnt->EntIndex()])
		{
			Globals::MissedShots[pEnt->EntIndex()] += 1;
			Globals::Shot[pEnt->EntIndex()] = false;
		}
		else if (g_pGlobalVars->curtime <= predTime[pEnt->EntIndex()] && Globals::Hit[pEnt->EntIndex()])
			Globals::Shot[pEnt->EntIndex()] = false;

	}
	else
		init[pEnt->EntIndex()] = true;

	Globals::Hit[pEnt->EntIndex()] = false;
}

void Resolver::OnCreateMove() // cancer v2
{
	if (!c_config::get().aimbot_resolver)
		return;

	if (!Globals::LocalPlayer->IsAlive())
		return;

	if (!Globals::LocalPlayer->GetActiveWeapon() || Globals::LocalPlayer->IsKnifeorNade())
		return;

	ResolverPoints();
}

void Resolver::FrameStage(ClientFrameStage_t stage)
{
	if (!Globals::LocalPlayer || !g_pEngine->IsInGame())
		return;

	static bool  wasDormant[65];

	for (int i = 1; i < g_pEngine->GetMaxClients(); ++i)
	{
		C_BaseEntity* pPlayerEntity = g_pEntityList->GetClientEntity(i);

		if (!pPlayerEntity
			|| !pPlayerEntity->IsAlive())
			continue;
		if (pPlayerEntity->IsDormant())
		{
			wasDormant[i] = true;
			continue;
		}

		if (stage == FRAME_RENDER_START)
		{
			//HandleHits(pPlayerEntity);

			/*C_AnimState* anim = pPlayerEntity->AnimState();
			PostResolver(anim, pPlayerEntity, Globals::Shot[pPlayerEntity->EntIndex()]);*/

			AnimationFix(pPlayerEntity);
			
			
		}

		if (stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
			/*C_AnimState* anim = pPlayerEntity->AnimState();
			PreResolver(anim, pPlayerEntity, Globals::Shot[pPlayerEntity->EntIndex()]);*/
			/*HandleBackUpResolve(pPlayerEntity);*/
		}

		if (stage == FRAME_NET_UPDATE_END && pPlayerEntity != Globals::LocalPlayer)
		{
			auto VarMap = reinterpret_cast<uintptr_t>(pPlayerEntity) + 36;
			auto VarMapSize = *reinterpret_cast<int*>(VarMap + 20);

			for (auto index = 0; index < VarMapSize; index++)
				*reinterpret_cast<uintptr_t*>(*reinterpret_cast<uintptr_t*>(VarMap) + index * 12) = 0;
		}

		wasDormant[i] = false;
	}
}