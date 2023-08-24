/******************************************************************************
 *  Driver.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_WALKER_DRIVER_H_
#define EV3_WALKER_DRIVER_H_

#include "Walker.h"
#include "Motor.h"
#include "Diagnostics.h"

class Driver {
public:
  Driver(ev3api::Motor& leftWheel,
         ev3api::Motor& rightWheel,
         Diagnostics* diag);

  void run(Walker* walker);

  void stop();

private:
  void setDriveParam(int leftPWM, int rightPWM);

  ev3api::Motor& mLeftWheel;
  ev3api::Motor& mRightWheel;
  Diagnostics* mDiag;
};

#endif  // EV3_WALKER_DRIVER_H_
