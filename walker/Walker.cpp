/******************************************************************************
 *  Walker.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "Walker.h"

Control::Control() : speed(), steering() {}

Control::Control(double _speed, double _steering)
  : speed(_speed), steering(_steering) {}

Walker::~Walker() {}

void Walker::init() { return; }

void Walker::reset(const ScenarioParams& params) { return; }

bool Walker::execute() { return false; }

Control Walker::get() { return Control(); }