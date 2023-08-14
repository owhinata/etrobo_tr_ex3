/******************************************************************************
 *  StayInPlace.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "StayInPlace.h"

StayInPlace::StayInPlace(Driver* driver) : Walker(driver) {}

StayInPlace::~StayInPlace() {}

const char* StayInPlace::getClassName() const {
  return "StayInPlace";
}

void StayInPlace::reset(const ScenarioParams& params) {
  stop();
}

void StayInPlace::run() {
}