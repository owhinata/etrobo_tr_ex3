/******************************************************************************
 *  LineWalker.h (for LEGO Mindstorms EV3)
 *  Created on: 2023/07/22
 *  Definition of the Class LineWalker
 *  Author: Risei Kodo
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_WALKER_LINE_WALKER_H_
#define EV3_WALKER_LINE_WALKER_H_

#include <stdint.h>

#include "Walker.h"

class LineWalker : public Walker {
public:
    LineWalker(Driver* driver);

    virtual ~LineWalker();

    virtual void init();

    virtual void run();

    virtual const char* getClassName() const;

private:
    void setCommand();
    int16_t steeringAmountCalculation();

    int mBrightness;
    int mEdge;
    bool mIsInitialized;

    static const int RIGHT_EDGE;
    static const int LEFT_EDGE;
    static const int WHITE_BRIGHTNESS;
    static const int BLACK_BRIGHTNESS;
    static const float STEERING_COEF;
    static const int BASE_SPEED;
};

#endif  // EV3_WALKER_LINE_WALKER_H_
