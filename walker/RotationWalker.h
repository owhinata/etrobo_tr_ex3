/******************************************************************************
 *  RotationWalker.h (for LEGO Mindstorms EV3)
 *  Created on: 2023/07/22
 *  Definition of the Class LineWalker
 *  Author: Risei Kodo
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_WALKER_ROTATION_WALKER_H_
#define EV3_WALKER_ROTATION_WALKER_H_

#include "Walker.h"
#include "PoseEstimator.h"
#include "Uptime.h"

class RotationWalker : public Walker {
public:
    RotationWalker(PoseEstimator* pose, Uptime* uptime);

    virtual ~RotationWalker();

    virtual const char* getClassName() const;

    virtual void reset(const ScenarioParams& params);
 
    virtual bool execute();

    virtual Control get();

private:
    RotationWalker(const RotationWalker&);
    RotationWalker& operator=(const RotationWalker&);

    class Impl;
    Impl* mImpl;
};

#endif  // EV3_WALKER_ROTATION_WALKER_H_