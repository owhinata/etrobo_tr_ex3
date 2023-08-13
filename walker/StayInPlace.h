/******************************************************************************
 *  StayInPlace.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_WALKER_STAY_IN_PLACE_H_
#define EV3_WALKER_STAY_IN_PLACE_H_

#include "Walker.h"

class StayInPlace : public Walker {
public:
  StayInPlace(Driver* driver);

  virtual ~StayInPlace();

  virtual void reset(const ScenarioParams& params);

  virtual void run();

  virtual const char* getClassName() const;
};

#endif  // EV3_WALKER_STAY_IN_PLACE_H_