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

  void init(ColorSensorMode mode);

  void update(uint32_t uptime);

  void MonitorColorSensor(ColorSensorMode mode);
  void MonitorGyroSensor();
  void MonitorSonarSensor();
  void MonitorMotors();

  void Commit();

private:
  struct Context;
  Context *ctx_;

  void Invalidate();

  Diagnostics(const Diagnostics&);
  Diagnostics& operator=(const Diagnostics&);
};

#endif // EV3_MONITOR_DIAGNOSTICS_H_