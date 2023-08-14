/******************************************************************************
 *  ColorDetector.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_DETECTOR_COLOR_DETECTOR_H_
#define EV3_DETECTOR_COLOR_DETECTOR_H_

#include "Detector.h"
#include "LineMonitor.h"

class ColorDetector : public Detector {
public:
  ColorDetector(LineMonitor* lineMonitor);

  virtual ~ColorDetector();

  virtual void reset(const ScenarioParams& params);

  virtual bool on();

  virtual const char* getClassName() const;

private:
  ColorDetector(const ColorDetector&);
  ColorDetector& operator=(const ColorDetector&);

  class Impl;
  Impl* mImpl;
};

#endif  // EV3_DETECTOR_DETECTOR_H_
