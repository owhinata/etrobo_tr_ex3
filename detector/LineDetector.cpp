/******************************************************************************
 *  LineDetector.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "LineDetector.h"

#include <math.h>
#include <string.h>

class LineDetector::Impl {
  LineMonitor* sensor;
  Uptime* uptime;
  double attenuation, peak;
  double y[16];
  double timestamp[16];
  int count, index;

public:
  Impl(LineMonitor* _sensor, Uptime* _uptime)
    : sensor(_sensor), uptime(_uptime) {}

  void reset(const ScenarioParams& params) {
    #define GET(a, b, c) params.get(a, &val) ? b(val) : c
    double val;
    attenuation = GET("attenuation", double, 1.0);
    count = GET("count", int, 0);
    count = count > 15 ? 15 : count;
    memset(y, 0, sizeof(y));
    memset(timestamp, 0, sizeof(timestamp));
    peak = 0.0;
    index = 0;
    printf("  attenuation: %f\n"
           "  count:       %d\n",
           attenuation, count);
  }

  bool on() {
    if (index <= count) {
      y[index] = sensor->getBrightness();
      timestamp[index] = uptime->getUptime();
    }
    double current = 0.0;
    if (index > 0) {
      for (int i = 1; i <= index; ++i) {
        current += (y[i] + y[i - 1]) / 2.0 * (timestamp[i] - timestamp[i - 1]);
      }
      peak = current > peak ? current : peak;
    }
    if (index == count) {
      for (int i = 1; i <= index; ++i) {
        y[i - 1] = y[i];
        timestamp[i - 1] = timestamp[i];
      }
      return peak && current / peak < attenuation;
    } else {
      ++index;
    }
    return false;
  }
};

LineDetector::LineDetector(LineMonitor* lineMonitor, Uptime* uptime)
  : mImpl(new Impl(lineMonitor, uptime)) {}

LineDetector::~LineDetector() { delete mImpl; }

const char* LineDetector::getClassName() const {
  return "LineDetector";
}

#define GET(a, b, c) params.get(a, &val) ? b(val) : c

void LineDetector::reset(const ScenarioParams& params) {
  mImpl->reset(params);
}

bool LineDetector::on() { return mImpl->on(); }
