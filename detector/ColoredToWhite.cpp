/******************************************************************************
 *  ColoredToWhite.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "ColoredToWhite.h"

#include <string.h>

class ColoredToWhite::Impl {
  LineMonitor* color;
  Uptime* uptime;
  Diagnostics* diag;
  double amplification, bottom;
  double luminance[16];
  double timestamp[16];
  int count, index;

public:
  Impl(LineMonitor* _color, Uptime* _uptime, Diagnostics* _diag)
    : color(_color), uptime(_uptime), diag(_diag) {}

  void reset(const ScenarioParams& params) {
    #define GET(a, b, c) params.get(a, &val) ? b(val) : c
    double val;
    amplification = GET("amplification", double, 1.0);
    memset(luminance, 0, sizeof(luminance));
    memset(timestamp, 0, sizeof(timestamp));
    bottom = INT_MAX;
    count = GET("count", int, 0);
    count = count > 15 ? 15 : count;
    index = 0;
    printf("  amplification: %f\n"
           "  count:         %d\n",
           amplification, count);
  }

  bool on() {
    if (index <= count) {
      luminance[index] = color->getBrightness();
      timestamp[index] = uptime->getUptime();
    }
    double current = 0.0;
    if (index > 0) {
      for (int i = 1; i <= index; ++i) {
        current += luminance[i] * (timestamp[i] - timestamp[i - 1]);
      }
      bottom = current < bottom ? current : bottom;
    }
    if (index == count) {
      for (int i = 1; i <= index; ++i) {
        luminance[i - 1] = luminance[i];
        timestamp[i - 1] = timestamp[i];
      }
      return bottom && current / bottom > amplification;
    } else {
      ++index;
    }
    return false;
  }
};

ColoredToWhite::ColoredToWhite(LineMonitor* lineMonitor,
                                 Uptime* uptime,
                                 Diagnostics* diag)
  : mImpl(new Impl(lineMonitor, uptime, diag)) {}

ColoredToWhite::~ColoredToWhite() { delete mImpl; }

const char* ColoredToWhite::getClassName() const { return "ColoredToWhite"; }

void ColoredToWhite::reset(const ScenarioParams& params) {
  mImpl->reset(params);
}

bool ColoredToWhite::on() { return mImpl->on(); }