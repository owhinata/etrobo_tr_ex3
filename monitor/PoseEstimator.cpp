/******************************************************************************
 *  PoseEstimator.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "PoseEstimator.h"

class PoseEstimator::Impl {
  ev3api::Motor& left;
  ev3api::Motor& right;
  ev3api::GyroSensor& gyro;
  Diagnostics* diag;

public:
  Impl(ev3api::Motor& _left, ev3api::Motor& _right, ev3api::GyroSensor& _gyro,
       Diagnostics* _diag)
    : left(_left), right(_right), gyro(_gyro), diag(_diag) {}

  void init(const ScenarioParams& params) {
    left.reset();
    right.reset();
    gyro.reset();
  }

  bool update() {
    double lc = float(left.getCount()),
           rc = float(right.getCount()),
           yaw = float(gyro.getAngle()),
           w = float(gyro.getAnglerVelocity());
    diag->setMeasure(lc, rc, yaw, w);
    return true;
  }
};

PoseEstimator::PoseEstimator(ev3api::Motor& left, ev3api::Motor& right,
                             ev3api::GyroSensor& gyro, Diagnostics* diag)
  : mImpl(new Impl(left, right, gyro, diag)) {}

PoseEstimator::~PoseEstimator() { delete mImpl; }

const char* PoseEstimator::getClassName() const { return "PoseEstimator"; }

void PoseEstimator::init(const ScenarioParams& params) {
  mImpl->init(params);
}

bool PoseEstimator::update() { return mImpl->update(); }