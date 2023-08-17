/******************************************************************************
 *  Walker.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "Walker.h"

Walker::Walker(Driver* driver) : mDriver(driver) {}

Walker::~Walker() {}

void Walker::init() { return; }

void Walker::reset(const ScenarioParams& params) { return; }

void Walker::stop() {
  mDriver->stop();
}

void Walker::setDriveParam(int leftPWM, int rightPWM) {
  mDriver->setDriveParam(leftPWM, rightPWM);
}

double Walker::getBrightness() const {
  return mDriver->getBrightness();
}

double Walker::getUptime() const {
  return mDriver->getUptime();
}