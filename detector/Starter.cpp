/******************************************************************************
 *  Starter.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Class Starter
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "Starter.h"

Starter::Starter(const ev3api::TouchSensor& touchSensor)
    : mTouchSensor(touchSensor) {}

Starter::~Starter() {}

const char* Starter::getClassName() const {
    return "Starter";
}

void Starter::reset(const ScenarioParams& params) {}

bool Starter::on() {
    return mTouchSensor.isPressed();
}