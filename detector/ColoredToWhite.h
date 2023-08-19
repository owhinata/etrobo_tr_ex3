/******************************************************************************
 *  ColoredToWhite.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_DETECTOR_COLORED_TO_WHITE_H_
#define EV3_DETECTOR_COLORED_TO_WHITE_H_

#include "Detector.h"
#include "LineMonitor.h"
#include "Uptime.h"
#include "Diagnostics.h"

class ColoredToWhite : public Detector {
public:  
  ColoredToWhite(LineMonitor* lineMonitor,
                 Uptime* uptime,
                 Diagnostics* diag);

  virtual ~ColoredToWhite();

  virtual void reset(const ScenarioParams& params);

  virtual bool on();

  virtual const char* getClassName() const;

public:
  ColoredToWhite(const ColoredToWhite&);
  ColoredToWhite& operator=(const ColoredToWhite&);

  class Impl;
  Impl* mImpl;
};

#endif  // EV3_DETECTOR_COLORED_TO_WHITE_H_
