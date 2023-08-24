/******************************************************************************
 *  SampleWalker.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "SampleWalker.h"

SampleWalker::SampleWalker() {}

SampleWalker::~SampleWalker() {}

const char* SampleWalker::getClassName() const {
  return "SampleWalker";
}

bool SampleWalker::execute() {
  return true;
}

Control SampleWalker::get() { return Control(40, 40); }