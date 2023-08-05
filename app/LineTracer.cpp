/******************************************************************************
 *  LineTracer.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/26
 *  Implementation of the Class LineTracer
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
<<<<<<< HEAD
 *  Copyright (c) 2023 Emtech Inc.
=======
 *  Copyright (c) 2023 Emtechs Inc.
>>>>>>> feature/pid/20230722
 *****************************************************************************/

#include "LineTracer.h"

#include "Diagnostics.h"

/**
 * コンストラクタ
 * @param lineMonitor     ライン判定
 * @param LineWalker 走行
 */
LineTracer::LineTracer(const LineMonitor* lineMonitor,
                       LineWalker* lineWalker)
    : mLineMonitor(lineMonitor),
      mLineWalker(lineWalker),
      mIsInitialized(false),
      diag_() {
}

LineTracer::LineTracer(const LineMonitor* lineMonitor,
                       LineWalker* walker,
                       Diagnostics* diag)
    : LineTracer(lineMonitor, walker) {
    diag_ = diag;
}

/**
 * ライントレースする
 */
void LineTracer::run() {
    if (mIsInitialized == false) {
        mLineWalker->init();
        mIsInitialized = true;
    }
    if (diag_) {
      diag_->MonitorColorSensor(ColorSensorMode::kRgbRaw);
      diag_->MonitorGyroSensor();
    }

    // 反射光の強さを取得する
    int brightness = (int)mLineMonitor->getBrightness();
    mLineWalker->setCommand(brightness);

    // 走行を行う
    int16_t steeringAmount = mLineWalker->steeringAmountCalculation();
    mLineWalker->run(steeringAmount);
}
