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
#include <string.h>

enum {
    UNDEFINED,
    SCENARIO_WALKING,
};

class MonitorsImpl {
public:
    MonitorsImpl(Monitor* monitors[], int monitorsNum, ScenarioReader* scenario)
        : mScenario(scenario),
          mMonitorsNum(monitorsNum),
          mMonitors((Monitor**)calloc(monitorsNum, sizeof(Monitor*))) {
        for (int i = 0; i < mMonitorsNum; ++i) {
            mMonitors[i] = monitors[i];
        }
    }

    ~MonitorsImpl() { free(mMonitors); }

    void init() {
        for (int i = 0; i < mMonitorsNum; ++i) {
            const char* klass = mMonitors[i]->getClassName();
            const ScenarioParams& params = mScenario->getMonitorParams(klass);
            mMonitors[i]->init(params);
        }
    }

    void update() {
        for (int i = 0; i < mMonitorsNum; ++i) {
            mMonitors[i]->update();
        }
    }

private:
    ScenarioReader *mScenario;
    int mMonitorsNum;
    Monitor** mMonitors;
};

class DetectorsImpl {
public:
    DetectorsImpl(Detector* detectors[], int detectorsNum, ScenarioReader* scenario)
        : mScenario(scenario), mCurrentDetector(), mDetectorsNum(detectorsNum),
          mDetectors((Detector**)calloc(detectorsNum, sizeof(Detector*))) {
        for (int i = 0; i < mDetectorsNum; ++i) {
            mDetectors[i] = detectors[i];
        }
    }

    ~DetectorsImpl() { free(mDetectors); }

    void init() {
        for (int i = 0; i < mDetectorsNum; ++i) {
            mDetectors[i]->init();
        }
    }

    bool isSceneTerminate() {
        return mCurrentDetector ? mCurrentDetector->on() : false;
    }

    void goToScene(int index) {
        mCurrentDetector = getDetectorForSceneIndex(index);
        printf("Detector: %s\n",
               mCurrentDetector ? mCurrentDetector->getClassName() : "nil");
        if (mCurrentDetector) {
            const ScenarioParams& params = mScenario->getSceneDetectorParams(index);
            mCurrentDetector->reset(params);
        }
    }

    Detector* getDetectorForSceneIndex(int index) {
        const char* target = mScenario->getSceneDetector(index);
        for (int i = 0; i < mDetectorsNum; ++i) {
            if (strcmp(mDetectors[i]->getClassName(), target) == 0) {
                return mDetectors[i];
            }
        }
        return 0;
    }

private:
    ScenarioReader *mScenario;
    Detector* mCurrentDetector;
    int mDetectorsNum;
    Detector** mDetectors;
};

class WalkersImpl {
public:
    WalkersImpl(Walker* walkers[], int walkersNum, ScenarioReader* scenario)
        : mScenario(scenario), mCurrentWalker(), mWalkersNum(walkersNum),
          mWalkers((Walker**)calloc(walkersNum, sizeof(Walker*))) {
        for (int i = 0; i < mWalkersNum; ++i) {
            mWalkers[i] = walkers[i];
        }
    }

    ~WalkersImpl() { free(mWalkers); }

    void init() {
        for (int i = 0; i < mWalkersNum; ++i) {
            mWalkers[i]->init();
        }
    }

    void run() {
        if (mCurrentWalker) {
            mCurrentWalker->run();
        }
    }

    void goToScene(int index) {
        mCurrentWalker = getWalkerForSceneIndex(index);
        printf("Walker: %s\n",
               mCurrentWalker ? mCurrentWalker->getClassName() : "nil");
        if (mCurrentWalker) {
            const ScenarioParams& params = mScenario->getSceneWalkerParams(index);
            mCurrentWalker->reset(params);
        }
    }

    Walker* getWalkerForSceneIndex(int index) {
        const char* target = mScenario->getSceneWalker(index);
        for (int i = 0; i < mWalkersNum; ++i) {
            if (strcmp(mWalkers[i]->getClassName(), target) == 0) {
                return mWalkers[i];
            }
        }
        return 0;
    }

private:
    ScenarioReader *mScenario;
    Walker* mCurrentWalker;
    int mWalkersNum;
    Walker** mWalkers;
};

ScenarioWalker::ScenarioWalker(
        ScenarioReader* scenario,
        Monitor* monitors[], int monitorsNum,
        Detector* detectors[], int detectorsNum,
        Walker* walkers[], int walkersNum)
    : mScenario(scenario), mState(UNDEFINED), mSceneIndex(),
      mMonitors(new MonitorsImpl(monitors, monitorsNum, mScenario)),
      mDetectors(new DetectorsImpl(detectors, detectorsNum, mScenario)),
      mWalkers(new WalkersImpl(walkers, walkersNum, mScenario)) {}

ScenarioWalker::~ScenarioWalker() {
    delete mWalkers;
    delete mDetectors;
    delete mMonitors;
}

void ScenarioWalker::execUndefined() {
    printf("**** Initialize ****\n");
    mMonitors->init();
    mWalkers->init();
    mDetectors->init();
    printf("**** Start Scene %d ****\n", mSceneIndex);
    mWalkers->goToScene(mSceneIndex);
    mDetectors->goToScene(mSceneIndex);
    mState = SCENARIO_WALKING;
}

void ScenarioWalker::execScenarioWalking() {
    mMonitors->update();
    if (mDetectors->isSceneTerminate()) {
        ++mSceneIndex;
        printf("**** Start Scene %d ****\n", mSceneIndex);
        mWalkers->goToScene(mSceneIndex);
        mDetectors->goToScene(mSceneIndex);
    }
    mWalkers->run();
}

void ScenarioWalker::run() {
    switch (mState) {
    case UNDEFINED:
        execUndefined();
        break;
    case SCENARIO_WALKING:
        execScenarioWalking();
        break;
    default:
        break;
    }
}