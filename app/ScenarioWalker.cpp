/******************************************************************************
 *  ScenarioWalker.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/02/07
 *  Implementation of the Class ScenarioWalker
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "ScenarioWalker.h"

#include <stdio.h>
#include <stdlib.h>

#include "ScenarioReader.h"

enum State {
    UNDEFINED,
    WAITING_FOR_START,
    LINE_TRACING,
    SCENARIO_TRACING,
};

struct ScenarioWalker::Context {
    Walkers walkers;
    Starter* starter;
    State state;

    Context(const Walkers& _walkers, Starter* _starter)
        : walkers(_walkers), starter(_starter),
          state(UNDEFINED) {}
};

class MonitorsImpl {
public:
    MonitorsImpl(Monitor* monitors[], int monitorsNum, ScenarioReader* scenario)
        : mMonitorsInitialized(), mScenario(scenario),
          mMonitorsNum(monitorsNum),
          mMonitors((Monitor**)calloc(monitorsNum, sizeof(Monitor*))) {
        for (int i = 0; i < mMonitorsNum; ++i) {
            mMonitors[i] = monitors[i];
        }
    }

    ~MonitorsImpl() { free(mMonitors); }

    void update() {
        for (int i = 0; i < mMonitorsNum; ++i) {
            if (!mMonitorsInitialized) {
                printf("--------\n");
                const char* klass = mMonitors[i]->getClassName();
                const ScenarioParams& params = mScenario->getMonitorParams(klass);
                mMonitors[i]->init(params);
                ++mMonitorsInitialized;
            }
            mMonitors[i]->update();
        }
    }

private:
    int mMonitorsInitialized;
    ScenarioReader *mScenario;
    int mMonitorsNum;
    Monitor** mMonitors;
};

ScenarioWalker::ScenarioWalker(
        ScenarioReader* scenario,
        Monitor* monitors[], int monitorsNum,
        const Walkers& walkers,
        Starter* starter)
    : mContext(new Context(walkers, starter)), mScenario(scenario),
      mMonitors(new MonitorsImpl(monitors, monitorsNum, mScenario)) {}

ScenarioWalker::~ScenarioWalker() { delete mContext; }

void ScenarioWalker::run() {
    mMonitors->update();

    switch (mContext->state) {
    case UNDEFINED:
        execUndefined();
        break;
    case WAITING_FOR_START:
        execWaitingForStart();
        break;
    case LINE_TRACING:
        execLineTracing();
        break;
    case SCENARIO_TRACING:
        execScenarioTracing();
        break;
    default:
        break;
    }
}

void ScenarioWalker::execUndefined() {
    mContext->state = WAITING_FOR_START;
}

/**
 * 開始待ち状態の処理
 */
void ScenarioWalker::execWaitingForStart() {
    if (mContext->starter->isPushed()) {
        mContext->state = LINE_TRACING;
    }
}

/**
 * ライントレース状態の処理
 */
void ScenarioWalker::execLineTracing() {
    mContext->walkers.lineWalker->run();
}

void ScenarioWalker::execScenarioTracing() {
}
