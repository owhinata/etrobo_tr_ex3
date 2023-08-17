/******************************************************************************
 *  SwitchEdgeDetector.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_DETECTOR_SWITECH_EDGE_DETECTOR_H_
#define EV3_DETECTOR_SWITECH_EDGE_DETECTOR_H_

#include "Detector.h"
#include "LineMonitor.h"

class SwitchEdgeDetector : public Detector {
public:
  SwitchEdgeDetector(LineMonitor* lineMonitor);

  virtual ~SwitchEdgeDetector();

  virtual void reset(const ScenarioParams& params);

  virtual bool on();

  virtual const char* getClassName() const;

public:
  LineMonitor* mLineMonitor;
  int mCount;
  double mPrevBrightness;
  int mIndex;
  double mSaturation[100];
  int mMode;
};

#endif  // EV3_DETECTOR_SWITECH_EDGE_DETECTOR_H_