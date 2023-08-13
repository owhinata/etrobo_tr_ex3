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
#include "Motor.h"
#include "LineMonitor.h"
#include "Diagnostics.h"

class LineWalker : public Walker {
public:
    static const int RIGHT_EDGE;
    static const int LEFT_EDGE;
    static const int WHITE_BRIGHTNESS;
    static const int BLACK_BRIGHTNESS;
    static const float STEERING_COEF;
    static const int BASE_SPEED;

    LineWalker(Driver* driver,
                const LineMonitor* lineMonitor,
                ev3api::Motor& leftWheel,
                ev3api::Motor& rightWheel);

    LineWalker(Driver* driver,
                const LineMonitor* lineMonitor,
                ev3api::Motor& leftWheel,
                ev3api::Motor& rightWheel,
                Diagnostics* diag);

    void init();
    void run();
    void setCommand();
    int16_t steeringAmountCalculation();

    const char* getClassName() const;

private:
    const LineMonitor* mLineMonitor;
    ev3api::Motor& mLeftWheel;
    ev3api::Motor& mRightWheel;
    int mBrightness;
    int mEdge;
    bool mIsInitialized;
    Diagnostics* diag_;
};

#endif  // EV3_WALKER_LINE_WALKER_H_
