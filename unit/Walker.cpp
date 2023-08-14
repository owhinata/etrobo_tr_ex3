/******************************************************************************
 *  Walker.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "Walker.h"

#include "ScenarioParams.h"
#include "Cockpit.h"

struct Context {
  Cockpit* cockpit;
  ScenarioParams params;
  Context(Cockpit* _cockpit) : cockpit(_cockpit) {}
};

Walker::Walker(Cockpit* cockpit) : mContext(new Context(cockpit)) {}

Walker::~Walker() {}

void Walker::init() { return; }

void Walker::reset() { return; }

void Walker::setParams(const WalkerParams& params) {}

void Walker::setDriveParam(int leftPWM, int rightPWM) {
  Context* ctx = (Context*)mContext;
  ctx->cockpit->setDriveParam(leftPWM, rightPWM);
}

double Walker::getBrightness() const {
  Context* ctx = (Context*)mContext;
  return ctx->cockpit->getBrightness();
}

bool Walker::getWalkerParam(const char* key, int keyLength, double* value) {
  Context* ctx = (Context*)mContext;
  char buf[32];
  snprintf(buf, sizeof(buf), "%.*s", keyLength, key);
  return ctx->params.get(buf, value);
}