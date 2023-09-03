/******************************************************************************
 *  RelativeTargetWalker.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "RelativeTargetWalker.h"

#include <float.h>
#include <math.h>

class RelativeTargetWalker::Impl {
    PoseEstimator* pose;
    Uptime* uptime;
    struct {
        double x, y;
    } target;
    double w, forward, nearness;
    int state;
    double wait;
    Pose prev;
    Control control;

#if 0
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

public:
    Impl(PoseEstimator* _pose, Uptime* _uptime)
        : pose(_pose), uptime(_uptime) {}

    void reset(const ScenarioParams& params) {
        #define GET(a, b, c) params.get(a, &val) ? b(val) : c
        double val;
        target.x = GET("x", double, 0.0);
        target.y = GET("y", double, 0.0);
        w = GET("w", double, 50.0);
        forward = GET("forward", double, 40.0);
        nearness = GET("nearness", double, 0.01);
        state = 0;
        wait = uptime->getUptime();
        prev = pose->getPose();
        control.speed = control.steering = 0.0;
        printf("  target.x: %f\n"
               "  target.y: %f\n"
               "  w:        %f\n"
               "  forward:  %f\n"
               "  nearness: %f\n",
               target.x, target.y, w, forward, nearness);
    }

    struct Work {
        double distance, direction;
    };

    Work update() {
        Work work;
        Pose current = pose->getPose();
        double dx = current.px - prev.px,
               dy = current.py - prev.py,
               dz = current.rz - prev.rz,
               dc = cos(dz),
               ds = sin(dz),
               c = cos(current.rz),
               s = sin(current.rz),
               x =   dc * target.x + ds * target.y - c * dx - s * dy,
               y = - ds * target.x + dc * target.y + s * dx - c * dy;

        work.distance = sqrt(x * x + y * y);
        work.direction = atan2(y, x) * 180.0 / M_PI;
            
        target.x = x;
        target.y = y;
        prev = current;
    
        DEBUG_PRINT("%f %f %f %f %f",
                    c * x - s * y + current.px,
                    s * x + c * y + current.py,
                    x, y, work.direction);

        return work;    
    }

    bool execute() {
        control.speed = control.steering = 0.0;

        if (state == 0) {
            if (uptime->getUptime() - wait > 0.4) {
                ++state;
            }
            prev = pose->getPose();
        } else if (state == 1) {
            Work work = update();

            if (work.direction < -5.0 || work.direction > 5.0) {
                control.speed = w / 2.0;
                control.steering = target.y > 0 ? w : -w;
                wait = uptime->getUptime();
                DEBUG_PRINT(" turn %f\n", control.steering);
            } else {
                if (uptime->getUptime() - wait > 0.4) {
                    ++state;
                }
                DEBUG_PRINT(" wait\n");
            }
        } else if (state == 2) {
            Work work = update();

            if (work.distance > nearness) {
                control.speed = forward;
                control.steering = forward / 4.0 * work.direction;
            } else {
                ++state;
            }
            DEBUG_PRINT(" forward %f %f\n", control.speed, control.steering);
        } else {
        }
        return true;
    }

    Control get() { return control; }

    bool end() { return state > 2; }
};

RelativeTargetWalker::RelativeTargetWalker(PoseEstimator* pose, Uptime* uptime)
    : mImpl(new Impl(pose, uptime)), mDetector(*this) {}

RelativeTargetWalker::~RelativeTargetWalker() { delete mImpl; }

const char* RelativeTargetWalker::getClassName() const {
    return "RelativeTargetWalker";
}

void RelativeTargetWalker::reset(const ScenarioParams& params) {
    mImpl->reset(params);
}

bool RelativeTargetWalker::execute() { return mImpl->execute(); }

Control RelativeTargetWalker::get() { return mImpl->get(); }

Detector* RelativeTargetWalker::getDetector() { return &mDetector; }

RelativeTargetWalker::WalkerDetector::WalkerDetector(
    RelativeTargetWalker& walker)
    : mWalker(walker) {}

RelativeTargetWalker::WalkerDetector::~WalkerDetector() {}

const char* RelativeTargetWalker::WalkerDetector::getClassName() const {
    return mWalker.getClassName();
}

void RelativeTargetWalker::WalkerDetector::reset(const ScenarioParams& params) {}

bool RelativeTargetWalker::WalkerDetector::on() { return mWalker.mImpl->end(); }