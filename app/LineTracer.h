/******************************************************************************
 *  LineTracer.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineTracer
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_APP_LINETRACER_H_
#define EV3_APP_LINETRACER_H_

#include "LineMonitor.h"
#include "LineWalker.h"
#include "Diagnostics.h"

class Diagnostics;

class LineTracer {
public:
    LineTracer(LineMonitor* lineMonitor,
               LineWalker* lineWalker);

    LineTracer(LineMonitor* lineMonitor,
               LineWalker* walker,
               Diagnostics* diag);

    void run();

private:
    LineMonitor* mLineMonitor;
    LineWalker* mLineWalker;
    bool mIsInitialized;

    Diagnostics* diag_;

    int calcDirection(bool isOnLine);
};

#endif  // EV3_APP_LINETRACER_H_
