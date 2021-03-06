#pragma once

#include "Runtime/IOStreams.hpp"
#include "Runtime/Character/CCharAnimTime.hpp"
#include "Runtime/Character/IMetaTrans.hpp"

namespace urde {

class CMetaTransTrans : public IMetaTrans {
  CCharAnimTime x4_transDur;
  bool xc_;
  bool xd_runA;
  u32 x10_flags;

public:
  explicit CMetaTransTrans(CInputStream& in);
  EMetaTransType GetType() const override { return EMetaTransType::Trans; }

  std::shared_ptr<CAnimTreeNode> VGetTransitionTree(const std::weak_ptr<CAnimTreeNode>& a,
                                                    const std::weak_ptr<CAnimTreeNode>& b,
                                                    const CAnimSysContext& animSys) const override;
};

} // namespace urde
