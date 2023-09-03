/******************************************************************************
 *  ColorAmplification.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "ColorAmplification.h"

#include <math.h>
#include <string.h>

class ColorAmplification::Impl {
  LineMonitor* color;
  Uptime* uptime;
  Diagnostics* diag;
  double hue;
  double amplification, bottom;
  double saturation[16];
  double timestamp[16];
  int count, index;
  int detected;

public:
  explicit Impl(LineMonitor* _color, Uptime* _uptime,Diagnostics* _diag)
    : color(_color), uptime(_uptime), diag(_diag) {}

  void reset(const ScenarioParams& params) {
    #define GET(a, b, c) params.get(a, &val) ? b(val) : c
    double val;
    hue = GET("hue", double, 204.0);
    count = GET("count", int, 5);
    count = count > 15 ? 15 : count;
    amplification = GET("amplification", double, 4.0);
    memset(saturation, 0, sizeof(saturation));
    memset(timestamp, 0, sizeof(timestamp));
    bottom = DOUBLE64_MAX;
    detected = 0;
    index = 0;
    printf("  hue:           %f\n"
           "  count:         %d\n"
           "  amplification: %f\n",
           hue, count, amplification);
  }

  static double normalize(double angle, double base) {
    double min = base - 180.0;
    angle = fmod(angle - min, 360) + min;
    if (angle < min) {
      angle += 360;
    }
    return angle;
  }

  bool on() {
    hsv_raw_t hsv = color->getHsvColor();
    double h = normalize(hsv.h, hue);
    if (h > hue - 30 && h < hue + 30) {
      ++detected;
    } else {
      detected = 0;
    }
    if (index <= count) {
      saturation[index] = hsv.s;
      timestamp[index] = uptime->getUptime();
    }
    double current = 0.0;
    if (index > 0) {
      for (int i = 1; i <= index; ++i) {
        current += saturation[i] * (timestamp[i] - timestamp[i - 1]);
      }
      bottom = current < bottom ? current : bottom;
    }
    if (index == count) {
      for (int i = 1; i <= index; ++i) {
        saturation[i - 1] = saturation[i];
        timestamp[i - 1] = timestamp[i];
      }
      return bottom && current / bottom > amplification && detected >= count;
    } else {
      ++index;
    }
    return false;
  }
};

ColorAmplification::ColorAmplification(LineMonitor* lineMonitor,
                                       Uptime* uptime,
                                       Diagnostics* diag)
  : mImpl(new Impl(lineMonitor, uptime, diag)) {}

ColorAmplification::~ColorAmplification() { delete mImpl; }

const char* ColorAmplification::getClassName() const {
  return "ColorAmplification";
}

#define GET(a, b, c) params.get(a, &val) ? b(val) : c

void ColorAmplification::reset(const ScenarioParams& params) {
  mImpl->reset(params);
}

bool ColorAmplification::on() { return mImpl->on(); }