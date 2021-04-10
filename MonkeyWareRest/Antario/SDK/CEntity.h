﻿
#pragma once
#include "Definitions.h"
#include "IClientUnknown.h"
#include "IClientEntityList.h"
#include "CInput.h"
#include "..\Utils\Utils.h"
#include "..\Utils\NetvarManager.h"
#include "CGlobalVarsBase.h"
class viewmodel_t;
#define NETVAR2(type, name, table, netvar)                           \
    type& name##() const {                                          \
        static int _##name = g_pNetvars->GetOffset(table, netvar);     \
        return *(type*)((uintptr_t)this + _##name);                 \
	}

#define PNETVAR2(type, name, table, netvar)                           \
    type* name##() const {                                          \
        static int _##name = g_pNetvars->GetOffset(table, netvar);     \
        return (type*)((uintptr_t)this + _##name);                 \
	}

#define ANETVAR2(type, funcname, num, table, netvar) std::array<type, num>& funcname() \
{ \
	static int _##name = g_pNetvars->GetOffset(table, netvar); \
	return *reinterpret_cast<std::array<type, num>*>( uintptr_t( this ) + _##name ); \
}

// class predefinition
class C_BaseCombatWeapon;

class C_AnimState
{
public:
	char pad[4];
	char bUnknown; //0x4
	char pad2[91];
	void* pBaseEntity; //0x60
	void* pActiveWeapon; //0x64
	void* pLastActiveWeapon; //0x68
	float m_flLastClientSideAnimationUpdateTime; //0x6C
	int m_iLastClientSideAnimationUpdateFramecount; //0x70
	float m_flEyePitch; //0x74
	float m_flEyeYaw; //0x78
	float m_flPitch; //0x7C
	float m_flGoalFeetYaw; //0x80
	float m_flCurrentFeetYaw; //0x84
	float m_flCurrentTorsoYaw; //0x88
	float m_flUnknownVelocityLean; //0x8C //changes when moving/jumping/hitting ground
	float m_flLeanAmount; //0x90
	char pad4[4]; //NaN
	float m_flFeetCycle; //0x98 0 to 1
	float m_flFeetYawRate; //0x9C 0 to 1
	float m_fUnknown2;
	float m_fDuckAmount; //0xA4
	float m_fLandingDuckAdditiveSomething; //0xA8
	float m_fUnknown3; //0xAC
	Vector m_vOrigin; //0xB0, 0xB4, 0xB8
	Vector m_vLastOrigin; //0xBC, 0xC0, 0xC4
	float m_vVelocityX; //0xC8
	float m_vVelocityY; //0xCC
	char pad5[4];
	float m_flUnknownFloat1; //0xD4 Affected by movement and direction
	char pad6[8];
	float m_flUnknownFloat2; //0xE0 //from -1 to 1 when moving and affected by direction
	float m_flUnknownFloat3; //0xE4 //from -1 to 1 when moving and affected by direction
	float m_unknown; //0xE8
	float speed_2d; //0xEC
	float flUpVelocity; //0xF0
	float m_flSpeedNormalized; //0xF4 //from 0 to 1
	float m_flFeetSpeedForwardsOrSideWays; //0xF8 //from 0 to 2. something  is 1 when walking, 2.something when running, 0.653 when crouch walking
	float m_flFeetSpeedUnknownForwardOrSideways; //0xFC //from 0 to 3. something
	float m_flTimeSinceStartedMoving; //0x100
	float m_flTimeSinceStoppedMoving; //0x104
	unsigned char m_bOnGround; //0x108
	unsigned char m_bInHitGroundAnimation; //0x109
	char pad7[10];
	float m_flLastOriginZ; //0x114
	float m_flHeadHeightOrOffsetFromHittingGroundAnimation; //0x118 from 0 to 1, is 1 when standing
	float m_flStopToFullRunningFraction; //0x11C from 0 to 1, doesnt change when walking or crouching, only running
	char pad8[4]; //NaN
	float m_flUnknownFraction; //0x124 affected while jumping and running, or when just jumping, 0 to 1
	char pad9[4]; //NaN
	float m_flUnknown3;
	char pad10[528];
};

struct c_animstate {

	char pad_0x0000[0x18]; //0x0000
	float anim_update_timer; //0x0018 
	char pad_0x001C[0xC]; //0x001C
	float started_moving_time; //0x0028 
	float last_move_time; //0x002C 
	char pad_0x0030[0x10]; //0x0030
	float last_lby_time; //0x0040 
	char pad_0x0044[0x8]; //0x0044
	float run_amount; //0x004C 
	char pad_0x0050[0x10]; //0x0050
	void *entity; //0x0060 
	__int32 active_weapon; //0x0064 
	__int32 last_active_weapon; //0x0068 
	float last_client_side_animation_update_time; //0x006C 
	__int32 last_client_side_animation_update_framecount; //0x0070 
	float eye_timer; //0x0074 
	float eye_angles_y; //0x0078 
	float eye_angles_x; //0x007C 
	float goal_feet_yaw; //0x0080 
	float current_feet_yaw; //0x0084 
	float torso_yaw; //0x0088 
	float last_move_yaw; //0x008C 
	float lean_amount; //0x0090 
	char pad_0x0094[0x4]; //0x0094
	float feet_cycle; //0x0098 
	float feet_yaw_rate; //0x009C 
	char pad_0x00A0[0x4]; //0x00A0
	float duck_amount; //0x00A4 
	float landing_duck_amount; //0x00A8 
	char pad_0x00AC[0x4]; //0x00AC
	Vector current_origin;
	Vector last_origin;
	float velocity_x; //0x00C8 
	float velocity_y; //0x00CC 
	char pad_0x00D0[0x10]; //0x00D0
	float move_direction_1; //0x00E0 
	float move_direction_2; //0x00E4 
	char pad_0x00E8[0x4]; //0x00E8
	float m_velocity; //0x00EC 
	float jump_fall_velocity; //0x00F0 
	float clamped_velocity; //0x00F4 
	float feet_speed_forwards_or_sideways; //0x00F8 
	float feet_speed_unknown_forwards_or_sideways; //0x00FC 
	float last_time_started_moving; //0x0100 
	float last_time_stopped_moving; //0x0104 
	bool on_ground; //0x0108 
	bool hit_in_ground_animation; //0x010C 
	char pad_0x0110[0x4]; //0x0110
	float last_origin_z; //0x0114 
	float head_from_ground_distance_standing; //0x0118 
	float stop_to_full_running_fraction; //0x011C 
	char pad_0x0120[0x14]; //0x0120
	__int32 is_not_moving; //0x0134 
	char pad_0x0138[0x20]; //0x0138
	float last_anim_update_time; //0x0158 
	float moving_direction_x; //0x015C 
	float moving_direction_y; //0x0160 
	float moving_direction_z; //0x0164 
	char pad_0x0168[0x44]; //0x0168
	__int32 started_moving; //0x01AC 
	char pad_0x01B0[0x8]; //0x01B0
	float lean_yaw; //0x01B8 
	char pad_0x01BC[0x8]; //0x01BC
	float poses_speed; //0x01C4 
	char pad_0x01C8[0x8]; //0x01C8
	float ladder_speed; //0x01D0 
	char pad_0x01D4[0x8]; //0x01D4
	float ladder_yaw; //0x01DC 
	char pad_0x01E0[0x8]; //0x01E0
	float some_pose; //0x01E8 
	char pad_0x01EC[0x14]; //0x01EC
	float body_yaw; //0x0200 
	char pad_0x0204[0x8]; //0x0204
	float body_pitch; //0x020C 
	char pad_0x0210[0x8]; //0x0210
	float death_yaw; //0x0218 
	char pad_0x021C[0x8]; //0x021C
	float stand; //0x0224 
	char pad_0x0228[0x8]; //0x0228
	float jump_fall; //0x0230 
	char pad_0x0234[0x8]; //0x0234
	float aim_blend_stand_idle; //0x023C 
	char pad_0x0240[0x8]; //0x0240
	float aim_blend_crouch_idle; //0x0248 
	char pad_0x024C[0x8]; //0x024C
	float strafe_yaw; //0x0254 
	char pad_0x0258[0x8]; //0x0258
	float aim_blend_stand_walk; //0x0260 
	char pad_0x0264[0x8]; //0x0264
	float aim_blend_stand_run; //0x026C 
	char pad_0x0270[0x8]; //0x0270
	float aim_blend_crouch_walk; //0x0278 
	char pad_0x027C[0x8]; //0x027C
	float move_blend_walk; //0x0284 
	char pad_0x0288[0x8]; //0x0288
	float move_blend_run; //0x0290 
	char pad_0x0294[0x8]; //0x0294
	float move_blend_crouch; //0x029C 
	char pad_0x02A0[0x4]; //0x02A0
	float speed; //0x02A4 
	__int32 moving_in_any_direction; //0x02A8 
	float acceleration; //0x02AC 
	char pad_0x02B0[0x74]; //0x02B0
	float crouch_height; //0x0324 
	__int32 is_full_crouched; //0x0328 
	char pad_0x032C[0x4]; //0x032C
	float velocity_subtract_x; //0x0330 
	float velocity_subtract_y; //0x0334 
	float velocity_subtract_z; //0x0338 
	float standing_head_height; //0x033C 
	char pad_0x0340[0x4]; //0x0340
}; //Size=0x0344

class AnimationLayer {
public:
	char  pad_0000[20];
	// These should also be present in the padding, don't see the use for it though
	//float	m_flLayerAnimtime;
	//float	m_flLayerFadeOuttime;
	unsigned int m_nOrder; //0x0014
	unsigned int m_nSequence; //0x0018
	float m_flPrevCycle; //0x001C
	float m_flWeight; //0x0020
	float m_flWeightDeltaRate; //0x0024
	float m_flPlaybackRate; //0x0028
	float m_flCycle; //0x002C
	void *m_pOwner; //0x0030 // player's thisptr
	char  pad_0038[4]; //0x0034
}; //Size: 0x0038
#include <iostream>
#include <cassert>

#define ONETVAR( funcname, name, table, extra, type ) \
    __forceinline auto& funcname( ) { \
    	static std::ptrdiff_t offset = g_pNetvars->GetOffset(  table ,  name  ); \
    	return GetValue< type >( offset + extra ); \
    }

#define dwThis (DWORD)this
#define NETVAR(type,offset) *(type*)(dwThis + offset)

class C_BaseEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable
{
private:
	template<class T>
	T GetPointer(const int offset)
	{
		return reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(this) + offset);
	}
	// To get value from the pointer itself
	template<class T>
	T GetValue(const int offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(this) + offset);
	}

	template <typename T>
	T& SetValue(uintptr_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset);
	}

public:

	C_AnimState *AnimState()
	{
		return *reinterpret_cast<C_AnimState**>(uintptr_t(this) + 0x3914);
	}

	float m_fDuckSpeed()
	{
		//DT_BasePlayer
		static int m_flDuckSpeed = g_pNetvars->GetOffset("DT_BasePlayer", "m_flDuckSpeed");
		return *(float*)((uintptr_t)this + (uintptr_t)m_flDuckSpeed);
	}

	c_animstate *AnimStatev2()
	{
		return *reinterpret_cast<c_animstate**>(uintptr_t(this) + 0x3914);
	}

	
	AnimationLayer *AnimOverlays()
	{
		return *reinterpret_cast<AnimationLayer**>(uintptr_t(this) + 0x2990);
	}

	float * m_flPoseParameter() {
		static int offset = g_pNetvars->GetOffset("DT_BaseAnimating", "m_flPoseParameter");

		return reinterpret_cast<float *>(uintptr_t(this) + offset);
	}

	AnimationLayer *GetAnimOverlays4()
	{
		// to find offset: use 9/12/17 dll
		// sig: 55 8B EC 51 53 8B 5D 08 33 C0
		return *(AnimationLayer**)((DWORD)this + 0x2990);
	}

	AnimationLayer *GetAnimOverlay4(int i)
	{
		if (i < 16)
			return &GetAnimOverlays4()[i];
	}
	int GetNumAnimOverlays()
	{
		return *(int*)((DWORD)this + 0x298C);
	}
	int NumOverlays()
	{
		return 15;
	}

	void UpdateClientAnimation()
	{
		Utils::GetVFunc<void(__thiscall*)(void*)>(this, 223)(this);
	}
	template <typename T>
	T& read(uintptr_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset);
	}

	std::array<float, 24>* get_ragdoll_pos()
	{
		return read<std::array<float, 24>*>(g_pNetvars->GetOffset("DT_Ragdoll", "m_ragPos"));
	}


	void ClientAnimations(bool value)
	{
		static int m_bClientSideAnimation = g_pNetvars->GetOffset("DT_BaseAnimating", "m_bClientSideAnimation");
		*reinterpret_cast<bool*>(uintptr_t(this) + m_bClientSideAnimation) = value;
	}

	int GetSequence()
	{
		static int m_nSequence = g_pNetvars->GetOffset("DT_BaseAnimating", "m_nSequence");
		return GetValue<int>(m_nSequence);
	}

	void SetSequence(int Sequence)
	{
		static int m_nSequence = g_pNetvars->GetOffset("DT_BaseAnimating", "m_nSequence");
		*reinterpret_cast<int*>(uintptr_t(this) + m_nSequence) = Sequence;
	}
	int Money()
	{
		static int m_ArmorValue = g_pNetvars->GetOffset("DT_CSPlayer", "m_iAccount");
		return GetValue<int>(m_ArmorValue);
	}
	void SimulatedEveryTick(bool value)
	{
		static int m_bSimulatedEveryTick = g_pNetvars->GetOffset("DT_BaseEntity", "m_bSimulatedEveryTick");
		*reinterpret_cast<bool*>(uintptr_t(this) + m_bSimulatedEveryTick) = value;
	}

	void SetAbsAngles(Vector angles);
	void SetAbsOrigin(Vector origin);

	void InvalidateBoneCache();

	Vector GetAbsOrigin()
	{
		return Utils::GetVFunc<Vector&(__thiscall*)(void*)>(this, 10)(this);
	}

	Vector& GetAbsAngles()
	{
		typedef Vector& (__thiscall* OriginalFn)(void*);
		return ((OriginalFn)Utils::GetVFunc<OriginalFn>(this, 11))(this);
	}

	void SetAbsVelocity(Vector velocity);

	C_BaseCombatWeapon* GetActiveWeapon()
	{
		static int m_hActiveWeapon = g_pNetvars->GetOffset("DT_BaseCombatCharacter", "m_hActiveWeapon");
		const auto weaponData = GetValue<CBaseHandle>(m_hActiveWeapon);
		return reinterpret_cast<C_BaseCombatWeapon*>(g_pEntityList->GetClientEntityFromHandle(weaponData));
	}

	int GetActiveWeaponIndex()
	{
		static int m_hActiveWeapon = g_pNetvars->GetOffset("DT_BaseCombatCharacter", "m_hActiveWeapon");
		return *reinterpret_cast<int*>(uintptr_t(this) + m_hActiveWeapon) & 0xFFF; //m_hActiveWeapon
	}

	int GetTeam()
	{
		static int m_iTeamNum = g_pNetvars->GetOffset("DT_BaseEntity", "m_iTeamNum");
		return GetValue<int>(m_iTeamNum);
	}

	float GetFireReadyTime()
	{
		static int m_flPostponeFireReadyTime = g_pNetvars->GetOffset("DT_WeaponCSBase", "m_flPostponeFireReadyTime");
		return GetValue<float>(m_flPostponeFireReadyTime);
	}

	EntityFlags GetFlags()
	{
		static int m_fFlags = g_pNetvars->GetOffset("DT_BasePlayer", "m_fFlags");
		return GetValue<EntityFlags>(m_fFlags);
	}

	void SetFlags(int offset)
	{
		static int m_fFlags = g_pNetvars->GetOffset("DT_BasePlayer", "m_fFlags");
		*reinterpret_cast<int*>(uintptr_t(this) + m_fFlags) = offset;
	}

	MoveType_t GetMoveType()
	{
		static int m_Movetype = g_pNetvars->GetOffset("DT_BaseEntity", "m_nRenderMode") + 1;
		return GetValue<MoveType_t>(m_Movetype);
	}

	float GetSimulationTime()
	{
		static int m_flSimulationTime = g_pNetvars->GetOffset("DT_BaseEntity", "m_flSimulationTime");
		return GetValue<float>(m_flSimulationTime);
	}

	float GetOldSimulationTime()
	{
		static int m_flOldSimulationTime = g_pNetvars->GetOffset("DT_BaseEntity", "m_flSimulationTime") + 4;
		return GetValue<float>(m_flOldSimulationTime);
	}

	float GetLowerBodyYaw()
	{
		static int m_flLowerBodyYawTarget = g_pNetvars->GetOffset("DT_CSPlayer", "m_flLowerBodyYawTarget");
		return GetValue<float>(m_flLowerBodyYawTarget);
	}
	CBaseHandle owner()
	{
		static int m_hOwnerEntity = g_pNetvars->GetOffset("DT_BaseEntity", "m_hOwnerEntity");

		return GetValue<CBaseHandle>(m_hOwnerEntity);
	}
	auto ObserverTarget() -> CBaseHandle {
		return *(CBaseHandle  *)((uintptr_t)this + 0x3388);
	}
	auto observer_target() -> uintptr_t {
		return *(uintptr_t *)((uintptr_t)this + g_pNetvars->GetOffset("DT_BaseEntity", "m_hObserverTarget"));
	}
	auto observer_mode() -> int32_t& {
		return *(int32_t *)((uintptr_t)this + g_pNetvars->GetOffset("DT_BaseEntity", "m_iObserverMode"));
	};

	matrix3x4_t GetBoneMatrix(int BoneID)
	{
		matrix3x4_t matrix;

		auto offset = *reinterpret_cast<uintptr_t*>(uintptr_t(this) + 0x26A8);
		if (offset)
			matrix = *reinterpret_cast<matrix3x4_t*>(offset + 0x30 * BoneID);

		return matrix;
	}

	void SetLowerBodyYaw(float value)
	{
		static int m_flLowerBodyYawTarget = g_pNetvars->GetOffset("DT_CSPlayer", "m_flLowerBodyYawTarget");
		*reinterpret_cast<float*>(uintptr_t(this) + m_flLowerBodyYawTarget) = value;
	}


	const matrix3x4_t& m_rgflCoordinateFrame()
	{
		static auto _m_rgflCoordinateFrame = g_pNetvars->GetOffset("DT_BaseEntity", "m_CollisionGroup") - 0x30;
		return *(matrix3x4_t*)((uintptr_t)this + _m_rgflCoordinateFrame);
	}

	bool GetHeavyArmor()
	{
		static int m_bHasHeavyArmor = g_pNetvars->GetOffset("DT_CSPlayer", "m_bHasHeavyArmor");
		return GetValue<bool>(m_bHasHeavyArmor);
	}

	int ArmorValue()
	{
		static int m_ArmorValue = g_pNetvars->GetOffset("DT_CSPlayer", "m_ArmorValue");
		return GetValue<int>(m_ArmorValue);
	}

	float* m_flFlashMaxAlpha()
	{
		static int flash = g_pNetvars->GetOffset("DT_CSPlayer", "m_flFlashMaxAlpha");
		return (float*)((uintptr_t)this + flash);
	}

	bool HasHelmet()
	{
		static int m_bHasHelmet = g_pNetvars->GetOffset("DT_CSPlayer", "m_bHasHelmet");
		return GetValue<bool>(m_bHasHelmet);
	}

	bool GetLifeState()
	{
		static int m_lifeState = g_pNetvars->GetOffset("DT_BasePlayer", "m_lifeState");
		return GetValue<bool>(m_lifeState);
	}

	bool IsScoped()
	{
		static int m_bIsScoped = g_pNetvars->GetOffset("DT_CSPlayer", "m_bIsScoped");
		return GetValue<bool>(m_bIsScoped);
	}

	int GetHealth()
	{
		static int m_iHealth = g_pNetvars->GetOffset("DT_BasePlayer", "m_iHealth");
		return GetValue<int>(m_iHealth);
	}

	CHandle<C_BaseCombatWeapon> *m_hMyWeapons() const
	{
		static int _m_hMyWeapons = 0x2DF8;
		return (CHandle<C_BaseCombatWeapon>*)((uintptr_t)this + (_m_hMyWeapons / 2));
	}

	CBaseHandle *GetWeapons()
	{
		return (CBaseHandle*)((DWORD)this + 0x2DE8);
	}

	bool IsKnifeorNade();

	bool IsKnife();

	bool IsPistol();

	bool IsShotgun();

	bool IsSniper();

	bool IsScopableWeapon();

	int GetSequenceActivity(int sequence);

	float DesyncValue();
	void SetModelIndex(const int index)
	{
		Utils::GetVFunc<void(__thiscall*)(C_BaseEntity*, int)>(this, 75)(this, index);
	}
	int* FallbackPaintKit()
	{
		return (int*)((uintptr_t)this + 0x31B8);
	}
	inline int* GetFallbackPaintKit() {
		return (int*)((DWORD)this + 0x31B8);
	}
	short* ItemDefinitionIndex2()
	{
		return (short*)((DWORD)this + g_pNetvars->GetOffset("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iItemDefinitionIndex"));
	}
	int* ViewModelIndex()
	{
		return (int*)((uintptr_t)this + g_pNetvars->GetOffset("DT_BaseViewModel", "m_nViewModelIndex"));
	}
	int* OwnerXuidLow()
	{
		return (int*)((uintptr_t)this + 0x31B0);
	}
	int* OwnerXuidHigh()
	{
		return (int*)((uintptr_t)this + 0x31B4);
	}
	int* ItemIDHigh()
	{
		return (int*)((uintptr_t)this + 0x2FC0);
	}

	float* FallbackWear()
	{
		return (float*)((uintptr_t)this + 0x31C0);
	}
	int* FallbackSeed()
	{
		return (int*)((uintptr_t)this + 0x31AC);
	}

	int& GetItemIDHigh()
	{
		return *(int *)((DWORD)this + g_pNetvars->GetOffset("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iItemIDHigh"));
	}

	int& GetItemIDLow()
	{
		return *(int *)((DWORD)this + g_pNetvars->GetOffset("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iItemIDLow"));
	}

	int& GetAccountID()
	{
		return *(int *)((DWORD)this + g_pNetvars->GetOffset("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iAccountID"));
	}

	bool IsAlive() { return this->GetHealth() > 0 && this->GetLifeState() == 0; }


	bool IsNade();
	bool is_valid(C_BaseEntity* local_player = nullptr, bool is_player = true, bool dormant = true, bool team_check = true) {
		if (!this)
			return false;

		if (dormant)
			if (this->IsDormant())
				return false;

		if (team_check && local_player)
			if (this->GetTeam() == local_player->GetTeam())
				return false;

		if (is_player)
			if (!this->IsPlayer())
				return false;

		if (this->GetHealth() <= 0)
			return false;

		return true;
	}
	bool IsPlayer() {
		using original_fn = bool(__thiscall*)(C_BaseEntity*);
		return (*(original_fn**)this)[155](this);
	}
	bool IsEnemy();

	bool IsImmune()
	{
		static int m_bGunGameImmunity = g_pNetvars->GetOffset("DT_CSPlayer", "m_bGunGameImmunity");
		return GetValue<bool>(m_bGunGameImmunity);
	}

	int GetTickBase()
	{
		static int m_nTickBase = g_pNetvars->GetOffset("DT_BasePlayer", "localdata", "m_nTickBase");
		return GetValue<int>(m_nTickBase);
	}

	int GetShotsFired()
	{
		static int m_iShotsFired = g_pNetvars->GetOffset("DT_CSPlayer", "cslocaldata", "m_iShotsFired");
		return GetValue<int>(m_iShotsFired);
	}

	void SetTickBase(int TickBase)
	{
		static int m_nTickBase = g_pNetvars->GetOffset("DT_BasePlayer", "localdata", "m_nTickBase");
		*reinterpret_cast<int*>(uintptr_t(this) + m_nTickBase) = TickBase;
	}

	Vector GetEyeAngles()
	{
		static int m_angEyeAngles = g_pNetvars->GetOffset("DT_CSPlayer", "m_angEyeAngles");
		return GetValue<Vector>(m_angEyeAngles);
	}
	Vector* GetEyeAnglesPointer()
	{
		return (Vector*)((DWORD)this + g_pNetvars->GetOffset("DT_CSPlayer", "m_angEyeAngles"));
	}

	Vector* GetEyeAngles2()
	{
		static int m_angEyeAngles = g_pNetvars->GetOffset("DT_CSPlayer", "m_angEyeAngles");
		return GetValue<Vector*>(m_angEyeAngles);
	}

	void SetEyeAngles(Vector Angle)
	{
		static int m_angEyeAngles = g_pNetvars->GetOffset("DT_CSPlayer", "m_angEyeAngles");
		*reinterpret_cast<Vector*>(uintptr_t(this) + m_angEyeAngles) = Angle;
	}

	Vector GetOrigin()
	{
		static int m_vecOrigin = g_pNetvars->GetOffset("DT_BaseEntity", "m_vecOrigin");
		return GetValue<Vector>(m_vecOrigin);
	}

	Vector GetOldOrigin()
	{
		static int m_vecOldOrigin = g_pNetvars->GetOffset("DT_BasePlayer", "localdata", "m_flFriction") + 12;
		return GetValue<Vector>(m_vecOldOrigin);
	}

	Vector GetNetworkOrigin()
	{
		static int m_vecNetworkOrigin = g_pNetvars->GetOffset("DT_BasePlayer", "localdata", "m_flFriction") + 40;
		return GetValue<Vector>(m_vecNetworkOrigin);
	}

	void SetOrigin(Vector Origin)
	{
		static int m_vecOrigin = g_pNetvars->GetOffset("DT_BaseEntity", "m_vecOrigin");
		*reinterpret_cast<Vector*>(uintptr_t(this) + m_vecOrigin) = Origin;
	}

	Vector GetVelocity()
	{
		static int m_vecVelocity = g_pNetvars->GetOffset("DT_BasePlayer", "localdata", "m_vecVelocity[0]");
		return GetValue<Vector>(m_vecVelocity);
	}

	void SetVelocity(Vector velocity)
	{
		static int m_vecVelocity = g_pNetvars->GetOffset("DT_BasePlayer", "localdata", "m_vecVelocity[0]");
		*reinterpret_cast<Vector*>(uintptr_t(this) + m_vecVelocity) = velocity;
	}

	Vector GetAimPunchAngle()
	{
		return *reinterpret_cast<Vector*>(uintptr_t(this) + uintptr_t(0x302C));
	}

	Vector GetViewPunchAngle()
	{
		return *reinterpret_cast<Vector*>(uintptr_t(this) + uintptr_t(0x3020));
	}

	Vector m_vecViewOffset()
	{
		return *reinterpret_cast<Vector*>(uintptr_t(this) + uintptr_t(0x108));
	}

	Vector GetViewOffset()
	{
		return *reinterpret_cast<Vector*>(uintptr_t(this) + 0x104);
	}

	int Deadflag()
	{
		static int m_iShotsFired = g_pNetvars->GetOffset("DT_CSPlayer", "deadflag");
		return GetValue<int>(m_iShotsFired);
	}

	Vector GetVecOrigin()
	{
		return *reinterpret_cast<Vector*>(uintptr_t(this) + g_pNetvars->GetOffset("DT_BaseEntity", "m_vecOrigin"));
	}

	Vector GetEyePosition()
	{
		if (!this)
			return Vector(0, 0, 0);

		Vector ret;
		typedef void(__thiscall *OrigFn)(void *, Vector&);
		Utils::GetVFunc<OrigFn>(this, 284)(this, ret);

		return ret;
	}
	inline Vector ExtrapolateTick(Vector p0, Vector v0)
	{
		return p0 + (v0 * g_pGlobalVars->intervalPerTick);
	}
	Vector GetPredicted(Vector p0)
	{
		return ExtrapolateTick(p0, this->GetVelocity());
	}

	Vector GetBonePosition(int iBone)
	{
		matrix3x4_t boneMatrixes[128];
		if (this->SetupBones(boneMatrixes, 128, 0x100, 0))
		{
			matrix3x4_t boneMatrix = boneMatrixes[iBone];
			return Vector(boneMatrix.flMatVal[0][3], boneMatrix.flMatVal[1][3], boneMatrix.flMatVal[2][3]);
		}
		else
			return Vector(0, 0, 0);
	}

	ICollideable* GetCollideable()
	{
		return (ICollideable*)((DWORD)this + 0x320);
	}

	void SetCurrentCommand(CUserCmd *cmd)
	{
		static int m_hConstraintEntity = g_pNetvars->GetOffset("DT_BasePlayer", "localdata", "m_hConstraintEntity");
		*reinterpret_cast<CUserCmd**>(uintptr_t(this) + m_hConstraintEntity - 0xC) = cmd;
	}

	float FireRate();

	void FixSetupBones(matrix3x4_t *Matrix);
	Vector GetHitboxPosition(int Hitbox, matrix3x4_t *Matrix, float *Radius);
	Vector GetHitboxPosition(int Hitbox, matrix3x4_t *Matrix);
};
class viewmodel_t;


class C_BaseCombatWeapon : public C_BaseEntity
{
private:
	template<class T>
	T GetPointer(const int offset)
	{
		return reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(this) + offset);
	}
	// To get value from the pointer itself
	template<class T>
	T GetValue(const int offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(this) + offset);
	}

public:
	//	offys.m_iItemDefinitionIndex = ;
	ItemDefinitionIndex GetItemDefinitionIndex()
	{
		static int m_iItemDefinitionIndex = g_pNetvars->GetOffset("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iItemDefinitionIndex");
		return GetValue<ItemDefinitionIndex>(m_iItemDefinitionIndex);
	}


	CBaseHandle GetWeaponWorldModel()
	{
		return *(CBaseHandle*)((uintptr_t)this + g_pNetvars->GetOffset("DT_BaseCombatWeapon", "m_hWeaponWorldModel")); //m_hWeaponWorldModel
	}

#define VirtualFn( cast ) typedef cast( __thiscall* OriginalFn )
	void SetModelIndex(int nModelIndex)
	{
		VirtualFn(void)(PVOID, int);
		Utils::GetVFunc< OriginalFn >(this, 75)(this, nModelIndex);
	}
	CBaseHandle m_hWeaponWorldModel_h()
	{
		return *(CBaseHandle*)((uintptr_t)this + 0x3234); //m_hWeaponWorldModel
	}
	HANDLE m_hWeaponWorldModel_c()
	{
		return *(HANDLE*)((uintptr_t)this + 0x3234); //m_hWeaponWorldModel
	}
	short* ItemDefinitionIndex2()
	{
		return (short*)((DWORD)this + g_pNetvars->GetOffset("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iItemDefinitionIndex"));
	}
	int* ModelIndex()
	{
		return (int*)((uintptr_t)this + 0x258);
	}
	int* WorldModelIndex()
	{
		return (int*)((uintptr_t)this + g_pNetvars->GetOffset("DT_BaseCombatWeapon", "m_iWorldModelIndex"));
	}
	int* GetEntityQuality() {
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iEntityQuality
		return (int*)((uintptr_t)this + 0x2FAC);
	}
	short* fixskins()
	{
		return (short*)((uintptr_t)this + 0x2FAA);
	}
	int* FallbackPaintKit()
	{
		return (int*)((uintptr_t)this + 0x31C8);
	}
	inline int* GetFallbackPaintKit() {
		return (int*)((DWORD)this + 0x31C8);
	}
	int* ViewModelIndex()
	{
		return (int*)((uintptr_t)this + g_pNetvars->GetOffset("DT_BaseViewModel", "m_nViewModelIndex"));
	}
	int* OwnerXuidLow()
	{
		return (int*)((uintptr_t)this + 0x31C0);
	}
	int* OwnerXuidHigh()
	{
		return (int*)((uintptr_t)this + 0x31C4);
	}
	int* ItemIDHigh()
	{
		return (int*)((uintptr_t)this + 0x2FC0);
	}

	float* FallbackWear()
	{
		return (float*)((uintptr_t)this + 0x31D0);
	}
	int* FallbackSeed()
	{
		return (int*)((uintptr_t)this + 0x31CC);
	}

	int& GetItemIDHigh()
	{
		return *(int *)((DWORD)this + g_pNetvars->GetOffset("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iItemIDHigh"));
	}

	int& GetItemIDLow()
	{
		return *(int *)((DWORD)this + g_pNetvars->GetOffset("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iItemIDLow"));
	}

	int& GetAccountID()
	{
		return *(int *)((DWORD)this + g_pNetvars->GetOffset("DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_iAccountID"));
	}


	float GetInaccuracy()
	{
		typedef float(__thiscall* oInaccuracy)(PVOID);
		return Utils::GetVFunc< oInaccuracy >(this, 482)(this);
	}

	float GetSpread()
	{
		typedef float(__thiscall* oWeaponSpread)(PVOID);
		return Utils::GetVFunc< oWeaponSpread >(this, 452)(this);
	}

	float GetAccuracyPenalty()
	{
		static int m_fAccuracyPenalty = g_pNetvars->GetOffset("DT_WeaponCSBase", "m_fAccuracyPenalty");
		return GetValue<float>(m_fAccuracyPenalty);
	}

	float GetLastShotTime()
	{
		static int m_fLastShotTime = g_pNetvars->GetOffset("DT_WeaponCSBase", "m_fLastShotTime");
		return GetValue<float>(m_fLastShotTime);
	}

	int GetZoomLevel()
	{
		static int m_fLastShotTime = g_pNetvars->GetOffset("DT_WeaponCSBase", "m_zoomLevel");
		return GetValue<int>(m_fLastShotTime);
	}

	void AccuracyPenalty()
	{
		typedef void(__thiscall *OrigFn)(void *);
		return Utils::GetVFunc<OrigFn>(this, 483)(this);
	}

	float GetNextPrimaryAttack()
	{
		static int m_flNextPrimaryAttack = g_pNetvars->GetOffset("DT_BaseCombatWeapon", "LocalActiveWeaponData", "m_flNextPrimaryAttack");
		return GetValue<float>(m_flNextPrimaryAttack);
	}

	float m_flPostponeFireReadyTime()
	{
		static int m_flNextPrimaryAttack = g_pNetvars->GetOffset("DT_BaseCombatWeapon", "LocalActiveWeaponData", "m_flPostponeFireReadyTime");
		return GetValue<float>(m_flNextPrimaryAttack);
	}

	int GetAmmo()
	{
		static int m_iClip1 = g_pNetvars->GetOffset("DT_BaseCombatWeapon", "m_iClip1");
		return GetValue<int>(m_iClip1);
	}

	int GetAmmo2()
	{
		static int m_iClip1 = g_pNetvars->GetOffset("DT_BaseCombatWeapon", "m_iClip2");
		return GetValue<int>(m_iClip1);
	}

	/*
	WeaponInfo_t* GetCSWpnData()
	{
		using OriginalFn = WeaponInfo_t * (__thiscall*)(void*);
		static OriginalFn return_func = (OriginalFn)((DWORD)Utils::FindSignature("client.dll", "55 8B EC 81 EC ? ? ? ? 53 8B D9 56 57 8D 8B"));
		return return_func(this);
	}


	std::string GetName()
	{
		///TODO: Test if szWeaponName returns proper value for m4a4 / m4a1-s or it doesnt recognize them.
		return std::string(this->GetCSWpnData()->weapon_name);
	}
	*/

	WeaponInfo_t* GetCSWpnData()
	{
		return Utils::CallVFunc<460, WeaponInfo_t*>(this);//457
	}

	std::string GetName()
	{
		///TODO: Test if szWeaponName returns proper value for m4a4 / m4a1-s or it doesnt recognize them.
		return std::string(this->GetCSWpnData()->weapon_name);
	}

};
#pragma once

#include <cstring>

#pragma once

#include <assert.h>

template< class T, class I = int >
class CUtlMemory
{
public:
	// constructor, destructor
	CUtlMemory(int nGrowSize = 0, int nInitSize = 0);
	CUtlMemory(T* pMemory, int numElements);
	CUtlMemory(const T* pMemory, int numElements);
	~CUtlMemory();

	// Set the size by which the memory grows
	void Init(int nGrowSize = 0, int nInitSize = 0);

	class Iterator_t
	{
	public:
		Iterator_t(I i) : index(i) {}
		I index;

		bool operator==(const Iterator_t it) const { return index == it.index; }
		bool operator!=(const Iterator_t it) const { return index != it.index; }
	};
	Iterator_t First() const { return Iterator_t(IsIdxValid(0) ? 0 : InvalidIndex()); }
	Iterator_t Next(const Iterator_t &it) const { return Iterator_t(IsIdxValid(it.index + 1) ? it.index + 1 : InvalidIndex()); }
	I GetIndex(const Iterator_t &it) const { return it.index; }
	bool IsIdxAfter(I i, const Iterator_t &it) const { return i > it.index; }
	bool IsValidIterator(const Iterator_t &it) const { return IsIdxValid(it.index); }
	Iterator_t InvalidIterator() const { return Iterator_t(InvalidIndex()); }

	// element access
	T& operator[](I i);
	const T& operator[](I i) const;
	T& Element(I i);
	const T& Element(I i) const;

	bool IsIdxValid(I i) const;

	static const I INVALID_INDEX = (I)-1; // For use with COMPILE_TIME_ASSERT
	static I InvalidIndex() { return INVALID_INDEX; }

	T* Base();
	const T* Base() const;

	void SetExternalBuffer(T* pMemory, int numElements);
	void SetExternalBuffer(const T* pMemory, int numElements);
	void AssumeMemory(T *pMemory, int nSize);
	T* Detach();
	void *DetachMemory();

	void Swap(CUtlMemory< T, I > &mem);
	void ConvertToGrowableMemory(int nGrowSize);
	int NumAllocated() const;
	int Count() const;
	void Grow(int num = 1);
	void EnsureCapacity(int num);
	void Purge();
	void Purge(int numElements);
	bool IsExternallyAllocated() const;
	bool IsReadOnly() const;
	void SetGrowSize(int size);

protected:
	void ValidateGrowSize()
	{

	}

	enum
	{
		EXTERNAL_BUFFER_MARKER = -1,
		EXTERNAL_CONST_BUFFER_MARKER = -2,
	};

	T* m_pMemory;
	int m_nAllocationCount;
	int m_nGrowSize;
};

//-----------------------------------------------------------------------------
// constructor, destructor
//-----------------------------------------------------------------------------

template< class T, class I >
CUtlMemory<T, I>::CUtlMemory(int nGrowSize, int nInitAllocationCount) : m_pMemory(0),
m_nAllocationCount(nInitAllocationCount), m_nGrowSize(nGrowSize)
{
	ValidateGrowSize();
	assert(nGrowSize >= 0);
	if (m_nAllocationCount) {
		m_pMemory = (T*)new unsigned char[m_nAllocationCount * sizeof(T)];
		//m_pMemory = (T*)malloc(m_nAllocationCount * sizeof(T));
	}
}

template< class T, class I >
CUtlMemory<T, I>::CUtlMemory(T* pMemory, int numElements) : m_pMemory(pMemory),
m_nAllocationCount(numElements)
{
	// Special marker indicating externally supplied modifyable memory
	m_nGrowSize = EXTERNAL_BUFFER_MARKER;
}

template< class T, class I >
CUtlMemory<T, I>::CUtlMemory(const T* pMemory, int numElements) : m_pMemory((T*)pMemory),
m_nAllocationCount(numElements)
{
	// Special marker indicating externally supplied modifyable memory
	m_nGrowSize = EXTERNAL_CONST_BUFFER_MARKER;
}

template< class T, class I >
CUtlMemory<T, I>::~CUtlMemory()
{
	Purge();
}

template< class T, class I >
void CUtlMemory<T, I>::Init(int nGrowSize /*= 0*/, int nInitSize /*= 0*/)
{
	Purge();

	m_nGrowSize = nGrowSize;
	m_nAllocationCount = nInitSize;
	ValidateGrowSize();
	assert(nGrowSize >= 0);
	if (m_nAllocationCount) {
		UTLMEMORY_TRACK_ALLOC();
		MEM_ALLOC_CREDIT_CLASS();
		m_pMemory = (T*)malloc(m_nAllocationCount * sizeof(T));
	}
}

//-----------------------------------------------------------------------------
// Fast swap
//-----------------------------------------------------------------------------
template< class T, class I >
void CUtlMemory<T, I>::Swap(CUtlMemory<T, I> &mem)
{
	V_swap(m_nGrowSize, mem.m_nGrowSize);
	V_swap(m_pMemory, mem.m_pMemory);
	V_swap(m_nAllocationCount, mem.m_nAllocationCount);
}


//-----------------------------------------------------------------------------
// Switches the buffer from an external memory buffer to a reallocatable buffer
//-----------------------------------------------------------------------------
template< class T, class I >
void CUtlMemory<T, I>::ConvertToGrowableMemory(int nGrowSize)
{
	if (!IsExternallyAllocated())
		return;

	m_nGrowSize = nGrowSize;
	if (m_nAllocationCount) {
		int nNumBytes = m_nAllocationCount * sizeof(T);
		T *pMemory = (T*)malloc(nNumBytes);
		memcpy(pMemory, m_pMemory, nNumBytes);
		m_pMemory = pMemory;
	}
	else {
		m_pMemory = NULL;
	}
}


//-----------------------------------------------------------------------------
// Attaches the buffer to external memory....
//-----------------------------------------------------------------------------
template< class T, class I >
void CUtlMemory<T, I>::SetExternalBuffer(T* pMemory, int numElements)
{
	// Blow away any existing allocated memory
	Purge();

	m_pMemory = pMemory;
	m_nAllocationCount = numElements;

	// Indicate that we don't own the memory
	m_nGrowSize = EXTERNAL_BUFFER_MARKER;
}

template< class T, class I >
void CUtlMemory<T, I>::SetExternalBuffer(const T* pMemory, int numElements)
{
	// Blow away any existing allocated memory
	Purge();

	m_pMemory = const_cast<T*>(pMemory);
	m_nAllocationCount = numElements;

	// Indicate that we don't own the memory
	m_nGrowSize = EXTERNAL_CONST_BUFFER_MARKER;
}

template< class T, class I >
void CUtlMemory<T, I>::AssumeMemory(T* pMemory, int numElements)
{
	// Blow away any existing allocated memory
	Purge();

	// Simply take the pointer but don't mark us as external
	m_pMemory = pMemory;
	m_nAllocationCount = numElements;
}

template< class T, class I >
void *CUtlMemory<T, I>::DetachMemory()
{
	if (IsExternallyAllocated())
		return NULL;

	void *pMemory = m_pMemory;
	m_pMemory = 0;
	m_nAllocationCount = 0;
	return pMemory;
}

template< class T, class I >
inline T* CUtlMemory<T, I>::Detach()
{
	return (T*)DetachMemory();
}


//-----------------------------------------------------------------------------
// element access
//-----------------------------------------------------------------------------
template< class T, class I >
inline T& CUtlMemory<T, I>::operator[](I i)
{
	assert(!IsReadOnly());
	assert(IsIdxValid(i));
	return m_pMemory[i];
}

template< class T, class I >
inline const T& CUtlMemory<T, I>::operator[](I i) const
{
	assert(IsIdxValid(i));
	return m_pMemory[i];
}

template< class T, class I >
inline T& CUtlMemory<T, I>::Element(I i)
{
	assert(!IsReadOnly());
	assert(IsIdxValid(i));
	return m_pMemory[i];
}

template< class T, class I >
inline const T& CUtlMemory<T, I>::Element(I i) const
{
	assert(IsIdxValid(i));
	return m_pMemory[i];
}


//-----------------------------------------------------------------------------
// is the memory externally allocated?
//-----------------------------------------------------------------------------
template< class T, class I >
bool CUtlMemory<T, I>::IsExternallyAllocated() const
{
	return (m_nGrowSize < 0);
}


//-----------------------------------------------------------------------------
// is the memory read only?
//-----------------------------------------------------------------------------
template< class T, class I >
bool CUtlMemory<T, I>::IsReadOnly() const
{
	return (m_nGrowSize == EXTERNAL_CONST_BUFFER_MARKER);
}


template< class T, class I >
void CUtlMemory<T, I>::SetGrowSize(int nSize)
{
	assert(!IsExternallyAllocated());
	assert(nSize >= 0);
	m_nGrowSize = nSize;
	ValidateGrowSize();
}


//-----------------------------------------------------------------------------
// Gets the base address (can change when adding elements!)
//-----------------------------------------------------------------------------
template< class T, class I >
inline T* CUtlMemory<T, I>::Base()
{
	assert(!IsReadOnly());
	return m_pMemory;
}

template< class T, class I >
inline const T *CUtlMemory<T, I>::Base() const
{
	return m_pMemory;
}


//-----------------------------------------------------------------------------
// Size
//-----------------------------------------------------------------------------
template< class T, class I >
inline int CUtlMemory<T, I>::NumAllocated() const
{
	return m_nAllocationCount;
}

template< class T, class I >
inline int CUtlMemory<T, I>::Count() const
{
	return m_nAllocationCount;
}


//-----------------------------------------------------------------------------
// Is element index valid?
//-----------------------------------------------------------------------------
template< class T, class I >
inline bool CUtlMemory<T, I>::IsIdxValid(I i) const
{
	// GCC warns if I is an unsigned type and we do a ">= 0" against it (since the comparison is always 0).
	// We Get the warning even if we cast inside the expression. It only goes away if we assign to another variable.
	long x = i;
	return (x >= 0) && (x < m_nAllocationCount);
}

//-----------------------------------------------------------------------------
// Grows the memory
//-----------------------------------------------------------------------------
inline int UtlMemory_CalcNewAllocationCount(int nAllocationCount, int nGrowSize, int nNewSize, int nBytesItem)
{
	if (nGrowSize) {
		nAllocationCount = ((1 + ((nNewSize - 1) / nGrowSize)) * nGrowSize);
	}
	else {
		if (!nAllocationCount) {
			// Compute an allocation which is at least as big as a cache line...
			nAllocationCount = (31 + nBytesItem) / nBytesItem;
		}

		while (nAllocationCount < nNewSize) {
#ifndef _X360
			nAllocationCount *= 2;
#else
			int nNewAllocationCount = (nAllocationCount * 9) / 8; // 12.5 %
			if (nNewAllocationCount > nAllocationCount)
				nAllocationCount = nNewAllocationCount;
			else
				nAllocationCount *= 2;
#endif
		}
	}

	return nAllocationCount;
}

template< class T, class I >
void CUtlMemory<T, I>::Grow(int num)
{
	assert(num > 0);

	if (IsExternallyAllocated()) {
		// Can't grow a buffer whose memory was externally allocated 
		assert(0);
		return;
	}


	auto oldAllocationCount = m_nAllocationCount;
	// Make sure we have at least numallocated + num allocations.
	// Use the grow rules specified for this memory (in m_nGrowSize)
	int nAllocationRequested = m_nAllocationCount + num;

	int nNewAllocationCount = UtlMemory_CalcNewAllocationCount(m_nAllocationCount, m_nGrowSize, nAllocationRequested, sizeof(T));

	// if m_nAllocationRequested wraps index type I, recalculate
	if ((int)(I)nNewAllocationCount < nAllocationRequested) {
		if ((int)(I)nNewAllocationCount == 0 && (int)(I)(nNewAllocationCount - 1) >= nAllocationRequested) {
			--nNewAllocationCount; // deal w/ the common case of m_nAllocationCount == MAX_USHORT + 1
		}
		else {
			if ((int)(I)nAllocationRequested != nAllocationRequested) {
				// we've been asked to grow memory to a size s.t. the index type can't address the requested amount of memory
				assert(0);
				return;
			}
			while ((int)(I)nNewAllocationCount < nAllocationRequested) {
				nNewAllocationCount = (nNewAllocationCount + nAllocationRequested) / 2;
			}
		}
	}

	m_nAllocationCount = nNewAllocationCount;

	if (m_pMemory) {
		auto ptr = new unsigned char[m_nAllocationCount * sizeof(T)];

		memcpy(ptr, m_pMemory, oldAllocationCount * sizeof(T));
		m_pMemory = (T*)ptr;
	}
	else {
		m_pMemory = (T*)new unsigned char[m_nAllocationCount * sizeof(T)];
	}
}


//-----------------------------------------------------------------------------
// Makes sure we've got at least this much memory
//-----------------------------------------------------------------------------
template< class T, class I >
inline void CUtlMemory<T, I>::EnsureCapacity(int num)
{
	if (m_nAllocationCount >= num)
		return;

	if (IsExternallyAllocated()) {
		// Can't grow a buffer whose memory was externally allocated 
		assert(0);
		return;
	}
	m_nAllocationCount = num;

	if (m_pMemory) {
		m_pMemory = (T*)realloc(m_pMemory, m_nAllocationCount * sizeof(T));
	}
	else {
		m_pMemory = (T*)malloc(m_nAllocationCount * sizeof(T));
	}
}


//-----------------------------------------------------------------------------
// Memory deallocation
//-----------------------------------------------------------------------------
template< class T, class I >
void CUtlMemory<T, I>::Purge()
{
	if (!IsExternallyAllocated()) {
		if (m_pMemory) {
			free((void*)m_pMemory);
			m_pMemory = 0;
		}
		m_nAllocationCount = 0;
	}
}

template< class T, class I >
void CUtlMemory<T, I>::Purge(int numElements)
{
	assert(numElements >= 0);

	if (numElements > m_nAllocationCount) {
		// Ensure this isn't a grow request in disguise.
		assert(numElements <= m_nAllocationCount);
		return;
	}

	// If we have zero elements, simply do a purge:
	if (numElements == 0) {
		Purge();
		return;
	}

	if (IsExternallyAllocated()) {
		// Can't shrink a buffer whose memory was externally allocated, fail silently like purge 
		return;
	}

	// If the number of elements is the same as the allocation count, we are done.
	if (numElements == m_nAllocationCount) {
		return;
	}


	if (!m_pMemory) {
		// Allocation count is non zero, but memory is null.
		assert(m_pMemory);
		return;
	}
	m_nAllocationCount = numElements;
	m_pMemory = (T*)realloc(m_pMemory, m_nAllocationCount * sizeof(T));
}

//-----------------------------------------------------------------------------
// The CUtlMemory class:
// A growable memory class which doubles in size by default.
//-----------------------------------------------------------------------------
template< class T, int nAlignment >
class CUtlMemoryAligned : public CUtlMemory<T>
{
public:
	// constructor, destructor
	CUtlMemoryAligned(int nGrowSize = 0, int nInitSize = 0);
	CUtlMemoryAligned(T* pMemory, int numElements);
	CUtlMemoryAligned(const T* pMemory, int numElements);
	~CUtlMemoryAligned();

	// Attaches the buffer to external memory....
	void SetExternalBuffer(T* pMemory, int numElements);
	void SetExternalBuffer(const T* pMemory, int numElements);

	// Grows the memory, so that at least allocated + num elements are allocated
	void Grow(int num = 1);

	// Makes sure we've got at least this much memory
	void EnsureCapacity(int num);

	// Memory deallocation
	void Purge();

	// Purge all but the given number of elements (NOT IMPLEMENTED IN CUtlMemoryAligned)
	void Purge(int numElements) { assert(0); }

private:
	void *Align(const void *pAddr);
};


//-----------------------------------------------------------------------------
// Aligns a pointer
//-----------------------------------------------------------------------------
template< class T, int nAlignment >
void *CUtlMemoryAligned<T, nAlignment>::Align(const void *pAddr)
{
	size_t nAlignmentMask = nAlignment - 1;
	return (void*)(((size_t)pAddr + nAlignmentMask) & (~nAlignmentMask));
}


//-----------------------------------------------------------------------------
// constructor, destructor
//-----------------------------------------------------------------------------
template< class T, int nAlignment >
CUtlMemoryAligned<T, nAlignment>::CUtlMemoryAligned(int nGrowSize, int nInitAllocationCount)
{
	CUtlMemory<T>::m_pMemory = 0;
	CUtlMemory<T>::m_nAllocationCount = nInitAllocationCount;
	CUtlMemory<T>::m_nGrowSize = nGrowSize;
	this->ValidateGrowSize();

	// Alignment must be a power of two
	COMPILE_TIME_ASSERT((nAlignment & (nAlignment - 1)) == 0);
	assert((nGrowSize >= 0) && (nGrowSize != CUtlMemory<T>::EXTERNAL_BUFFER_MARKER));
	if (CUtlMemory<T>::m_nAllocationCount) {
		UTLMEMORY_TRACK_ALLOC();
		MEM_ALLOC_CREDIT_CLASS();
		CUtlMemory<T>::m_pMemory = (T*)_aligned_malloc(nInitAllocationCount * sizeof(T), nAlignment);
	}
}

template< class T, int nAlignment >
CUtlMemoryAligned<T, nAlignment>::CUtlMemoryAligned(T* pMemory, int numElements)
{
	// Special marker indicating externally supplied memory
	CUtlMemory<T>::m_nGrowSize = CUtlMemory<T>::EXTERNAL_BUFFER_MARKER;

	CUtlMemory<T>::m_pMemory = (T*)Align(pMemory);
	CUtlMemory<T>::m_nAllocationCount = ((int)(pMemory + numElements) - (int)CUtlMemory<T>::m_pMemory) / sizeof(T);
}

template< class T, int nAlignment >
CUtlMemoryAligned<T, nAlignment>::CUtlMemoryAligned(const T* pMemory, int numElements)
{
	// Special marker indicating externally supplied memory
	CUtlMemory<T>::m_nGrowSize = CUtlMemory<T>::EXTERNAL_CONST_BUFFER_MARKER;

	CUtlMemory<T>::m_pMemory = (T*)Align(pMemory);
	CUtlMemory<T>::m_nAllocationCount = ((int)(pMemory + numElements) - (int)CUtlMemory<T>::m_pMemory) / sizeof(T);
}

template< class T, int nAlignment >
CUtlMemoryAligned<T, nAlignment>::~CUtlMemoryAligned()
{
	Purge();
}


//-----------------------------------------------------------------------------
// Attaches the buffer to external memory....
//-----------------------------------------------------------------------------
template< class T, int nAlignment >
void CUtlMemoryAligned<T, nAlignment>::SetExternalBuffer(T* pMemory, int numElements)
{
	// Blow away any existing allocated memory
	Purge();

	CUtlMemory<T>::m_pMemory = (T*)Align(pMemory);
	CUtlMemory<T>::m_nAllocationCount = ((int)(pMemory + numElements) - (int)CUtlMemory<T>::m_pMemory) / sizeof(T);

	// Indicate that we don't own the memory
	CUtlMemory<T>::m_nGrowSize = CUtlMemory<T>::EXTERNAL_BUFFER_MARKER;
}

template< class T, int nAlignment >
void CUtlMemoryAligned<T, nAlignment>::SetExternalBuffer(const T* pMemory, int numElements)
{
	// Blow away any existing allocated memory
	Purge();

	CUtlMemory<T>::m_pMemory = (T*)Align(pMemory);
	CUtlMemory<T>::m_nAllocationCount = ((int)(pMemory + numElements) - (int)CUtlMemory<T>::m_pMemory) / sizeof(T);

	// Indicate that we don't own the memory
	CUtlMemory<T>::m_nGrowSize = CUtlMemory<T>::EXTERNAL_CONST_BUFFER_MARKER;
}


//-----------------------------------------------------------------------------
// Grows the memory
//-----------------------------------------------------------------------------
template< class T, int nAlignment >
void CUtlMemoryAligned<T, nAlignment>::Grow(int num)
{
	assert(num > 0);

	if (this->IsExternallyAllocated()) {
		// Can't grow a buffer whose memory was externally allocated 
		assert(0);
		return;
	}

	UTLMEMORY_TRACK_FREE();

	// Make sure we have at least numallocated + num allocations.
	// Use the grow rules specified for this memory (in m_nGrowSize)
	int nAllocationRequested = CUtlMemory<T>::m_nAllocationCount + num;

	CUtlMemory<T>::m_nAllocationCount = UtlMemory_CalcNewAllocationCount(CUtlMemory<T>::m_nAllocationCount, CUtlMemory<T>::m_nGrowSize, nAllocationRequested, sizeof(T));

	UTLMEMORY_TRACK_ALLOC();

	if (CUtlMemory<T>::m_pMemory) {
		MEM_ALLOC_CREDIT_CLASS();
		CUtlMemory<T>::m_pMemory = (T*)MemAlloc_ReallocAligned(CUtlMemory<T>::m_pMemory, CUtlMemory<T>::m_nAllocationCount * sizeof(T), nAlignment);
		assert(CUtlMemory<T>::m_pMemory);
	}
	else {
		MEM_ALLOC_CREDIT_CLASS();
		CUtlMemory<T>::m_pMemory = (T*)MemAlloc_AllocAligned(CUtlMemory<T>::m_nAllocationCount * sizeof(T), nAlignment);
		assert(CUtlMemory<T>::m_pMemory);
	}
}


//-----------------------------------------------------------------------------
// Makes sure we've got at least this much memory
//-----------------------------------------------------------------------------
template< class T, int nAlignment >
inline void CUtlMemoryAligned<T, nAlignment>::EnsureCapacity(int num)
{
	if (CUtlMemory<T>::m_nAllocationCount >= num)
		return;

	if (this->IsExternallyAllocated()) {
		// Can't grow a buffer whose memory was externally allocated 
		assert(0);
		return;
	}

	UTLMEMORY_TRACK_FREE();

	CUtlMemory<T>::m_nAllocationCount = num;

	UTLMEMORY_TRACK_ALLOC();

	if (CUtlMemory<T>::m_pMemory) {
		MEM_ALLOC_CREDIT_CLASS();
		CUtlMemory<T>::m_pMemory = (T*)MemAlloc_ReallocAligned(CUtlMemory<T>::m_pMemory, CUtlMemory<T>::m_nAllocationCount * sizeof(T), nAlignment);
	}
	else {
		MEM_ALLOC_CREDIT_CLASS();
		CUtlMemory<T>::m_pMemory = (T*)MemAlloc_AllocAligned(CUtlMemory<T>::m_nAllocationCount * sizeof(T), nAlignment);
	}
}


//-----------------------------------------------------------------------------
// Memory deallocation
//-----------------------------------------------------------------------------
template< class T, int nAlignment >
void CUtlMemoryAligned<T, nAlignment>::Purge()
{
	if (!this->IsExternallyAllocated()) {
		if (CUtlMemory<T>::m_pMemory) {
			UTLMEMORY_TRACK_FREE();
			MemAlloc_FreeAligned(CUtlMemory<T>::m_pMemory);
			CUtlMemory<T>::m_pMemory = 0;
		}
		CUtlMemory<T>::m_nAllocationCount = 0;
	}
}
template< class T, class A = CUtlMemory<T> >
class CUtlVector
{
	typedef T *iterator;
	typedef const T *const_iterator;
	typedef A CAllocator;
public:
	typedef T ElemType_t;

	// constructor, destructor
	CUtlVector(int growSize = 0, int initSize = 0);
	CUtlVector(T* pMemory, int allocationCount, int numElements = 0);
	~CUtlVector();

	// Copy the array.
	CUtlVector<T, A>& operator=(const CUtlVector<T, A> &other);

	// element access
	T& operator[](int i);
	const T& operator[](int i) const;
	T& Element(int i);
	const T& Element(int i) const;
	T& Head();
	const T& Head() const;
	T& Tail();
	const T& Tail() const;

	// Gets the base address (can change when adding elements!)
	T* Base() { return m_Memory.Base(); }
	const T* Base() const { return m_Memory.Base(); }
	// Returns the number of elements in the vector
	int Count() const;
	// Is element index valid?
	bool IsValidIndex(int i) const;
	static int InvalidIndex();
	// Adds an element, uses default constructor
	int AddToHead();
	int AddToTail();
	int InsertBefore(int elem);
	int InsertAfter(int elem);
	// Adds an element, uses copy constructor
	int AddToHead(const T& src);
	int AddToTail(const T& src);
	int InsertBefore(int elem, const T& src);
	int InsertAfter(int elem, const T& src);
	// Adds multiple elements, uses default constructor
	int AddMultipleToHead(int num);
	int AddMultipleToTail(int num);
	int AddMultipleToTail(int num, const T *pToCopy);
	int InsertMultipleBefore(int elem, int num);
	int InsertMultipleBefore(int elem, int num, const T *pToCopy);
	int InsertMultipleAfter(int elem, int num);
	// Calls RemoveAll() then AddMultipleToTail.
	void SetSize(int size);
	void SetCount(int count);
	void SetCountNonDestructively(int count); //sets count by adding or removing elements to tail TODO: This should probably be the default behavior for SetCount
	void CopyArray(const T *pArray, int size); //Calls SetSize and copies each element.
											   // Fast swap
	void Swap(CUtlVector< T, A > &vec);
	// Add the specified array to the tail.
	int AddVectorToTail(CUtlVector<T, A> const &src);
	// Finds an element (element needs operator== defined)
	int GetOffset(const T& src) const;
	void FillWithValue(const T& src);
	bool HasElement(const T& src) const;
	// Makes sure we have enough memory allocated to store a requested # of elements
	void EnsureCapacity(int num);
	// Makes sure we have at least this many elements
	void EnsureCount(int num);
	// Element removal
	void FastRemove(int elem);    // doesn't preserve order
	void Remove(int elem);        // preserves order, shifts elements
	bool FindAndRemove(const T& src);    // removes first occurrence of src, preserves order, shifts elements
	bool FindAndFastRemove(const T& src);    // removes first occurrence of src, doesn't preserve order
	void RemoveMultiple(int elem, int num);    // preserves order, shifts elements
	void RemoveMultipleFromHead(int num); // removes num elements from tail
	void RemoveMultipleFromTail(int num); // removes num elements from tail
	void RemoveAll();                // doesn't deallocate memory
	void Purge(); // Memory deallocation
				  // Purges the list and calls delete on each element in it.
	void PurgeAndDeleteElements();
	// Compacts the vector to the number of elements actually in use 
	void Compact();
	// Set the size by which it grows when it needs to allocate more memory.
	void SetGrowSize(int size) { m_Memory.SetGrowSize(size); }
	int NumAllocated() const;    // Only use this if you really know what you're doing!
	void Sort(int(__cdecl *pfnCompare)(const T *, const T *));

	iterator begin() { return Base(); }
	const_iterator begin() const { return Base(); }
	iterator end() { return Base() + Count(); }
	const_iterator end() const { return Base() + Count(); }

protected:
	// Can't copy this unless we explicitly do it!
	CUtlVector(CUtlVector const& vec) { assert(0); }

	// Grows the vector
	void GrowVector(int num = 1);

	// Shifts elements....
	void ShiftElementsRight(int elem, int num = 1);
	void ShiftElementsLeft(int elem, int num = 1);

public:
	CAllocator m_Memory;
	int m_Size;

	// For easier access to the elements through the debugger
	// it's in release builds so this can be used in libraries correctly
	T *m_pElements;

	inline void ResetDbgInfo()
	{
		m_pElements = Base();
	}
};


//-----------------------------------------------------------------------------
// constructor, destructor
//-----------------------------------------------------------------------------
template< typename T, class A >
inline CUtlVector<T, A>::CUtlVector(int growSize, int initSize) :
	m_Memory(growSize, initSize), m_Size(0)
{
	ResetDbgInfo();
}

template< typename T, class A >
inline CUtlVector<T, A>::CUtlVector(T* pMemory, int allocationCount, int numElements) :
	m_Memory(pMemory, allocationCount), m_Size(numElements)
{
	ResetDbgInfo();
}

template< typename T, class A >
inline CUtlVector<T, A>::~CUtlVector()
{
	Purge();
}

template< typename T, class A >
inline CUtlVector<T, A>& CUtlVector<T, A>::operator=(const CUtlVector<T, A> &other)
{
	int nCount = other.Count();
	SetSize(nCount);
	for (int i = 0; i < nCount; i++) {
		(*this)[i] = other[i];
	}
	return *this;
}


//-----------------------------------------------------------------------------
// element access
//-----------------------------------------------------------------------------
template< typename T, class A >
inline T& CUtlVector<T, A>::operator[](int i)
{
	assert(i < m_Size);
	return m_Memory[i];
}

template< typename T, class A >
inline const T& CUtlVector<T, A>::operator[](int i) const
{
	assert(i < m_Size);
	return m_Memory[i];
}

template< typename T, class A >
inline T& CUtlVector<T, A>::Element(int i)
{
	assert(i < m_Size);
	return m_Memory[i];
}

template< typename T, class A >
inline const T& CUtlVector<T, A>::Element(int i) const
{
	assert(i < m_Size);
	return m_Memory[i];
}

template< typename T, class A >
inline T& CUtlVector<T, A>::Head()
{
	assert(m_Size > 0);
	return m_Memory[0];
}

template< typename T, class A >
inline const T& CUtlVector<T, A>::Head() const
{
	assert(m_Size > 0);
	return m_Memory[0];
}

template< typename T, class A >
inline T& CUtlVector<T, A>::Tail()
{
	assert(m_Size > 0);
	return m_Memory[m_Size - 1];
}

template< typename T, class A >
inline const T& CUtlVector<T, A>::Tail() const
{
	assert(m_Size > 0);
	return m_Memory[m_Size - 1];
}


//-----------------------------------------------------------------------------
// Count
//-----------------------------------------------------------------------------
template< typename T, class A >
inline int CUtlVector<T, A>::Count() const
{
	return m_Size;
}


//-----------------------------------------------------------------------------
// Is element index valid?
//-----------------------------------------------------------------------------
template< typename T, class A >
inline bool CUtlVector<T, A>::IsValidIndex(int i) const
{
	return (i >= 0) && (i < m_Size);
}


//-----------------------------------------------------------------------------
// Returns in invalid index
//-----------------------------------------------------------------------------
template< typename T, class A >
inline int CUtlVector<T, A>::InvalidIndex()
{
	return -1;
}


//-----------------------------------------------------------------------------
// Grows the vector
//-----------------------------------------------------------------------------
template< typename T, class A >
void CUtlVector<T, A>::GrowVector(int num)
{
	if (m_Size + num > m_Memory.NumAllocated()) {
		m_Memory.Grow(m_Size + num - m_Memory.NumAllocated());
	}

	m_Size += num;
	ResetDbgInfo();
}


//-----------------------------------------------------------------------------
// Sorts the vector
//-----------------------------------------------------------------------------
template< typename T, class A >
void CUtlVector<T, A>::Sort(int(__cdecl *pfnCompare)(const T *, const T *))
{
	typedef int(__cdecl *QSortCompareFunc_t)(const void *, const void *);
	if (Count() <= 1)
		return;

	if (Base()) {
		qsort(Base(), Count(), sizeof(T), (QSortCompareFunc_t)(pfnCompare));
	}
	else {
		assert(0);
		// this path is untested
		// if you want to sort vectors that use a non-sequential memory allocator,
		// you'll probably want to patch in a quicksort algorithm here
		// I just threw in this bubble sort to have something just in case...

		for (int i = m_Size - 1; i >= 0; --i) {
			for (int j = 1; j <= i; ++j) {
				if (pfnCompare(&Element(j - 1), &Element(j)) < 0) {
					V_swap(Element(j - 1), Element(j));
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Makes sure we have enough memory allocated to store a requested # of elements
//-----------------------------------------------------------------------------
template< typename T, class A >
void CUtlVector<T, A>::EnsureCapacity(int num)
{
	MEM_ALLOC_CREDIT_CLASS();
	m_Memory.EnsureCapacity(num);
	ResetDbgInfo();
}


//-----------------------------------------------------------------------------
// Makes sure we have at least this many elements
//-----------------------------------------------------------------------------
template< typename T, class A >
void CUtlVector<T, A>::EnsureCount(int num)
{
	if (Count() < num) {
		AddMultipleToTail(num - Count());
	}
}


//-----------------------------------------------------------------------------
// Shifts elements
//-----------------------------------------------------------------------------
template< typename T, class A >
void CUtlVector<T, A>::ShiftElementsRight(int elem, int num)
{
	assert(IsValidIndex(elem) || (m_Size == 0) || (num == 0));
	int numToMove = m_Size - elem - num;
	if ((numToMove > 0) && (num > 0))
		memmove(&Element(elem + num), &Element(elem), numToMove * sizeof(T));
}

template< typename T, class A >
void CUtlVector<T, A>::ShiftElementsLeft(int elem, int num)
{
	assert(IsValidIndex(elem) || (m_Size == 0) || (num == 0));
	int numToMove = m_Size - elem - num;
	if ((numToMove > 0) && (num > 0)) {
		memmove(&Element(elem), &Element(elem + num), numToMove * sizeof(T));

#ifdef _DEBUG
		memset(&Element(m_Size - num), 0xDD, num * sizeof(T));
#endif
	}
}


//-----------------------------------------------------------------------------
// Adds an element, uses default constructor
//-----------------------------------------------------------------------------
template< typename T, class A >
inline int CUtlVector<T, A>::AddToHead()
{
	return InsertBefore(0);
}

template< typename T, class A >
inline int CUtlVector<T, A>::AddToTail()
{
	return InsertBefore(m_Size);
}

template< typename T, class A >
inline int CUtlVector<T, A>::InsertAfter(int elem)
{
	return InsertBefore(elem + 1);
}

template< typename T, class A >
int CUtlVector<T, A>::InsertBefore(int elem)
{
	// Can insert at the end
	assert((elem == Count()) || IsValidIndex(elem));

	GrowVector();
	ShiftElementsRight(elem);
	Construct(&Element(elem));
	return elem;
}


//-----------------------------------------------------------------------------
// Adds an element, uses copy constructor
//-----------------------------------------------------------------------------
template< typename T, class A >
inline int CUtlVector<T, A>::AddToHead(const T& src)
{
	// Can't insert something that's in the list... reallocation may hose us
	assert((Base() == NULL) || (&src < Base()) || (&src >= (Base() + Count())));
	return InsertBefore(0, src);
}

template< typename T, class A >
inline int CUtlVector<T, A>::AddToTail(const T& src)
{
	// Can't insert something that's in the list... reallocation may hose us
	assert((Base() == NULL) || (&src < Base()) || (&src >= (Base() + Count())));
	return InsertBefore(m_Size, src);
}

template< typename T, class A >
inline int CUtlVector<T, A>::InsertAfter(int elem, const T& src)
{
	// Can't insert something that's in the list... reallocation may hose us
	assert((Base() == NULL) || (&src < Base()) || (&src >= (Base() + Count())));
	return InsertBefore(elem + 1, src);
}

//-----------------------------------------------------------------------------
// Adds multiple elements, uses default constructor
//-----------------------------------------------------------------------------
template< typename T, class A >
inline int CUtlVector<T, A>::AddMultipleToHead(int num)
{
	return InsertMultipleBefore(0, num);
}

template< typename T, class A >
inline int CUtlVector<T, A>::AddMultipleToTail(int num)
{
	return InsertMultipleBefore(m_Size, num);
}

template< typename T, class A >
inline int CUtlVector<T, A>::AddMultipleToTail(int num, const T *pToCopy)
{
	// Can't insert something that's in the list... reallocation may hose us
	assert((Base() == NULL) || !pToCopy || (pToCopy + num <= Base()) || (pToCopy >= (Base() + Count())));

	return InsertMultipleBefore(m_Size, num, pToCopy);
}

template< typename T, class A >
int CUtlVector<T, A>::InsertMultipleAfter(int elem, int num)
{
	return InsertMultipleBefore(elem + 1, num);
}


template< typename T, class A >
void CUtlVector<T, A>::SetCount(int count)
{
	RemoveAll();
	AddMultipleToTail(count);
}

template< typename T, class A >
inline void CUtlVector<T, A>::SetSize(int size)
{
	SetCount(size);
}

template< typename T, class A >
void CUtlVector<T, A>::SetCountNonDestructively(int count)
{
	int delta = count - m_Size;
	if (delta > 0) AddMultipleToTail(delta);
	else if (delta < 0) RemoveMultipleFromTail(-delta);
}

template< typename T, class A >
void CUtlVector<T, A>::CopyArray(const T *pArray, int size)
{
	// Can't insert something that's in the list... reallocation may hose us
	assert((Base() == NULL) || !pArray || (Base() >= (pArray + size)) || (pArray >= (Base() + Count())));

	SetSize(size);
	for (int i = 0; i < size; i++) {
		(*this)[i] = pArray[i];
	}
}

template< typename T, class A >
void CUtlVector<T, A>::Swap(CUtlVector< T, A > &vec)
{
	m_Memory.Swap(vec.m_Memory);
	V_swap(m_Size, vec.m_Size);
#ifndef _X360
	V_swap(m_pElements, vec.m_pElements);
#endif
}

template< typename T, class A >
int CUtlVector<T, A>::AddVectorToTail(CUtlVector const &src)
{
	assert(&src != this);

	int base = Count();

	// Make space.
	int nSrcCount = src.Count();
	EnsureCapacity(base + nSrcCount);

	// Copy the elements.	
	m_Size += nSrcCount;
	for (int i = 0; i < nSrcCount; i++) {
		CopyConstruct(&Element(base + i), src[i]);
	}
	return base;
}

template< typename T, class A >
inline int CUtlVector<T, A>::InsertMultipleBefore(int elem, int num)
{
	if (num == 0)
		return elem;

	// Can insert at the end
	assert((elem == Count()) || IsValidIndex(elem));

	GrowVector(num);
	ShiftElementsRight(elem, num);

	// Invoke default constructors
	for (int i = 0; i < num; ++i) {
		Construct(&Element(elem + i));
	}

	return elem;
}

template< typename T, class A >
inline int CUtlVector<T, A>::InsertMultipleBefore(int elem, int num, const T *pToInsert)
{
	if (num == 0)
		return elem;

	// Can insert at the end
	assert((elem == Count()) || IsValidIndex(elem));

	GrowVector(num);
	ShiftElementsRight(elem, num);

	// Invoke default constructors
	if (!pToInsert) {
		for (int i = 0; i < num; ++i) {
			Construct(&Element(elem + i));
		}
	}
	else {
		for (int i = 0; i < num; i++) {
			CopyConstruct(&Element(elem + i), pToInsert[i]);
		}
	}

	return elem;
}


//-----------------------------------------------------------------------------
// Finds an element (element needs operator== defined)
//-----------------------------------------------------------------------------
template< typename T, class A >
int CUtlVector<T, A>::GetOffset(const T& src) const
{
	for (int i = 0; i < Count(); ++i) {
		if (Element(i) == src)
			return i;
	}
	return -1;
}

template< typename T, class A >
void CUtlVector<T, A>::FillWithValue(const T& src)
{
	for (int i = 0; i < Count(); i++) {
		Element(i) = src;
	}
}

template< typename T, class A >
bool CUtlVector<T, A>::HasElement(const T& src) const
{
	return (GetOffset(src) >= 0);
}


//-----------------------------------------------------------------------------
// Element removal
//-----------------------------------------------------------------------------
template< typename T, class A >
void CUtlVector<T, A>::FastRemove(int elem)
{
	assert(IsValidIndex(elem));

	Destruct(&Element(elem));
	if (m_Size > 0) {
		if (elem != m_Size - 1)
			memcpy(&Element(elem), &Element(m_Size - 1), sizeof(T));
		--m_Size;
	}
}

template< typename T, class A >
void CUtlVector<T, A>::Remove(int elem)
{
	Destruct(&Element(elem));
	ShiftElementsLeft(elem);
	--m_Size;
}

template< typename T, class A >
bool CUtlVector<T, A>::FindAndRemove(const T& src)
{
	int elem = GetOffset(src);
	if (elem != -1) {
		Remove(elem);
		return true;
	}
	return false;
}

template< typename T, class A >
bool CUtlVector<T, A>::FindAndFastRemove(const T& src)
{
	int elem = GetOffset(src);
	if (elem != -1) {
		FastRemove(elem);
		return true;
	}
	return false;
}

template< typename T, class A >
void CUtlVector<T, A>::RemoveMultiple(int elem, int num)
{
	assert(elem >= 0);
	assert(elem + num <= Count());

	for (int i = elem + num; --i >= elem; )
		Destruct(&Element(i));

	ShiftElementsLeft(elem, num);
	m_Size -= num;
}

template< typename T, class A >
void CUtlVector<T, A>::RemoveMultipleFromHead(int num)
{
	assert(num <= Count());

	for (int i = num; --i >= 0; )
		Destruct(&Element(i));

	ShiftElementsLeft(0, num);
	m_Size -= num;
}

template< typename T, class A >
void CUtlVector<T, A>::RemoveMultipleFromTail(int num)
{
	assert(num <= Count());

	for (int i = m_Size - num; i < m_Size; i++)
		Destruct(&Element(i));

	m_Size -= num;
}

//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose:
//
// $NoKeywords: $
//
//===========================================================================//
#pragma once

#include <malloc.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <new.h>

#define COMPILER_MSVC

//-----------------------------------------------------------------------------
// NOTE: All compiler defines are Set up in the base VPC scripts
// COMPILER_MSVC, COMPILER_MSVC32, COMPILER_MSVC64, COMPILER_MSVCX360
// COMPILER_GCC
// The rationale for this is that we need COMPILER_MSVC for the pragma blocks
// #pragma once that occur at the top of all header files, therefore we can't
// place the defines for these in here.
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Set up platform defines.
//-----------------------------------------------------------------------------
#ifdef _WIN32
#define IsPlatformLinux()	false
#define IsPlatformPosix()	false
#define IsPlatformOSX()		false
#define IsPlatformPS3()		false
#define IsPlatformWindows() true
#ifndef PLATFORM_WINDOWS
#define PLATFORM_WINDOWS	1
#endif

#ifndef _X360
#define IsPlatformX360() false
#define IsPlatformWindowsPC() true
#define PLATFORM_WINDOWS_PC 1

#ifdef _WIN64
#define IsPlatformWindowsPC64() true
#define IsPlatformWindowsPC32() false
#define PLATFORM_WINDOWS_PC64 1
#else
#define IsPlatformWindowsPC64() false
#define IsPlatformWindowsPC32() true
#define PLATFORM_WINDOWS_PC32 1
#endif

#else // _X360

#define IsPlatformWindowsPC()	false
#define IsPlatformWindowsPC64() false
#define IsPlatformWindowsPC32() false
#define IsPlatformX360()		true
#define PLATFORM_X360 1

#endif // _X360

#elif defined(POSIX)
#define IsPlatformX360()		false
#define IsPlatformPS3()			false
#define IsPlatformWindows()		false
#define IsPlatformWindowsPC()	false
#define IsPlatformWindowsPC64()	false
#define IsPlatformWindowsPC32()	false
#define IsPlatformPosix()		true
#ifndef PLATFORM_POSIX
#define PLATFORM_POSIX 1
#endif

#if defined( LINUX )
#define IsPlatformLinux() true
#define IsPlatformOSX() false
#ifndef PLATFORM_LINUX
#define PLATFORM_LINUX 1
#endif
#elif defined ( OSX )
#define IsPlatformLinux() false
#define IsPlatformOSX() true
#ifndef PLATFORM_OSX
#define PLATFORM_OSX 1
#endif
#else
#define IsPlatformLinux() false
#define IsPlatformOSX() false
#endif

#else
#error
#endif

//-----------------------------------------------------------------------------
// Set up platform type defines.
//-----------------------------------------------------------------------------
#ifdef PLATFORM_X360
#ifndef _CONSOLE
#define _CONSOLE
#endif
#define IsPC()		false
#define IsConsole() true
#else
#define IsPC()		true
#define IsConsole() false
#endif



//-----------------------------------------------------------------------------
// Set up build configuration defines.
//-----------------------------------------------------------------------------
#ifdef _CERT
#define IsCert() true
#else
#define IsCert() false
#endif

#ifdef _DEBUG
#define IsRelease() false
#define IsDebug() true
#else
#define IsRelease() true
#define IsDebug() false
#endif

#ifdef _RETAIL
#define IsRetail() true
#else
#define IsRetail() false
#endif

// Maximum and minimum representable values
#if !defined(PLATFORM_OSX) && !defined(__STDC_LIMIT_MACROS)

#ifndef INT8_MAX
#define  INT8_MAX			SCHAR_MAX
#endif
#ifndef INT16_MAX
#define  INT16_MAX			SHRT_MAX
#endif
#ifndef INT32_MAX
#define  INT32_MAX			LONG_MAX
#endif
#ifndef INT64_MAX
#define  INT64_MAX			(((int64_t)~0) >> 1)
#endif

#ifndef INT8_MIN
#define  INT8_MIN			SCHAR_MIN
#endif
#ifndef INT16_MIN
#define  INT16_MIN			SHRT_MIN
#endif
#ifndef INT32_MIN
#define  INT32_MIN			LONG_MIN
#endif
#ifndef INT64_MIN
#define  INT64_MIN			(((int64_t)1) << 63)
#endif

#ifndef UINT8_MAX
#define  UINT8_MAX			((uint8_t)~0)
#endif
#ifndef UINT16_MAX
#define  UINT16_MAX			((uint16)~0)
#endif
#ifndef UINT32_MAX
#define  UINT32_MAX			((uint32_t)~0)
#endif
#ifndef UINT16_MAX
#define  UINT64_MAX			((uint64_t)~0)
#endif

#ifndef UINT8_MIN
#define  UINT8_MIN			0
#endif
#ifndef UINT16_MIN
#define  UINT16_MIN			0
#endif
#ifndef UINT32_MIN
#define  UINT32_MIN			0
#endif
#ifndef UINT64_MIN
#define  UINT64_MIN			0
#endif

#endif // !PLATFORM_OSX && !__STDC_LIMIT_MACROS

#ifndef  UINT_MIN
#define  UINT_MIN			UINT32_MIN
#endif

#define  FLOAT32_MAX		FLT_MAX
#define  FLOAT64_MAX		DBL_MAX

#ifdef GNUC
#undef offsetof
//#define offsetof( type, var ) __builtin_offsetof( type, var ) 
#define offsetof(s,m)	(size_t)&(((s *)0)->m)
#else
#include <stddef.h>
#undef offsetof
#define offsetof(s,m)	(size_t)&(((s *)0)->m)
#endif


#define  FLOAT32_MIN		FLT_MIN
#define  FLOAT64_MIN		DBL_MIN

//-----------------------------------------------------------------------------
// Long is evil because it's treated differently by different compilers
// Preventing its use is nasty however. This #define, which should be
// turned on in individual VPC files, causes you to include tier0/valve_off.h
// before standard C + windows headers, and include tier0/valve_on.h after
// standard C + windows headers. So, there's some painful overhead to disabling long
//-----------------------------------------------------------------------------
#ifdef DISALLOW_USE_OF_LONG
#define long			long_is_the_devil_stop_using_it_use_int32_or_int64
#endif


//-----------------------------------------------------------------------------
// Various compiler-specific keywords
//-----------------------------------------------------------------------------
#ifdef COMPILER_MSVC

#ifdef FORCEINLINE
#undef FORCEINLINE
#endif
#define STDCALL					__stdcall
#ifndef FASTCALL
#define  FASTCALL			__fastcall
#endif
#define FORCEINLINE				__forceinline
#define FORCEINLINE_TEMPLATE	__forceinline
#define NULLTERMINATED			__nullterminated

// This can be used to ensure the size of pointers to members when declaring
// a pointer type for a class that has only been forward declared
#define SINGLE_INHERITANCE		__single_inheritance
#define MULTIPLE_INHERITANCE	__multiple_inheritance
#define EXPLICIT				explicit
#define NO_VTABLE				__declspec( novtable )

// gcc doesn't allow storage specifiers on explicit template instatiation, but visual studio needs them to avoid link errors.
#define TEMPLATE_STATIC			static

// Used for dll exporting and importing
#define DLL_EXPORT				extern "C" __declspec( dllexport )
#define DLL_IMPORT				extern "C" __declspec( dllimport )

// Can't use extern "C" when DLL exporting a class
#define DLL_CLASS_EXPORT		__declspec( dllexport )
#define DLL_CLASS_IMPORT		__declspec( dllimport )

// Can't use extern "C" when DLL exporting a global
#define DLL_GLOBAL_EXPORT		extern __declspec( dllexport )
#define DLL_GLOBAL_IMPORT		extern __declspec( dllimport )

// Pass hints to the compiler to prevent it from generating unnessecary / stupid code
// in certain situations.  Several compilers other than MSVC also have an equivilent
// construct.
//
// Essentially the 'Hint' is that the condition specified is assumed to be true at
// that point in the compilation.  If '0' is passed, then the compiler assumes that
// any subsequent code in the same 'basic block' is unreachable, and thus usually
// removed.
#define HINT(THE_HINT)			__assume((THE_HINT))

// decls for aligning data
#define DECL_ALIGN(x)			__declspec( align( x ) )

// GCC had a few areas where it didn't construct objects in the same order 
// that Windows does. So when CVProfile::CVProfile() would access g_pMemAlloc,
// it would crash because the allocator wasn't initalized yet.
#define CONSTRUCT_EARLY

#define SELECTANY				__declspec(selectany)

#define RESTRICT				__restrict
#define RESTRICT_FUNC			__declspec(restrict)
#define FMTFUNCTION( a, b )
#define NOINLINE

#if !defined( NO_THREAD_LOCAL )
#define DECL_THREAD_LOCAL		__declspec(thread)
#endif 

#define DISABLE_VC_WARNING( x ) __pragma(warning(disable:4310) )
#define DEFAULT_VC_WARNING( x ) __pragma(warning(default:4310) )


#elif defined ( COMPILER_GCC )

#if (CROSS_PLATFORM_VERSION >= 1) && !defined( PLATFORM_64BITS )
#define  STDCALL			__attribute__ ((__stdcall__))
#else
#define  STDCALL
#define  __stdcall			__attribute__ ((__stdcall__))
#endif

#define  FASTCALL
#ifdef _LINUX_DEBUGGABLE
#define  FORCEINLINE
#else
#define  FORCEINLINE		inline
#endif

// GCC 3.4.1 has a bug in supporting forced inline of templated functions
// this macro lets us not force inlining in that case
#define FORCEINLINE_TEMPLATE	inline
#define SINGLE_INHERITANCE
#define MULTIPLE_INHERITANCE
#define EXPLICIT
#define NO_VTABLE

#define NULLTERMINATED			

#define TEMPLATE_STATIC

// Used for dll exporting and importing
#define DLL_EXPORT				extern "C" __attribute__ ((visibility("default")))
#define DLL_IMPORT				extern "C"

// Can't use extern "C" when DLL exporting a class
#define DLL_CLASS_EXPORT		__attribute__ ((visibility("default")))
#define DLL_CLASS_IMPORT

// Can't use extern "C" when DLL exporting a global
#define DLL_GLOBAL_EXPORT		__attribute__((visibility("default")))
#define DLL_GLOBAL_IMPORT		extern

#define HINT(THE_HINT)			0
#define DECL_ALIGN(x)			__attribute__( ( aligned( x ) ) )
#define CONSTRUCT_EARLY			__attribute__((init_priority(101)))
#define SELECTANY				__attribute__((weak))
#define RESTRICT
#define RESTRICT_FUNC
#define FMTFUNCTION( fmtargnumber, firstvarargnumber ) __attribute__ (( format( printf, fmtargnumber, firstvarargnumber )))
#define NOINLINE				__attribute__ ((noinline))

#if !defined( NO_THREAD_LOCAL )
#define DECL_THREAD_LOCAL		__thread
#endif

#define DISABLE_VC_WARNING( x )
#define DEFAULT_VC_WARNING( x )

#else

#define DECL_ALIGN(x)			/* */
#define SELECTANY				static

#endif

#if defined( GNUC )
// gnuc has the align decoration at the end
#define ALIGN4
#define ALIGN8 
#define ALIGN16
#define ALIGN32
#define ALIGN128

#define ALIGN4_POST DECL_ALIGN(4)
#define ALIGN8_POST DECL_ALIGN(8)
#define ALIGN16_POST DECL_ALIGN(16)
#define ALIGN32_POST DECL_ALIGN(32)
#define ALIGN128_POST DECL_ALIGN(128)
#else
// MSVC has the align at the start of the struct
#define ALIGN4 DECL_ALIGN(4)
#define ALIGN8 DECL_ALIGN(8)
#define ALIGN16 DECL_ALIGN(16)
#define ALIGN32 DECL_ALIGN(32)
#define ALIGN128 DECL_ALIGN(128)

#define ALIGN4_POST
#define ALIGN8_POST
#define ALIGN16_POST
#define ALIGN32_POST
#define ALIGN128_POST
#endif


// This can be used to declare an abstract (interface only) class.
// Classes marked abstract should not be instantiated.  If they are, and access violation will occur.
//
// Example of use:
//
// abstract_class CFoo
// {
//      ...
// }
//
// MSDN __declspec(novtable) documentation: http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vclang/html/_langref_novtable.asp
//
// Note: NJS: This is not enabled for regular PC, due to not knowing the implications of exporting a class with no no vtable.
//       It's probable that this shouldn't be an issue, but an experiment should be done to verify this.
//
#ifndef COMPILER_MSVCX360
#define abstract_class class
#else
#define abstract_class class NO_VTABLE
#endif


//-----------------------------------------------------------------------------
// Why do we need this? It would be nice to make it die die die
//-----------------------------------------------------------------------------
// Alloca defined for this platform
#if defined( COMPILER_MSVC ) && !defined( WINDED )
#if defined(_M_IX86)
#define __i386__	1
#endif
#endif

#if defined __i386__ && !defined __linux__
#define id386	1
#else
#define id386	0
#endif  // __i386__


//-----------------------------------------------------------------------------
// Disable annoying unhelpful warnings
//-----------------------------------------------------------------------------
#ifdef COMPILER_MSVC
// Remove warnings from warning level 4.
#pragma warning(disable : 4514) // warning C4514: 'acosl' : unreferenced inline function has been removed
#pragma warning(disable : 4100) // warning C4100: 'hwnd' : unreferenced formal parameter
#pragma warning(disable : 4127) // warning C4127: conditional expression is constant
#pragma warning(disable : 4512) // warning C4512: 'InFileRIFF' : assignment operator could not be generated
#pragma warning(disable : 4611) // warning C4611: interaction between '_setjmp' and C++ object destruction is non-portable
#pragma warning(disable : 4710) // warning C4710: function 'x' not inlined
#pragma warning(disable : 4702) // warning C4702: unreachable code
#pragma warning(disable : 4505) // unreferenced local function has been removed
#pragma warning(disable : 4239) // nonstandard extension used : 'argument' ( conversion from class Vector to class Vector& )
#pragma warning(disable : 4097) // typedef-name 'BaseClass' used as synonym for class-name 'CFlexCycler::CBaseFlex'
#pragma warning(disable : 4324) // Padding was added at the end of a structure
#pragma warning(disable : 4244) // type conversion warning.
#pragma warning(disable : 4305)	// truncation from 'const double ' to 'float '
#pragma warning(disable : 4786)	// Disable warnings about long symbol names
#pragma warning(disable : 4250) // 'X' : inherits 'Y::Z' via dominance
#pragma warning(disable : 4201) // nonstandard extension used : nameless struct/union

#if _MSC_VER >= 1300
#pragma warning(disable : 4511)	// Disable warnings about private copy constructors
#pragma warning(disable : 4121)	// warning C4121: 'symbol' : alignment of a member was sensitive to packing
#pragma warning(disable : 4530)	// warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc (disabled due to std headers having exception syntax)
#endif

#if _MSC_VER >= 1400
#pragma warning(disable : 4996)	// functions declared deprecated
#endif

// When we port to 64 bit, we'll have to resolve the int, ptr vs size_t 32/64 bit problems...
#if !defined( COMPILER_MSVC64 )
#if ( CROSS_PLATFORM_VERSION < 1 )
#pragma warning( disable : 4267 )	// conversion from 'size_t' to 'int', possible loss of data
#pragma warning( disable : 4311 )	// pointer truncation from 'char *' to 'int'
#pragma warning( disable : 4312 )	// conversion from 'unsigned int' to 'memhandle_t' of greater size
#endif
#endif

#endif


//-----------------------------------------------------------------------------
// Stack-based allocation related helpers
//-----------------------------------------------------------------------------
#if defined( COMPILER_GCC )

#define stackalloc( _size )		alloca( ALIGN_VALUE( _size, 16 ) )

#ifdef PLATFORM_OSX
#define mallocsize( _p )	( malloc_size( _p ) )
#else
#define mallocsize( _p )	( malloc_usable_size( _p ) )
#endif

#elif defined ( COMPILER_MSVC )

#define stackalloc( _size )		_alloca( ALIGN_VALUE( _size, 16 ) )
#define mallocsize( _p )		( _msize( _p ) )

#endif

#define  stackfree( _p )			0


//-----------------------------------------------------------------------------
// Used to break into the debugger
//-----------------------------------------------------------------------------
#ifdef COMPILER_MSVC64
#define DebuggerBreak()		__debugbreak()
#elif COMPILER_MSVC32
#define DebuggerBreak()		__asm { int 3 }
#elif COMPILER_MSVCX360
#define DebuggerBreak()		DebugBreak()
#elif COMPILER_GCC 
#if defined( PLATFORM_CYGWIN ) || defined( PLATFORM_POSIX )
#define DebuggerBreak()		__asm__( "int $0x3;")
#else
#define DebuggerBreak()		asm( "int3" )
#endif
#endif


//-----------------------------------------------------------------------------
// DLL export for platform utilities
//-----------------------------------------------------------------------------
#ifndef STATIC_TIER0

#ifdef TIER0_DLL_EXPORT
#define PLATFORM_INTERFACE	DLL_EXPORT
#define PLATFORM_OVERLOAD	DLL_GLOBAL_EXPORT
#define PLATFORM_CLASS		DLL_CLASS_EXPORT
#else
#define PLATFORM_INTERFACE	DLL_IMPORT
#define PLATFORM_OVERLOAD	DLL_GLOBAL_IMPORT
#define PLATFORM_CLASS		DLL_CLASS_IMPORT
#endif

#else	// BUILD_AS_DLL

#define PLATFORM_INTERFACE	extern
#define PLATFORM_OVERLOAD
#define PLATFORM_CLASS

#endif	// BUILD_AS_DLL

//-----------------------------------------------------------------------------
// Posix platform helpers
//-----------------------------------------------------------------------------
#ifdef PLATFORM_POSIX

// Visual Studio likes to put an underscore in front of anything that looks like a portable function.
#define _strupr strupr
#define _getcwd getcwd
#define _open open
#define _lseek lseek
#define _read read
#define _close close
#define _vsnprintf vsnprintf
#define _stat stat
#define _O_RDONLY O_RDONLY
#define _stricmp strcasecmp
#define _finite finite
#define _unlink unlink
#define _putenv putenv
#define _chdir chdir
#define _access access
#define _strtoi64 strtoll

#if !defined( _snprintf )	// some vpc's define this on the command line
#define _snprintf snprintf
#endif

#include <alloca.h>
#include <unistd.h>											// Get unlink
#include <errno.h>

#endif // PLATFORM_POSIX


//-----------------------------------------------------------------------------
// Generally useful platform-independent macros (move to another file?)
//-----------------------------------------------------------------------------

// need macro for constant expression
#define ALIGN_VALUE( val, alignment ) ( ( val + alignment - 1 ) & ~( alignment - 1 ) ) 

// Force a function call site -not- to inlined. (useful for profiling)
#define DONT_INLINE(a) (((int)(a)+1)?(a):(a))

// Marks the codepath from here until the next branch entry point as unreachable,
// and asserts if any attempt is made to execute it.
#define UNREACHABLE() { Assert(0); HINT(0); }

// In cases where no default is present or appropriate, this causes MSVC to generate
// as little code as possible, and throw an assertion in debug.
#define NO_DEFAULT default: UNREACHABLE();

// Defines MAX_PATH
#ifndef MAX_PATH
#define MAX_PATH  260
#endif


//-----------------------------------------------------------------------------
// FP exception handling
//-----------------------------------------------------------------------------
//#define CHECK_FLOAT_EXCEPTIONS		1
//#define CHECK_FPU_CONTROL_WORD_SET	1	// x360 only

#if defined( COMPILER_MSVC64 )

inline void SetupFPUControlWord()
{
}

#elif defined ( COMPILER_MSVC32 )

inline void SetupFPUControlWordForceExceptions()
{
	// use local to Get and store control word
	uint16 tmpCtrlW;
	__asm
	{
		fnclex						/* clear all current exceptions */
		fnstcw word ptr[tmpCtrlW]	/* Get current control word */
		and [tmpCtrlW], 0FCC0h		/* Keep infinity control + rounding control */
		or [tmpCtrlW], 0230h		/* Set to 53-bit, mask only inexact, underflow */
		fldcw word ptr[tmpCtrlW]	/* put new control word in FPU */
	}
}

#ifdef CHECK_FLOAT_EXCEPTIONS

inline void SetupFPUControlWord()
{
	SetupFPUControlWordForceExceptions();
}

#else

inline void SetupFPUControlWord()
{
	// use local to Get and store control word
	uint16 tmpCtrlW;
	__asm
	{
		fnstcw word ptr[tmpCtrlW]	/* Get current control word */
		and [tmpCtrlW], 0FCC0h		/* Keep infinity control + rounding control */
		or [tmpCtrlW], 023Fh		/* Set to 53-bit, mask only inexact, underflow */
		fldcw word ptr[tmpCtrlW]	/* put new control word in FPU */
	}
}

#endif

#elif defined ( COMPILER_GCC )

inline void SetupFPUControlWord()
{
	__volatile unsigned short int __cw;
	__asm __volatile("fnstcw %0" : "=m" (__cw));
	__cw = __cw & 0x0FCC0;	// keep infinity control, keep rounding mode
	__cw = __cw | 0x023F;	// Set 53-bit, no exceptions
	__asm __volatile("fldcw %0" : : "m" (__cw));
}

#elif defined( COMPILER_MSVCX360 )

#ifdef CHECK_FPU_CONTROL_WORD_SET
FORCEINLINE bool IsFPUControlWordSet()
{
	float f = 0.996f;
	union
	{
		double flResult;
		int pResult[2];
	};
	flResult = __fctiw(f);
	return (pResult[1] == 1);
}
#else
#define IsFPUControlWordSet() true
#endif

inline void SetupFPUControlWord()
{
	// Set round-to-nearest in FPSCR
	// (cannot assemble, must use op-code form)
	__emit(0xFF80010C);	// mtfsfi  7,0

						// Favour compatibility over speed (make sure the VPU Set to Java-compliant mode)
						// NOTE: the VPU *always* uses round-to-nearest
	__vector4  a = { 0.0f, 0.0f, 0.0f, 0.0f };
	a;				//	Avoid compiler warning
	__asm
	{
		mtvscr a;	// Clear the Vector Status & Control Register to zero
	}
}

#endif // COMPILER_MSVCX360


//-----------------------------------------------------------------------------
// Purpose: Standard functions for handling endian-ness
//-----------------------------------------------------------------------------

//-------------------------------------
// Basic swaps
//-------------------------------------

template <typename T>
inline T WordSwapC(T w)
{
	uint16 temp;

	temp = ((*((uint16 *)&w) & 0xff00) >> 8);
	temp |= ((*((uint16 *)&w) & 0x00ff) << 8);

	return *((T*)&temp);
}

template <typename T>
inline T DWordSwapC(T dw)
{
	uint32_t temp;

	temp = *((uint32_t *)&dw) >> 24;
	temp |= ((*((uint32_t *)&dw) & 0x00FF0000) >> 8);
	temp |= ((*((uint32_t *)&dw) & 0x0000FF00) << 8);
	temp |= ((*((uint32_t *)&dw) & 0x000000FF) << 24);

	return *((T*)&temp);
}

//-------------------------------------
// Fast swaps
//-------------------------------------

#if defined( COMPILER_MSVCX360 )

#define WordSwap  WordSwap360Intr
#define DWordSwap DWordSwap360Intr

template <typename T>
inline T WordSwap360Intr(T w)
{
	T output;
	__storeshortbytereverse(w, 0, &output);
	return output;
}

template <typename T>
inline T DWordSwap360Intr(T dw)
{
	T output;
	__storewordbytereverse(dw, 0, &output);
	return output;
}

#elif defined( COMPILER_MSVC32 )

#define WordSwap  WordSwapAsm
#define DWordSwap DWordSwapAsm

#pragma warning(push)
#pragma warning (disable:4035) // no return value

template <typename T>
inline T WordSwapAsm(T w)
{
	__asm
	{
		mov ax, w
		xchg al, ah
	}
}

template <typename T>
inline T DWordSwapAsm(T dw)
{
	__asm
	{
		mov eax, dw
		bswap eax
	}
}

#pragma warning(pop)

#else

#define WordSwap  WordSwapC
#define DWordSwap DWordSwapC

#endif

//-------------------------------------
// The typically used methods.
//-------------------------------------

#if defined( _SGI_SOURCE ) || defined( PLATFORM_X360 )
#define	PLAT_BIG_ENDIAN 1
#else
#define PLAT_LITTLE_ENDIAN 1
#endif


// If a swapped float passes through the fpu, the bytes may Get changed.
// Prevent this by swapping floats as DWORDs.
#define SafeSwapFloat( pOut, pIn )	(*((unsigned int*)pOut) = DWordSwap( *((unsigned int*)pIn) ))

#if defined(PLAT_LITTLE_ENDIAN)
#define BigShort( val )				WordSwap( val )
#define BigWord( val )				WordSwap( val )
#define BigLong( val )				DWordSwap( val )
#define BigDWord( val )				DWordSwap( val )
#define LittleShort( val )			( val )
#define LittleWord( val )			( val )
#define LittleLong( val )			( val )
#define LittleDWord( val )			( val )
#define SwapShort( val )			BigShort( val )
#define SwapWord( val )				BigWord( val )
#define SwapLong( val )				BigLong( val )
#define SwapDWord( val )			BigDWord( val )

// Pass floats by pointer for swapping to avoid truncation in the fpu
#define BigFloat( pOut, pIn )		SafeSwapFloat( pOut, pIn )
#define LittleFloat( pOut, pIn )	( *pOut = *pIn )
#define SwapFloat( pOut, pIn )		BigFloat( pOut, pIn )

#elif defined(PLAT_BIG_ENDIAN)

#define BigShort( val )				( val )
#define BigWord( val )				( val )
#define BigLong( val )				( val )
#define BigDWord( val )				( val )
#define LittleShort( val )			WordSwap( val )
#define LittleWord( val )			WordSwap( val )
#define LittleLong( val )			DWordSwap( val )
#define LittleDWord( val )			DWordSwap( val )
#define SwapShort( val )			LittleShort( val )
#define SwapWord( val )				LittleWord( val )
#define SwapLong( val )				LittleLong( val )
#define SwapDWord( val )			LittleDWord( val )

// Pass floats by pointer for swapping to avoid truncation in the fpu
#define BigFloat( pOut, pIn )		( *pOut = *pIn )
#define LittleFloat( pOut, pIn )	SafeSwapFloat( pOut, pIn )
#define SwapFloat( pOut, pIn )		LittleFloat( pOut, pIn )

#else

// @Note (toml 05-02-02): this technique expects the compiler to
// optimize the expression and eliminate the other path. On any new
// platform/compiler this should be tested.
inline short BigShort(short val) { int test = 1; return (*(char *)&test == 1) ? WordSwap(val) : val; }
inline uint16 BigWord(uint16 val) { int test = 1; return (*(char *)&test == 1) ? WordSwap(val) : val; }
inline long BigLong(long val) { int test = 1; return (*(char *)&test == 1) ? DWordSwap(val) : val; }
inline uint32_t BigDWord(uint32_t val) { int test = 1; return (*(char *)&test == 1) ? DWordSwap(val) : val; }
inline short LittleShort(short val) { int test = 1; return (*(char *)&test == 1) ? val : WordSwap(val); }
inline uint16 LittleWord(uint16 val) { int test = 1; return (*(char *)&test == 1) ? val : WordSwap(val); }
inline long LittleLong(long val) { int test = 1; return (*(char *)&test == 1) ? val : DWordSwap(val); }
inline uint32_t LittleDWord(uint32_t val) { int test = 1; return (*(char *)&test == 1) ? val : DWordSwap(val); }
inline short SwapShort(short val) { return WordSwap(val); }
inline uint16 SwapWord(uint16 val) { return WordSwap(val); }
inline long SwapLong(long val) { return DWordSwap(val); }
inline uint32_t SwapDWord(uint32_t val) { return DWordSwap(val); }

// Pass floats by pointer for swapping to avoid truncation in the fpu
inline void BigFloat(float *pOut, const float *pIn) { int test = 1; (*(char *)&test == 1) ? SafeSwapFloat(pOut, pIn) : (*pOut = *pIn); }
inline void LittleFloat(float *pOut, const float *pIn) { int test = 1; (*(char *)&test == 1) ? (*pOut = *pIn) : SafeSwapFloat(pOut, pIn); }
inline void SwapFloat(float *pOut, const float *pIn) { SafeSwapFloat(pOut, pIn); }

#endif

inline uint32_t LoadLittleDWord(uint32_t *base, unsigned int dwordIndex)
{
	return LittleDWord(base[dwordIndex]);
}

inline void StoreLittleDWord(uint32_t *base, unsigned int dwordIndex, uint32_t dword)
{
	base[dwordIndex] = LittleDWord(dword);
}

// Protect against bad auto operator=
#define DISALLOW_OPERATOR_EQUAL( _classname )			\
	private:											\
		_classname &operator=( const _classname & );	\
	public:

// Define a reasonable operator=
#define IMPLEMENT_OPERATOR_EQUAL( _classname )			\
	public:												\
		_classname &operator=( const _classname &src )	\
		{												\
			memcpy( this, &src, sizeof(_classname) );	\
			return *this;								\
		}

#if _X360
#define Plat_FastMemset XMemSet
#define Plat_FastMemcpy XMemCpy
#else
#define Plat_FastMemset memset
#define Plat_FastMemcpy memcpy
#endif

//-----------------------------------------------------------------------------
// XBOX Components valid in PC compilation space
//-----------------------------------------------------------------------------

#define XBOX_DVD_SECTORSIZE			2048
#define XBOX_DVD_ECC_SIZE			32768 // driver reads in quantum ECC blocks
#define XBOX_HDD_SECTORSIZE			512

// Custom windows messages for Xbox input
#define WM_XREMOTECOMMAND					(WM_USER + 100)
#define WM_XCONTROLLER_KEY					(WM_USER + 101)
#define WM_SYS_UI							(WM_USER + 102)
#define WM_SYS_SIGNINCHANGED				(WM_USER + 103)
#define WM_SYS_STORAGEDEVICESCHANGED		(WM_USER + 104)
#define WM_SYS_PROFILESETTINGCHANGED		(WM_USER + 105)
#define WM_SYS_MUTELISTCHANGED				(WM_USER + 106)
#define WM_SYS_INPUTDEVICESCHANGED			(WM_USER + 107)
#define WM_SYS_INPUTDEVICECONFIGCHANGED		(WM_USER + 108)
#define WM_LIVE_CONNECTIONCHANGED			(WM_USER + 109)
#define WM_LIVE_INVITE_ACCEPTED				(WM_USER + 110)
#define WM_LIVE_LINK_STATE_CHANGED			(WM_USER + 111)
#define WM_LIVE_CONTENT_INSTALLED			(WM_USER + 112)
#define WM_LIVE_MEMBERSHIP_PURCHASED		(WM_USER + 113)
#define WM_LIVE_VOICECHAT_AWAY				(WM_USER + 114)
#define WM_LIVE_PRESENCE_CHANGED			(WM_USER + 115)
#define WM_FRIENDS_PRESENCE_CHANGED			(WM_USER + 116)
#define WM_FRIENDS_FRIEND_ADDED				(WM_USER + 117)
#define WM_FRIENDS_FRIEND_REMOVED			(WM_USER + 118)
#define WM_CUSTOM_GAMEBANNERPRESSED			(WM_USER + 119)
#define WM_CUSTOM_ACTIONPRESSED				(WM_USER + 120)
#define WM_XMP_STATECHANGED					(WM_USER + 121)
#define WM_XMP_PLAYBACKBEHAVIORCHANGED		(WM_USER + 122)
#define WM_XMP_PLAYBACKCONTROLLERCHANGED	(WM_USER + 123)

inline const char *GetPlatformExt(void)
{
	return IsPlatformX360() ? ".360" : "";
}

// flat view, 6 hw threads
#define XBOX_PROCESSOR_0			( 1<<0 )
#define XBOX_PROCESSOR_1			( 1<<1 )
#define XBOX_PROCESSOR_2			( 1<<2 )
#define XBOX_PROCESSOR_3			( 1<<3 )
#define XBOX_PROCESSOR_4			( 1<<4 )
#define XBOX_PROCESSOR_5			( 1<<5 )

// core view, 3 cores with 2 hw threads each
#define XBOX_CORE_0_HWTHREAD_0		XBOX_PROCESSOR_0
#define XBOX_CORE_0_HWTHREAD_1		XBOX_PROCESSOR_1
#define XBOX_CORE_1_HWTHREAD_0		XBOX_PROCESSOR_2
#define XBOX_CORE_1_HWTHREAD_1		XBOX_PROCESSOR_3
#define XBOX_CORE_2_HWTHREAD_0		XBOX_PROCESSOR_4
#define XBOX_CORE_2_HWTHREAD_1		XBOX_PROCESSOR_5

//-----------------------------------------------------------------------------
// Include additional dependant header components.
//-----------------------------------------------------------------------------
#if defined( PLATFORM_X360 )
#include "xbox/xbox_core.h"
#endif

//-----------------------------------------------------------------------------
// Methods to invoke the constructor, copy constructor, and destructor
//-----------------------------------------------------------------------------

template <class T>
inline T* Construct(T* pMemory)
{
	return ::new(pMemory) T;
}

template <class T, typename ARG1>
inline T* Construct(T* pMemory, ARG1 a1)
{
	return ::new(pMemory) T(a1);
}

template <class T, typename ARG1, typename ARG2>
inline T* Construct(T* pMemory, ARG1 a1, ARG2 a2)
{
	return ::new(pMemory) T(a1, a2);
}

template <class T, typename ARG1, typename ARG2, typename ARG3>
inline T* Construct(T* pMemory, ARG1 a1, ARG2 a2, ARG3 a3)
{
	return ::new(pMemory) T(a1, a2, a3);
}

template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
inline T* Construct(T* pMemory, ARG1 a1, ARG2 a2, ARG3 a3, ARG4 a4)
{
	return ::new(pMemory) T(a1, a2, a3, a4);
}

template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
inline T* Construct(T* pMemory, ARG1 a1, ARG2 a2, ARG3 a3, ARG4 a4, ARG5 a5)
{
	return ::new(pMemory) T(a1, a2, a3, a4, a5);
}

template <class T>
inline T* CopyConstruct(T* pMemory, T const& src)
{
	return ::new(pMemory) T(src);
}

template <class T>
inline void Destruct(T* pMemory)
{
	pMemory->~T();

#ifdef _DEBUG
	memset(pMemory, 0xDD, sizeof(T));
#endif
}


//
// GET_OUTER()
//
// A platform-independent way for a contained class to Get a pointer to its
// owner. If you know a class is exclusively used in the context of some
// "outer" class, this is a much more space efficient way to Get at the outer
// class than having the inner class store a pointer to it.
//
//	class COuter
//	{
//		class CInner // Note: this does not need to be a nested class to work
//		{
//			void PrintAddressOfOuter()
//			{
//				printf( "Outer is at 0x%x\n", GET_OUTER( COuter, m_Inner ) );
//			}
//		};
//
//		CInner m_Inner;
//		friend class CInner;
//	};

#define GET_OUTER( OuterType, OuterMember ) \
   ( ( OuterType * ) ( (uint8_t *)this - offsetof( OuterType, OuterMember ) ) )


/*	TEMPLATE_FUNCTION_TABLE()

(Note added to platform.h so platforms that correctly support templated
functions can handle portions as templated functions rather than wrapped
functions)

Helps automate the process of creating an array of function
templates that are all specialized by a single integer.
This sort of thing is often useful in optimization work.

For example, using TEMPLATE_FUNCTION_TABLE, this:

TEMPLATE_FUNCTION_TABLE(int, Function, ( int blah, int blah ), 10)
{
return argument * argument;
}

is equivilent to the following:

(NOTE: the function has to be wrapped in a class due to code
generation bugs involved with directly specializing a function
based on a constant.)

template<int argument>
class FunctionWrapper
{
public:
int Function( int blah, int blah )
{
return argument*argument;
}
}

typedef int (*FunctionType)( int blah, int blah );

class FunctionName
{
public:
enum { count = 10 };
FunctionType functions[10];
};

FunctionType FunctionName::functions[] =
{
FunctionWrapper<0>::Function,
FunctionWrapper<1>::Function,
FunctionWrapper<2>::Function,
FunctionWrapper<3>::Function,
FunctionWrapper<4>::Function,
FunctionWrapper<5>::Function,
FunctionWrapper<6>::Function,
FunctionWrapper<7>::Function,
FunctionWrapper<8>::Function,
FunctionWrapper<9>::Function
};
*/

PLATFORM_INTERFACE bool vtune(bool resume);


#define TEMPLATE_FUNCTION_TABLE(RETURN_TYPE, NAME, ARGS, COUNT)			  \
                                                                      \
typedef RETURN_TYPE (FASTCALL *__Type_##NAME) ARGS;						        \
																		                                  \
template<const int nArgument>											                    \
struct __Function_##NAME												                      \
{																		                                  \
	static RETURN_TYPE FASTCALL Run ARGS;								                \
};																		                                \
																		                                  \
template <const int i>														                    \
struct __MetaLooper_##NAME : __MetaLooper_##NAME<i-1>					        \
{																		                                  \
	__Type_##NAME func;													                        \
	inline __MetaLooper_##NAME() { func = __Function_##NAME<i>::Run; }	\
};																		                                \
																		                                  \
template<>																                            \
struct __MetaLooper_##NAME<0>											                    \
{																		                                  \
	__Type_##NAME func;													                        \
	inline __MetaLooper_##NAME() { func = __Function_##NAME<0>::Run; }	\
};																		                                \
																		                                  \
class NAME																                            \
{																		                                  \
private:																                              \
    static const __MetaLooper_##NAME<COUNT> m;							          \
public:																	                              \
	enum { count = COUNT };												                      \
	static const __Type_##NAME* functions;								              \
};																		                                \
const __MetaLooper_##NAME<COUNT> NAME::m;								              \
const __Type_##NAME* NAME::functions = (__Type_##NAME*)&m;				    \
template<const int nArgument>													                \
RETURN_TYPE FASTCALL __Function_##NAME<nArgument>::Run ARGS


#define LOOP_INTERCHANGE(BOOLEAN, CODE)\
	if( (BOOLEAN) )\
	{\
		CODE;\
	} else\
	{\
		CODE;\
	}

#ifdef COMPILER_MSVC
FORCEINLINE uint32_t RotateBitsLeft32(uint32_t nValue, int nRotateBits)
{
	return _rotl(nValue, nRotateBits);
}
FORCEINLINE uint64_t RotateBitsLeft64(uint64_t nValue, int nRotateBits)
{
	return _rotl64(nValue, nRotateBits);
}
FORCEINLINE uint32_t RotateBitsRight32(uint32_t nValue, int nRotateBits)
{
	return _rotr(nValue, nRotateBits);
}
FORCEINLINE uint64_t RotateBitsRight64(uint64_t nValue, int nRotateBits)
{
	return _rotr64(nValue, nRotateBits);
}
#endif

template< typename T, class A >
void CUtlVector<T, A>::RemoveAll()
{
	for (int i = m_Size; --i >= 0; ) {
		Destruct(&Element(i));
	}

	m_Size = 0;
}


//-----------------------------------------------------------------------------
// Memory deallocation
//-----------------------------------------------------------------------------

template< typename T, class A >
inline void CUtlVector<T, A>::Purge()
{
	RemoveAll();
	m_Memory.Purge();
	ResetDbgInfo();
}


template< typename T, class A >
inline void CUtlVector<T, A>::PurgeAndDeleteElements()
{
	for (int i = 0; i < m_Size; i++) {
		delete Element(i);
	}
	Purge();
}

template< typename T, class A >
inline void CUtlVector<T, A>::Compact()
{
	m_Memory.Purge(m_Size);
}

template< typename T, class A >
inline int CUtlVector<T, A>::NumAllocated() const
{
	return m_Memory.NumAllocated();
}


//-----------------------------------------------------------------------------
// Data and memory validation
//-----------------------------------------------------------------------------
#ifdef DBGFLAG_VALIDATE
template< typename T, class A >
void CUtlVector<T, A>::Validate(CValidator &validator, char *pchName)
{
	validator.Push(typeid(*this).name(), this, pchName);

	m_Memory.Validate(validator, "m_Memory");

	validator.Pop();
}
#endif // DBGFLAG_VALIDATE

// A vector class for storing pointers, so that the elements pointed to by the pointers are deleted
// on exit.
template<class T> class CUtlVectorAutoPurge : public CUtlVector< T, CUtlMemory< T, int> >
{
public:
	~CUtlVectorAutoPurge(void)
	{
		this->PurgeAndDeleteElements();
	}
};

// easy string list class with dynamically allocated strings. For use with V_SplitString, etc.
// Frees the dynamic strings in destructor.
class CUtlStringList : public CUtlVectorAutoPurge< char *>
{
public:
	void CopyAndAddToTail(char const *pString)			// clone the string and add to the end
	{
		char *pNewStr = new char[1 + strlen(pString)];
		strcpy_s(pNewStr, 1 + strlen(pString), pString);
		AddToTail(pNewStr);
	}

	static int __cdecl SortFunc(char * const * sz1, char * const * sz2)
	{
		return strcmp(*sz1, *sz2);
	}

};
class IRefCounted
{
private:
	volatile long refCount;

public:
	virtual void destructor(char bDelete) = 0;
	virtual bool OnFinalRelease() = 0;

	void unreference()
	{
		if (InterlockedDecrement(&refCount) == 0 && OnFinalRelease())
			destructor(1);
	}
};


class C_EconItemView
{
public:
	char pad_0000[4]; //0x0000
	CUtlVector<IRefCounted*> m_CustomMaterials; //0x0004
	char pad_0018[520]; //0x0018
	CUtlVector<IRefCounted*> m_VisualsDataProcessors; //0x0220
};

class C_AttributeManager
{
public:
	char pad_0000[64]; //0x0000
	C_EconItemView m_Item; //0x0040
};

class C_WeaponCSBase : public C_BaseEntity
{
public:
	char _pad_0x0000[2508];
	CUtlVector<IRefCounted*> m_CustomMaterials; //0x09DC
	char _pad_0x09F0[9120];
	C_AttributeManager m_AttributeManager; //0x2D80
	char _pad_0x2D94[812];
	bool m_bCustomMaterialInitialized; //0x3330
};

class CBaseWeaponWorldModel : public C_BaseEntity
{
public:
	inline int* GetModelIndex() {

		return (int*)((DWORD)this + 0x258);
	}
};

class CBaseCSGrenade : public C_BaseCombatWeapon
{
public:
	bool pin_pulled()
	{
		return *reinterpret_cast<float*>(uintptr_t(this) + 0x3332);
	}

	template<class T>
	T GetValue(const int offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(this) + offset);
	}

	float throw_time()
	{
		static int m_flNextPrimaryAttack = g_pNetvars->GetOffset("C_BaseCSGrenade", "m_fThrowTime");
		return GetValue<float>(m_flNextPrimaryAttack);
	}
};


class viewmodel_t : public C_BaseEntity {
public:
	NETVAR2(int, m_nModelIndex, "DT_BaseViewModel", "m_nModelIndex");
	NETVAR2(int, m_nViewModelIndex, "DT_BaseViewModel", "m_nViewModelIndex");
};

class C_BaseViewModel
{
public:

	inline DWORD GetOwner() {

		return *(PDWORD)((DWORD)this + 0x29CC);
	}

	inline int GetModelIndex() {

		return *(int*)((DWORD)this + 0x258);
	}
};


