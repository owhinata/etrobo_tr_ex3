/******************************************************************************
 *  TreasureWalker.h (for LEGO Mindstorms EV3)
 *  Created on: 2023/07/22
 *  Definition of the Class TreasureWalker
 *  Author: Risei Kodo
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_WALKER_TREASURE_WALKER_H_
#define EV3_WALKER_TREASURE_WALKER_H_

#include "Walker.h"
#include "LineMonitor.h"
#include "Uptime.h"

class TreasureWalker : public Walker {
public:
    TreasureWalker(Uptime* uptime, LineMonitor* lineMonitor);

    virtual ~TreasureWalker();

    virtual const char* getClassName() const;

    virtual void reset(const ScenarioParams& params);
 
    virtual bool execute();

    virtual Control get();

protected:
    void setParam(double speed, double kp, double kd, double ki);
    void getParam(double* target, double* speed, double* kp, double* kd, double* ki);
    void clearIntegral();

private:
    Uptime* mUptime;
    LineMonitor* mLineMonitor;

    double mEdge;
    double mWhilteBrightness;
    double mBlackBrightness;
    double mSteeringCoef;
    double mDifferentialCoef;
    double mIntegralCoef;
    double mPrevDiffBrightness;
    double mPrevTime;
    double mIntegral;
    double mBaseSpeed;
    double mSteeringAmount;
};

#endif  // EV3_WALKER_TREASURE_WALKER_H_
