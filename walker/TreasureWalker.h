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
#include "Motor.h"
#include "LineMonitor.h"

class TreasureWalker : public Walker {
public:
    TreasureWalker(ev3api::Motor& armMotor, LineMonitor* lineMonitor);

    virtual ~TreasureWalker();

    virtual const char* getClassName() const;

    virtual void reset();
 
    virtual bool execute();

    virtual Control get();

private:
    ev3api::Motor& mArmMotor;
    LineMonitor* mLineMonitor;
    int mCount = 0;
    int mPwm = 30;
    int state;
    double mPrevAngle = 0;
    hsv_raw_t mHsv;
};

#endif  // EV3_WALKER_TREASURE_WALKER_H_
