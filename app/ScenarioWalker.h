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
#include "Detector.h"
#include "Walker.h"

class MonitorsImpl;
class DetectorsImpl;
class WalkersImpl;

class ScenarioWalker {
public:
    ScenarioWalker(ScenarioReader* scenario,
                   Monitor* monitors[], int monitorsNum,
                   Detector* detectors[], int detectorsNum,
                   Walker* walkers[], int walkerNum);

    ~ScenarioWalker();

    void run();

private:
    void execUndefined();
    void execScenarioWalking();

    ScenarioReader* mScenario;
    int mState;
    int mSceneIndex;

    MonitorsImpl* mMonitors;
    DetectorsImpl* mDetectors;
    WalkersImpl* mWalkers;
};

#endif  // EV3_APP_SCENARIO_WALKER_H_
