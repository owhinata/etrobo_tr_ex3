/******************************************************************************
 *  Driver.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_WALKER_DRIVER_H_
#define EV3_WALKER_DRIVER_H_

#include "Uptime.h"
#include "LineMonitor.h"
#include "Motor.h"
#include "Diagnostics.h"

class Driver {
public:
  Driver(Uptime* uptime,
         LineMonitor* lineMonitor,
         ev3api::Motor& leftWheel,
         ev3api::Motor& rightWheel,
         Diagnostics* diag);

  void stop();

  void setDriveParam(int leftPWM, int rightPWM);

  double getBrightness() const;

  uint32_t getUptime() const;

private:
  Uptime* mUptime;
  LineMonitor* mLineMonitor;
  ev3api::Motor& mLeftWheel;
  ev3api::Motor& mRightWheel;
  Diagnostics* mDiag;
};

#endif  // EV3_WALKER_DRIVER_H_