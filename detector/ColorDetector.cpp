/******************************************************************************
 *  ColorDetector.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "ColorDetector.h"

#include <math.h>

static const double HUE = 204.0;
static const double SATURATION = 0.36;
static const int COUNT = 10;

class ColorDetector::Impl {
  LineMonitor* sensor;
  hsv_raw_t hsv;
  int detected;
  double hue;
  double saturation;
  int count;

public:
  explicit Impl(LineMonitor* _sensor)
    : sensor(_sensor), hsv(), detected(),
      hue(HUE), saturation(SATURATION), count(COUNT) {}

  void reset(const ScenarioParams& params) {
    #define GET(a, b, c) params.get(a, &val) ? b(val) : c
    double val;
    hue = GET("hue", double, HUE);
    saturation = GET("saturation", double, SATURATION);
    count = GET("count", int, COUNT);
    detected = 0;
    printf("  hue:        %f\n"
           "  saturation: %f\n"
           "  count:      %d\n",
           hue, saturation, count);
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
    hsv = sensor->getHsvColor();
    double h = normalize(hsv.h, hue);
    if (h > hue - 30 && h < hue + 30) {
      ++detected;
    } else {
      detected = 0;
    }
    return detected >= count && hsv.s > saturation;
  }
};

ColorDetector::ColorDetector(LineMonitor* lineMonitor)
  : mImpl(new Impl(lineMonitor)) {}

ColorDetector::~ColorDetector() { delete mImpl; }

const char* ColorDetector::getClassName() const {
  return "ColorDetector";
}

#define GET(a, b, c) params.get(a, &val) ? b(val) : c

void ColorDetector::reset(const ScenarioParams& params) {
  mImpl->reset(params);
}

bool ColorDetector::on() { return mImpl->on(); }