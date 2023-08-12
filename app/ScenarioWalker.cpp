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
    ScenarioReader scenario;
    Monitors monitors;
    Walkers walkers;
    Starter* starter;
    State state;

    Context(const Monitors& _monitors,
            const Walkers& _walkers,
            Starter* _starter)
        : scenario(), monitors(_monitors), walkers(_walkers), starter(_starter),
          state(UNDEFINED) {}
};

ScenarioWalker::ScenarioWalker(const Monitors& monitors,
                               const Walkers& walkers,
                               Starter* starter)
    : mContext(new Context(monitors, walkers, starter)) {}

ScenarioWalker::~ScenarioWalker() { delete mContext; }

void ScenarioWalker::run() {
    mContext->monitors.lineMonitor->update();

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
