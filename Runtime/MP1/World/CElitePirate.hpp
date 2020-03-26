#pragma once

#include "Runtime/Character/CBoneTracking.hpp"
#include "Runtime/Collision/CJointCollisionDescription.hpp"
#include "Runtime/World/CActorParameters.hpp"
#include "Runtime/World/CAnimationParameters.hpp"
#include "Runtime/World/CPatterned.hpp"
#include "Runtime/World/CPathFindSearch.hpp"

namespace urde {
class CCollisionActorManager;
class CGenDescription;
namespace MP1 {
class CElitePirateData {
public:
  float x0_;
  float x4_;
  float x8_;
  float xc_;
  float x10_;
  float x14_;
  float x18_;
  float x1c_;
  CAssetId x20_;
  s16 x24_;
  CActorParameters x28_;
  CAnimationParameters x90_launcherParams;
  CAssetId x9c_;
  s16 xa0_;
  CAssetId xa4_;
  CDamageInfo xa8_;
  float xc4_;
  CAssetId xc8_;
  CAssetId xcc_;
  CAssetId xd0_;
  CAssetId xd4_;
  float xd8_;
  float xdc_;
  float xe0_;
  float xe4_;
  float xe8_;
  float xec_;
  u32 xf0_;
  u16 xf4_;
  u16 xf6_;
  CAssetId xf8_;
  CDamageInfo xfc_;
  CAssetId x118_;
  s16 x11c_;
  bool x11e_;
  bool x11f_;

  CElitePirateData(CInputStream&, u32 propCount);

  CAssetId GetX20() const { return x20_; }
  CAssetId GetXF8() const { return xf8_; }
  const CDamageInfo& GetXFC() const { return xfc_; }
  CAssetId GetX118() const { return x118_; }
  s16 GetX11C() const { return x11c_; }
};

class CElitePirate : public CPatterned {
  struct SUnknownStruct {
    float x0_;
    s32 x4_ = 0;
    SUnknownStruct(float f) : x0_(f * f) {}
  };

  struct SUnknownStruct2 {
    u32 x0_ = 8;
    CAssetId x4_particleDesc;
    CDamageInfo x8_damageInfo;
    float x24_ = 0.f;
    float x28_ = 0.5f;
    float x2c_ = 16.5217f;
    float x30_ = 0.f;
    CAssetId x34_weaponDesc;
    s16 x38_sfx;

    SUnknownStruct2(CAssetId part, const CDamageInfo& dInfo, CAssetId weapon, s16 sfx)
    : x4_particleDesc(part), x8_damageInfo(dInfo), x34_weaponDesc(weapon), x38_sfx(sfx) {}
  };

  s32 x568_ = -1;
  CDamageVulnerability x56c_vulnerability;
  std::unique_ptr<CCollisionActorManager> x5d4_collisionActorMgr1;
  CElitePirateData x5d8_data;
  CBoneTracking x6f8_boneTracking;
  std::unique_ptr<CCollisionActorManager> x730_collisionActorMgr2;
  s32 x734_;
  CCollidableAABox x738_;
  std::optional<TLockedToken<CGenDescription>> x760_;
  TUniqueId x770_collisionHeadId = kInvalidUniqueId;
  TUniqueId x772_ = kInvalidUniqueId;
  rstl::reserved_vector<TUniqueId, 8> x774_collisionRJointIds;
  rstl::reserved_vector<TUniqueId, 8> x788_collisionLJointIds;
  TUniqueId x79c_ = kInvalidUniqueId;
  float x7a0_;
  float x7a4_ = 1.f;
  float x7a8_ = 0.f;
  float x7ac_ = 0.f;
  float x7b0_ = 1.f;
  float x7b4_ = 0.f;
  float x7b8_ = 0.f;
  float x7bc_ = 0.f;
  float x7c0_ = 0.f;
  float x7c4_ = 0.f;
  s32 x7c8_ = -1;
  s32 x7cc_ = 0;
  CPathFindSearch x7d0_pathFindSearch;
  zeus::CVector3f x8b4_;
  SUnknownStruct x8c0_;
  bool x988_24_ : 1;
  bool x988_25_ : 1;
  bool x988_26_ : 1;
  bool x988_27_ : 1;
  bool x988_28_alert : 1;
  bool x988_29_ : 1;
  bool x988_30_ : 1;
  bool x988_31_ : 1;
  bool x989_24_ : 1;

public:
  DEFINE_PATTERNED(ElitePirate)

  CElitePirate(TUniqueId uid, std::string_view name, const CEntityInfo& info, const zeus::CTransform& xf,
               CModelData&& mData, const CPatternedInfo& pInfo, const CActorParameters& actParms,
               const CElitePirateData& data);

  void Accept(IVisitor& visitor) override;
  void Think(float dt, CStateManager& mgr) override;
  void AcceptScriptMsg(EScriptObjectMessage msg, TUniqueId uid, CStateManager& mgr) override;
  void PreRender(CStateManager& mgr, const zeus::CFrustum& frustum) override;
  const CDamageVulnerability* GetDamageVulnerability() const override;
  const CDamageVulnerability* GetDamageVulnerability(const zeus::CVector3f& pos, const zeus::CVector3f& dir,
                                                     const CDamageInfo& dInfo) const override;
  zeus::CVector3f GetOrbitPosition(const CStateManager& mgr) const override;
  zeus::CVector3f GetAimPosition(const CStateManager& mgr, float) const override;
  void DoUserAnimEvent(CStateManager& mgr, const CInt32POINode& node, EUserEventType type, float dt) override;
  const CCollisionPrimitive* GetCollisionPrimitive() const override;
  void KnockBack(const zeus::CVector3f&, CStateManager&, const CDamageInfo& info, EKnockBackType type, bool inDeferred,
                 float magnitude) override;
  void TakeDamage(const zeus::CVector3f&, float arg) override;
  void Patrol(CStateManager&, EStateMsg msg, float dt) override;
  void PathFind(CStateManager&, EStateMsg msg, float dt) override;
  void TargetPatrol(CStateManager&, EStateMsg msg, float dt) override;
  void Halt(CStateManager&, EStateMsg msg, float dt) override;
  void Run(CStateManager&, EStateMsg msg, float dt) override;
  void Generate(CStateManager&, EStateMsg msg, float dt) override;
  void Attack(CStateManager&, EStateMsg msg, float dt) override;
  void Taunt(CStateManager&, EStateMsg msg, float dt) override;
  void ProjectileAttack(CStateManager&, EStateMsg msg, float dt) override;
  void SpecialAttack(CStateManager&, EStateMsg msg, float dt) override;
  void CallForBackup(CStateManager&, EStateMsg msg, float dt) override;
  bool TooClose(CStateManager&, float arg) override;
  bool InDetectionRange(CStateManager&, float arg) override;
  bool SpotPlayer(CStateManager&, float arg) override;
  bool AnimOver(CStateManager&, float arg) override;
  bool ShouldAttack(CStateManager&, float arg) override;
  bool InPosition(CStateManager&, float arg) override;
  bool ShouldTurn(CStateManager&, float arg) override;
  bool AggressionCheck(CStateManager&, float arg) override;
  bool ShouldTaunt(CStateManager&, float arg) override;
  bool ShouldFire(CStateManager&, float arg) override;
  bool ShotAt(CStateManager&, float arg) override;
  bool ShouldSpecialAttack(CStateManager&, float arg) override;
  bool ShouldCallForBackup(CStateManager&, float arg) override;
  CPathFindSearch* GetSearchPath() override;
  virtual bool sub_802273a8() { return true; }
  virtual bool sub_802273b0() { return true; }
  virtual void sub_80229114(CStateManager& mgr);
  virtual void sub_802289b0(CStateManager& mgr, bool b);
  virtual SUnknownStruct2 sub_802273b8() const {
    return {x5d8_data.GetXF8(), x5d8_data.GetXFC(), x5d8_data.GetX118(), x5d8_data.GetX11C()};
  }

private:
  void sub_80229248();
  void sub_8022759c(bool param_1, CStateManager& mgr);
  bool sub_802293f8(TUniqueId uid, const rstl::reserved_vector<TUniqueId, 8>& vec) const;
  void AddSphereCollisionList(const SSphereJointInfo* joints, size_t count,
                              std::vector<CJointCollisionDescription>& outJoints) const;
  void AddCollisionList(const SJointInfo* joints, size_t count,
                        std::vector<CJointCollisionDescription>& outJoints) const;
  void SetupCollisionManagers(CStateManager& mgr);
  void sub_80229818(CStateManager& mgr);
  bool sub_8022943c(std::string_view name, std::string_view locator, const SJointInfo* info, size_t infoCount);
  void CreateGrenadeLauncher(CStateManager& mgr, TUniqueId uid);
};
} // namespace MP1
} // namespace urde
