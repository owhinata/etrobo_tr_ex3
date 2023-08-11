/******************************************************************************
 *  ScenarioWalker.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/02/07
 *  Implementation of the Class RandomWalker
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_APP_SCENARIO_WALKER_H_
#define EV3_APP_SCENARIO_WALKER_H_

#include "Starter.h"

#include "LineMonitor.h"
#include "LineTracer.h"

struct Monitors {
    LineMonitor* lineMonitor;
};

struct Walkers {
    LineTracer* lineTracer;  // TODO: ->lineWalker
};

class ScenarioWalker {
public:
    ScenarioWalker(const Monitors& monitors,
                   const Walkers& walkers,
                   Starter* starter);

    ~ScenarioWalker();

    void run();

private:
    struct Context;
    Context* mContext;

    void execUndefined();
    void execWaitingForStart();
    void execLineTracing();
    void execScenarioTracing();
};

#endif  // EV3_APP_SCENARIO_WALKER_H_
