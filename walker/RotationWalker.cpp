/******************************************************************************
 *  RotationWalker.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2023/07/22
 *  Implementation of the Class LineWalker
 *  Author: Risei Kodo
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "RotationWalker.h"

#include <float.h>
#include <math.h>

class RotationWalker::Impl {
    PoseEstimator* pose;
    Uptime* uptime;
    double speed;

public:
    Impl(PoseEstimator* _pose, Uptime* _uptime)
        : pose(_pose), uptime(_uptime) {}

    void reset(const ScenarioParams& params) {
        #define GET(a, b, c) params.get(a, &val) ? b(val) : c
        double val;
        speed = GET("speed", double, 0.0);
        printf("  speed: %f\n", speed);
    }

    bool execute() { return true; }

    Control get() { return Control(0.0, speed); }
};

RotationWalker::RotationWalker(PoseEstimator* pose, Uptime* uptime)
    : mImpl(new Impl(pose, uptime)) {}

RotationWalker::~RotationWalker() { delete mImpl; }

const char* RotationWalker::getClassName() const { return "RotationWalker"; }

void RotationWalker::reset(const ScenarioParams& params) {
    mImpl->reset(params);
}

bool RotationWalker::execute() { return mImpl->execute(); }

Control RotationWalker::get() { return mImpl->get(); }