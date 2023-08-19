/******************************************************************************
 *  ExitColoredArea.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_DETECTOR_EXIT_COLORED_AREA_H_
#define EV3_DETECTOR_EXIT_COLORED_AREA_H_

#include "Detector.h"
#include "LineMonitor.h"
#include "Uptime.h"
#include "Diagnostics.h"

class ExitColoredArea : public Detector {
public:
  ExitColoredArea(LineMonitor* lineMonitor,
                  Uptime* uptime,
                  Diagnostics* diag);

  virtual ~ExitColoredArea();

  virtual void reset(const ScenarioParams& params);

  virtual bool on();

  virtual const char* getClassName() const;

public:
  ExitColoredArea(const ExitColoredArea&);
  ExitColoredArea& operator=(const ExitColoredArea&);

  class Impl;
  Impl* mImpl;
};

#endif  // EV3_DETECTOR_EXIT_COLORED_AREA_H_
