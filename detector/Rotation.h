/******************************************************************************
 *  Rotation.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_DETECTOR_ROTATION_H_
#define EV3_DETECTOR_ROTATION_H_

#include "Detector.h"
#include "PoseEstimator.h"

class Rotation : public Detector {
public:
  Rotation(PoseEstimator* pose, Diagnostics* diag);

  virtual ~Rotation();

  virtual void reset(const ScenarioParams& params);

  virtual bool on();

  virtual const char* getClassName() const;

public:
  Rotation(const Rotation&);
  Rotation& operator=(const Rotation&);

  class Impl;
  Impl* mImpl;
};

#endif  // EV3_DETECTOR_ROTATION_H_