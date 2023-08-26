/******************************************************************************
 *  StepLineWalker.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2023/07/22
 *  Implementation of the Class LineWalker
 *  Author: Risei Kodo
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "StepLineWalker.h"

#include <float.h>
#include <math.h>

struct Param {
    double max;
    double target;
    double sp, sp1;
    double kp, kp1;
    double kd, kd1;
    double ki, ki1;
};

StepLineWalker::StepLineWalker(Uptime* uptime, LineMonitor* lineMonitor)
    : LineWalker(uptime, lineMonitor), mLine(lineMonitor), mParam(new Param) {}

StepLineWalker::~StepLineWalker() { delete (Param*)mParam; }

const char* StepLineWalker::getClassName() const {
    return "StepLineWalker";
}

void StepLineWalker::reset(const ScenarioParams& params) {
    LineWalker::reset(params);
    double target, speed, kp, kd, ki;
    LineWalker::getParam(&target, &speed, &kp, &kd, &ki);
    #define GET(a, b, c) params.get(a, &val) ? b(val) : c
    double val;
    Param* p = (Param*)mParam;
    p->target = GET("target", double, target);
    p->max = GET("max", double, 2.5);
    p->sp = GET("speed", double, speed);
    p->sp1 = GET("sp1", double, speed);
    p->kp = GET("kp", double, kp);
    p->kp1 = GET("kp1", double, kp);
    p->kd = GET("kd", double, kd);
    p->kd1 = GET("kd1", double, kd);
    p->ki = GET("ki", double, ki);
    p->ki1 = GET("ki1", double, ki);
    printf("  max:    %f\n"
           "  sp1:    %f\n"
           "  kp1:    %f\n"
           "  kd1:    %f\n"
           "  ki1:    %f\n",
           p->max, p->sp1, p->kp1, p->kd1, p->ki1);
}

bool StepLineWalker::execute() {
    Param* p = (Param*)mParam;
    double speed = p->sp, kp = p->kp, kd = p->kd, ki = p->ki;
    if (p->target > 1.0 && p->target < 99.0) {
        double d = fabs(p->target - mLine->getBrightness());
        d /= p->target > 50.0 ? 100 - p->target : p->target;
        d = -log10(d < 1e-10 ? 1e-10 : d > 1.0 ? 1.0 : d);
        speed = d * (p->sp1 - p->sp) / p->max + p->sp;
        speed = speed > p->sp1 ? p->sp1 : speed;
        kp = d * (p->kp1 - p->kp) / p->max + p->kp;
        kp = kp < 0.0 ? 0.0 : kp;
        kd = d * (p->kd1 - p->kd) / p->max + p->kd;
        kd = kd < 0.0 ? 0.0 : kd;
        ki = d * (p->ki1 - p->ki) / p->max + p->ki;
        ki = ki < 0.0 ? 0.0 : ki;
    }
    LineWalker::setParam(speed, kp, kd, ki);
    return LineWalker::execute();
}

Control StepLineWalker::get() { return LineWalker::get(); }