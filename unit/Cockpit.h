/******************************************************************************
 *  Cockpit.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_APP_COCKPIT_H_
#define EV3_APP_COCKPIT_H_

#include "LineMonitor.h"
#include "Motor.h"

class Cockpit {
public:
  Cockpit(LineMonitor* lineMonitor,
          ev3api::Motor& leftWheel,
          ev3api::Motor& rightWheel);

  void setDriveParam(int leftPWM, int rightPWM);

  double getBrightness() const;

private:
  LineMonitor*  mLineMonitor;
  ev3api::Motor& mLeftWheel;
  ev3api::Motor& mRightWheel;
};

#endif  // EV3_APP_COCKPIT_H_