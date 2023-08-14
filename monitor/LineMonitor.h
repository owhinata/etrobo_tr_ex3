/******************************************************************************
 *  LineMonitor.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineMonitor
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_MONITOR_LINE_MONITOR_H_
#define EV3_MONITOR_LINE_MONITOR_H_

#include "Monitor.h"

#include "ColorSensor.h"
#include "Diagnostics.h"

class LineMonitor : public Monitor {
public:
  explicit LineMonitor(const ev3api::ColorSensor& colorSensor,
                       Diagnostics* diag);

  virtual ~LineMonitor();

  virtual void update();

  virtual const char* getClassName() const;

  virtual void init(const ScenarioParams& params);

  bool isOnBlueLine() const;

  double getBrightness() const;

private:
  const ev3api::ColorSensor& mColorSensor;
  Diagnostics* mDiag;

  struct Context;
  Context* mContext;
};

#endif  // EV3_MONITOR_LINE_MONITOR_H_