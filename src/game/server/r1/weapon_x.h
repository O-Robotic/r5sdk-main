//===========================================================================//
//
// Purpose: 
//
//===========================================================================//
#ifndef WEAPON_X_H
#define WEAPON_X_H

#include "../baseanimating.h"
#include "game/shared/shared_activity.h"
#include "game/shared/predictioncopy.h"
#include "game/shared/r1/weapon_playerdata.h"
#include "game/shared/r1/smartammo.h"

class CWeaponX : CBaseAnimating
{
public:
	float GetZoomFOVInterpAmount(const float curTime) const;

private:
	EHANDLE m_weaponOwner;
	float m_lastPrimaryAttack;
	float m_nextReadyTime;
	float m_nextPrimaryAttackTime;
	float m_attackTimeThisFrame;
	int m_worldModelIndexOverride;
	int m_iWorldModelIndex;
	int m_holsterModelIndex;
	int m_droppedModelIndex;
	int m_nIdealSequence;
	int m_IdealActivity;
	int m_weaponActivity;
	int m_ActiveState;
	int m_ammoInClip;
	int m_ammoInStockpile;
	int m_lifetimeShots;
	float m_flTimeWeaponIdle;
	int m_weapState;
	bool m_allowedToUse;
	bool m_discarded;
	bool m_bInReload;
	char gap_123b[1];
	int m_forcedADS;
	char m_tossRelease;
	char gap_1241[3];
	sharedactivity_e m_customActivity;
	int m_customActivitySequence;
	EHANDLE m_customActivityOwner;
	float m_customActivityEndTime;
	char m_customActivityFlags;
	char gap_1255[3];
	WeaponPlayerData m_playerData;
	bool m_smartAmmoEnable;
	char gap_1339[7];
	SmartAmmo_WeaponData m_smartAmmo;
	bool m_needsReloadCheck;
	bool m_needsEmptyCycleCheck;
	char gap_1532[2];
	int m_skinOverride;
	bool m_skinOverrideIsValid;
	char gap_1539[3];
	float m_chargeStartTime;
	float m_chargeEndTime;
	float m_lastChargeFrac;
	float m_lastRegenTime;
	float m_cooldownEndTime;
	bool m_stockPileWasDraining;
	bool m_weaponIsCharging;
	bool m_weaponChargeLevelIncreasedAnimPlaying;
	char gap_1553[1];
	int m_lastChargeLevel;
	int m_chargeEnergyDepleteStepCounter;
	int m_burstFireCount;
	int m_burstFireIndex;
	int m_shotCount;
	float m_sustainedDischargeEndTime;
	float m_sustainedLaserCurrentSpread;
	bool m_sustainedDischargeIsInPrimaryAttack;
	char m_sustainedLaserNextRandomSeed;
	char gap_1572[2];
	int m_modBitfieldFromPlayer;
	int m_modBitfieldInternal;
	int m_modBitfieldCurrent;
	int m_curSharedEnergyCost;
	bool m_grappleWeaponNeedsDryfire;
	bool m_scriptActivated;
	bool m_isLoadoutPickup;
	char gap_1587[1];
	EHANDLE m_utilityEnt;
	int m_projectileModelIndex;
	int m_weaponNameIndex;
	int m_animModelIndexPredictingClientOnly;
	int m_animSequencePredictingClientOnly;
	bool m_shouldPlayIdleAnims;
	char gap_159d[3];
	int m_oaActiveOverride;
	char gap_15a4[4];
	void* m_weaponData;
	char m_weaponName[65];
	char gap_15f1[3];
	int m_oaScriptOverrideIndices[32];
	char gap_1674[4];
	char m_weaponScriptCB_[360];
	char m_modVars[4432];
	int m_latestActiveInventorySlot;
	int m_tracerAttachment[2];
	int m_damageSourceIdentifier;
	float m_flNextEmptySoundTime;
	int m_ownerMuzzleAttachment;
	short m_weaponInfoFileHandle;
	char m_activityModifierSymbolForName[2];
	bool m_activityModifierSymbolForNameIsSet;
	bool m_hasAltAnim_adsIn[3];
	bool m_hasAltAnim_adsOut[3];
	bool m_hasAltAnim_idle[3];
	bool m_hasAltAnim_attack[3];
	bool m_hasAltAnim_oneHandedAdsIn[3];
	bool m_hasAltAnim_oneHandedAdsOut[3];
	bool m_hasAltAnim_oneHandedIdle[3];
	bool m_hasAltAnim_oneHandedAttack[3];
	bool m_cookWarningSoundActive;
	bool m_bRemoveable;
	bool m_loopSoundActive_1p;
	bool m_loopSoundActive_3p;
	bool m_loopSoundActive_3pAsNPC;
	char gap_296a[2];
	float m_loopSoundLastAttackClockTime;
	float m_loopSoundLastAttackClockTimeWithFireDelay;
	int m_loopSoundCurrentParity;
	int m_loopSoundActiveParity_1p;
	float m_tossPrepStartTime;
	short m_prevViewModelWpnStr;
	short m_prevWorldModelWpnStr;
	short m_prevHolsterModelWpnStr;
	bool m_ziplineWeaponHasAdjust;
	char gap_2987[1];
	Vector3D m_ziplineWeaponAdjustInitialPosition;
	Vector3D m_ziplineWeaponAdjustInitialVelocity;
	float m_ziplineWeaponAdjustHitTime;
	Vector3D m_ziplineWeaponAdjustHitPosition;
	Vector3D m_ziplineWeaponAdjustHitNormal;
	int m_shotCountAtFrameStart;
	bool m_isHolstering;
	char gap_29c1[3];
	float m_sustainedDischargeStartTime;
	float m_sustainedDischargeNextPulseTime;
	float m_sustainedLaserNextSpreadPatternX;
	float m_sustainedLaserNextSpreadPatternY;
	char m_sustainedLaserNextSpreadPatternIndex;
	char gap_29d5[3];
	EHANDLE m_weaponOwnerPrevious;
	bool m_weaponOwnerPreviousWasNPC;
	char gap_29dd[3];
	EHANDLE m_physicsAttacker;
	bool m_forceReleaseFromServer;
	char gap_29e5[3];
	CWeaponX* m_smartAmmoNextWeapon;
	CWeaponX* m_smartAmmoPrevWeapon;
	float m_npcUseCheckTime;
	float m_npcUseCheckDist;
	char m_OnPlayerPickup[40];
	char m_OnNPCPickup[40];
	char m_OnCacheInteraction[40];
	char padding_or_data[8];
};

static_assert(sizeof(CWeaponX) == 0x2A80);

#endif // WEAPON_X_H
