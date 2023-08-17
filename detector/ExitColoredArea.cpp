/******************************************************************************
 *  ExitColoredArea.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "ExitColoredArea.h"

#include <string.h>

class ExitColoredArea::Impl {
  LineMonitor* color;
  Uptime* uptime;
  Diagnostics* diag;
  double attenuation, peak;
  double saturation[16];
  double timestamp[16];
  int count, index;

public:
  Impl(LineMonitor* _color, Uptime* _uptime, Diagnostics* _diag)
    : color(_color), uptime(_uptime), diag(_diag) {}

  void reset(const ScenarioParams& params) {
    #define GET(a, b, c) params.get(a, &val) ? b(val) : c
    double val;
    attenuation = GET("attenuation", double, 1.0);
    memset(saturation, 0, sizeof(saturation));
    memset(timestamp, 0, sizeof(timestamp));
    peak = 0.0;
    count = GET("count", int, 0);
    count = count > 15 ? 15 : count;
    index = 0;
    printf("  attenuation: %f\n"
           "  count:       %d\n",
           attenuation, count);
  }

  bool on() {
    if (index <= count) {
      saturation[index] = color->getHsvColor().s;
      timestamp[index] = uptime->getUptime();
    }
    double current = 0.0;
    if (index > 0) {
      for (int i = 1; i <= index; ++i) {
        current += saturation[i] * (timestamp[i] - timestamp[i - 1]);
      }
      peak = current > peak ? current : peak;
    }
    if (index == count) {
      for (int i = 1; i <= index; ++i) {
        saturation[i - 1] = saturation[i];
        timestamp[i - 1] = timestamp[i];
      }
      return peak && current / peak < attenuation;
    } else {
      ++index;
    }
    return false;
  }
};

ExitColoredArea::ExitColoredArea(LineMonitor* lineMonitor,
                                 Uptime* uptime,
                                 Diagnostics* diag)
  : mImpl(new Impl(lineMonitor, uptime, diag)) {}

ExitColoredArea::~ExitColoredArea() { delete mImpl; }

const char* ExitColoredArea::getClassName() const { return "ExitColoredArea"; }

void ExitColoredArea::reset(const ScenarioParams& params) {
  mImpl->reset(params);
}

bool ExitColoredArea::on() { return mImpl->on(); }