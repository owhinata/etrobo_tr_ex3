/******************************************************************************
 *  Rotation.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "Rotation.h"

#include <math.h>

class Rotation::Impl {
  PoseEstimator* pose;
  Diagnostics* diag;
  double base, angle;

public:
  Impl(PoseEstimator* _pose, Diagnostics* _diag)
    : pose(_pose), diag(_diag) {}

  void reset(const ScenarioParams& params) {
    #define GET(a, b, c) params.get(a, &val) ? b(val) : c
    double val;
    angle = GET("angle", double, 0.0);
    angle = fabs(angle);
    printf("  angle: %f\n", angle);
    base = pose->getPose().rz;
  }

  bool on() {
    return fabs(pose->getPose().rz - base) > M_PI / 180.0 * angle;
  }
};

Rotation::Rotation(PoseEstimator* pose, Diagnostics* diag)
  : mImpl(new Impl(pose, diag)) {}

Rotation::~Rotation() { delete mImpl; }

const char* Rotation::getClassName() const { return "Rotation"; }

void Rotation::reset(const ScenarioParams& params) {
  return mImpl->reset(params);
  }

bool Rotation::on() { return mImpl->on(); }