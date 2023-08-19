/******************************************************************************
 *  ColorDetector.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "ColorDetector.h"

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

  bool on() {
    hsv = sensor->getHsvColor();
    if (hsv.h > hue - 30 && hsv.h < hue + 30) {
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