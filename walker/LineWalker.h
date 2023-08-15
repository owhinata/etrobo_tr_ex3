/******************************************************************************
 *  LineWalker.h (for LEGO Mindstorms EV3)
 *  Created on: 2023/07/22
 *  Definition of the Class LineWalker
 *  Author: Risei Kodo
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_WALKER_LINE_WALKER_H_
#define EV3_WALKER_LINE_WALKER_H_

#include "Walker.h"

class LineWalker : public Walker {
public:
    LineWalker(Driver* driver);

    virtual ~LineWalker();

    virtual const char* getClassName() const;

    virtual void reset(const ScenarioParams& params);

    virtual void run();

private:
    double steeringAmountCalculation(double brightness);

    double mEdge;
    double mWhilteBrightness;
    double mBlackBrightness;
    double mSteeringCoef;
    double mDifferentialCoef;
    double mPrevDiffBrightness;
    uint32_t mPrevTime;
    double mBaseSpeed;
};

#endif  // EV3_WALKER_LINE_WALKER_H_
