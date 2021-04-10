#pragma once

#include "Antario/Utils/GlobalVars.h"
#include "Antario/SDK/CGlobalVarsBase.h"

class HideShots
{
public:
	int				 m_tick_to_shift = 0;
	int				 m_tick_to_recharge;
	bool			 m_charged;

	void Hideshots();
	bool CanFireWeapon(float curtime);
	bool CanFireWithExploit(int m_iShiftedTick);
	bool CanDT();
	void start();
	void end();
};

extern HideShots g_Hideshots;
