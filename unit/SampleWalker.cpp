/******************************************************************************
 *  SampleWalker.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "SampleWalker.h"

SampleWalker::SampleWalker(Cockpit* cockpit) : Walker(cockpit) {}

SampleWalker::~SampleWalker() {}

const char* SampleWalker::getClassName() const {
  return "SampleWalker";
}

void SampleWalker::run() {
  double brightness = getBrightness();
  int left = 30, right = 30;
  setDriveParam(left, right);
}