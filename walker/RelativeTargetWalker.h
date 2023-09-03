/******************************************************************************
 *  RelativeTargetWalker.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_WALKER_RELATIVE_TARGET_WALKER_H_
#define EV3_WALKER_RELATIVE_TARGET_WALKER_H_

#include "Walker.h"
#include "Detector.h"
#include "PoseEstimator.h"
#include "Uptime.h"

class RelativeTargetWalker : public Walker {
public:
    RelativeTargetWalker(PoseEstimator* pose, Uptime* uptime);

    virtual ~RelativeTargetWalker();

    virtual const char* getClassName() const;

    virtual void reset(const ScenarioParams& params);
 
    virtual bool execute();

    virtual Control get();

    Detector* getDetector();

private:
    RelativeTargetWalker(const RelativeTargetWalker&);
    RelativeTargetWalker& operator=(const RelativeTargetWalker&);

    class Impl;
    Impl* mImpl;

    class WalkerDetector : public Detector {
    public:
        WalkerDetector(RelativeTargetWalker& walker);
        virtual ~WalkerDetector();
        virtual void reset(const ScenarioParams& params);
        virtual bool on();
        virtual const char* getClassName() const;
    private:
        RelativeTargetWalker& mWalker;
    } mDetector;

    friend class RelativeTargetWalker::WalkerDetector;
};

#endif  // EV3_WALKER_RELATIVE_TARGET_WALKER_H_