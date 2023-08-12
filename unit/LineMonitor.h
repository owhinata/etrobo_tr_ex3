/******************************************************************************
 *  LineMonitor.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineMonitor
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_UNIT_LINE_MONITOR_H_
#define EV3_UNIT_LINE_MONITOR_H_

#include "ColorSensor.h"
#include "Diagnostics.h"

class LineMonitor {
public:
    explicit LineMonitor(const ev3api::ColorSensor& colorSensor,
                         Diagnostics* diag);

    ~LineMonitor();

    void update();

    bool isOnBlueLine() const;

    double getBrightness() const;

private:
    const ev3api::ColorSensor& mColorSensor;
    Diagnostics* mDiag;

    struct Context;
    Context* mContext;
};

#endif  // EV3_UNIT_LINE_MONITOR_H_