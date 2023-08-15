/******************************************************************************
 *  SwitchEdgeDetector.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "SwitchEdgeDetector.h"

#include <string.h>

SwitchEdgeDetector::SwitchEdgeDetector(LineMonitor* lineMonitor)
  : mLineMonitor(lineMonitor), mCount(), mPrevBrightness()/* {}
  : mLineMonitor(lineMonitor)*/, mIndex(), mMode() { memset(mSaturation, 0, sizeof(mSaturation)); }

SwitchEdgeDetector::~SwitchEdgeDetector() {}

const char* SwitchEdgeDetector::getClassName() const {
  return "SwitchEdgeDetector";
}

void SwitchEdgeDetector::reset(const ScenarioParams& params) {
  #define GET(a, b, c) params.get(a, &val) ? b(val) : c
  double val;
  mMode = GET("mode", int, 0);
  mPrevBrightness = mLineMonitor->getBrightness();
  mCount = 0;
  mIndex = 0;
  //mSaturation[mIndex++] = mLineMonitor->getHsvColor().s;
}

bool SwitchEdgeDetector::on() {
  if (mMode == 0) {
    double brightness = mLineMonitor->getBrightness();
    if (brightness >= mPrevBrightness) {
      ++mCount;
    } else {
      mCount = 0;
    }
    return mCount >= 10;
  } else {
    bool ret = false;
    mSaturation[mIndex] = mLineMonitor->getHsvColor().s;
    //if (mIndex == 0) {
    //} else if (mIndex == 1) {
    //  printf(" *> %f\n", mSaturation[1] - mSaturation[0]);
    //} else if (mIndex == 2) {
    //  printf(" *> %f\n", mSaturation[2] - mSaturation[0]);
    //} else if (mIndex == 3) {
    //  printf(" *> %f\n", mSaturation[3] - mSaturation[0]);
    //} else if (mIndex >= 4) {
    //  printf(" *> %f\n", mSaturation[mIndex] - mSaturation[mIndex - 4]);
    //}
    if (mIndex >= 4 && mSaturation[mIndex] - mSaturation[mIndex - 4] < -0.1) {
      ret = true;
    }
    if (++mIndex >= 100) {
      for (int i = 1; i < 100; ++i) {
        mSaturation[i - 1] = mSaturation[i];
      }
      mIndex = 99;
    }
    return ret;
  }
}