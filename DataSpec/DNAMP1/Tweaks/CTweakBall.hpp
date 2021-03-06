#pragma once

#include "../../DNACommon/Tweaks/ITweakBall.hpp"
#include "zeus/CVector3f.hpp"

namespace DataSpec::DNAMP1 {
struct CTweakBall final : public ITweakBall {
  AT_DECL_EXPLICIT_DNA_YAML
  Value<float> x4_maxTranslationAcceleration[8];
  Value<float> x24_translationFriction[8];
  Value<float> x44_translationMaxSpeed[8];
  Value<float> x64_;
  Value<float> x68_;
  Value<float> x6c_;
  Value<float> x70_;
  Value<float> x74_ballCameraAnglePerSecond;
  Value<zeus::CVector3f> x78_ballCameraOffset;
  Value<float> x84_ballCameraMinSpeedDistance;
  Value<float> x88_ballCameraMaxSpeedDistance;
  Value<float> x8c_ballCameraBackwardsDistance;
  Value<float> x90_;
  Value<float> x94_ballCameraSpringConstant;
  Value<float> x98_ballCameraSpringMax;
  Value<float> x9c_ballCameraSpringTardis;
  Value<float> xa0_ballCameraCentroidSpringConstant;
  Value<float> xa4_ballCameraCentroidSpringMax;
  Value<float> xa8_ballCameraCentroidSpringTardis;
  Value<float> xac_ballCameraCentroidDistanceSpringConstant;
  Value<float> xb0_ballCameraCentroidDistanceSpringMax;
  Value<float> xb4_ballCameraCentroidDistanceSpringTardis;
  Value<float> xb8_ballCameraLookAtSpringConstant;
  Value<float> xbc_ballCameraLookAtSpringMax;
  Value<float> xc0_ballCameraLookAtSpringTardis;
  Value<float> xc4_ballForwardBrakingAcceleration[8];
  Value<float> xe4_ballGravity;
  Value<float> xe8_ballWaterGravity;
  float xec_ = 10000.f;
  float xf0_ = 1000.f;
  float xf4_ = 40000.f;
  float xf8_ = 40000.f;
  float xfc_ = 40000.f;
  float x100_ = 40000.f;
  float x104_ = 40000.f;
  float x108_ = 40000.f;
  float x10c_ = 10000.f;
  float x110_ = 1000.f;
  float x114_ = 40000.f;
  float x118_ = 40000.f;
  float x11c_ = 40000.f;
  float x120_ = 40000.f;
  float x124_ = 40000.f;
  float x128_ = 40000.f;
  float x12c_ballSlipFactor[8] = {10000.f, 10000.f, 1000.f, 10000.f, 2000.f, 2000.f, 2000.f, 2000.f};
  Value<float> x14c_;
  Value<float> x150_;
  Value<float> x158_;
  Value<float> x154_;
  Value<float> x15c_;
  Value<float> x160_;
  Value<float> x164_;
  Value<float> x168_;
  Value<float> x16c_;
  Value<float> x170_conservativeDoorCamDistance;
  Value<float> x174_;
  Value<float> x178_ballCameraChaseElevation;
  Value<float> x17c_ballCameraChaseDampenAngle;
  Value<float> x180_ballCameraChaseDistance;
  Value<float> x184_ballCameraChaseYawSpeed;
  Value<float> x188_ballCameraChaseAnglePerSecond;
  Value<zeus::CVector3f> x18c_ballCameraChaseLookAtOffset;
  Value<float> x198_ballCameraChaseSpringConstant;
  Value<float> x19c_ballCameraChaseSpringMax;
  Value<float> x1a0_ballCameraChaseSpringTardis;
  Value<float> x1a4_ballCameraBoostElevation;
  Value<float> x1a8_ballCameraBoostDampenAngle;
  Value<float> x1ac_ballCameraBoostDistance;
  Value<float> x1b0_ballCameraBoostYawSpeed;
  Value<float> x1b4_ballCameraBoostAnglePerSecond;
  Value<zeus::CVector3f> x1b8_ballCameraBoostLookAtOffset;
  Value<float> x1c4_ballCameraBoostSpringConstant;
  Value<float> x1c8_ballCameraBoostSpringMax;
  Value<float> x1cc_ballCameraBoostSpringTardis;
  Value<float> x1d0_ballCameraControlDistance;
  Value<float> x1d4_;
  Value<float> x1d8_;
  Value<float> x1dc_minimumAlignmentSpeed;
  Value<float> x1e0_tireness;
  Value<float> x1ec_maxLeanAngle;
  Value<float> x1f0_tireToMarbleThresholdSpeed;
  Value<float> x1f4_marbleToTireThresholdSpeed;
  Value<float> x1f8_forceToLeanGain;
  Value<float> x1fc_leanTrackingGain;
  Value<float> x1e4_leftStickDivisor;
  Value<float> x1e8_rightStickDivisor;
  Value<float> x200_;
  Value<float> x204_ballTouchRadius;
  float x208_;
  Value<float> x20c_boostBallDrainTime;
  Value<float> x218_boostBallMinChargeTime;
  Value<float> x21c_boostBallMinRelativeSpeedForDamage;
  Value<float> x220_boostBallChargeTime0;
  Value<float> x224_boostBallChargeTime1;
  float x228_boostBallChargeTime2;
  Value<float> x210_boostBallMaxChargeTime;
  Value<float> x22c_boostBallIncrementalSpeed0;
  Value<float> x230_boostBallIncrementalSpeed1;
  Value<float> x234_boostBallIncrementalSpeed2;

  CTweakBall() = default;
  CTweakBall(athena::io::IStreamReader& r) {
    this->read(r);
    x6c_ = -x6c_;
    x70_ = -x70_;
    x74_ballCameraAnglePerSecond = zeus::degToRad(x74_ballCameraAnglePerSecond);
    x90_ = zeus::degToRad(x90_);
    xe4_ballGravity = -xe4_ballGravity;
    xe8_ballWaterGravity = -xe8_ballWaterGravity;
    x15c_ = zeus::degToRad(x15c_);
    x16c_ = zeus::degToRad(x16c_);
    x174_ = zeus::degToRad(x174_);
    x17c_ballCameraChaseDampenAngle = zeus::degToRad(x17c_ballCameraChaseDampenAngle);
    x184_ballCameraChaseYawSpeed = zeus::degToRad(x184_ballCameraChaseYawSpeed);
    x188_ballCameraChaseAnglePerSecond = zeus::degToRad(x188_ballCameraChaseAnglePerSecond);
    x1a8_ballCameraBoostDampenAngle = zeus::degToRad(x1a8_ballCameraBoostDampenAngle);
    x1b0_ballCameraBoostYawSpeed = zeus::degToRad(x1b0_ballCameraBoostYawSpeed);
    x1b4_ballCameraBoostAnglePerSecond = zeus::degToRad(x1b4_ballCameraBoostAnglePerSecond);
    x1ec_maxLeanAngle = zeus::degToRad(x1ec_maxLeanAngle);
  }

  float GetMaxBallTranslationAcceleration(int s) const override { return x4_maxTranslationAcceleration[s]; }
  float GetBallTranslationFriction(int s) const override { return x24_translationFriction[s]; }
  float GetBallTranslationMaxSpeed(int s) const override { return x44_translationMaxSpeed[s]; }
  float GetBallCameraElevation() const override { return 2.736f; }
  float GetBallCameraAnglePerSecond() const override { return x74_ballCameraAnglePerSecond; }
  const zeus::CVector3f& GetBallCameraOffset() const override { return x78_ballCameraOffset; }
  float GetBallCameraMinSpeedDistance() const override { return x84_ballCameraMinSpeedDistance; }
  float GetBallCameraMaxSpeedDistance() const override { return x88_ballCameraMaxSpeedDistance; }
  float GetBallCameraBackwardsDistance() const override { return x8c_ballCameraBackwardsDistance; }
  float GetBallCameraSpringConstant() const override { return x94_ballCameraSpringConstant; }
  float GetBallCameraSpringMax() const override { return x98_ballCameraSpringMax; }
  float GetBallCameraSpringTardis() const override { return x9c_ballCameraSpringTardis; }
  float GetBallCameraCentroidSpringConstant() const override { return xa0_ballCameraCentroidSpringConstant; }
  float GetBallCameraCentroidSpringMax() const override { return xa4_ballCameraCentroidSpringMax; }
  float GetBallCameraCentroidSpringTardis() const override { return xa8_ballCameraCentroidSpringTardis; }
  float GetBallCameraCentroidDistanceSpringConstant() const override {
    return xac_ballCameraCentroidDistanceSpringConstant;
  }
  float GetBallCameraCentroidDistanceSpringMax() const override { return xb0_ballCameraCentroidDistanceSpringMax; }
  float GetBallCameraCentroidDistanceSpringTardis() const override {
    return xb4_ballCameraCentroidDistanceSpringTardis;
  }
  float GetBallCameraLookAtSpringConstant() const override { return xb8_ballCameraLookAtSpringConstant; }
  float GetBallCameraLookAtSpringMax() const override { return xbc_ballCameraLookAtSpringMax; }
  float GetBallCameraLookAtSpringTardis() const override { return xc0_ballCameraLookAtSpringTardis; }
  float GetBallForwardBrakingAcceleration(int s) const override { return xc4_ballForwardBrakingAcceleration[s]; }
  float GetBallGravity() const override { return xe4_ballGravity; }
  float GetBallWaterGravity() const override { return xe8_ballWaterGravity; }
  float GetBallSlipFactor(int s) const override { return x12c_ballSlipFactor[s]; }
  float GetConservativeDoorCameraDistance() const override { return x170_conservativeDoorCamDistance; }
  float GetBallCameraChaseElevation() const override { return x178_ballCameraChaseElevation; }
  float GetBallCameraChaseDampenAngle() const override { return x17c_ballCameraChaseDampenAngle; }
  float GetBallCameraChaseDistance() const override { return x180_ballCameraChaseDistance; }
  float GetBallCameraChaseYawSpeed() const override { return x184_ballCameraChaseYawSpeed; }
  float GetBallCameraChaseAnglePerSecond() const override { return x188_ballCameraChaseAnglePerSecond; }
  const zeus::CVector3f& GetBallCameraChaseLookAtOffset() const override { return x18c_ballCameraChaseLookAtOffset; }
  float GetBallCameraChaseSpringConstant() const override { return x198_ballCameraChaseSpringConstant; }
  float GetBallCameraChaseSpringMax() const override { return x19c_ballCameraChaseSpringMax; }
  float GetBallCameraChaseSpringTardis() const override { return x1a0_ballCameraChaseSpringTardis; }
  float GetBallCameraBoostElevation() const override { return x1a4_ballCameraBoostElevation; }
  float GetBallCameraBoostDampenAngle() const override { return x1a8_ballCameraBoostDampenAngle; }
  float GetBallCameraBoostDistance() const override { return x1ac_ballCameraBoostDistance; }
  float GetBallCameraBoostYawSpeed() const override { return x1b0_ballCameraBoostYawSpeed; }
  float GetBallCameraBoostAnglePerSecond() const override { return x1b4_ballCameraBoostAnglePerSecond; }
  const zeus::CVector3f& GetBallCameraBoostLookAtOffset() const override { return x1b8_ballCameraBoostLookAtOffset; }
  float GetBallCameraBoostSpringConstant() const override { return x1c4_ballCameraBoostSpringConstant; }
  float GetBallCameraBoostSpringMax() const override { return x1c8_ballCameraBoostSpringMax; }
  float GetBallCameraBoostSpringTardis() const override { return x1cc_ballCameraBoostSpringTardis; }
  float GetBallCameraControlDistance() const override { return x1d0_ballCameraControlDistance; }
  float GetMinimumAlignmentSpeed() const override { return x1dc_minimumAlignmentSpeed; }
  float GetTireness() const override { return x1e0_tireness; }
  float GetMaxLeanAngle() const override { return x1ec_maxLeanAngle; }
  float GetTireToMarbleThresholdSpeed() const override { return x1f0_tireToMarbleThresholdSpeed; }
  float GetMarbleToTireThresholdSpeed() const override { return x1f4_marbleToTireThresholdSpeed; }
  float GetForceToLeanGain() const override { return x1f8_forceToLeanGain; }
  float GetLeanTrackingGain() const override { return x1fc_leanTrackingGain; }
  float GetLeftStickDivisor() const override { return x1e4_leftStickDivisor; }
  float GetRightStickDivisor() const override { return x1e8_rightStickDivisor; }
  float GetBallTouchRadius() const override { return x204_ballTouchRadius; }
  float GetBoostBallDrainTime() const override { return x20c_boostBallDrainTime; }
  float GetBoostBallMaxChargeTime() const override { return x210_boostBallMaxChargeTime; }
  float GetBoostBallMinChargeTime() const override { return x218_boostBallMinChargeTime; }
  float GetBoostBallMinRelativeSpeedForDamage() const override { return x21c_boostBallMinRelativeSpeedForDamage; }
  float GetBoostBallChargeTimeTable(int i) const override {
    switch (i) {
    default:
    case 0:
      return x220_boostBallChargeTime0;
    case 1:
      return x224_boostBallChargeTime1;
    case 2:
      return x228_boostBallChargeTime2;
    }
  }
  float GetBoostBallIncrementalSpeedTable(int i) const override {
    switch (i) {
    default:
    case 0:
      return x22c_boostBallIncrementalSpeed0;
    case 1:
      return x230_boostBallIncrementalSpeed1;
    case 2:
      return x234_boostBallIncrementalSpeed2;
    }
  }
};
} // namespace DataSpec::DNAMP1
