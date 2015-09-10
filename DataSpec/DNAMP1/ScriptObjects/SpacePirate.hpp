#ifndef _DNAMP1_SPACEPIRATE_HPP_
#define _DNAMP1_SPACEPIRATE_HPP_

#include "../../DNACommon/DNACommon.hpp"
#include "IScriptObject.hpp"
#include "Parameters.hpp"

namespace Retro
{
namespace DNAMP1
{
struct SpacePirate : IScriptObject
{
    DECL_YAML
    String<-1> name;
    Value<atVec3f> location;
    Value<atVec3f> orientation;
    Value<atVec3f> scale;
    PatternedInfo patternedInfo;
    ActorParameters actorParameters;
    Value<float> unknown1;
    Value<float> unknown2;
    Value<float> unknown3;
    Value<float> unknown4;
    Value<float> unknown5;
    Value<float> unknown6;
    Value<atUint32> unknown7;
    Value<bool> unknown8;
    UniqueID32 wpsc1;
    DamageInfo damageInfo1;
    Value<atUint32> soundID1;
    DamageInfo damageInfo2;
    Value<float> unknown9;
    UniqueID32 wpsc2;
    DamageInfo damageInfo3;
    Value<float> unknown10;
    Value<atUint32> soundID2;
    Value<float> unknown11;
    Value<float> unknown12;
    Value<atUint32> soundID3;
    Value<float> unknown13;
    Value<atUint32> unknown14;
    Value<float> unknown15;
    Value<float> unknown16;
    Value<float> unknown17;
    Value<float> unknown18;
    Value<atUint32> soundID4;
    Value<atUint32> soundID5;
    Value<float> unknown19;
    Value<float> unknown20;
};
}
}

#endif
