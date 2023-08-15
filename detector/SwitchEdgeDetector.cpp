/******************************************************************************
 *  SwitchEdgeDetector.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "SwitchEdgeDetector.h"

SwitchEdgeDetector::SwitchEdgeDetector(LineMonitor* lineMonitor)
  : mLineMonitor(lineMonitor), mCount(), mPrevBrightness() {}

SwitchEdgeDetector::~SwitchEdgeDetector() {}

const char* SwitchEdgeDetector::getClassName() const {
  return "SwitchEdgeDetector";
}

void SwitchEdgeDetector::reset(const ScenarioParams& params) {
  mPrevBrightness = mLineMonitor->getBrightness();
  mCount = 0;
}

bool SwitchEdgeDetector::on() {
  double brightness = mLineMonitor->getBrightness();
  if (brightness >= mPrevBrightness) {
    ++mCount;
  } else {
    mCount = 0;
  }
  return mCount >= 10;
}