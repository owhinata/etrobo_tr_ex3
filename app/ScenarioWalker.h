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

#include "ScenarioReader.h"
#include "Monitor.h"
#include "Starter.h"

#include "LineWalker.h"
#include "SampleWalker.h"

struct Walkers {
    LineWalker* lineWalker;
    SampleWalker* sampleWalker;
};

class MonitorsImpl;

class ScenarioWalker {
public:
    ScenarioWalker(ScenarioReader* scenario,
                   Monitor* monitors[], int monitorsNum,
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

    ScenarioReader* mScenario;
    MonitorsImpl* mMonitors;
};

#endif  // EV3_APP_SCENARIO_WALKER_H_
