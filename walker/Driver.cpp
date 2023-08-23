/******************************************************************************
 *  Drive.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "Driver.h"

#include <math.h>

Driver::Driver(ev3api::Motor& leftWheel,
               ev3api::Motor& rightWheel,
               Diagnostics* diag)
  : mLeftWheel(leftWheel),
    mRightWheel(rightWheel),
    mDiag(diag) {}

void Driver::run(Walker* walker) {
  if (!walker || !walker->execute()) {
    stop();
    return;
  }
  Control ctrl = walker->get();

  // 左右モータ駆動パワーの計算 (steering > 0 で左に曲がる)
  int leftMotorPower = (int)round(ctrl.speed - ctrl.steering);
  int rightMotorPower = (int)round(ctrl.speed + ctrl.steering);
  // printf(" l: %f r: %f",
  //        ctrl.speed + ctrl.steering,
  //        ctrl.speed - ctrl.steering);
  // printf(" left: %d right: %d\n", leftMotorPower, rightMotorPower);

  setDriveParam(leftMotorPower, rightMotorPower);
}

void Driver::stop() {
  mLeftWheel.setPWM(0);
  mRightWheel.setPWM(0);
  mLeftWheel.stop();
  mRightWheel.stop();
  mDiag->setDriveParam(0.0, 0.0);
}

void Driver::setDriveParam(int leftPWM, int rightPWM) {
  mLeftWheel.setPWM(leftPWM);
  mRightWheel.setPWM(rightPWM);
  mDiag->setDriveParam(float(leftPWM), float(rightPWM));
}