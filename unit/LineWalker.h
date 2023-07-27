/******************************************************************************
 *  LineWalker.h (for LEGO Mindstorms EV3)
 *  Created on: 2023/07/22
 *  Definition of the Class LineWalker
 *  Author: Risei Kodo
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_UNIT_LINE_WALKER_H_
#define EV3_UNIT_LINE_WALKER_H_

#include "Motor.h"

class LineWalker {
public:
    static const int RIGHT_EDGE;
    static const int LEFT_EDGE;
    static const int WHITE_BRIGHTNESS;
    static const int BLACK_BRIGHTNESS;
    static const float STEERING_COEF;
    static const int BASE_SPEED;

    LineWalker(ev3api::Motor& leftWheel,
                    ev3api::Motor& rightWheel);

    void init();
    void run(int16_t steeringAmount);
    void setCommand(int brightness);
    int16_t steeringAmountCalculation();

private:
    ev3api::Motor& mLeftWheel;
    ev3api::Motor& mRightWheel;
    int mBrightness;
    int mEdge;
};

#endif  // EV3_UNIT_LINE_WALKER_H_
