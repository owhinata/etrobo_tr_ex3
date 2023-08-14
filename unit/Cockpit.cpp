/******************************************************************************
 *  WalkerParam.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "Cockpit.h"

Cockpit::Cockpit(LineMonitor* lineMonitor,
                 ev3api::Motor& leftWheel,
                 ev3api::Motor& rightWheel)
  : mLineMonitor(lineMonitor),
    mLeftWheel(leftWheel),
    mRightWheel(rightWheel) {}

void Cockpit::setDriveParam(int leftPWM, int rightPWM) {
  mLeftWheel.setPWM(leftPWM);
  mRightWheel.setPWM(rightPWM);
}

double Cockpit::getBrightness() const {
  return mLineMonitor->getBrightness();
}