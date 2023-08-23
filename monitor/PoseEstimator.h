/******************************************************************************
 *  PoseEstimator.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_MONITOR_POSE_ESTIMATOR_H_
#define EV3_MONITOR_POSE_ESTIMATOR_H_

#include "Monitor.h"

#include "Motor.h"
#include "GyroSensor.h"
#include "Diagnostics.h"

class PoseEstimator : public Monitor {
public:
  PoseEstimator(ev3api::Motor& left, ev3api::Motor& right,
                ev3api::GyroSensor& gyro, Diagnostics* diag);

  virtual ~PoseEstimator();

  virtual void init(const ScenarioParams& params);

  virtual bool update();

  virtual const char* getClassName() const;

private:
  PoseEstimator(const PoseEstimator&);
  PoseEstimator& operator=(const PoseEstimator&);

  class Impl;
  Impl* mImpl;
};

#endif  // EV3_MONITOR_MONITOR_H_
