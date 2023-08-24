/******************************************************************************
 *  Odometer.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_DETECTOR_ODOMETER_H_
#define EV3_DETECTOR_ODOMETER_H_

#include "Detector.h"
#include "PoseEstimator.h"

class Odometer : public Detector {
public:
  Odometer(PoseEstimator* pose, Diagnostics* diag);

  virtual ~Odometer();

  virtual void reset(const ScenarioParams& params);

  virtual bool on();

  virtual const char* getClassName() const;

public:
  Odometer(const Odometer&);
  Odometer& operator=(const Odometer&);

  class Impl;
  Impl* mImpl;
};

#endif  // EV3_DETECTOR_ODOMETER_H_
