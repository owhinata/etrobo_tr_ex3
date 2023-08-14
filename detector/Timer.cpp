/******************************************************************************
 *  Timer.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "TImer.h"

#include <stdio.h>

class Timer::Impl {
  Uptime* time;
  uint32_t start;
  float timeout;

public:
  explicit Impl(Uptime* _time) : time(_time) {}

  void reset(const ScenarioParams& params) {
    #define GET(a, b, c) params.get(a, &val) ? b(val) : c
    double val;
    timeout = GET("timeout", float, 0.0f);
    start = time->getUptime();
    printf("  timeout: %f\n", timeout);
  }

  bool on() {
    uint32_t us = time->getUptime() - start;
    return float(us) * 1e-6 >= timeout;
  }
};

Timer::Timer(Uptime* time) : mImpl(new Impl(time)) {}

Timer::~Timer() { delete mImpl; }

const char* Timer::getClassName() const { return "Timer"; }

void Timer::reset(const ScenarioParams& params) { mImpl->reset(params); }

bool Timer::on() { return mImpl->on(); }