/******************************************************************************
 *  SampleWalker.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_UNIT_SAMPLE_WALKER_H_
#define EV3_UNIT_SAMPLE_WALKER_H_

#include "Walker.h"

class SampleWalker : public Walker {
public:
  SampleWalker(Cockpit* cockpit);

  ~SampleWalker();

  void run();

  const char* getClassName() const;

private:
};

#endif  // EV3_UNIT_SAMPLE_WALKER_H_