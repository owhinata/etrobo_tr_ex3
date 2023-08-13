/******************************************************************************
 *  Starter.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Class Starter
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_DETECTOR_STARTER_H_
#define EV3_DETECTOR_STARTER_H_

#include "Detector.h"
#include "TouchSensor.h"

class Starter : public Detector {
public:
    explicit Starter(const ev3api::TouchSensor& touchSensor);

    virtual ~Starter();

    virtual void reset(const ScenarioParams& params);

    virtual bool on();

    virtual const char* getClassName() const;

private:
    const ev3api::TouchSensor& mTouchSensor;
};

#endif  // EV3_DETECTOR_STARTER_H_