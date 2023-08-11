/******************************************************************************
 *  LineMonitor.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineMonitor
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "LineMonitor.h"

static const double SATURATED = 0.36;
static const int COLORED_COUNT = 5;

typedef struct {
    double h, s, v;
} hsv_raw_t;

struct LineMonitor::Context {
    rgb_raw_t rgb;
    hsv_raw_t hsv;
    int blueDetected;

    Context() : rgb(), hsv(), blueDetected() {}
};

LineMonitor::LineMonitor(const ev3api::ColorSensor& colorSensor,
                         Diagnostics* diag)
    : mColorSensor(colorSensor), mDiag(diag),
      mContext(new Context) {}

LineMonitor::~LineMonitor() { delete mContext; }

static uint16_t max(const rgb_raw_t& rgb) {
    if (rgb.r >= rgb.g && rgb.r >= rgb.b) {
        return rgb.r;
    } else if (rgb.g >= rgb.b && rgb.g >= rgb.r) {
        return rgb.g;
    } else if (rgb.b >= rgb.r && rgb.b >= rgb.g) {
        return rgb.b;
    } else {
        return 0;
    }
}

static uint16_t min(const rgb_raw_t& rgb) {
    if (rgb.r <= rgb.g && rgb.r <= rgb.b) {
        return rgb.r;
    } else if (rgb.g <= rgb.b && rgb.g <= rgb.r) {
        return rgb.g;
    } else if (rgb.b <= rgb.r && rgb.b <= rgb.g) {
        return rgb.b;
    } else {
        return 0.0;
    }
}

void LineMonitor::update() {
    rgb_raw_t& rgb = mContext->rgb;
    hsv_raw_t& hsv = mContext->hsv;

    if (mDiag) {
        mDiag->MonitorColorSensor(kColorSensorModeRgbRaw);
    }
    mColorSensor.getRawColor(rgb);

    const uint16_t a = max(rgb), b = min(rgb);

    if (a == b) {
        hsv.h = 0.0;
    } else if (rgb.r == a) {
        hsv.h = 60.0 * double(rgb.g - rgb.b) / double(a - b);
    } else if (rgb.g == a) {
        hsv.h = 60.0 * double(rgb.b - rgb.r) / double(a - b) + 120.0;
    } else if (rgb.b == a) {
        hsv.h = 240.0 * double(rgb.r - rgb.g) / double(a - b) + 240.0;
    } else {
        hsv.h = 0.0;
    }

    hsv.s = double(a - b) / double(a);
    hsv.v = double(a);

    if (hsv.s > SATURATED && hsv.h > 180 && hsv.h < 300) {
        ++mContext->blueDetected;
    } else {
        mContext->blueDetected = 0;
    }
}

bool LineMonitor::isOnBlueLine() const {
    return mContext->blueDetected >= COLORED_COUNT;
}

double LineMonitor::getBrightness() const {
    const rgb_raw_t& rgb = mContext->rgb;
    return 0.299 * rgb.r + 0.587 * rgb.g + 0.114 * rgb.b;
}