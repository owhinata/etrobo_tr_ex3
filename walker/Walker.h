/******************************************************************************
 *  Walker.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_WALKER_WALKER_H_
#define EV3_WALKER_WALKER_H_

#include "ScenarioParams.h"

struct Control {
  double speed;
  double steering;

  Control();
  Control(double _speed, double _steering);
};

class Walker {
public:
  virtual ~Walker();

  virtual void init();

  virtual void reset(const ScenarioParams& params);

  virtual bool execute();

  virtual Control get();

  virtual const char* getClassName() const = 0;
};

#endif  // EV3_UNIT_WALKER_H_
