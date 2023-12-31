/******************************************************************************
 *  SampleWalker.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_WALKER_SAMPLE_WALKER_H_
#define EV3_WALKER_SAMPLE_WALKER_H_

#include "Walker.h"

class SampleWalker : public Walker {
public:
  SampleWalker();

  virtual ~SampleWalker();

  virtual bool execute();

  virtual Control get();

  virtual const char* getClassName() const;
};

#endif  // EV3_UNIT_SAMPLE_WALKER_H_