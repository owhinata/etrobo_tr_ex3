/******************************************************************************
 *  TreasureWalker.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2023/07/22
 *  Implementation of the Class TreasureWalker
 *  Author: Risei Kodo
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "TreasureWalker.h"

/**
 * コンストラクタ
 * @param armMotor  アームモータ
 */
TreasureWalker::TreasureWalker(ev3api::Motor& armMotor, LineMonitor* lineMonitor)
    : mArmMotor(armMotor),
      mLineMonitor(lineMonitor) {
        TreasureWalker::reset();
}

TreasureWalker::~TreasureWalker() {}

const char* TreasureWalker::getClassName() const { return "TreasureWalker"; }

void TreasureWalker::reset() {
    double angle;
    double prevAngle = 0;
    int i = 0;
    state = 0;
    mArmMotor.setPWM(-30);
    while (i < 10) {
        angle = mArmMotor.getCount();
	// printf("angle=%lf\n", angle);
        if (angle == prevAngle) {
            i++;
        } else {
            i = 0;
        }
        prevAngle = angle;
    }
    mArmMotor.stop();
    mArmMotor.reset();
    // printf("--------------reset over------------");
}

bool TreasureWalker::execute() {
    double angle;
    if (state == 0) {
	// printf("state 0\n");
        angle = (float)mArmMotor.getCount();
        mArmMotor.setPWM(-30);
        // printf("angle=%lf mCount=%d pwm=-30\n", angle, mCount);
        if (angle - 1 < mPrevAngle && mPrevAngle < angle + 1) {
            mCount++;
        } else {
            mCount = 0;
        }
        if (mCount > 20) {
            mArmMotor.stop();
            mCount = 0;
            ++state;
        }
        mPrevAngle = angle;
    } else if (state == 1) {
	// printf("state 1\n");
        mHsv = mLineMonitor->getHsvColor();
	mCount++;
        // printf("h=%lf s=%lf v=%lf\n", mHsv.h, mHsv.s, mHsv.v);
        if (mCount > 10) {
            mCount = 0;
            ++state;
        }
    } else if (state == 2) {
	// printf("state 2\n");
        angle = (float)mArmMotor.getCount();
        mArmMotor.setPWM(30);
        // printf("angle=%lf mCount=%d pwm=30\n", angle, mCount);
        if (angle - 2 < mPrevAngle && mPrevAngle < angle + 2) {
            mCount++;
        } else {
            mCount = 0;
        }
        if (mCount > 20) {
            mArmMotor.stop();
            mCount = 0;
            ++state;
        }
        mPrevAngle = angle;
    }
    return true;
}

Control TreasureWalker::get() { return Control(0.0, 0.0); }
