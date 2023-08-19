/******************************************************************************
 *  ColorAmplification.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_DETECTOR_COLOR_AMPLIFICATION_H_
#define EV3_DETECTOR_COLOR_AMPLIFICATION_H_

#include "Detector.h"
#include "LineMonitor.h"
#include "Uptime.h"
#include "Diagnostics.h"

class ColorAmplification : public Detector {
public:
  ColorAmplification(LineMonitor* lineMonitor,
                     Uptime* uptime,
                     Diagnostics* diag);

  virtual ~ColorAmplification();

  virtual void reset(const ScenarioParams& params);

  virtual bool on();

  virtual const char* getClassName() const;

private:
  ColorAmplification(const ColorAmplification&);
  ColorAmplification& operator=(const ColorAmplification&);

  class Impl;
  Impl* mImpl;
};

#endif  // EV3_DETECTOR_AMPLIFICATION_H_