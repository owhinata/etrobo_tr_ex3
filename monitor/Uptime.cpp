/******************************************************************************
 *  Uptime.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "Uptime.h"
#include <inttypes.h>

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
    diag->update(uint32_t(now - start));
  }

  uint32_t getUptime() const { return uint32_t(now - start); }
};

Uptime::Uptime(ev3api::Clock& clock, Diagnostics* diag)
  : mImpl(new Impl(clock, diag)) {}

Uptime::~Uptime() { delete mImpl; }

const char* Uptime::getClassName() const { return "Uptime"; }

void Uptime::init(const ScenarioParams& params) { mImpl->init(); }

void Uptime::update() { mImpl->update(); }

uint32_t Uptime::getUptime() const { return mImpl->getUptime(); }