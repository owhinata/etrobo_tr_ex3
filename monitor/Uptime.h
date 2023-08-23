/******************************************************************************
 *  Uptime.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_MONITOR_UPTIME_H_
#define EV3_MONITOR_UPTIME_H_

#include "Monitor.h"

#include "Clock.h"
#include "Diagnostics.h"

class Uptime : public Monitor {
public:
  Uptime(ev3api::Clock& clock, Diagnostics* diag);

  virtual ~Uptime();

  virtual void init(const ScenarioParams& params);

  virtual bool update();

  virtual const char* getClassName() const;

  double getUptime() const;

private:
  Uptime(const Uptime&);
  Uptime& operator=(const Uptime&);

  class Impl;
  Impl* mImpl;
};

#endif  // EV3_MONITOR_UPTIME_H_