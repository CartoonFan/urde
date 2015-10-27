#ifndef _DNAMP1_PARAMETERS_HPP_
#define _DNAMP1_PARAMETERS_HPP_

#include "../../DNACommon/DNACommon.hpp"
#include "../ANCS.hpp"

namespace Retro
{
namespace DNAMP1
{

enum EPickupType
{
    PkPowerBeam,
    PkIceBeam,
    PkWaveBeam,
    PkPlasmaBeam,
    PkMissile,
    PkScanVisor,
    PkMorphBallBomb,
    PkPowerBomb,
    PkFlamethrower,
    PkChargeBeam,
    PkXRayVisor,
    PkIceSpreader,
    PkSpaceJump,
    PkMorphBall,
    PkCombatVisor,
    PkSpiderBall,
    PkPowerSuit,
    PkGravitySuit,
    PkVariaSuit,
    PkPhazonSuit,
    PkEnergyTank,
    PkUnknownItem1,
    PkHealthRefill,
    PkUnknownItem2,
    PkWaveBuster,
    PkTruth,
    PkStrength,
    PkElder,
    PkWild,
    PkLifeGiver,
    PkWarrior,
    PkChozo,
    PkNature,
    PkSun,
    PkWorld,
    PkSpirit,
    PkNewborn
};

enum ESpecialFunctionType
{
    SpFnWhat,
    SpFnPlayerFollowLocator,
    SpFnSpinnerController,
    SpFnObjectFollowLocator,
    SpFnFunction4,
    SpFnInventoryActivator,
    SpFnMapStation,
    SpFnSaveStation,
    SpFnIntroBossRingController,
    SpFnViewFrustumTest,
    SpFnShotSpinnerController,
    SpFnEscapeSequence,
    SpFnBossEnergyBar,
    SpFnEndGame,
    SpFnHUDFadeIn,
    SpFnCinematicSkip,
    SpFnScriptLyaerController,
    SpFnRainSimulator,
    SpFnAreaDamage,
    SpFnObjectFollowObject,
    SpFnHintSystem,
    SpFnDropBomb,
    SpFnFunction22,
    SpFnMissileStation,
    SpFnBillboard,
    SpFnPlayerInAreaRelay,
    SpFnHUDTarget,
    SpFnFogFader,
    SpFnEnterLogbook,
    SpFnPowerBombStation,
    SpFnEnding,
    SpFnFusionRelay,
    SpFnWeaponSwitch // PAL Only
};

struct AnimationParameters : BigYAML
{
    DECL_YAML
    UniqueID32 animationCharacterSet;
    Value<atUint32> character;
    Value<atUint32> defaultAnimation;

    UniqueID32 getCINF(PAKRouter<PAKBridge>& pakRouter) const
    {
        if (!animationCharacterSet)
            return UniqueID32();
        const NOD::Node* node;
        const PAK::Entry* ancsEnt = pakRouter.lookupEntry(animationCharacterSet, &node);
        ANCS ancs;
        {
            PAKEntryReadStream rs = ancsEnt->beginReadStream(*node);
            ancs.read(rs);
        }
        return ancs.characterSet.characters.at(character).cinf;
    }

    void nameANCS(PAKRouter<PAKBridge>& pakRouter, const std::string& name) const
    {
        if (!animationCharacterSet)
            return;
        PAK::Entry* ancsEnt = (PAK::Entry*)pakRouter.lookupEntry(animationCharacterSet);
        if (ancsEnt->name.empty())
            ancsEnt->name = name;
    }
};

struct BehaveChance : BigYAML
{
    DECL_YAML
    Value<atUint32> propertyCount;
    Value<float>    unknown1;
    Value<float>    unknown2;
    Value<float>    unknown3;
    Value<float>    unknown4;
    Value<float>    unknown5;
    Value<float>    unknown6;
    Value<float>    unknown7;
};

struct DamageInfo : BigYAML
{
    DECL_YAML
    Value<atUint32> propertyCount;
    Value<atUint32> weaponType;
    Value<float>    damage;
    Value<float>    radius;
    Value<float>    knockbackPower;
};

struct DamageVulnerability : BigYAML
{
    DECL_YAML
    Value<atUint32> propertyCount;
    Value<atUint32> power;
    Value<atUint32> ice;
    Value<atUint32> wave;
    Value<atUint32> plasma;
    Value<atUint32> bomb;
    Value<atUint32> powerBomb;
    Value<atUint32> missile;
    Value<atUint32> boostBall;
    Value<atUint32> phazon;
    Value<atUint32> enemyWeapon1;
    Value<atUint32> enemyWeapon2Poison;
    Value<atUint32> enemyWeapon3Lava;
    Value<atUint32> enemyWeapon4;
    Value<atUint32> unkownWeapon1;
    Value<atUint32> unkownWeapon2;
    Value<atUint32> unkownWeapon3;
    struct ChargedBeams : BigYAML
    {
        DECL_YAML
        Value<atUint32> propertyCount;
        Value<atUint32> power;
        Value<atUint32> ice;
        Value<atUint32> wave;
        Value<atUint32> plasma;
        Value<atUint32> phazon;
    } chargedBeams;

    struct BeamCombos : BigYAML
    {
        DECL_YAML
        Value<atUint32> propertyCount;
        Value<atUint32> superMissiles;
        Value<atUint32> iceSpreader;
        Value<atUint32> wavebuster;
        Value<atUint32> flameThrower;
        Value<atUint32> phazonCombo;
    } beamCombos;
};

struct FlareDefinition : BigYAML
{
    DECL_YAML
    Value<atUint32> propertyCount;
    UniqueID32      texture;
    Value<float>    unknown1;
    Value<float>    unknown2;
    Value<atVec4f>  unknown4; // CColor

    void nameIDs(PAKRouter<PAKBridge>& pakRouter, const std::string& name) const
    {
        if (texture)
        {
            PAK::Entry* ent = (PAK::Entry*)pakRouter.lookupEntry(texture);
            ent->name = name + "_texture";
        }
    }
};

struct GrappleParameters : BigYAML
{
    DECL_YAML
    Value<atUint32> propertyCount;
    Value<float>    unknown1;
    Value<float>    unknown2;
    Value<float>    unknown3;
    Value<float>    unknown4;
    Value<float>    unknown5;
    Value<float>    unknown6;
    Value<float>    unknown7;
    Value<float>    unknown8;
    Value<float>    unknown9;
    Value<float>    unknown10;
    Value<float>    unknown11;
    Value<bool>     disableTurning;
};

struct HealthInfo : BigYAML
{
    DECL_YAML
    Value<atUint32> propertyCount;
    Value<float>    health;
    Value<float>    knockbackResistence;
};

struct LightParameters : BigYAML
{
    DECL_YAML
    Value<atUint32> propertyCount;
    Value<bool>     unknown1;
    Value<float>    unknown2;
    Value<atUint32> shadowTesselation;
    Value<float>    unknown3;
    Value<float>    unknown4;
    Value<atVec4f>  unknown5; // CColor
    Value<bool>     unknown6;
    Value<atUint32> worldLightingOptions;
    Value<atUint32> lightRecalculationOptions;
    Value<atVec3f>  unknown7;
    Value<atUint32> unknown8;
    Value<atUint32> unknown9;
    Value<bool>     unknown10;
    Value<atUint32> unknown11;
};

struct PatternedInfo : BigYAML
{
    DECL_YAML
    Value<atUint32> propertyCount;
    Value<float>    mass;
    Value<float>    speed;
    Value<float>    turnSpeed;
    Value<float>    detectionRange;
    Value<float>    detectionHeightRange;
    Value<float>    dectectionAngle;
    Value<float>    minAttackRange;
    Value<float>    maxAttackRange;
    Value<float>    averageAttackTime;
    Value<float>    attackTimeVariation;
    Value<float>    leashRadius;
    Value<float>    playerLeashRadius;
    Value<float>    playerLeashTime;
    DamageInfo      contactDamage;
    Value<float>    damageWaitTime;
    HealthInfo      healthInfo;
    DamageVulnerability damageVulnerability;
    Value<float>    unkown1;
    Value<float>    unkown2;
    Value<atVec3f>  unkown3;
    Value<float>    unkown4;
    Value<float>    unkown5;
    Value<float>    unkown6;
    Value<float>    unkown7;
    Value<atUint32> soundID1;
    AnimationParameters animationParameters;
    Value<bool>     active;
    UniqueID32      stateMachine;
    Value<float>    unknown8;
    Value<float>    unknown9;
    Value<float>    unknown10;
    Value<atUint32> unknown11;
    Value<atVec3f>  unknown12;
    UniqueID32      particle1;
    Value<atUint32> unknown13;
    Value<atVec3f>  unknown14;
    UniqueID32      particle2;
    Value<atUint32> soundID2;

    void nameIDs(PAKRouter<PAKBridge>& pakRouter, const std::string& name) const
    {
        animationParameters.nameANCS(pakRouter, name + "_animp");
        if (stateMachine)
        {
            PAK::Entry* ent = (PAK::Entry*)pakRouter.lookupEntry(stateMachine);
            ent->name = name + "_fsm";
        }
        if (particle1)
        {
            PAK::Entry* ent = (PAK::Entry*)pakRouter.lookupEntry(particle1);
            ent->name = name + "_part1";
        }
        if (particle2)
        {
            PAK::Entry* ent = (PAK::Entry*)pakRouter.lookupEntry(particle2);
            ent->name = name + "_part2";
        }
    }
};

struct PlayerHintParameters : BigYAML
{
    DECL_YAML
    Value<atUint32> propertyCount;
    Value<bool>     unknown1;
    Value<bool>     unknown2;
    Value<bool>     unknown3;
    Value<bool>     unknown4;
    Value<bool>     unknown5;
    Value<bool>     unknown6;
    Value<bool>     unknown7;
    Value<bool>     unknown8;
    Value<bool>     unknown9;
    Value<bool>     unknown10;
    Value<bool>     unknown11;
    Value<bool>     unknown12;
    Value<bool>     unknown13;
    Value<bool>     unknown14;
    Value<bool>     unknown15;
};

struct ScannableParameters : BigYAML
{
    DECL_YAML
    Value<atUint32> propertyCount;
    UniqueID32      scanId;

    void nameIDs(PAKRouter<PAKBridge>& pakRouter, const std::string& name) const
    {
        if (scanId)
        {
            PAK::Entry* scanEnt = (PAK::Entry*)pakRouter.lookupEntry(scanId);
            scanEnt->name = name + "_scan";
        }
    }
};

struct VisorParameters : BigYAML
{
    DECL_YAML
    Value<atUint32> propertyCount;
    Value<bool>     unknown1;
    Value<bool>     unknown2;
    Value<atUint32> unknown3;
};

struct ActorParameters : BigYAML
{
    DECL_YAML
    Value<atUint32> propertyCount;
    LightParameters lightParameters;
    ScannableParameters scannableParameters;
    UniqueID32   xrayModel;
    UniqueID32   xraySkin;
    UniqueID32   thermalModel;
    UniqueID32   thermalSkin;
    Value<bool>  unknown1;
    Value<float> unknown2;
    Value<float> unknown3;
    VisorParameters visorParameters;
    Value<bool>  thermalHeat;
    Value<bool>  unknown4;
    Value<bool>  unknown5;
    Value<float> unknown6;

    void addCMDLRigPairs(std::unordered_map<UniqueID32, std::pair<UniqueID32, UniqueID32>>& addTo,
                         const UniqueID32& cinf) const
    {
        if (xrayModel && xraySkin)
            addTo[xrayModel] = std::make_pair(xraySkin, cinf);
        if (thermalModel && thermalSkin)
            addTo[thermalModel] = std::make_pair(thermalSkin, cinf);
    }

    void nameIDs(PAKRouter<PAKBridge>& pakRouter, const std::string& name) const
    {
        scannableParameters.nameIDs(pakRouter, name);
        if (xrayModel)
        {
            PAK::Entry* xmEnt = (PAK::Entry*)pakRouter.lookupEntry(xrayModel);
            xmEnt->name = name + "_xraymodel";
        }
        if (xraySkin)
        {
            PAK::Entry* xsEnt = (PAK::Entry*)pakRouter.lookupEntry(xraySkin);
            xsEnt->name = name + "_xrayskin";
        }
        if (thermalModel)
        {
            PAK::Entry* xmEnt = (PAK::Entry*)pakRouter.lookupEntry(thermalModel);
            xmEnt->name = name + "_thermalmodel";
        }
        if (thermalSkin)
        {
            PAK::Entry* xsEnt = (PAK::Entry*)pakRouter.lookupEntry(thermalSkin);
            xsEnt->name = name + "_thermalskin";
        }
    }
};
}
}

#endif
