/******************************************************************************
 *  LineMonitor.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineMonitor
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "LineMonitor.h"

struct LineMonitor::Context {
    double rgb[3];
    double hsv[3];
    double y;
    double gain[3];
    Context() : rgb(), hsv(), y(), gain() {}
};

LineMonitor::LineMonitor(const ev3api::ColorSensor& colorSensor,
                         Diagnostics* diag)
    : mColorSensor(colorSensor), mDiag(diag),
      mContext(new Context) {}

LineMonitor::~LineMonitor() { delete mContext; }

const char* LineMonitor::getClassName() const { return "LineMonitor"; }

void LineMonitor::init(const ScenarioParams& params) {
    #define GET(a, b, c) params.get(a, &val) ? b(val) : c
    double val;
    double* gain = mContext->gain;
    gain[0] = GET("rgain", double, 1.0);
    gain[1] = GET("ggain", double, 1.0);
    gain[2] = GET("bgain", double, 1.0);
    printf("LineMonitor\n"
           "  rgain: %f\n"
           "  ggain: %f\n"
           "  bgain: %f\n",
           gain[0], gain[1], gain[2]);
}

static double max(const double rgb[3]) {
    if (rgb[0] >= rgb[1] && rgb[0] >= rgb[2]) {
        return rgb[0];
    } else if (rgb[1] >= rgb[2] && rgb[1] >= rgb[0]) {
        return rgb[1];
    } else if (rgb[2] >= rgb[0] && rgb[2] >= rgb[1]) {
        return rgb[2];
    } else {
        return 0;
    }
}

static double min(const double rgb[3]) {
    if (rgb[0] <= rgb[1] && rgb[0] <= rgb[2]) {
        return rgb[0];
    } else if (rgb[1] <= rgb[2] && rgb[1] <= rgb[0]) {
        return rgb[1];
    } else if (rgb[2] <= rgb[0] && rgb[2] <= rgb[1]) {
        return rgb[2];
    } else {
        return 0.0;
    }
}

bool LineMonitor::update() {
    double* rgb = mContext->rgb;
    double* hsv = mContext->hsv;
    double& y = mContext->y;
    const double* gain = mContext->gain;

    rgb_raw_t _rgb = {};
    mColorSensor.getRawColor(_rgb);

    rgb[0] = float(_rgb.r) * gain[0];
    rgb[1] = float(_rgb.g) * gain[1];
    rgb[2] = float(_rgb.b) * gain[2];
    double a = max(rgb), b = min(rgb);

    if (a == b) {
        hsv[0] = 0.0;
    } else if (rgb[0] == a) {
        hsv[0] = 60.0 * (rgb[1] - rgb[2]) / (a - b);
    } else if (rgb[1] == a) {
        hsv[0] = 60.0 * (rgb[2] - rgb[0]) / (a - b) + 120.0;
    } else if (rgb[2] == a) {
        hsv[0] = 60.0 * (rgb[0] - rgb[1]) / (a - b) + 240.0;
    } else {
        hsv[0] = 0.0;
    }
    if (a) {
        hsv[1] = (a - b) / a;
    } else {
        hsv[1] = 0;
    }
    hsv[2] = a;

    y = 0.299 * rgb[0] + 0.587 * rgb[1] + 0.114 * rgb[2];
    // u = -0.169 * rgb[0] - 0.331 * rgb[1] + 0.500 * rgb[2];
    // v = 0.500 * rgb[0] - 0.419 * rgb[1] - 0.081 * rgb[2];

    mDiag->setColor(rgb, hsv, y);

    return true;
}

double LineMonitor::getBrightness() const { return mContext->y; }

hsv_raw_t LineMonitor::getHsvColor() const {
    const hsv_raw_t hsv = {
        .h = mContext->hsv[0],
        .s = mContext->hsv[1],
        .v = mContext->hsv[2],
    };
    return hsv;
}