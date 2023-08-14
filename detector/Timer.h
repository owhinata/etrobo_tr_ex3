/******************************************************************************
 *  Timer.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_DETECTOR_TIMER_H_
#define EV3_DETECTOR_TIMER_H_

#include "Detector.h"
#include "Uptime.h"

class Timer : public Detector {
public:
  explicit Timer(Uptime* time);

  virtual ~Timer();

  virtual void reset(const ScenarioParams& params);

  virtual bool on();

  virtual const char* getClassName() const;

private:
  Timer(const Timer&);
  Timer& operator=(const Timer&);

  class Impl;
  Impl* mImpl;
};

#endif  // EV3_DETECTOR_TIMER_H_