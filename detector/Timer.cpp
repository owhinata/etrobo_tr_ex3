/******************************************************************************
 *  Timer.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "Timer.h"

#include <stdio.h>

class Timer::Impl {
  Uptime* time;
  double start;
  double timeout;

public:
  explicit Impl(Uptime* _time) : time(_time) {}

  void reset(const ScenarioParams& params) {
    #define GET(a, b, c) params.get(a, &val) ? b(val) : c
    double val;
    timeout = GET("timeout", double, 0.0);
    start = time->getUptime();
    printf("  start:   %f\n", start);
    printf("  timeout: %f\n", timeout);
  }

  bool on() {
    return time->getUptime() - start >= timeout;
  }
};

Timer::Timer(Uptime* time) : mImpl(new Impl(time)) {}

Timer::~Timer() { delete mImpl; }

const char* Timer::getClassName() const { return "Timer"; }

void Timer::reset(const ScenarioParams& params) { mImpl->reset(params); }

bool Timer::on() { return mImpl->on(); }
