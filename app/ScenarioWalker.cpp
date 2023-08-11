/******************************************************************************
 *  ScenarioWalker.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/02/07
 *  Implementation of the Class ScenarioWalker
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "Scenario.h"

#include "Diagnostics.h"
#include "ScenarioWalker.h"

enum State {
    UNDEFINED,
    WAITING_FOR_START,
    LINE_TRACING,
    SCENARIO_TRACING,
};

// scene object
static Scene gScenes[] = {
    { TURN_LEFT,   1250 * 1000, 0 },  // 左旋回1.25秒
    { GO_STRAIGHT, 5000 * 1000, 0 },  // 直進5秒
    { TURN_LEFT,   1250 * 1000, 0 },  // 左旋回1.25秒
    { GO_STRAIGHT, 2500 * 1000, 0 }   // 直進2.5秒
};
static const int SCENES_NUM = sizeof(gScenes) / sizeof(gScenes[0]);

struct ScenarioWalker::Context {
    Monitors monitors;
    Walkers walkers;
    Starter* starter;
    Scenario scenario;
    int scenarioNumber;
    State state;

    Context(const Monitors& _monitors,
            const Walkers& _walkers,
            Starter* _starter)
        : monitors(_monitors), walkers(_walkers), starter(_starter),
          scenario(0), scenarioNumber(0) {}
};

ScenarioWalker::ScenarioWalker(const Monitors& monitors,
                               const Walkers& walkers,
                               Starter* starter)
    : mContext(new Context(monitors, walkers, starter)) {
    // シナリオを構築する
    for (int i = 0; i < SCENES_NUM; i++) {
        mContext->scenario.add(&gScenes[i]);
    }

    FILE* fp = fopen("setting.txt", "r");
    if (fp) {
        char buf[80];
        while (fgets(buf, sizeof(buf), fp)) {
            printf("%s", buf);
            int number = atoi(buf);
            if (0 < number && number < SCENES_NUM) {
                mContext->scenarioNumber = number;
            }
        }
        fclose(fp);
    }

    mContext->state = UNDEFINED;
}

ScenarioWalker::~ScenarioWalker() { delete mContext; }

/**
 * ランダム走行する
 */
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
    mContext->walkers.lineTracer->run();
}

void ScenarioWalker::execScenarioTracing() {
}
