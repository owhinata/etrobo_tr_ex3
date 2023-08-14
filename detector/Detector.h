/******************************************************************************
 *  Detector.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_DETECTOR_DETECTOR_H_
#define EV3_DETECTOR_DETECTOR_H_

#include "ScenarioParams.h"

class Detector {
public:
  virtual ~Detector();

  virtual void init();

  virtual void reset(const ScenarioParams& params) = 0;

  virtual bool on() = 0;

  virtual const char* getClassName() const = 0;
};

#endif  // EV3_DETECTOR_DETECTOR_H_
