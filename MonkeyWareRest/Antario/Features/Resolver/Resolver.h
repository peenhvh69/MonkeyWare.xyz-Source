#pragma once
#include "..\..\Utils\GlobalVars.h"
#include "..\..\SDK\CGlobalVarsBase.h"
#include "..\..\SDK\IClientMode.h"
#include <deque>

#define MAX_NETWORKID_LENGTH 65

class Resolver
{
public:
	bool UseFreestandAngle[65];
	float FreestandAngle[65];

	float pitchHit[65];

	void OnCreateMove();
	void Yaw(C_BaseEntity * ent);
	void FrameStage(ClientFrameStage_t stage);
private:
	void AnimationFix(C_BaseEntity* pEnt);


	void ResolverPoints(); // still my old reverse freestanding
	void PreResolver(C_AnimState* AnimState, C_BaseEntity* pEntity, bool bShot);
	void PostResolver(C_AnimState* AnimState, C_BaseEntity* pEntity, bool bShot);


	float flOldGoalFeetYaw[MAX_NETWORKID_LENGTH];
	float flGoalFeetYaw[MAX_NETWORKID_LENGTH];
	Vector vOldEyeAng[MAX_NETWORKID_LENGTH];
	bool bUseFreestandAngle[MAX_NETWORKID_LENGTH];
	float flFreestandAngle[MAX_NETWORKID_LENGTH];
	float flLastFreestandAngle[MAX_NETWORKID_LENGTH];
	float flGoalFeetYawB[MAX_NETWORKID_LENGTH];
	float flLbyB[MAX_NETWORKID_LENGTH];
	std::string ResolverMode[MAX_NETWORKID_LENGTH];
};
extern Resolver g_Resolver;