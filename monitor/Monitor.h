/******************************************************************************
 *  Monitor.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_MONITOR_MONITOR_H_
#define EV3_MONITOR_MONITOR_H_

#include "ScenarioParams.h"

class Monitor {
public:
  virtual ~Monitor();

  virtual void init(const ScenarioParams& params);

  virtual bool update() = 0;

  virtual const char* getClassName() const = 0;
};

#endif  // EV3_MONITOR_MONITOR_H_
