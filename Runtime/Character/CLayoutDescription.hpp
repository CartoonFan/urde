#pragma once

#include <optional>

#include "Runtime/CToken.hpp"

#include <zeus/CVector3f.hpp>

namespace urde {
class CCharLayoutInfo;

class CLayoutDescription {
public:
  class CScaledLayoutDescription {
    TLockedToken<CCharLayoutInfo> x0_layoutToken;
    float xc_scale = 0.0f;
    std::optional<zeus::CVector3f> x10_scaleVec;

  public:
    const TLockedToken<CCharLayoutInfo>& ScaledLayout() const { return x0_layoutToken; }
    float GlobalScale() const { return xc_scale; }
    const std::optional<zeus::CVector3f>& GetScaleVec() const { return x10_scaleVec; }
  };

private:
  TLockedToken<CCharLayoutInfo> x0_layoutToken;
  std::optional<CScaledLayoutDescription> xc_scaled;

public:
  explicit CLayoutDescription(const TLockedToken<CCharLayoutInfo>& token) : x0_layoutToken(token) {}

  const std::optional<CScaledLayoutDescription>& GetScaledLayoutDescription() const { return xc_scaled; }

  const TLockedToken<CCharLayoutInfo>& GetCharLayoutInfo() const { return x0_layoutToken; }
  bool UsesScale() const { return bool(xc_scaled); }
  const TLockedToken<CCharLayoutInfo>& ScaledLayout() const {
    if (UsesScale())
      return xc_scaled->ScaledLayout();
    return x0_layoutToken;
  }
};

} // namespace urde
