﻿//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef PLAYERNET_VARS_H
#define PLAYERNET_VARS_H
#ifdef _WIN32
#pragma once
#endif
#include "mathlib/mathlib.h"
#include "shared_classnames.h"

class CFogParams
{
	void* __vftable;
	float botAlt;
	float topAlt;
	float halfDistBot;
	float halfDistTop;
	float distColorStr;
	float dirColorStr;
	float distOffset;
	float densityScale;
	float halfAngleDeg;
	float HDRColorScale;
	color32 distColor;
	color32 dirColor;
	Vector3D direction;
	float minFadeTime;
	bool forceOntoSky;
	bool enable;
	char gap_4a[2];
	int id;
};

struct sky3dparams_t
{
	void* __vftable;
	int scale;
	int cellNum;
	bool useWorldFog;
	char gap_11[7];
	CFogParams fog;
};

struct audioparams_t
{
	void* __vftable;
	Vector3D localSound[8];
	int soundscapeIndex;
	int localBits;
	int entIndex;
	char gap_74[4];
};

#endif // PLAYERNET_VARS_H
