/******************************************************************************
 *  LineDetector.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_DETECTOR_LINE_DETECTOR_H_
#define EV3_DETECTOR_LINE_DETECTOR_H_

#include "Detector.h"
#include "LineMonitor.h"
#include "Uptime.h"

class LineDetector : public Detector {
public:
  LineDetector(LineMonitor* lineMonitor, Uptime* uptime);

  virtual ~LineDetector();

  virtual void reset(const ScenarioParams& params);

  virtual bool on();

  virtual const char* getClassName() const;

private:
  LineDetector(const LineDetector&);
  LineDetector& operator=(const LineDetector&);

  class Impl;
  Impl* mImpl;
};

#endif  // EV3_DETECTOR_LINE_DETECTOR_H_
