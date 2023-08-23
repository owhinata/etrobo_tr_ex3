/******************************************************************************
 *  Uptime.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "Uptime.h"
#include <stdint.h>

class Uptime::Impl {
  ev3api::Clock& clock;
  Diagnostics* diag;
  uint64_t start, now;

public:
  Impl(ev3api::Clock& _clock, Diagnostics* _diag)
    : clock(_clock), diag(_diag), start(), now() {}

  void init() {
    printf("Clock initialized\n");
    start = now = clock.now();
  }

  void update() {
    now = clock.now();
    diag->update(float(now - start) * 1e-6f);
  }

  double getUptime() const { return float(now - start) * 1e-6f; }
};

Uptime::Uptime(ev3api::Clock& clock, Diagnostics* diag)
  : mImpl(new Impl(clock, diag)) {}

Uptime::~Uptime() { delete mImpl; }

const char* Uptime::getClassName() const { return "Uptime"; }

void Uptime::init(const ScenarioParams& params) { mImpl->init(); }

bool Uptime::update() {
  mImpl->update();
  return true;
}

double Uptime::getUptime() const { return mImpl->getUptime(); }
