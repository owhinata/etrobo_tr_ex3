/******************************************************************************
 *  Walker.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_WALKER_WALKER_H_
#define EV3_WALKER_WALKER_H_

#include <stdint.h>

#include "Driver.h"
#include "ScenarioParams.h"

class Walker {
public:
  Walker(Driver* driver);

  virtual ~Walker();

  virtual void init();

  virtual void reset(const ScenarioParams& params);

  virtual void run() = 0;

  virtual const char* getClassName() const = 0;

protected:
  void stop();
  void setDriveParam(int leftPWM, int rightPWM);
  double getBrightness() const;
  uint32_t getUptime() const;

private:
  Driver* mDriver;
};

#endif  // EV3_UNIT_WALKER_H_
