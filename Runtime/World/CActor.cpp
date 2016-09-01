#include "CActor.hpp"
#include "CActorParameters.hpp"
#include "CStateManager.hpp"
#include "Collision/CMaterialList.hpp"
#include "Audio/CSfxManager.hpp"

namespace urde
{
static CMaterialList MakeActorMaterialList(const CMaterialList& materialList, const CActorParameters& params)
{
    CMaterialList ret = materialList;
    if (params.GetVisorParameters().x0_28_b3)
        ret.Add(EMaterialTypes::Fourteen);
    if (params.GetVisorParameters().x0_29_b4)
        ret.Add(EMaterialTypes::Fifteen);
    return ret;
}

CActor::CActor(TUniqueId uid, bool active, const std::string& name, const CEntityInfo& info,
               const zeus::CTransform&, CModelData&& mData, const CMaterialList& list,
               const CActorParameters& params, TUniqueId otherUid)
    : CEntity(uid, info, active, name),
      x68_material(MakeActorMaterialList(list, params)),
      x70_(CMaterialFilter::MakeIncludeExclude({EMaterialTypes::Nineteen}, {EMaterialTypes::Zero})),
      xc6_(otherUid)
{
    if (mData.x10_animData || mData.x1c_normalModel)
        x64_modelData = std::make_unique<CModelData>(std::move(mData));
}

void CActor::AcceptScriptMsg(EScriptObjectMessage msg, TUniqueId uid, CStateManager& mgr)
{
    switch(msg)
    {
    case EScriptObjectMessage::Activate:
    {
        if (!x30_24_active)
            xbc_time = CGraphics::GetSecondsMod900();
    }
        break;
    case EScriptObjectMessage::Decrement:
        RemoveEmitter();
        break;
    case EScriptObjectMessage::InternalMessage11: // 33
    {
        /*
        if (x94_simpleShadow)
            AddMaterial(EMaterialTypes::ThirtyNine, mgr);
        else
            RemoveMaterial(EMaterialTypes::ThirtyNine, mgr);
        */


        if (HasModelData() && x64_modelData->AnimationData())
        {
            TAreaId aid = GetAreaId();
            //x64_modelData->AnimationData()->sub_8002AE6C(mgr, aid, x64_modelData->x0_particleScale);
        }
    }
        break;
    case EScriptObjectMessage::InternalMessage12: // 34
    {
        RemoveEmitter();
        /* TODO: Not sure about this
        if (HasModelData() && x64_modelData->AnimationData() && x64_modelData->x28_)
            x64_modelData->AnimationData().GetParticleDB().GetActiveParticleLightIds(mgr);
        */
    }
        break;
    case EScriptObjectMessage::InternalMessage13: // 35
    {
        for (const SConnection& conn : x20_conns)
        {
            if (conn.x0_state != EScriptObjectState::DFST)
                continue;

            const CActor* act = dynamic_cast<const CActor*>(mgr.GetObjectById(mgr.GetIdForScript(conn.x8_objId)));
            if (act && xc6_ == kInvalidUniqueId)
                xc6_ = act->GetUniqueId();
        }
    }
        break;
    case EScriptObjectMessage::InternalMessage15: // 37
        SetInFluid(true, uid);
        break;
    case EScriptObjectMessage::InternalMessage17: // 39
        SetInFluid(false, kInvalidUniqueId);
        break;
    default:break;
    }
    CEntity::AcceptScriptMsg(msg, uid, mgr);
}

zeus::CAABox CActor::CalculateRenderBounds()
{
    return {};
}

const CHealthInfo* CActor::GetHealthInfo() const
{
    return nullptr;
}

const CDamageVulnerability* CActor::GetDamageVulnerability() const
{
    return nullptr;
}

const CDamageVulnerability* CActor::GetDamageVulnerability(const zeus::CVector3f &, const zeus::CVector3f &, const CDamageInfo &) const
{
    return nullptr;
}

rstl::optional_object<zeus::CAABox> CActor::GetTouchBounds() const
{
    return {} ;
}

void CActor::Touch(CActor &, CStateManager &)
{

}

zeus::CVector3f CActor::GetOrbitPosition(const CStateManager&) const
{
    return x34_transform.origin;
}

zeus::CVector3f CActor::GetAimPosition(const CStateManager &, float) const
{
    return x34_transform.origin;
}

zeus::CVector3f CActor::GetHomingPosition(const CStateManager& mgr, float f) const
{
    return GetAimPosition(mgr, f);
}

zeus::CVector3f CActor::GetScanObjectIndicatorPosition(const CStateManager &)
{
    return {};
}

void CActor::RemoveEmitter()
{
    if (x8c_sfxHandle)
    {
        CSfxManager::RemoveEmitter(*x8c_sfxHandle.get());
        x88_sfxId = -1;
        x8c_sfxHandle.reset();
    }
}

EWeaponCollisionResponseTypes CActor::GetCollisionResponseType(const zeus::CVector3f&,
                                                               const zeus::CVector3f&, CWeaponMode&, int)
{
    return EWeaponCollisionResponseTypes::Unknown13;
}

void CActor::FluidFXThink(CActor::EFluidState, CScriptWater &, CStateManager &)
{

}

void CActor::OnScanStateChanged(EScanState state, CStateManager& mgr)
{
    if (state == EScanState::Zero)
        SendScriptMsgs(EScriptObjectState::UNKS7, mgr, EScriptObjectMessage::None);
    else if (state == EScanState::One)
        SendScriptMsgs(EScriptObjectState::UNKS8, mgr, EScriptObjectMessage::None);
    else if (state == EScanState::Two)
        SendScriptMsgs(EScriptObjectState::ScanDone, mgr, EScriptObjectMessage::None);

}

zeus::CAABox CActor::GetSortingBounds(const zeus::CTransform &) const
{
    return {};
}

void CActor::DoUserAnimEvent(CStateManager &, CInt32POINode &, EUserEventType)
{
}

void CActor::RemoveMaterial(EMaterialTypes t1, EMaterialTypes t2, EMaterialTypes t3, EMaterialTypes t4, CStateManager& mgr)
{
    x68_material.Remove(t1);
    RemoveMaterial(t2, t3, t4, mgr);
}

void CActor::RemoveMaterial(EMaterialTypes t1, EMaterialTypes t2, EMaterialTypes t3, CStateManager & mgr)
{
    x68_material.Remove(t1);
    RemoveMaterial(t2, t3, mgr);
}

void CActor::RemoveMaterial(EMaterialTypes t1, EMaterialTypes t2, CStateManager& mgr)
{
    x68_material.Remove(t1);
}

void CActor::RemoveMaterial(EMaterialTypes t, CStateManager& mgr)
{
    x68_material.Remove(t);
    mgr.UpdateObjectInLists(*this);
}

void CActor::AddMaterial(EMaterialTypes t1, EMaterialTypes t2, EMaterialTypes t3, EMaterialTypes t4, EMaterialTypes t5, CStateManager& mgr)
{
    x68_material.Add(t1);
    AddMaterial(t2, t3, t4, t5, mgr);
}

void CActor::AddMaterial(EMaterialTypes t1, EMaterialTypes t2, EMaterialTypes t3, EMaterialTypes t4, CStateManager& mgr)
{
    x68_material.Add(t1);
    AddMaterial(t2, t3, t4, mgr);
}

void CActor::AddMaterial(EMaterialTypes t1, EMaterialTypes t2, EMaterialTypes t3, CStateManager& mgr)
{
    x68_material.Add(t1);
    AddMaterial(t2, t3, mgr);
}

void CActor::AddMaterial(EMaterialTypes t1, EMaterialTypes t2, CStateManager& mgr)
{
    x68_material.Add(t1);
    AddMaterial(t2, mgr);
}

void CActor::AddMaterial(EMaterialTypes type, CStateManager& mgr)
{
    x68_material.Add(type);
    mgr.UpdateObjectInLists(*this);
}

void CActor::SetCallTouch(bool callTouch)
{
    xe5_28_callTouch = callTouch;
}

bool CActor::GetCallTouch() const
{
    return xe5_28_callTouch;
}

void CActor::SetUseInSortedList(bool use)
{
    xe5_27_useInSortedLists = use;
}

bool CActor::GetUseInSortedLists() const
{
    return xe5_27_useInSortedLists;
}

void CActor::SetInFluid(bool in, TUniqueId uid)
{
    if (in)
    {
        xe6_26_inFluid = false;
        xc4_fluidId = uid;
    }
    else
    {
        if (!xe6_26_inFluid)
            return;

        xe6_26_inFluid = true;
        if (xe6_26_inFluid == 0)
            xc4_fluidId = kInvalidUniqueId;
    }
}

bool CActor::HasModelData() const
{
    return bool(x64_modelData);
}

const CSfxHandle* CActor::GetSfxHandle() const
{
    return x8c_sfxHandle.get();
}

void CActor::SetSfxPitchBend(s32 val)
{
    xe6_30_enablePitchBend = true;
    xc0_ = val;
    if (x8c_sfxHandle == 0)
        return;

    CSfxManager::PitchBend(*x8c_sfxHandle.get(), val);
}

void CActor::SetTranslation(const zeus::CVector3f &tr)
{
    x34_transform.origin = tr;
    xe4_27_ = true;
    xe4_28_ = true;
    xe4_29_ = true;
}

}
