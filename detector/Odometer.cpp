/******************************************************************************
 *  Odometer.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "Odometer.h"

class Odometer::Impl {
  PoseEstimator* pose;
  Diagnostics* diag;
  double base, distance;

public:
  Impl(PoseEstimator* _pose, Diagnostics* _diag)
    : pose(_pose), diag(_diag) {}

  void reset(const ScenarioParams& params) {
    #define GET(a, b, c) params.get(a, &val) ? b(val) : c
    double val;
    distance = GET("distance", double, 0.0);
    printf("  distance: %f\n", distance);
    base = pose->getDistance();
  }

  bool on() { return distance < pose->getDistance() - base; }
};

Odometer::Odometer(PoseEstimator* pose, Diagnostics* diag)
  : mImpl(new Impl(pose, diag)) {}

Odometer::~Odometer() { delete mImpl; }

const char* Odometer::getClassName() const { return "Odometer"; }

void Odometer::reset(const ScenarioParams& params) {
  return mImpl->reset(params);
  }

bool Odometer::on() { return mImpl->on(); }