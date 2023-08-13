/******************************************************************************
 *  Drive.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "Driver.h"

Driver::Driver(LineMonitor* lineMonitor,
               ev3api::Motor& leftWheel,
               ev3api::Motor& rightWheel)
  : mLineMonitor(lineMonitor),
    mLeftWheel(leftWheel),
    mRightWheel(rightWheel) {}

void Driver::stop() {
  mLeftWheel.setPWM(0);
  mRightWheel.setPWM(0);
  mLeftWheel.stop();
  mRightWheel.stop();
}

void Driver::setDriveParam(int leftPWM, int rightPWM) {
  mLeftWheel.setPWM(leftPWM);
  mRightWheel.setPWM(rightPWM);
}

double Driver::getBrightness() const {
  return mLineMonitor->getBrightness();
}