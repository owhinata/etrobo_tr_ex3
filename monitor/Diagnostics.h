/******************************************************************************
 *  Diagnostics.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_MONITOR_DIAGNOSTICS_H_
#define EV3_MONITOR_DIAGNOSTICS_H_

#include "ColorSensor.h"

enum ColorSensorMode {
  kColorSensorModeReflect,
  kColorSensorModeRgbRaw,
};

class Diagnostics {
public:
  Diagnostics();
  ~Diagnostics();

  void update(uint32_t uptime);

  void setColor(double rgb[3], double hsv[3], double y);
  void setMeasure(double leftWheelCount, double rightWheelCount,
                  double yaw, double anglVel);

  void setDriveParam(double leftPower, double rightPower);

  void MonitorColorSensor(ColorSensorMode mode);
  void MonitorGyroSensor();
  void MonitorSonarSensor();
  void MonitorMotors();

  void Commit();

private:
  Diagnostics(const Diagnostics&);
  Diagnostics& operator=(const Diagnostics&);

  struct Context;
  Context *ctx_;
};

#endif // EV3_MONITOR_DIAGNOSTICS_H_
