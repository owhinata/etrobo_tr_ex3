/******************************************************************************
 *  Diagnostics.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_APP_DIAGNOSTICS_H_
#define EV3_APP_DIAGNOSTICS_H_

#include "ColorSensor.h"

enum ColorSensorMode {
  kReflect,
  kRgbRaw,
};

class Diagnostics {
public:
  Diagnostics();
  ~Diagnostics();

  void MonitorColorSensor(ColorSensorMode mode);
  void MonitorGyroSensor();
  void MonitorSonarSensor();
  void MonitorMotors();

  void Commit();

  Diagnostics(const Diagnostics&) = delete;
  Diagnostics& operator=(const Diagnostics&) = delete;

private:
  struct Context;
  Context *ctx_;

  void Invalidate();
};

#endif // EV3_APP_DIAGNOSTICS_H_
